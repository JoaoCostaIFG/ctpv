#include <MagickWand/MagickWand.h>
#include <chafa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "error.h"
#include "image.h"

static ChafaTermInfo* term_info = NULL;
static ChafaPixelMode detected_pixel_mode = CHAFA_PIXEL_MODE_SYMBOLS;
static int image_initialized = 0;

RESULT image_init(void) {
    if (image_initialized)
        return OK;

    /* Initialize ImageMagick */
    MagickWandGenesis();

    /* Detect terminal capabilities */
    ChafaTermDb* term_db = chafa_term_db_get_default();
    gchar** envp = g_get_environ();
    term_info = chafa_term_db_detect(term_db, envp);
    g_strfreev(envp);

    if (!term_info) {
        print_error("failed to detect terminal capabilities");
        return ERR;
    }

    /* Get best pixel mode for this terminal */
    detected_pixel_mode = chafa_term_info_get_best_pixel_mode(term_info);

    image_initialized = 1;
    return OK;
}

void image_cleanup(void) {
    if (!image_initialized)
        return;

    if (term_info) {
        chafa_term_info_unref(term_info);
        term_info = NULL;
    }

    MagickWandTerminus();
    image_initialized = 0;
}

static RESULT load_image_pixels(const char* path, guint8** pixels_out, int* width_out,
                                int* height_out, int* rowstride_out) {
    MagickWand* wand = NewMagickWand();

    if (MagickReadImage(wand, path) == MagickFalse) {
        ExceptionType severity;
        char* desc = MagickGetException(wand, &severity);
        print_errorf("failed to load image '%s': %s", path, desc);
        MagickRelinquishMemory(desc);
        DestroyMagickWand(wand);
        return ERR;
    }

    /* For animated images, use only the first frame */
    MagickSetIteratorIndex(wand, 0);

    size_t width = MagickGetImageWidth(wand);
    size_t height = MagickGetImageHeight(wand);
    size_t rowstride = width * 4; /* RGBA = 4 bytes per pixel */

    guint8* pixels = g_malloc(rowstride * height);
    if (!pixels) {
        print_error("failed to allocate memory for image pixels");
        DestroyMagickWand(wand);
        return ERR;
    }

    /* Export pixels as RGBA */
    if (MagickExportImagePixels(wand, 0, 0, width, height, "RGBA", CharPixel, pixels) ==
        MagickFalse) {
        ExceptionType severity;
        char* desc = MagickGetException(wand, &severity);
        print_errorf("failed to export image pixels: %s", desc);
        MagickRelinquishMemory(desc);
        g_free(pixels);
        DestroyMagickWand(wand);
        return ERR;
    }

    DestroyMagickWand(wand);

    *pixels_out = pixels;
    *width_out = (int)width;
    *height_out = (int)height;
    *rowstride_out = (int)rowstride;

    return OK;
}

RESULT image_display(const char* path, int w, int h, int x, int y) {
    if (!image_initialized) {
        ERRCHK_RET_OK(image_init());
    }

    /* Load image pixels */
    guint8* pixels = NULL;
    int img_width, img_height, rowstride;
    ERRCHK_RET_OK(load_image_pixels(path, &pixels, &img_width, &img_height, &rowstride));

    /* Create canvas configuration */
    ChafaCanvasConfig* config = chafa_canvas_config_new();
    chafa_canvas_config_set_geometry(config, w, h);
    chafa_canvas_config_set_pixel_mode(config, detected_pixel_mode);

    /* Set cell geometry for proper aspect ratio calculation */
    /* Typical terminal cell is roughly 8x16 pixels (width x height) */
    chafa_canvas_config_set_cell_geometry(config, 8, 16);

    /* Use truecolor for best results */
    chafa_canvas_config_set_canvas_mode(config, CHAFA_CANVAS_MODE_TRUECOLOR);

    /* Create canvas */
    ChafaCanvas* canvas = chafa_canvas_new(config);

    /* Create frame (borrow pixels - we free them ourselves) */
    ChafaFrame* frame = chafa_frame_new_borrow(pixels, CHAFA_PIXEL_RGBA8_UNASSOCIATED, img_width,
                                               img_height, rowstride);

    /* Create image and set frame */
    ChafaImage* image = chafa_image_new();
    chafa_image_set_frame(image, frame);

    /* Create placement with aspect-preserving tuck policy */
    ChafaPlacement* placement = chafa_placement_new(image, 0);
    chafa_placement_set_tuck(placement, CHAFA_TUCK_FIT);
    chafa_placement_set_halign(placement, CHAFA_ALIGN_START);
    chafa_placement_set_valign(placement, CHAFA_ALIGN_START);

    /* Set placement on canvas (replaces draw_all_pixels) */
    chafa_canvas_set_placement(canvas, placement);

    /* Generate output */
    GString* output = chafa_canvas_print(canvas, term_info);

    /* Position cursor if x,y specified and we're in a graphics mode */
    if ((x > 0 || y > 0) && detected_pixel_mode != CHAFA_PIXEL_MODE_SYMBOLS) {
        /* Move cursor to position */
        fprintf(stdout, "\033[%d;%dH", y + 1, x + 1);
    }

    /* Write output to terminal */
    fwrite(output->str, 1, output->len, stdout);
    fflush(stdout);

    /* Cleanup */
    g_string_free(output, TRUE);
    chafa_placement_unref(placement);
    chafa_image_unref(image);
    chafa_frame_unref(frame);
    chafa_canvas_unref(canvas);
    chafa_canvas_config_unref(config);
    g_free(pixels);

    return OK;
}

void image_clear(void) {
    /* Write to /dev/tty to ensure it reaches the terminal even if stdout is redirected.
     * This matches the old kitty icat behavior which also wrote to /dev/tty.
     * ESC_Ga=d;ESC\ - action=delete, delete all placements */
    FILE* tty = fopen("/dev/tty", "w");
    if (tty) {
        static const char clear_seq[] = "\033_Ga=d\033\\";
        fwrite(clear_seq, 1, sizeof(clear_seq) - 1, tty);
        fflush(tty);
        fclose(tty);
    }
}
