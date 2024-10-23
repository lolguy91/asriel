#include <papyrus.h>
#include <papyrus_structures.h>

#include <stdio.h>
#include <string.h>

#include <cvector.h>

Error papyrus_init()
{
    /* ------------------------------------ */
    /*          Initialize window           */
    /* ------------------------------------ */
    Window window = {
        .name = "Papyrus",
        .width = 650,
        .height = 650,
    };

    Error window_error = init_window(window);
    if (window_error != NO_ERROR)
    {
        return window_error;
    }

    /* ------------------------------------ */
    /*          Initialize button           */
    /* ------------------------------------ */

    Button button = {
        .name = "test_button",
        .title = "Test button",
        .x = 10,
        .y = 20,
        .width = 50,
        .height = 30,
    };

    Error button_error = init_button(window, button);
    if (button_error != NO_ERROR)
    {
        return button_error;
    }

    /* ------------------------------------ */
    /*      Copy buttons to window          */
    /* ------------------------------------ */

    cvector_push_back(window.buttons, button);

    /* Button* b = cvector_at(window.buttons, 0);
    printf("%d\n", b->height); */

    /* ------------------------------------ */
    /*              Draw window             */
    /* ------------------------------------ */

    internal_draw_window(window);
}

Error init_button(Window window, Button button)
{
    // TODO: make button checks
    return NO_ERROR;
}

Error init_window(Window window)
{
    // TODO: make window checks

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
