#pragma once

#include <papyrus_structures.h>
#include <cvector.h>

/* ------------------------------------ */
/*          Papyrus functions           */
/* ------------------------------------ */

/**
 * Initialize Papyrus
 */
Error papyrus_init();

/**
 * Initialize a new button.
 * Perform checks and return `NO_ERROR` if button can be drawn.
 * @param window window where button will be drawn
 * @param button button to be drawn
 * @return `Error` enum
 */
Error init_button(Window window, Button button);

/**
 * Initialize a new window.
 * Perform checks and return `NO_ERROR` if window can be drawn.
 * @param window window to be drawn
 * @return `Error` enum
 */
Error init_window(Window window);

/* ------------------------------------ */
/*      Backend initialize functions    */
/* ------------------------------------ */

/**
 * Initialize GLFW backend
 */
void papyrus_init_glfw_render();

/* ------------------------------------ */
/*          Backend functions           */
/* ------------------------------------ */

/**
 * Draw window (backend agnostic function)
 */
Error internal_draw_window(Window window);

/**
 * Draw button (backend agnostic function)
 */
Error internal_draw_button(Window window, Button button);
