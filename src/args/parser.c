#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "./storages.h"
#include "./options.h"
#include "./parser.h"

#define IS_FLAG(arg, opt) (strcmp((arg), (opt)) == 0)

/* Validate Boolean Flag Repeation;
 * do not fear, this is JUST a ternary operation;
 * optField is a LITERAL field name of optsData->list. */
#define VBFR(optsData, optField, argId, optName, optPrefix) \
	( \
		(bool)(optsData->list.optField) \
		? storeError( OPT_REPEAT, (argId), (optName), (optPrefix) ) \
		: ((optsData->list.optField) = (bool)true) \
	)

size_t errorsCount;
FILE *errorsBuf;

static void storeError(EArgsErr id, int argId, const char *arg, const char *optPrefix)
{
#	define MSG(first) fprintf( errorsBuf, first " (#%d): \"%s%s\".\n", argId, optPrefix, arg )
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

static void valFile(OptionsData *optsData, int argId, const char *fileName)
{
	FILE *file = fopen(fileName, "r");

	if(file == NULL)
	{
		storeError(
			(!optsData->list.optListEnd && fileName[0] == '-')
				? INVALID_FLAG_POSITION
				: FILE_NOT_FOUND,
			argId,
			fileName,
			OPT_P_NONE
		);

		return;
	}

	addFileToList(&(optsData->filesList), file);
}

static void valLongFlag(OptionsData *optsData, int argId, const char *opt)
{
#	define VAL(optField) VBFR(optsData, optField, argId, opt, OPT_P_LONG)

	if(IS_FLAG(opt, OPT_QUIET_W))
		VAL( quietWarn );

	else if(IS_FLAG(opt, OPT_QUIET_E))
		VAL( quietError );

	else if(IS_FLAG(opt, OPT_QUIET))
		VAL( quiet );

	else if(IS_FLAG(opt, OPT_FATAL_W))
		VAL( fatalWarn );

	else if(IS_FLAG(opt, OPT_FATAL_E))
		VAL( fatalError );

	else if(IS_FLAG(opt, OPT_FATAL))
		VAL( fatal );

	else if(IS_FLAG(opt, OPT_STDIN))
		VAL( readStdin );

	else if(IS_FLAG(opt, OPT_END))
		VAL( optListEnd );

	else
		storeError( INVALID_OPT, argId, opt, OPT_P_LONG);

#	undef VAL
}

static void valShortFlag(OptionsData *optsData, int argId, const char *optsList)
{
	char *f = (char*)optsList;
	char curFlag[2];
	curFlag[1] = '\0';

#	define VAL(optField) VBFR(optsData, optField, argId, curFlag, OPT_P_SHORT);
#	define CASE(optField, expectedFlag) \
	case expectedFlag: \
		VAL( optField ); \
		break

	for(; *f != '\0'; (f)++)
	{
		curFlag[0] = *f;

		switch(*f)
		{
			CASE(quietWarn,  OPT_S_QUIET_W);
			CASE(quietError, OPT_S_QUIET_E);
			CASE(quiet,      OPT_S_QUIET);
			CASE(fatalWarn,  OPT_S_FATAL_W);
			CASE(fatalError, OPT_S_FATAL_E);
			CASE(fatal,      OPT_S_FATAL);
			default: storeError( INVALID_OPT, argId, curFlag, OPT_P_SHORT );
		}
	}

#	undef VAL
#	undef CASE
}

void argsParser(int argc, char *argv[], OptionsData *optsData)
{
	if(argc == 1)
	{
		/* It has only program name. */
		optsData->noArgs = true;
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

		if(isFileList || optsData->list.optListEnd)
			valFile( optsData, argId, cur );

		else if(cur[0] != '-')
			isFileList = true;

		else if(cur[1] != '-')
			valShortFlag( optsData, argId, &(cur[1]) );

		else
			valLongFlag( optsData, argId, &(cur[2]) );
	}

	if(errorsCount > 0)
	{
		if(!(optsData->list.quietError) && !(optsData->list.quiet))
			displayErrors();
		else
			fclose(errorsBuf);

		exit( errorsCount );
	}
}

