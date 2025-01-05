#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

GLFWwindow* window;
static bool WindowInit();
template<typename... Args>
static void UnbindAll(Args&... objects);

int main()
{
    if (!WindowInit()) return -1;
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f,
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,
        };

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        IndexBuffer ib(indices, 6);
        Shader shader("Resources/Shaders/Basic.shader");
        shader.Bind();

        Texture texture("Resources/Textures/Cool.png");
        texture.Bind();
        shader.SetUniform1i("u_texture", 0);

        UnbindAll(va, vb, ib, shader);

        Renderer renderer;

        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();
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

template<typename... Args>
static void UnbindAll(Args&... objects) {
    (objects.Unbind(), ...);
}