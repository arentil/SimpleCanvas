#include "Model.h"

namespace sc
{
Model::Model(std::vector<BaseMeshPtr> const& meshes)
: _meshes(meshes)
{}

void Model::draw(ShaderPtr shader, FPSCamera const& camera, Lights const& lights, scmath::Mat4 const& modelMatrix) const
{
    for (BaseMeshPtr const& mesh : _meshes)
    {
        mesh->draw(shader, camera, lights, modelMatrix);
    }
}

void ModelsContainer::addModel(std::string const& modelName, ModelPtr const& model) 
{
    if (_models.find(modelName) != _models.end())
    {
        LOG_WARNING("%s() %s model already exist! Skipping...", __FUNCTION__, modelName.c_str());
        return;
    }
    _models.emplace(modelName, model);
}

void ModelsContainer::addModelFromFile(std::string const& modelName, std::string const& objFilePath) 
{
    if (_models.find(modelName) != _models.end())
    {
        LOG_WARNING("%s() %s model already exist! Skipping...", __FUNCTION__, modelName.c_str());
        return;
    }
    _models.emplace(modelName, sc::ObjLoader::loadObjFromFile(objFilePath));
}

ModelPtr ModelsContainer::getModel(std::string const& modelName) const
{
    if (_models.find(modelName) == _models.end())
    {
        LOG_ERROR("%s() %s model does not exist! Skipping...", __FUNCTION__, modelName.c_str());
        return nullptr;
    }

    return _models.at(modelName);
}
} // namespace sc