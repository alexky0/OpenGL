#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

GLFWwindow* window;
static bool WindowInit();

int main()
{
    if (!WindowInit()) return -1;
    {
        float positions[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f,
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,
        };

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        IndexBuffer ib(indices, 6);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_color", 0.6f, 0.0f, 0.8f, 1.0f);
        
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        float r = 0.5f, g = 0.2f, b = 0.9f, a = 1.0f, rInc = 0.05f, gInc = 0.002f, bInc = -0.07f;

        Renderer renderer;

        while (!glfwWindowShouldClose(window))
        {
            if (r >= 1.0f || r <= 0.0f) rInc *= -1; if (g >= 1.0f || g <= 0.0f) gInc *= -1; if (b >= 1.0f || b <= 0.0f) bInc *= -1;
            r += rInc; g += gInc; b += bInc;
            shader.SetUniform4f("u_color", 0.6f, 0.0f, 0.8f, 1.0f);

            renderer.Draw(va, ib, shader);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}

static bool WindowInit()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW." << std::endl;
        glfwTerminate();
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 480, "Engine3D", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW." << std::endl;
        glfwTerminate();
        return false;
    }
    return true;
}