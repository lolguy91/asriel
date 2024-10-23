/* Glad include */
#include <glad/glad.h>

/* GLFW 3 include */
#include <GLFW/glfw3.h>

/* Standard library includes */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* Papyrus include */
#include <papyrus.h>
#include <papyrus_structures.h>

int width = 0;
int height = 0;

Error internal_draw_window(Window window)
{
    glfwInit();
    GLFWwindow *glfw_window = glfwCreateWindow(window.width, window.height, window.name, NULL, NULL);
    glfwMakeContextCurrent(glfw_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    if (glfw_window == NULL)
    {
        printf("Unable to create OpenGL window!\nExiting...\n");
        return UNSPECIFIED_ERROR;
    }

    else
    {
        printf("OpenGL window has been created.\n");
    }

    while (!glfwWindowShouldClose(glfw_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwGetWindowSize(glfw_window, &width, &height);

        glfwSwapBuffers(glfw_window);
        glfwPollEvents();
    }

    glfwTerminate();
    return NO_ERROR;
}

Error internal_draw_button(Window window, Button button)
{
    return NOT_IMPLEMENTED;
}

void papyrus_init_glfw_render()
{
    papyrus_init();    
}
