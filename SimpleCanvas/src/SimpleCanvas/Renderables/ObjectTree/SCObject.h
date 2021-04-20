#pragma once

#include "Renderables/ObjectTree/SCNode.h"
#include "Renderer/Camera.h"

namespace sc
{
class SCObject : public SCNode
{
public:
    SCObject();
    virtual ~SCObject() = default;

    virtual void load() {}
    virtual void unload() {}

    void draw(Camera const& camera);
    void animate(float deltaTime);
    void processCollisions(SCObject *object);
    void prepare();
    SCObject* findRoot();

    scmath::Vec3 position;
    scmath::Vec3 velocity;
    scmath::Vec3 acceleration;
    bool isDead;

protected:
    virtual void onAnimate(float deltaTime);
    virtual void onDraw(Camera const& camera) {}
    virtual void onCollision(SCObject *collisionObject) {}
    virtual void onPrepare();
};
} // namespace sc