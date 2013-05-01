/*
 * SymTab.h
 *
 *  Created on: Feb 9, 2013
 *      Author: Vladimir Tsoy
 */

#ifndef SymTab_H_
#define SymTab_H_

#include <stdbool.h>  //Your version of C might not have this include file.
				     //In that case you can use the local copy I put on the web


/*	 The symbol table structure proper. Implemented as a hash table that uses
	 separate chaining to resolve collisions
	 Contents is dynamically allocated according to size
*/
typedef struct SymTab{
	int Size;
    struct SymEntry **Contents;
 } SymTab;

/* 	The Name/Attributes association structure used in the symbol tables
     	linked lists.
*/
typedef struct SymEntry{
	const char *Name;
	void *Attributes;
	struct SymEntry *Next;
 } SymEntry;

/* 	CreateSymTab:    create and return a reference to a symbol table of
 *          approximately Size many entries.
 *
 *	DestroySymTab:  destroy all storage associated with a Symbol Table which
 *			is under the table's control. This does not include the attributes
*/

SymTab * CreateSymTab(int Size);

void DestroySymTab(SymTab *ATable);

/* 	EnterName:      enter a Name into a symbol table. Passes back an argument
                   		 containing an entry reference for the name. Return true if the
				  name was not already in the symbol table, otherwise return
 				 false. EnterName must allocate space for the Name and copy
				  the contents the parameter Name.

   	FindName:        find a Name in a symbol table. Return an entry reference
                   		  or NULL depending on whether the Name was found.
*/
bool EnterName(SymTab *ATable, const char *Name, SymEntry * *AnEntry);

SymEntry * FindName(SymTab *ATable, const char * Name);

/* 	SetAttr:        set the attribute pointer associated with an entry.
   	GetAttr:        get the attribute pointer associated with an entry.
   	GetName:    get the name string associated with an entry.
*/

void SetAttr(SymEntry *AnEntry, void *Attributes);

void * GetAttr(SymEntry *AnEntry);

const char * GetName(SymEntry *AnEntry);

/* symHash: hash function */
int symHash (int Size, const char *Name);

/* 	These two functions can be used to enumerate the contents of a table.
   	The enumeration order is arbitrary.

   	FirstEntry:     	return the "first" entry in a symbol table or
                   		NULL if the table is empty. "First" does not
                  		imply a particular order (e.g. alphabetical)
                  		it is simply the order found in the table.

   	NextEntry:      return the next entry after the supplied entry
                   		or NULL if no more entries.
*/

SymEntry * FirstEntry(SymTab *ATable);

SymEntry * NextEntry(SymTab *ATable, SymEntry *AnEntry);

#endif /* SymTab_H_ */
