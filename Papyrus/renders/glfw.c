#include "glfw.h"

/* Glad include */
#include <glad/glad.h>

/* GLFW 3 include */
#include <GLFW/glfw3.h>

/* Standard library includes */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int width = 0;
int height = 0;

int internal_init_window()
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
