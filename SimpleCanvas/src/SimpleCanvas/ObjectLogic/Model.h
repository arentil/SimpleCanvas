#pragma once

#include "BaseMesh.h"
#include "Renderer/Shader.h"
#include "Camera/CameraController.h"
#include "ObjectLogic/Lights.h"
#include "ObjectLogic/ObjLoader.h"

#include <SCMath.h>
#include <vector>

namespace sc
{
class Model;
using ModelPtr = std::shared_ptr<Model>;

class Model
{
public:
    Model() = default;
    Model(std::vector<BaseMeshPtr> const& meshes);
    ~Model() = default;

    void draw(ShaderPtr shader, CameraController const& camCtrl, Lights const& lights, scmath::Mat4 const& modelMatrix) const;
    AABB getModelAABB() const;

private:
    std::vector<BaseMeshPtr> const _meshes;
};

class ModelsContainer
{
public:
    ModelsContainer() = default;

    void addModel(std::string const& modelName, ModelPtr const& model);
    void addModelFromFile(std::string const& modelName, std::string const& objFilePath);
    ModelPtr getModel(std::string const& modelName) const;

private:
    std::unordered_map<std::string, ModelPtr> _models;
};
} // namespace sc