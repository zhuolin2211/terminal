#ifndef _CLI_STRING_A_H
#define _CLI_STRING_A_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "terminal_config.h"

typedef struct{
	uint8_t argc;
	char argv[TERM_ARGS_BUF_SIZE][TERM_ARG_SIZE + 1];
}Params_s;

void ArgDestroy(Params_s* src);

void split(char* strSrc, const char* separator, Params_s* dst);

#endif // _CLI_STRING_A_H
