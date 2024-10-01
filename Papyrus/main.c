/* Standard library includes */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* Glad include */
#if defined _WIN32 || defined _WIN64
    #include "Libraries/include/glad/glad.h"
#else
    #include <glad/glad.h>
#endif

/* GLFW 3 include */
#if defined _WIN32 || defined _WIN64
    #include "Libraries/include/GLFW/glfw3.h"
#else
    #include <GLFW/glfw3.h>
#endif

int width = 0;
int height = 0;

int main()
{
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(650, 650, "Papyrus", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    if (window == NULL)
    {
        printf("Unable to create OpenGL window!\nExiting...\n");
        return 1;
    }

    else
    {
        printf("OpenGL window has been created.\n");
    }

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwGetWindowSize(window, &width, &height);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
