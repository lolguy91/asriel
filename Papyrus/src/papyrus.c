#include <papyrus.h>
#include <papyrus_structures.h>

#include <stdio.h>
#include <string.h>

Error papyrus_init()
{
    Button button = {
        .name = "test_button",
        .title = "Test button",
        .x = 10,
        .y = 20,
        .width = 50,
        .height = 30,
    };

    // TODO: add_button() function
    Button buttons[64];
    buttons[0] = button;

    return init_window("Papyrus", 650, 650, buttons);
}

Error init_button(Window* window, char* name, char* title, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    Button button = {
        .name = name,
        .title = title,
        .x = x,
        .y = y,
        .width = width,
        .height = height,
    };

    // TODO: add_button() function
    window->buttons[0] = button;

    Error error = check_button(*window, button);
    if (error == NO_ERROR)
    {
        return internal_init_button(*window, button);
    }

    else
    {
        return error;
    }
}

Error init_window(char* name, uint16_t width, uint16_t height, Button buttons[64])
{
    Window window = {
        .name = name,
        .width = width,
        .height = height,
    };

    memcpy(window.buttons, buttons, sizeof(Button) * 64);

    Error error = check_window(window);
    if (error == NO_ERROR)
    {
        return internal_init_window(window);
    }

    else
    {
        return error;
    }
}
