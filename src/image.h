#ifndef IMAGE_H
#define IMAGE_H

#include "result.h"

/*
 * Initialize image subsystem (chafa terminal detection).
 * Should be called once at startup.
 */
RESULT image_init(void);

/*
 * Cleanup image subsystem resources.
 */
void image_cleanup(void);

/*
 * Display an image at the specified position.
 *
 * path: Path to image file
 * w: Width in terminal columns
 * h: Height in terminal rows
 * x: X position (column)
 * y: Y position (row)
 *
 * Returns OK on success, ERR on failure.
 */
RESULT image_display(const char* path, int w, int h, int x, int y);

/*
 * Clear any displayed images.
 * Used for kitty graphics protocol cleanup.
 */
void image_clear(void);

#endif
