#include "Model.h"

namespace sc
{
Model::Model(std::vector<BaseMeshPtr> const& meshes)
: meshes(meshes)
{}

Model::Model(Model const& other)
: meshes(getCopiedMeshes(other.getMeshes()))
{}

void Model::draw(ShaderPtr shader, CameraController const& camCtrl, Lights const& lights, scmath::Mat4 const& modelMatrix) const
{
    for (BaseMeshPtr const& mesh : meshes)
    {
        mesh->draw(shader, camCtrl, lights, modelMatrix);
    }
}

AABB Model::getModelAABB() const
{
    scmath::Vec3 min = scmath::Vec3::Max();
    scmath::Vec3 max = scmath::Vec3::Min();
    for (auto const& mesh : meshes)
    {
        for (auto const& corner : mesh->getAABB().bb.get8Corners())
        {
            min.x = std::min(min.x, corner.x);
            min.y = std::min(min.y, corner.y);
            min.z = std::min(min.z, corner.z);

            max.x = std::max(max.x, corner.x);
            max.y = std::max(max.y, corner.y);
            max.z = std::max(max.z, corner.z);
        }
    }
    AABB result(min, max);
    return result;
}

std::vector<BaseMeshPtr> Model::getMeshes() const
{
    return meshes;
}

std::vector<BaseMeshPtr> Model::getCopiedMeshes(std::vector<BaseMeshPtr> const& meshes) const
{
    std::vector<BaseMeshPtr> result;
    result.reserve(meshes.size());

    for (auto const& meshToCopy : meshes)
    {
        result.push_back(meshToCopy->clone());
    }

    return result;
}

void ModelsContainer::addModel(std::string const& modelName, ModelPtr const& model) 
{
    if (models.find(modelName) != models.end())
    {
        LOG_WARNING("%s() %s model already exist! Skipping...", __FUNCTION__, modelName.c_str());
        return;
    }
    models.emplace(modelName, model);
}

void ModelsContainer::addModelFromFile(std::string const& modelName, std::string const& objFilePath) 
{
    if (models.find(modelName) != models.end())
    {
        LOG_WARNING("%s() %s model already exist! Skipping...", __FUNCTION__, modelName.c_str());
        return;
    }
    models.emplace(modelName, sc::ObjLoader::loadObjFromFile(objFilePath));
}

ModelPtr ModelsContainer::getModel(std::string const& modelName) const
{
    if (models.find(modelName) == models.end())
    {
        LOG_ERROR("%s() %s model does not exist! Skipping...", __FUNCTION__, modelName.c_str());
        return nullptr;
    }

    // the NEW instance(deep copy) of Model will be created from the existing one
    return std::make_shared<Model>(*(models.at(modelName)));
}
} // namespace sc