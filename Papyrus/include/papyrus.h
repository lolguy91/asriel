#pragma once

/* ------------------------------------ */
/*          Papyrus functions           */
/* ------------------------------------ */

/**
 * Initialize Papyrus
 */
void papyrus_init();

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
void internal_init_window();
