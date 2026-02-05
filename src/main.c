#include <stdlib.h>
#include <stdio.h>

#include "./args/storages.h"
#include "./args/parser.h"

void transferToStderr(FILE *buf)
{
	char c;
	fseek(buf, 0, SEEK_SET);

	while((c = fgetc(buf)) != EOF)
		fputc(c, stderr);
}

int main(int argc, char *argv[])
{
	OptionsData* opts = malloc(sizeof(OptionsData));
	opts->noArgs = false;

	opts->filesList.firstItem = NULL;
	opts->filesList.lastItem  = NULL;
	opts->filesList.abort     = false;

	opts->list.quietWarn  = false;
	opts->list.quietError = false;
	opts->list.quiet      = false;
	opts->list.fatalWarn  = false;
	opts->list.fatalError = false;
	opts->list.fatal      = false;
	opts->list.readStdin  = false;
	opts->list.optListEnd = false;

	ArgsErrorsLog* log = argsParser(argc, argv, opts);

	if(log->quant > 0)
	{
		const int ERR = log->quant;

		transferToStderr( log->msgBuf );
		fclose(log->msgBuf);
		free(log);

		return ERR;
	}

	fclose(log->msgBuf);
	free(log);

	printf("quietWarn: %d\n",  opts->list.quietWarn );
	printf("quietError: %d\n", opts->list.quietError);
	printf("quiet: %d\n",      opts->list.quiet     );
	printf("fatalWarn: %d\n",  opts->list.fatalWarn );
	printf("fatalError: %d\n", opts->list.fatalError);
	printf("fatal: %d\n",      opts->list.fatal     );
	printf("readStdin: %d\n",  opts->list.readStdin );
	printf("optListEnd: %d\n", opts->list.optListEnd);
	dropFilesList(&(opts->filesList));
	free(opts);

	return 0;
}

