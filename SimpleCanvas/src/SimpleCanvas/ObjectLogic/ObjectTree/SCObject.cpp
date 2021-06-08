#include "ObjectLogic/ObjectTree/SCObject.h"

namespace sc
{
SCObject::SCObject(std::string const& name, ShaderPtr shader)
: IsDead(false)
, Name(name)
, _shader(shader)
{}

void SCObject::prepare(float deltaT) 
{
    deltaTime = deltaT;
    onPrepare();

    if (hasChild())
        ((SCObject*)childNode)->prepare(deltaTime);

    if (hasParent() && !isLastChild())
        ((SCObject*)nextNode)->prepare(deltaTime);
}

void SCObject::physic() 
{
    onPhysic();
    updateCollider();
    checkCollision(findRoot());

    if (hasChild())
        ((SCObject*)childNode)->physic();

    if (hasParent() && !isLastChild())
        ((SCObject*)nextNode)->physic();

    if (IsDead)
        delete this;
}

void SCObject::checkCollision(SCObject *object) 
{
    if (object != (SCObject*)this &&
        Collider.has_value() &&
        object->Collider.has_value() &&
        Collider->isCollision(object->Collider.value()))
    {
        onCollision(object);
        

        if (hasChild())
            ((SCObject*)childNode)->checkCollision(object);

        if (hasParent() && !isLastChild())
            ((SCObject*)nextNode)->checkCollision(object);
    }

    if (object->hasChild())
        checkCollision((SCObject*)(object->childNode));

    if (object->hasParent() && !object->isLastChild())
        checkCollision((SCObject*)(object->nextNode));
}

void SCObject::update() 
{
    onUpdate();

    if (hasChild())
        ((SCObject*)childNode)->update();

    if (hasParent() && !isLastChild())
        ((SCObject*)nextNode)->update();
}

void SCObject::draw(FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix) 
{
    // apply all parents model transforms, add it another this transform and position
    scmath::Mat4 const allTransforms = modelMatrix * Transform.GetTransform();
    onDraw(camera, lights, allTransforms);

    if (hasChild())
        ((SCObject*)childNode)->draw(camera, lights, allTransforms);
    
    if (hasParent() && !isLastChild())
        ((SCObject*)nextNode)->draw(camera, lights, modelMatrix);
}

SCObject* SCObject::findRoot() 
{
    if (parentNode != nullptr)
        return ((SCObject*)parentNode)->findRoot();

    return this;
}

SCObject* SCObject::findChildByName(std::string const& name) 
{
    if (Name == name)
        return this;

    SCObject *result = nullptr;
    
    if (hasChild())
    {
        if (SCObject* node = ((SCObject*)childNode)->findChildByName(name); node != nullptr)
            return node;
    }

    if (hasParent() && !isLastChild())
    {
        if (SCObject* node = ((SCObject*)nextNode)->findChildByName(name); node != nullptr)
            return node;
    }

    return nullptr;
}

SCObject* SCObject::getParent() 
{
    return ((SCObject*)parentNode);
}

SCObject* SCObject::getChild() 
{
    return ((SCObject*)childNode);
}

void SCObject::updateCollider() 
{
    Collider = _model->getModelAABB();
}

void SCObject::onPhysic() 
{
    Transform.Translation += Velocity * deltaTime;
    Velocity += Acceleration * deltaTime;
}

void SCObject::onDraw(FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix) 
{
    if (Collider.has_value())
    {
        auto &aabb = Collider.value();
        aabb.initDebugShader();
        aabb.draw(camera, scmath::Mat4::identity());
    }
    _model->draw(_shader, camera, lights, modelMatrix);
}
} // namespace sc