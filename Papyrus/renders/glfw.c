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

int width = 0;
int height = 0;

void internal_init_window()
{
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(650, 650, "Papyrus", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    if (window == NULL)
    {
        printf("Unable to create OpenGL window!\nExiting...\n");
        return;
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
    return;
}

void papyrus_init_glfw_render()
{
    papyrus_init();       
}
