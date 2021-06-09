#include "ObjectLogic/ObjectTree/SCObject.h"

namespace sc
{
SCObject::SCObject(std::string const& name, ShaderPtr shader)
: IsDead(false)
, Name(name)
, _shader(shader)
{
    Rigidbody.emplace();
}

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
        Rigidbody.has_value() &&
        object->Rigidbody.has_value() &&
        Rigidbody->isCollision(object->Rigidbody.value()))
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

void SCObject::onPhysic()
{
    if (!Rigidbody.has_value())
        return;

    Rigidbody->physic(Transform.Translation, deltaTime);
    updateCollider();
    checkCollision(findRoot());
}

void SCObject::updateCollider() 
{
    AABB const& modelAABB = _model->getModelAABB();
    Rigidbody->setColliderMinMax(modelAABB.bb.min, modelAABB.bb.max);
}

void SCObject::onDraw(FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix) 
{
    if (Rigidbody.has_value())
    {
        auto &aabb = Rigidbody->Collider;
        aabb.initDebugShader();
        aabb.draw(camera, scmath::Mat4::identity());
    }

    _model->draw(_shader, camera, lights, modelMatrix);
}
} // namespace sc