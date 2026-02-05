#ifndef __ARGS_PARSE__
#define __ARGS_PARSE__

#include <stdio.h>
#include <stdbool.h>

#include "./storages.h"

typedef struct
{
	int quant;
	FILE *msgBuf;
} ArgsErrorsLog;

typedef enum
{
	/* Update storeError()
	 * after to update this. */
	INVALID_OPT,
	OPT_REPEAT,
	FILE_NOT_FOUND,
	INVALID_FLAG_POSITION,
} EArgsErr;

static void storeError(EArgsErr id, ArgsErrorsLog *errorsLog, int argId, const char *arg, const char *optPrefix);

static void valFile(     OptionsData *optsData, ArgsErrorsLog *errorsLog, int argId, const char *fileName);
static void valLongFlag( OptionsData *optsData, ArgsErrorsLog *errorsLog, int argId, const char *opt);
static void valShortFlag(OptionsData *optsData, ArgsErrorsLog *errorsLog, int argId, const char *optsList);

ArgsErrorsLog* argsParser(int argc, char *argv[], OptionsData *optsData);

#endif
