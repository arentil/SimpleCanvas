#include "Cubemap.h"

#include <glad/glad.h>
#include "Tools/stb_image.h"

namespace sc
{
Cubemap::Cubemap(std::vector<std::string> const& facesFilePaths)
{
    glGenTextures(1, &_rendererId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _rendererId);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < facesFilePaths.size(); i++)
    {
        unsigned char *data = stbi_load(facesFilePaths[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << facesFilePaths[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}


Cubemap::~Cubemap()
{
    glDeleteTextures(1, &_rendererId);
}

void Cubemap::bind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, _rendererId);
}
} // namespace sc