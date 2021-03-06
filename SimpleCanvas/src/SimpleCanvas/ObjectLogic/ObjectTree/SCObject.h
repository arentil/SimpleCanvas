#pragma once

#include "ObjectLogic/ObjectTree/SCNode.h"
#include "Camera/CameraController.h"
#include "ObjectLogic/Model.h"
#include "ObjectLogic/TransformComponent.h"
#include "ObjectLogic/RigidbodyComponent.h"

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
    void prepare(float deltaT);
    void physic();
    void collisionsCheck();
    void update();
    void lateUpdate();
    void draw(CameraController const& camCtrl, Lights const& lights, scmath::Mat4 const& modelMatrix);
    void destroyCheck();

    void checkCollision(SCObject *object);
    void destroy();

    SCObject* getParent();
    SCObject* findRoot();
    SCObject* findChildByName(std::string const& name);
    SCObject* findByName(std::string const& name);

    scmath::Vec3 getGlobalPos();
    scmath::Mat4 getGlobalTransform();

    float deltaTime = 0.0f;
    std::string Name = "Default";
    TransformComponent Transform;
    std::optional<RigidbodyComponent> Rigidbody;
    bool hasItCheckedChildren = false;

protected:
    virtual void onPrepare() {} //----------------------------------------------------------------------------------// define object preparation
    virtual void onPhysic(); //-------------------------------------------------------------------------------------// define your own physics
    virtual void updateCollider(); //-------------------------------------------------------------------------------// define your own collider
    virtual void onCollision(SCObject *object, CollisionSide side) {} //----------------------------------------------------------------// check if collision occured
    virtual void onUpdate() {} //-----------------------------------------------------------------------------------// script everything you want
    virtual void onLateUpdate() {} //-------------------------------------------------------------------------------// update camera position
    virtual void onDraw(CameraController const& camCtrl, Lights const& lights, scmath::Mat4 const& modelMatrix); //-// define own draw function
    virtual void onDestroyCheck(); //----------------------------------------------------------------------------------// define behaviour on destroy

    ShaderPtr _shader;
    ModelPtr _model;

private:
    bool isDestroyed = false;
};
} // namespace sc