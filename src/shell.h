#ifndef SHELL_H
#define SHELL_H

#include "ctpv.h"
#include "utils.h"

#define SHELL_ARGS(script, ...)                                                                    \
    {ctpv.opts.shell, "-c", script, ctpv.opts.shell, __VA_ARGS__ __VA_OPT__(, ) NULL}

RESULT run_script(unsigned char* script, size_t script_len, int* exitcode, int* signal,
                  SpawnProg sp, void* sp_arg);

#endif
