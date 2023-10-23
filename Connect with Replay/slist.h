/*
 * slist.h
 *
 *  Created on: Oct 1, 2023
 *      Author: Zaki Ilyas
 */

#ifndef SLIST_H_
#define SLIST_H_

#include <stdio.h>

struct node
{
	int column;
	char player;
	struct node* next;

};


struct singlylinkedlist
{
	struct node* head;
	struct node* tail;
};

typedef struct singlylinkedlist slist;

void insertNext(slist* list, int column, char player);
void deleteLinkedList(slist* list);
void printList(slist* list);

#endif /* SLIST_H_ */
