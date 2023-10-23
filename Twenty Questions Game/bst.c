/*
 * bst.c
 *
 *  Created on: Oct 8, 2023
 *      Author: Zaki Ilyas
 */
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/* ------------------------------------------------
 *  insert()
 *  takes the information, creates a node, finds
 *  the parent of which to insert the node as a
 *  new leaf node
 * -----------------------------------------------*/
struct node* insert(struct node* root, int data, char* question, char* guess)
{

	//allocate memory
	struct node* temp = malloc(sizeof(struct node));
	temp->data = data;
	temp->question = question;
	temp->guess = guess;
	temp->right=temp->left = NULL;

	//if tree is empty
	if (root == NULL)
	{
		root = temp;
		return root;
	}

	//search for new node's parent
	struct node* current = root;
	struct node* parent = root;
	while (current != NULL)
	{
		parent = current;
		if (data < current->data)
			current = current->left;
		else
			current = current->right;
	}

	//insert node
	if (data < parent->data)
		parent->left = temp;
	else
		parent->right = temp;

	return temp;
}

/* ------------------------------------------------
 *  printOrder()
 *  a recursive function to print bst for debugging
 * -----------------------------------------------*/
void printOrder(struct node* root)
{
	if (root == NULL)
	{
		return;
	}

	printOrder(root->left);
	printf("%d->", root->data);
	printOrder(root->right);
}
