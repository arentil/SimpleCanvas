#pragma once

#include "ObjectLogic/ObjectTree/SCNode.h"
#include "Camera/CameraController.h"
#include "ObjectLogic/Model.h"
#include "ObjectLogic/TransformComponent.h"
#include "ObjectLogic/Rigidbody.h"

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
    void checkCollision(SCObject *object);
    void update();
    void draw(CameraController const& camCtrl, Lights const& lights, scmath::Mat4 const& modelMatrix);

    SCObject* findRoot();
    SCObject* findChildByName(std::string const& name);

    float deltaTime = 0.0f;
    std::string Name;
    TransformComponent Transform;
    std::optional<Rigidbody> Rigidbody;

    bool IsDead;

protected:
    virtual void onPrepare() {}
    virtual void onPhysic();
    virtual void updateCollider();
    virtual void onCollision(SCObject *object) {}
    virtual void onUpdate() {}
    virtual void onDraw(CameraController const& camCtrl, Lights const& lights, scmath::Mat4 const& modelMatrix);

    ShaderPtr _shader;
    ModelPtr _model;
};
} // namespace sc