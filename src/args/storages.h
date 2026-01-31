#ifndef __ARGS_ARGS__
#define __ARGS_ARGS__

#include <stdio.h>
#include <stdbool.h>


typedef struct FilesListItem
{
	FILE *stream;
	struct FilesListItem *next;
} FilesListItem;

typedef struct
{
	FilesListItem *firstItem;
	FilesListItem *lastItem;

	/* If true, all included/future
	 * files will be closed. */
	bool abort;
} FilesList;


typedef struct
{
	bool noArgs;
	FilesList filesList;

	struct
	{
		bool quietWarn;
		bool quietError;
		bool quiet;
		bool fatalWarn;
		bool fatalError;
		bool fatal;
		bool readStdin;
		bool optListEnd;
	} list;
} OptionsData;


void addFileToList(FilesList *list, FILE *stream);
void dropFilesList(FilesList *list);

static void dropFilesListItem(FilesListItem *item);


#endif
