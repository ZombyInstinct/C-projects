/*
 * connect.c
 *
 *  Created on: Sep 11, 2023
 *      Author: Zaki Ilyas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char playerOne[32];
char playerTwo[32];
char currPlayer;

int num_tokens_needed, game_state;

char grid[6][7];

/*-------------------------------------
 * getPlayerChoice
 * returns the column the player picks.
 -------------------------------------*/
int getPlayerChoice(char player)
{
	int choice;

	if(player == 'R')
	{
		printf("Red to play. ");
	}
	else
	{
		printf("Yellow to play. ");
	}

	printf("Pick a column (1-7): ");
	scanf("%d", &choice);
	while (choice < 1 || choice > 7)
	{
		printf("Please input a valid answer (must be from 1-7).\n ");

		fflush(stdin); // NEVER USE THIS, INSTEAD USE
		while ((getchar()) != '\n'); //THIS
		scanf("%d", &choice);
	}
	return choice;
}

/*-------------------------------------
 * preGame
 * prompts players for their name and
 * how many tokens are needed to win.
 -------------------------------------*/
void preGame()
{
	printf("Enter in player-one's name: ");
	fflush(stdin);
	scanf("%[^\n]%*c", &playerOne);
	printf("Welcome %s. You are Red.\n", playerOne);

	printf("Enter in player-two's name: ");
	fflush(stdin);
	scanf("%[^\n]%*c", &playerTwo);
	printf("Welcome %s. You are Yellow.\n", playerTwo);

	printf("Enter how many tokens are needed to win: ");
	scanf("%d", &num_tokens_needed);

	while (num_tokens_needed < 3 || num_tokens_needed > 5)
	{
		printf("Try again. Please enter either 3, 4, or 5.\n");
		scanf("%d", &num_tokens_needed);
	}

	printf("%d tokens are needed to win...\n\n", num_tokens_needed);

	currPlayer = 'R';
	game_state = 1;
}

/*-------------------------------------
 * createEmptyBoard
 * fills the matrix with empty spaces
 * for a new game.
 -------------------------------------*/
void createEmptyBoard()
{
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 7; j++)
		{
			grid[i][j] = ' ';
		}
	}
}

/*-------------------------------------
 * printBoard
 * prints out the array visually as a
 * connect board
 -------------------------------------*/
void printBoard()
{
	for (int i = 0; i < 6; i++) {
		printf("|");
		for (int j = 0; j < 7; j++)
		{
			printf("%c|", grid[i][j]);
		}
		printf("\n");
	}
	printf("---------------\n");
}

/*-------------------------------------
 * checkWin
 * procedurally checks the array if
 * any game conclusion is satisfied.
 -------------------------------------*/
void checkWin(char player)
{
	//horizontal check
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6 - num_tokens_needed + 1; j++)
		{
			int count = 0;
			for (int k = 0; k < num_tokens_needed; k++)
			{
				if (grid[i][j + k] == player)
				{
					count++;
				}
			}
			if (count == num_tokens_needed)
			{
				game_state = 0;
			}
		}
	}

	//vertical check
	for (int i = 0; i < 6 - num_tokens_needed + 1; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			int count = 0;
			for (int k = 0; k < num_tokens_needed; k++)
			{
				if (grid[i + k][j] == player)
				{
					count++;
				}
			}
			if (count == num_tokens_needed)
			{
				game_state = 0;
			}
		}
	}

	//downwards diagonal check
	for (int i = 0; i < 6 - num_tokens_needed + 1; i++)
	{
		for (int j = 0; j < 7 - num_tokens_needed + 1; j++)
		{
			int count = 0;
			for (int k = 0; k < num_tokens_needed; k++)
			{
				if (grid[i + k][j + k] == player)
				{
					count++;
				}
			}
			if (count == num_tokens_needed)
			{
				game_state = 0;
			}
		}
	}

	//upwards diagonal check
	for (int i = num_tokens_needed - 1; i < 6; i++)
	{
		for (int j = 0; j < 7 - num_tokens_needed + 1; j++)
		{
			int count = 0;
			for (int k = 0; k < num_tokens_needed; k++)
			{
				if (grid[i - k][j] == player)
				{
					count++;
				}
			}
			if (count == num_tokens_needed)
			{
				game_state = 0;
			}
		}
	}

	//draw
	for (int i = 0; i < 7; i++)
	{
		if (grid[0][i] == ' ')
		{
			break;
		}
		else
		{
			if (i == 6)
			{
				game_state = 2;
			}
		}
	}

	//switch current player
	if (player == 'R' && game_state == 1)
	{
		currPlayer = 'Y';
	}
	else if (player == 'Y' && game_state == 1)
	{
		currPlayer = 'R';
	}
}

/*-------------------------------------
 * playRound
 * plays a turn for each player, the
 * player char is the parameter.
 * This calls the getPlayerChoice and
 * checkWin functions after each turn.
 -------------------------------------*/
void playRound(char player)
{
	int column = getPlayerChoice(player) - 1;

	while (grid[0][column] != ' ')
	{
		printf("This column is filled, try a different one.\n");
		column = getPlayerChoice(player) - 1;
	}

	for (int i = 5; i >= 0; i--)
	{
		if (grid[i][column] == ' ')
		{
			grid[i][column] = player;
			break;
		}
	}

	checkWin(player);
}

/*-------------------------------------
 * endGame
 * displays the winner/draw
 -------------------------------------*/
void endGame(char player)
{
	printBoard();

	if (player == 'R' && game_state == 0)
	{
		printf("Congratulations, %s!! You Win!\n", playerOne);
	}
	else if (player == 'Y' && game_state == 0)
	{
		printf("Congratulations, %s!! You Win!\n", playerTwo);
	}
	else
	{
		printf("It's a draw!\n");
	}
}

/*-------------------------------------
 * playingConnect
 * procedurally calls each state of the
 * game.
 -------------------------------------*/
void playingConnect()
{
	preGame();
	createEmptyBoard();

	while(game_state == 1)
	{
		printBoard();
		playRound(currPlayer);
	}
	endGame(currPlayer);
}

/*-------------------------------------
 * main
 * runs the game, until user wants to
 * quit.
 -------------------------------------*/
int main()
{
	char play = ' ';

	while (play != 'q')
	{
		playingConnect();
		printf("If you would like to play again, press any key to continue, or 'q' to quit.");
		fflush(stdin);
		scanf("%c", &play);
	}
}
