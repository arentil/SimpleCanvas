#include "Crosshair.h"


Crosshair::Crosshair(sc::AssetsContainer const& assets) 
: sc::SCObject("Crosshair", assets.Shaders.getShader("Debug"))
{
    Transform.Scale = scmath::Vec3(0.03f, 0.03f, 1.0f);

    std::vector<scmath::Vec3> vertices{
        {-0.1f, -0.5f, -1.0f},
        {0.1f, -0.5f, -1.0f},
        {0.0f, -0.1f, -1.0f},
    };

    vertices.push_back(scmath::Mat4::rotateZ(scmath::degToRad(90)) * vertices[0]);
    vertices.push_back(scmath::Mat4::rotateZ(scmath::degToRad(90)) * vertices[1]);
    vertices.push_back(scmath::Mat4::rotateZ(scmath::degToRad(90)) * vertices[2]);

    vertices.push_back(scmath::Mat4::rotateZ(scmath::degToRad(-90)) * vertices[0]);
    vertices.push_back(scmath::Mat4::rotateZ(scmath::degToRad(-90)) * vertices[1]);
    vertices.push_back(scmath::Mat4::rotateZ(scmath::degToRad(-90)) * vertices[2]);

    vertices.push_back(scmath::Mat4::rotateZ(scmath::degToRad(180)) * vertices[0]);
    vertices.push_back(scmath::Mat4::rotateZ(scmath::degToRad(180)) * vertices[1]);
    vertices.push_back(scmath::Mat4::rotateZ(scmath::degToRad(180)) * vertices[2]);


    verticesCount = vertices.size();

    uint32_t VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(scmath::Vec3), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, sizeof(scmath::Vec3), nullptr);
    glBindVertexArray(0);
}

void Crosshair::onDraw(sc::CameraController const& camCtrl, sc::Lights const& lights, scmath::Mat4 const& modelMatrix) 
{
    _shader->bind();
    _shader->uploadUniformMat4("u_ViewProjection", camCtrl.getViewProj());
    _shader->uploadUniformMat4("u_Model", modelMatrix);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
    glBindVertexArray(0);
}