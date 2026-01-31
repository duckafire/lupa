#ifndef __ARGS_PARSE__
#define __ARGS_PARSE__

#include <stdio.h>
#include <stdbool.h>

#include "./storages.h"

typedef enum
{
	/* Update storeError()
	 * after to update this. */
	INVALID_OPT,
	OPT_REPEAT,
	FILE_NOT_FOUND,
	INVALID_FLAG_POSITION,
} EArgsErr;

static void storeError(EArgsErr id, int argId, const char *arg, const char *optPrefix);
static void displayErrors(void);

static void valFile(     OptionsData *optsData, int argId, const char *fileName);
static void valLongFlag( OptionsData *optsData, int argId, const char *opt);
static void valShortFlag(OptionsData *optsData, int argId, const char *optsList);

void argsParser(int argc, char *argv[], OptionsData *optsData);

#endif
