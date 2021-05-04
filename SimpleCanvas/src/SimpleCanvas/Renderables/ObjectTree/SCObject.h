#pragma once

#include "Renderables/ObjectTree/SCNode.h"
#include "Camera/FPSCamera.h"
#include "Renderables/Model.h"

namespace sc
{
class SCObject : public SCNode
{
public:
    SCObject(std::string const& name, ShaderPtr shader);
    virtual ~SCObject() = default;

    std::string getName() const;
    void setName(std::string const& name);

    virtual void load() {}
    virtual void unload() {}

    virtual void prepare();
    virtual void animate(float deltaTime);
    virtual void processCollisions(SCObject *object);
    virtual void draw(FPSCamera const& camera, Lights const& lights);
    SCObject* findRoot();
    SCObject* findChildByName(std::string const& name);
    const scmath::Mat4 &getModelMatrix() const;

    scmath::Vec3 position;
    scmath::Vec3 velocity;
    scmath::Vec3 acceleration;
    bool isDead;

protected:
    virtual void onPrepare();
    virtual void onAnimate(float deltaTime);
    virtual void onCollision(SCObject *collisionObject) {}
    virtual void onDraw(FPSCamera const& camera, Lights const& lights);

    std::string _name;
    ShaderPtr _shader;
    ModelPtr _model;
    scmath::Mat4 _modelMatrix;
};
} // namespace sc