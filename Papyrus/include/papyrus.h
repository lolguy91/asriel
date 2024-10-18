#pragma once

#include <papyrus_structures.h>

/* ------------------------------------ */
/*          Papyrus functions           */
/* ------------------------------------ */

/**
 * Initialize Papyrus
 */
Error papyrus_init();

/**
 * Make new button
 * @param window window where button will be created
 * @param name button's name
 * @param title button's title
 * @param x x coordinate of left top corner
 * @param y y coordinate of left top corner
 * @param width button's width
 * @param height button's height
 * 
 */
Error init_button(Window* window, char* name, char* title, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

/**
 * Make new button
 * @param name window's name
 * @param width window's width
 * @param height window's height
 * @param buttons buttons
 */
Error init_window(char* name, uint16_t width, uint16_t height, Button buttons[64]);

/* ------------------------------------ */
/*          Papyrus check functions     */
/* ------------------------------------ */

/**
 * Check window
 * @param window window to be checked
 */
Error check_window(Window window);

/**
 * Check button
 * @param window button's window
 * @param button button to be checked
 */
Error check_button(Window window, Button button);

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
Error internal_init_window(Window window);

/**
 * Draw button (backend agnostic function)
 */
Error internal_init_button(Window window, Button button);
