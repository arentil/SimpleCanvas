#include "Renderables/ObjectTree/SCObject.h"

namespace sc
{
SCObject::SCObject()
: isDead(false)
{
    
}

void SCObject::draw(Camera const& camera) 
{
    onDraw(camera);
    


    // draw child send somehow translation matrix or sth
    if (hasChild())
        ((SCObject*)childNode)->draw(camera);
    
    // draw sister nodes
    if (hasParent() && !isLastChild())
        ((SCObject*)nextNode)->draw(camera);
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

    if (hasChild())
        processCollisions(  (SCObject*)(object->childNode)  );

    if (object->hasParent() && !object->isLastChild())
        processCollisions(  (SCObject*)(object->nextNode)  );
}

void SCObject::prepare() 
{
    onPrepare();

    if (hasChild())
        ((SCObject*)childNode)->prepare();

    if (hasParent() && !isLastChild())
        ((SCObject*)nextNode)->prepare();
}

SCObject* SCObject::findRoot() 
{
    if (parentNode != nullptr)
        return ((SCObject*)parentNode)->findRoot();

    return this;
}

void SCObject::onAnimate(float deltaTime) 
{
    position += velocity * deltaTime;
    velocity += acceleration * deltaTime;
}

void SCObject::onPrepare() 
{
    processCollisions(findRoot());
}
} // namespace sc