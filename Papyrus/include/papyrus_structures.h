#pragma once

#include <stdint.h>

/**
 * Internal structure for error codes
 */
typedef enum error_T
{
    NO_ERROR,
    NOT_IMPLEMENTED,
    INVALID_NAME,
    INVALID_TITLE,
    INVALID_X,
    INVALID_Y,
    INVALID_WIDTH,
    INVALID_HEIGHT,
    INVALID_ELEMENTS
} Error;

/**
 * Internal structure for buttons
 * @param name button's name
 * @param title button's title
 * @param x x coordinate of left top corner
 * @param y y coordinate of left top corner
 * @param width button's width
 * @param height button's height
 */
typedef struct button_T
{
    char* name;
    char* title;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} Button;

/**
 * Internal structure for windows
 * @param name window's name
 * @param width window's width
 * @param height window's height
 * @param buttons buttons
 */
typedef struct window_T
{
    char* name;
    uint16_t width;
    uint16_t height;
    Button buttons[64];
} Window;

/**
 * Array containing all windows
 */
static Window windows[64];
