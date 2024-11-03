#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <time.h>


void ProcessInput(GLFWwindow* window);
void OnFrameBufferSizeChanged(GLFWwindow* window, int width, int height);


int main()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(800, 600, "Ugly", nullptr, nullptr);

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << '\n';
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << '\n';
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, OnFrameBufferSizeChanged);


    clock_t lastTime{ clock() };


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Frame time */
        clock_t elapsedTime{ clock() };
        clock_t frameTime{ elapsedTime - lastTime };
        lastTime = elapsedTime;

        /* Input */
        ProcessInput(window);

        /* Update */
        char title[128];
        snprintf(title, 128, "Ugly. Frame time: %f seconds.", ((float)frameTime) / CLOCKS_PER_SEC);
        glfwSetWindowTitle(window, title);

        /* Rendering */
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void OnFrameBufferSizeChanged(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
