#include <stdio.h>
#include <stdlib.h>

#include "./storages.h"

void addFileToList(FilesList *list, FILE *stream)
{
	if(list->abort)
	{
		fclose(stream);
		dropFilesList(list);
		return;
	}

	FilesListItem *newItem = malloc( sizeof(FilesListItem) );
	newItem->stream = stream;
	newItem->next  = NULL;

	if(list->firstItem == NULL)
	{
		list->firstItem = newItem;
		list->lastItem  = newItem;
		return;
	}

	list->lastItem->next = newItem;
	list->lastItem = newItem;
}

void dropFilesList(FilesList *list)
{
	if(list->firstItem == NULL)
		return;

	dropFilesListItem(list->firstItem);

	list->firstItem = NULL;
	list->lastItem = NULL;
}

static void dropFilesListItem(FilesListItem *item)
{
	if(item == NULL)
		return;

	dropFilesListItem(item->next);

	fclose(item->stream);
	free(item);
}

