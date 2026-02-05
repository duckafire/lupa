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

FILE** convertFilesListToFilesArray(FilesList *list)
{
	size_t quant;
	FilesListItem *cur, *next;

	for(quant = 0, cur = list->firstItem; cur != NULL; cur = cur->next)
		quant++;

	FILE **array = malloc( sizeof(FILE*) * quant );

	for(quant = 0, cur = list->firstItem; cur != NULL; cur = next)
	{
		array[ quant ] = cur->stream;
		next = cur->next;
		free(cur);
	}

	return array;
}

static void dropFilesList(FilesList *list)
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

