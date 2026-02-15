#include "../gen/cleanup.h"
#include "shell.h"
#include "utils.h"

static inline RESULT run_cleanup_script(unsigned char* script, size_t script_len) {
    return run_script(script, script_len, NULL, NULL, NULL, NULL);
}

RESULT cleanup_clear(void) {
    return run_cleanup_script(scr_clear_sh, LEN(scr_clear_sh));
}

RESULT cleanup_end(void) {
    return run_cleanup_script(scr_end_sh, LEN(scr_end_sh));
}
