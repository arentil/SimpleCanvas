#include "ObjectLogic/ObjectTree/SCObject.h"

namespace sc
{
SCObject::SCObject(std::string const& name, ShaderPtr shader)
: IsDead(false)
, Name(name)
, _shader(shader)
{}

void SCObject::prepare() 
{
    prepareCollider();
    onPrepare();

    if (hasChild())
        ((SCObject*)childNode)->prepare();

    if (hasParent() && !isLastChild())
        ((SCObject*)nextNode)->prepare();
}

void SCObject::animate(float deltaTime) 
{
    onAnimate(deltaTime);

    if (hasChild())
        ((SCObject*)childNode)->animate(deltaTime);

    if (hasParent() && !isLastChild())
        ((SCObject*)nextNode)->animate(deltaTime);

    if (IsDead)
        delete this;
}

void SCObject::processCollisions(SCObject *object) 
{
    // TODO: IMPLEMENT AABB AND USE HERE
    if (object != (SCObject*)this && Collider.isCollision(object->Collider))
    {
        onCollision(object);

        if (hasChild())
            ((SCObject*)childNode)->processCollisions(object);

        if (hasParent() && !isLastChild())
            ((SCObject*)nextNode)->processCollisions(object);
    }

    if (object->hasChild())
        processCollisions(  (SCObject*)(object->childNode)  );

    if (object->hasParent() && !object->isLastChild())
        processCollisions(  (SCObject*)(object->nextNode)  );
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

void SCObject::prepareCollider() 
{
    //getParent()->Transform
}

void SCObject::onPrepare() 
{
    processCollisions(findRoot());
}

void SCObject::onAnimate(float deltaTime) 
{
    Transform.Translation += Velocity * deltaTime;
    Velocity += Acceleration * deltaTime;
}

void SCObject::onDraw(FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix) 
{
    _model->draw(_shader, camera, lights, modelMatrix);
}
} // namespace sc