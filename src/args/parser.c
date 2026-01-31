#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "./storages.h"
#include "./flags.h"
#include "./parser.h"

#define IS_FLAG(arg, flag) (strcmp((arg), (flag)) == 0)

/* Validate Boolean Flag Repeation;
 * do not fear, this is JUST a ternary operation;
 * optField is a LITERAL field name of opts->argsList. */
#define VBFR(opts, optField, argId, flagName, flagPrefix) \
	( \
		(bool)(opts->argsList.optField) \
		? storeError( OPT_REPEAT, (argId), (flagName), (flagPrefix) ) \
		: ((opts->argsList.optField) = (bool)true) \
	)

size_t errorsCount;
FILE *errorsBuf;

static void storeError(EArgsErr id, int argId, const char *arg, const char *flagPrefix)
{
#	define MSG(first) fprintf( errorsBuf, first " (#%d): \"%s%s\".\n", argId, flagPrefix, arg )
	switch(id)
	{
		case INVALID_OPT:           MSG("Invalid option"); break;
		case OPT_REPEAT:            MSG("Option repeating"); break;
		case FILE_NOT_FOUND:        MSG("File not found"); break;
		case INVALID_FLAG_POSITION: MSG("Invalid option possition"); break;
	}
#	undef MSG
}

static void displayErrors(void)
{
	char c;
	fseek(errorsBuf, 0, SEEK_SET);

	while((c = fgetc(errorsBuf)) != EOF)
		fputc(c, stderr);

	fclose(errorsBuf);
}

static void valFile(Options *opts, int argId, const char *fileName)
{
	FILE *file = fopen(fileName, "r");

	if(file == NULL)
	{
		storeError(
			(!opts->list.optListEnd && fileName[0] == '-')
				? INVALID_FLAG_POSITION
				: FILE_NOT_FOUND,
			argId,
			fileName,
			FP_NONE
		);

		return;
	}

	addFileToList(&(opts->filesList), file);
}

static void valLongFlag(Options *opts, int argId, const char *flag)
{
#	define VAL(optField) VBFR(opts, optField, argId, flag, FP_LONG)

	if(IS_FLAG(flag, F_QUIET_W))
		VAL( quietWarn );

	else if(IS_FLAG(flag, F_QUIET_E))
		VAL( quietError );

	else if(IS_FLAG(flag, F_QUIET))
		VAL( quiet );

	else if(IS_FLAG(flag, F_FATAL_W))
		VAL( fatalWarn );

	else if(IS_FLAG(flag, F_FATAL_E))
		VAL( fatalError );

	else if(IS_FLAG(flag, F_FATAL))
		VAL( fatal );

	else if(IS_FLAG(flag, F_STDIN))
		VAL( readStdin );

	else if(IS_FLAG(flag, F_OPT_END))
		VAL( optListEnd );

	else
		storeError( INVALID_OPT, argId, flag, FP_LONG);

#	undef VAL
}

static void valShortFlag(Options *opts, int argId, const char *flagsList)
{
	char *f = (char*)flagsList;
	char *curFlag = "\0\0";

#	define VAL(optField) VBFR(opts, optField, argId, curFlag, FP_SHORT);
#	define CASE(optField, expectedFlag) \
	case expectedFlag: \
		VAL( optField ); \
		break

	for(; *f != '\0'; (f)++)
	{
		switch(*f)
		{
			CASE(quietWarn,  FS_QUIET_W);
			CASE(quietError, FS_QUIET_E);
			CASE(quiet,      FS_QUIET);
			CASE(fatalWarn,  FS_FATAL_W);
			CASE(fatalError, FS_FATAL_E);
			CASE(fatal,      FS_FATAL);
			default:
				curFlag[0] = *f;
				storeError( INVALID_OPT, argId, curFlag, FP_SHORT );
		}
	}

#	undef VAL
#	undef CASE
}

void argsParser(int argc, char *argv[], Options *opts)
{
	if(argc == 1)
	{
		/* It has only program name. */
		opts->noArgs = true;
		return;
	}

	errorsCount = 0;
	errorsBuf   = tmpfile();

	/* After OPT_END or a file, the next
	 * arguments will be considered files. */
	bool isFileList = false;

	const char *cur;
	int argId = 1; /* jump program name */

	for(; argId < argc; argId++)
	{
		cur = argv[argId];

		if(isFileList || opts->argsList.optListEnd)
			valFile( opts, argId, cur );

		else if(cur[0] != '-')
			isFileList = true;

		else if(cur[1] != '-')
			valShortFlag( opts, argId, &(cur[1]) );

		else
			valLongFlag( opts, argId, &(cur[2]) );
	}

	if(errorsCount > 0)
	{
		if(!(opts->argsList.quietError) && !(opts->argsList.quiet))
			displayErrors();
		else
			fclose(errorsBuf);

		exit( errorsCount );
	}
}

