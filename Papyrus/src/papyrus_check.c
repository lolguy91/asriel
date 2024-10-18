#include <papyrus.h>
#include <papyrus_structures.h>

/**
 * Check window
 * @param window window to be checked
 */
Error check_window(Window window)
{
    if (window.width > 1920)
    {
        return INVALID_WIDTH;
    }

    if (window.height > 1080)
    {
        return INVALID_HEIGHT;
    }

    return NO_ERROR;
}

/**
 * Check button
 * @param window button's window
 * @param button button to be checked
 */
Error check_button(Window window, Button button)
{
    return NOT_IMPLEMENTED;
}
