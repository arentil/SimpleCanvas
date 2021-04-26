#pragma once

#include "Renderables/ObjectTree/SCNode.h"
#include "Renderer/Camera.h"
#include "Renderables/Model.h"

namespace sc
{
class SCObject : public SCNode
{
public:
    SCObject(std::string const& name, sc::Shader const& shader);
    virtual ~SCObject() = default;

    std::string getName() const;
    void setName(std::string const& name);

    virtual void load() {}
    virtual void unload() {}

    virtual void prepare();
    virtual void animate(float deltaTime);
    virtual void processCollisions(SCObject *object);
    virtual void draw(Camera const& camera, Lights const& lights);
    SCObject* findRoot();
    SCObject* findChildByName(std::string const& name);

    scmath::Vec3 position;
    scmath::Vec3 velocity;
    scmath::Vec3 acceleration;
    bool isDead;

protected:
    virtual void onPrepare();
    virtual void onAnimate(float deltaTime);
    virtual void onCollision(SCObject *collisionObject) {}
    virtual void onDraw(Camera const& camera, Lights const& lights);

    std::string _name;
    Shader const& _shader;
    ModelPtr _model;
    scmath::Mat4 _modelMatrix;
};
} // namespace sc