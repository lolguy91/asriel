#include <papyrus.h>
#include <papyrus_structures.h>

Error papyrus_init()
{
    internal_init_window();
    return NO_ERROR;
}

Error init_button(Window* window, char* name, char* title, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    return NOT_IMPLEMENTED;
}

Error init_window(char* name, uint16_t width, uint16_t height, Button buttons[64])
{
    return NOT_IMPLEMENTED;
}
