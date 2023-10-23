/*
 * twenty.c
 *
 *  Created on: Oct 8, 2023
 *      Author: Zaki Ilyas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

/* ------------------------------------------------
 *  create_game_tree()
 *  creates the bst and inserts all the nodes for
 *  the twenty questions game
 * -----------------------------------------------*/
struct node* create_game_tree()
{
	struct node* root = NULL;

	root = insert(root, 100, "Does it grow underground?", "");
	insert(root, 50, "Is it long in shape?", "");
	insert(root, 25, "Is it orange in color?", "");
	insert(root, 15, "", "It's a carrot!");
	insert(root, 35, "", "It's a parsnip!");
	insert(root, 75, "Is it red in color?", "");
	insert(root, 65, "", "It's a radish!");
	insert(root, 85, "", "It's a potato!");
	insert(root, 150, "Does it grow on a tree?", "");
	insert(root, 125, "Is it red in color?", "");
	insert(root, 115, "", "It's an apple!");
	insert(root, 135, "", "It's a peach!");
	insert(root, 175, "Is it red in color?", "");
	insert(root, 165, "", "It's a tomato!");
	insert(root, 185, "", "It's a pea!");

	return root;
}

/* ------------------------------------------------
 *  getUserChoice()
 *  scans for user input and returns the response
 * -----------------------------------------------*/
char getUserChoice()
{
	char response = ' ';

	scanf("%c", &response);
	while((getchar()) != '\n');

	while (response != 'y' && response != 'n')
	{
		printf("Please respond with either 'y' or 'n':");
		scanf("%c", &response);
		while((getchar()) != '\n');
	}

	return response;
}


/* ------------------------------------------------
 *  playingTwentyQuestions()
 *  following the user's input, the bst cycles
 *  through the nodes and returns a response
 * -----------------------------------------------*/
void playingTwentyQuestions(struct node* game_tree)
{
	int game_end = 0; //checks for game completion
	printf("You think of a fruit or vegetable and I will try to guess it!\n");

	struct node* current = game_tree;

	while (game_end == 0)
	{
		char response = ' ';

		if (strcmp(current->guess, "") != 0)
		{
			printf("%s \n", current->guess);
			printf("y/n: ");
			response = getUserChoice();

			if (response == 'y')
				printf("I Win!\n");
			else
				printf("You Win!\n");

			game_end = 1;
		}
		else
		{
			printf("%s \n", current->question);
			printf("y/n: ");
			response = getUserChoice();

			if (response == 'y')
				current = current->left;
			else
				current = current->right;
		}
	}
}

/* ------------------------------------------------
 *  main()
 *  creates the game tree node
 *  loops the game until the user quits
 * -----------------------------------------------*/
int main()
{

	struct node* game_tree = create_game_tree();


	printf("Welcome! Press 'q' to quit or any other key to continue:\n");
	char play = ' ';
	scanf("%c", &play);
	while((getchar()) != '\n');

	while (play != 'q')
	{
		playingTwentyQuestions(game_tree);

		printf("Press 'q' to quit or any other key to continue:\n");
		scanf("%c", &play);
		while((getchar()) != '\n');
	}

	//printOrder(game_tree);
	return 0;
}

