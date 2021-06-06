#pragma once

#include "ObjectLogic/ObjectTree/SCNode.h"
#include "Camera/FPSCamera.h"
#include "ObjectLogic/Model.h"
#include "ObjectLogic/TransformComponent.h"

namespace sc
{
class SCObject : public SCNode
{
public:
    SCObject(std::string const& name, ShaderPtr shader);
    virtual ~SCObject() = default;

    virtual void load() {}
    virtual void unload() {}

    // these methods are called while traverse through tree
    // can not be overriden
    void prepare();
    void animate(float deltaTime);
    void processCollisions(SCObject *object);
    void draw(FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix);

    SCObject* findRoot();
    SCObject* findChildByName(std::string const& name);

    // unsafe! make sure that object has a parent!
    SCObject* getParent();
    // unsafe! make sure that object has a child!
    SCObject* getChild();

    TransformComponent Transform;
    std::string Name;

    // rigidbody?
    scmath::Vec3 Velocity;
    scmath::Vec3 Acceleration;
    bool IsDead;

    std::optional<AABB> Collider;
    void updateCollider();

protected:
    virtual void onPrepare();
    virtual void onAnimate(float deltaTime);
    virtual void onCollision(SCObject *collisionObject) {}
    virtual void onDraw(FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix);

    ShaderPtr _shader;
    ModelPtr _model;
};
} // namespace sc