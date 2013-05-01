/*
 * IOMngr.c
 *
 *  Created on: Mar 3, 2013
 *      Author: Vladimir Tsoy
 */

#include "IOMngr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *source;
FILE *listing;
char line[MAXLINE];
int linenum = 0;
int column = 0;
bool printed = false;
bool isListingNull = true;

bool OpenFiles(const char * ASourceName,  const char * AListingName){

	source = fopen(ASourceName, "r");

	if(AListingName != NULL){
		listing = fopen(AListingName, "w");
		isListingNull = false;
	}
	else {
		listing = stdout;
		isListingNull = true;
	}

	if (source != NULL && listing != NULL) return true;
	else return false;
}

void CloseFiles(){
	fclose(source);
	fclose(listing);
}

bool ReadLine(){
	if (fgets(line, MAXLINE - 1, source) != NULL){
		linenum++;
		column = 0;
		printed = false;
		return true;
	}
	else return false;
}

char GetSourceChar(){
	char retval;

	if(line[column] == '\0' || column == 0) {
		if (!ReadLine()) return EOF;
	}

	retval = line[column];

	if (!isListingNull && !printed){
		fprintf(listing, "%d. %s", linenum, line);
		printed = true;
	}

	column++;
	return retval;
}

void WriteIndicator(int AColumn){
	if (isListingNull && !printed){
		fprintf(listing, "%s\n", line);
		printed = true;
	}
	if (linenum < 10 && !isListingNull){
		fprintf(listing, "   %*s\n", column, "^");
	}
	else if (!isListingNull && linenum <= 0){
		fprintf(listing, "    %*s\n", column, "^");
	}
	else fprintf(listing, "%*s\n", column, "^");
}

void WriteMessage(const char * AMessage){
	fprintf(listing, "%s\n", AMessage);
}

int GetCurrentLine(){
	return linenum;
}

int GetCurrentColumn(){
	return column;
}
