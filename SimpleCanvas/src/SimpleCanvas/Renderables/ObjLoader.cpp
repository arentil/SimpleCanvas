#include "ObjLoader.h"

#include "Tools/tiny_obj_loader.h"
#include "Model.h"
#include "Mesh.h"

#include <vector>

namespace sc
{
namespace
{
// returns file parent folder
std::string getFileParentFolder(std::string const& filePath)
{
    size_t i;
    if (i = filePath.find_last_of('/'); i == std::string::npos)
        return "";
    return filePath.substr(0, i);
}
} // namespace

Model ObjLoader::loadObjFromFile(std::string const& objFilePath)
{
    std::string const parentFolder = getFileParentFolder(objFilePath);

    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = parentFolder; // Path to material files

    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(objFilePath, reader_config))
    {
        if (!reader.Error().empty())
        {
            LOG_ERROR("Failed to open %s! TinyObjReader: %s", objFilePath.c_str(), reader.Error().c_str());
            exit(1);
        }
    }

    if (!reader.Warning().empty())
    {
        LOG_WARNING("Warning tinyObjReader: %s", reader.Warning().c_str());
    }

    const tinyobj::attrib_t &attrib = reader.GetAttrib();
    const std::vector<tinyobj::shape_t> &shapes = reader.GetShapes();
    const std::vector<tinyobj::material_t> &materials = reader.GetMaterials();

    // load diffuse textures
    std::map<std::string, TexturePtr> textures;
    for (tinyobj::material_t const& material: materials)
    {
        if (material.diffuse_texname.empty())
        {
            LOG_WARNING("Material texture name empty! Skipping...");
            continue;
        }

        std::string const textureFilePath = parentFolder + "/" + material.diffuse_texname;
        textures.emplace(textureFilePath, Texture2d::create(textureFilePath));
    }


    std::vector<BaseMeshPtr> meshes;
    meshes.reserve(shapes.size());

    // loop over shapes
    for (tinyobj::shape_t const& shape : shapes)
    {
        std::vector<TextureVertex> vertices;
        vertices.reserve(
            std::accumulate(shape.mesh.num_face_vertices.begin(),
                            shape.mesh.num_face_vertices.end(),
                            0
        ));

        // loop over faces(polygon)
        size_t index_offset = 0;
        for (uint8_t asd : shape.mesh.num_face_vertices)
        {
            // loop over vertices in the face
            size_t fv = size_t(asd);
            for (size_t v = 0; v < fv; v++)
            {
                TextureVertex vertex;

                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                vertex.position.x = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                vertex.position.y = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                vertex.position.z = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                // check if normal_index is zero or positive. negative = no normal data
                if (idx.normal_index >= 0)
                {
                    vertex.normal.x = attrib.normals[3 * size_t(idx.normal_index) + 0];
                    vertex.normal.y = attrib.normals[3 * size_t(idx.normal_index) + 1];
                    vertex.normal.z = attrib.normals[3 * size_t(idx.normal_index) + 2];
                }

                // check if texcoord_index is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0)
                {
                    vertex.texCoord.x = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                    vertex.texCoord.y = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                }
                vertices.push_back(vertex);
            }
            index_offset += fv;
        }

        auto const& faceTexture = materials[shape.mesh.material_ids.front()].diffuse_texname;
        std::string const& textureFilePath = parentFolder + "/" + faceTexture;
        if (textures.find(textureFilePath) == textures.end())
        {
            LOG_ERROR("Could not find texture at path: %s", textureFilePath);
            meshes.push_back(std::make_shared<TextureMesh>(vertices, nullptr));
            continue;
        }

        meshes.push_back(std::make_shared<TextureMesh>(vertices, textures[textureFilePath]));
    }

    Model result(meshes);
    return result;
}
}