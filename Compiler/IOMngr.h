/*
 * IOMngr.h
 *
 *  Created on: Mar 3, 2013
 *      Author: Vladimir Tsoy
 */

#ifndef IOMngr_H_
#define IOMngr_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXLINE 1024

/* Open the source file whose name is given in ASourceName
You can assume ASourceName is assigned a legal char* (i.e. a string)
If ALisitingName is not NULL open the listing file whose name is given in AListingName
If AListingName is NULL, the output goes to stdout
Return true if the file open(s) were successful, otherwise return false */

bool OpenFiles(const char * ASourceName,  const char * AListingName);

/*
 * Close the source file and the listing file if one was created
 */

void CloseFiles();

/* Return the next source char
* This function is also responsible for echoing the lines in the source file
* to the listing file (if one exists)
* The lines in the listing file should be numbered
* Return EOF when the end of the source file is reached
*/

char GetSourceChar();

/* Write a line containing a single ‘^’ character in the indicated column
If there is no listing file then the current line should be echoed to stdout
the first time (for that line) that WriteIndicator or WriteMessage is called.
*/
void WriteIndicator(int AColumn);

/* Write the message on a separate line */
void WriteMessage(const char * AMessage);

/* Return the current line number */
int GetCurrentLine();

/* Return the column number of the most recently returned line */
int GetCurrentColumn();

/* Reads a line from a given file
 * Returns false if EOF is read.
 */
bool ReadLine();

#endif /* IOMngr_H_ */
