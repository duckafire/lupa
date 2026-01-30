#include <stdlib.h>
#include <stdio.h>

#include "./args/storages.h"
#include "./args/parser.h"

int main(int argc, char *argv[])
{
	Options opts;
	opts.noArgs = false;

	opts.filesList.firstItem = NULL;
	opts.filesList.lastItem  = NULL;
	opts.filesList.abort     = false;

	opts.argsList.quietWarn  = false;
	opts.argsList.quietError = false;
	opts.argsList.quiet      = false;
	opts.argsList.fatalWarn  = false;
	opts.argsList.fatalError = false;
	opts.argsList.fatal      = false;
	opts.argsList.readStdin  = false;
	opts.argsList.optListEnd = false;

	argsParser(argc, argv, &opts);

	printf("quietWarn: %d\n", opts.argsList.quietWarn );
	printf("quietError: %d\n", opts.argsList.quietError);
	printf("quiet: %d\n", opts.argsList.quiet     );
	printf("fatalWarn: %d\n", opts.argsList.fatalWarn );
	printf("fatalError: %d\n", opts.argsList.fatalError);
	printf("fatal: %d\n", opts.argsList.fatal     );
	printf("readStdin: %d\n", opts.argsList.readStdin );
	printf("optListEnd: %d\n", opts.argsList.optListEnd);
	dropFilesList(&(opts.filesList));

	return 0;
}

