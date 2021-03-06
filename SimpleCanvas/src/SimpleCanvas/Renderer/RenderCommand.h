#pragma once

#include <SCMath.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace sc 
{
class RenderCommand
{
public:
    static void init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE); // for one side triangle draw
        glCullFace(GL_BACK);    // for one side triangle draw
        //glfwWindowHint(GLFW_SAMPLES, 4);   // this needs to be called before glfwCreateWindow !!!!!!!!!!!!!!!!
        glEnable(GL_MULTISAMPLE);

        //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // for wireframe draw
        //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // for normal draw

    }

    static void setClearColor(scmath::Vec4 const& color)
    {
        glClearColor(color.x, color.y, color.z, color.w);
    }

    static void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    static void setCursorMode(int mode)
    {
        GLFWwindow *window = glfwGetCurrentContext();
        glfwSetInputMode(window, GLFW_CURSOR, mode);
    }
};
} // namespace sc