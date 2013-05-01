/*
 * SymTab.c
 *
 * Created on: Feb 9, 2013
 * Author: Vladimir Tsoy
 * Description: CS442 : Assignment 1
 */

#include "SymTab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SymTab * CreateSymTab(int Size){
	SymTab *theTable;

	theTable = malloc(sizeof(SymTab*));
	theTable->Contents = malloc(sizeof (SymEntry) * Size);
	theTable->Size = Size;

	for (int i = 0; i < Size; i++){
		theTable->Contents[i] = NULL;
	}

	return theTable;
}

void DestroySymTab(SymTab *ATable){
	SymEntry *curRow, *temp;

	for (int i = 0; i < ATable->Size; i++){
		curRow = ATable->Contents[i];
		while (curRow != NULL){
			temp = curRow;
			curRow = curRow->Next;
			free(temp->Attributes);
			free(temp);
		}
	}

	free(ATable->Contents);
	free(ATable);
}

bool EnterName(SymTab *ATable, const char *Name, SymEntry **AnEntry){
	int bucket;
	SymEntry *newName;
	SymEntry *curNames;

	newName = malloc(sizeof(SymEntry*));
	curNames = FindName(ATable, Name);
	if (curNames != NULL) {
		*AnEntry = curNames;
		return false;
	}
	bucket = symHash(ATable->Size, Name);
	newName->Next = ATable->Contents[bucket];
	newName->Name = strdup(Name);
	*AnEntry = newName;

	ATable->Contents[bucket] = malloc(sizeof(SymEntry *));
	ATable->Contents[bucket] = newName;

	return true;
}

SymEntry * FindName(SymTab *ATable, const char * Name){
	int bucket = symHash(ATable->Size, Name);
	SymEntry *match;

	match = ATable->Contents[bucket];

	for (match = ATable->Contents[bucket]; match != NULL; match = match->Next){
		if (strcmp(Name, match->Name) == 0)return match;
	}
 	return NULL;
}

SymEntry * FirstEntry(SymTab *ATable){
	SymEntry *first;
	for (int i = 0; i < ATable->Size; i++){
		first = ATable->Contents[i];
		if(first != NULL){
			return first;
		}
	}
	return NULL;
}

SymEntry * NextEntry(SymTab *ATable, SymEntry *AnEntry){
	SymEntry *next;

	next = AnEntry->Next;

	if (NULL != next) return next;

	int i = symHash(ATable->Size, AnEntry->Name);

	for(; i < ATable->Size; i++){
		next = ATable->Contents[i];
		if (next != NULL && next != AnEntry) return next; //added additional validation since the first time around next == AnEntry
	}

	return NULL;
}

int symHash (int Size, const char *Name){
	unsigned int hashval = 0;

	for(; *Name != '\0'; Name++) hashval = *Name + (hashval<<5) - hashval;

	return hashval % Size;
}


void SetAttr(SymEntry *AnEntry, void *Attributes){
	AnEntry->Attributes = Attributes;
}

void * GetAttr(SymEntry *AnEntry){
	return AnEntry->Attributes;
}

const char * GetName(SymEntry *AnEntry){
	const char *aName = AnEntry->Name;
	return aName;
}
