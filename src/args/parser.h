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
} EArgsErr;

static void storeError(EArgsErr id, int argId, const char *arg, const char *flagPrefix);
static void displayErrors(void);

static void valFile(     Options *opts, int argId, const char *fileName);
static void valLongFlag( Options *opts, int argId, const char *flag);
static void valShortFlag(Options *opts, int argId, const char *flagsList);

void argsParser(int argc, char *argv[], Options *opts);

#endif
