/*
 * slist.c
 *
 *  Created on: Oct 1, 2023
 *      Author: Zaki Ilyas
 */
#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

/*-------------------------------------
 * insertNext(slist* list, int column, char player)
 * inserts new node at the end of the
 * list
 -------------------------------------*/
void insertNext(slist* list, int column, char player)
{

	//create new node
	struct node* newNode;
	newNode = malloc(sizeof(struct node));
	newNode -> column = column;
	newNode -> player = player;

	//adjust pointers
	if (list->head == NULL)
	{
		list->tail = newNode;
		list->head = list->tail;
	}
	else
	{
		list->tail->next = newNode;
		list->tail = newNode;
	}
}

/*-------------------------------------
 * deleteLinkedList(slist* list)
 * empties the list
 * frees memory
 -------------------------------------*/
void deleteLinkedList(slist* list) {

    struct node* current = (list->head);
    struct node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    (list->head) = NULL;
}

/*-------------------------------------
 * printList()
 * UNUSED - for debugging
 * prints list
 -------------------------------------*/
void printList(slist* list)
{
	struct node* tmp = list->head;
	while(tmp != NULL)
	{
		printf("%d%c->",tmp->column, tmp->player);
		tmp = tmp->next;
	}
	printf("NULL\n");
}
