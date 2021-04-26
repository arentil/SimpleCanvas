#include "Renderables/ObjectTree/SCObject.h"

namespace sc
{
SCObject::SCObject(std::string const& name, sc::Shader const& shader)
: isDead(false)
, _name(name)
, _shader(shader)
{}

std::string SCObject::getName() const
{
    return _name;
}

void SCObject::setName(std::string const& name) 
{
    _name = name;
}

void SCObject::prepare() 
{
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

    if (isDead)
        delete this;
}

void SCObject::processCollisions(SCObject *object) 
{
    // TODO: IMPLEMENT AABB AND USE HERE
    if (object != (SCObject*)this /* && collidersOverlapp(object, this)*/)
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

void SCObject::draw(Camera const& camera, Lights const& lights) 
{
    onDraw(camera, lights);

    // draw child send somehow translation matrix or sth
    if (hasChild())
        ((SCObject*)childNode)->draw(camera, lights);
    
    // draw sister nodes
    if (hasParent() && !isLastChild())
        ((SCObject*)nextNode)->draw(camera, lights);
}

SCObject* SCObject::findRoot() 
{
    if (parentNode != nullptr)
        return ((SCObject*)parentNode)->findRoot();

    return this;
}

SCObject* SCObject::findChildByName(std::string const& name) 
{
    if (_name == name)
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

const scmath::Mat4& SCObject::getModelMatrix() const
{
    return _modelMatrix;
}

void SCObject::onPrepare() 
{
    processCollisions(findRoot());
}

void SCObject::onAnimate(float deltaTime) 
{
    position += velocity * deltaTime;
    velocity += acceleration * deltaTime;
}

void SCObject::onDraw(Camera const& camera, Lights const& lights) 
{
    if (_model)
    {
        if (parentNode != nullptr)
            _model->draw(_shader, camera, lights, _modelMatrix * ((SCObject*)parentNode)->getModelMatrix());
        else
            _model->draw(_shader, camera, lights, _modelMatrix);            
    }        
}
} // namespace sc