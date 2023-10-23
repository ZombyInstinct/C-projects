/*
 * bst.h
 *
 *  Created on: Oct 8, 2023
 *      Author: Zaki Ilyas
 */

#ifndef BST_H_
#define BST_H_

#include <stdio.h>

//bst node
struct node
{
	int data;
	char* question;
	char* guess;
	struct node* left;
	struct node* right;
};

// functions to implement
struct node* insert(struct node* root, int data, char* question, char* guess);
void printOrder(struct node* root);

#endif /* BST_H_ */
