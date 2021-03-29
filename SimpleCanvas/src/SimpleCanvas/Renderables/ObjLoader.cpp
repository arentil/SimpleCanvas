#include "ObjLoader.h"

#include "Tools/tiny_obj_loader.h"

#include <vector>

namespace sc
{
Model ObjLoader::loadObjFromFile(std::string const& objFilePath) const
{
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./"; // Path to material files

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

    std::vector<Mesh> meshes;
    meshes.reserve(shapes.size());

    // loop over shapes
    for (tinyobj::shape_t const& shape : shapes)
    {
        size_t index_offset = 0;

        // loop over faces(polygon)
        for (uint8_t asd : shape.mesh.num_face_vertices)
        {
            size_t fv = size_t(asd);

            // loop over vertices in the face
            for (size_t v = 0; v < fv; v++)
            {
                Vertex vertex;

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

            }
            index_offset += fv;
        }
    }


    Model result({});
    return result;
}
}