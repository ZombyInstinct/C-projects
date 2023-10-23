/*
 * guess.c
 *
 *  Created on: Sep 20, 2023
 *      Author: Zaki Ilyas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/*-------------------------------------
 * struct players;
 * this data structure contains player
 * information such as their name and
 * num of guesses.
 -------------------------------------*/
struct players
{
	char playerName[20];
	int numGuesses;
};

//Array of player structs
struct players leadersList[5];

/*-------------------------------------
 * printLeaders()
 * prints the leaderboard nicely
 -------------------------------------*/
void printLeaders()
{
	printf("Leaderboard:\n");
	printf("--------------------\n");
	for (int i = 0; i < 5; i++)
	{
		if (leadersList[i].numGuesses > 0)
		printf("%s made %d guess(es).\n",leadersList[i].playerName, leadersList[i].numGuesses);
	}
	printf("--------------------\n");
}


/*-------------------------------------
 * fillLeadersList()
 * takes a file input and reads for
 * name and score.
 -------------------------------------*/
void fillLeadersList(const char* filename)
{
	//opens file
	FILE* fp = NULL;
	if ( (fp = fopen(filename, "r+")) )
	{
		//variables for player gathering
		int index = 0;
		int data = 0;
		int playerIndex = 0;
		char a;
		char tempName[20] = "";
		char tempGuess[2] = "";

		//loops through each character to find name and score
		//using fgets() may have been more efficient here
		while ((a = fgetc(fp)) != EOF)
		{
			//printf("%c\n", a);
			//printf("%s\n", tempName);
			if (a != '~' && data == 0)
			{
				tempName[index] = a;
				index++;
			}
			else if (a == '~' && data == 0)
			{
				index = 0;
				data = 1;
				strcpy(leadersList[playerIndex].playerName, tempName);
				memset(tempName,0,sizeof(tempName));
			}

			if (data == 1 && a != '~' && a != '\n')
			{
				tempGuess[index] = a;
				index++;
			}
			else if (data == 1 && a == '\n')
			{
				index = 0;
				data = 0;
				leadersList[playerIndex].numGuesses = atoi(tempGuess);
				strcpy(tempGuess, "");
				playerIndex++;
			}
		}
	}
	if (fp != NULL)
	{
		fclose(fp);
		printf("Previous scores were found; the leaderboard has updated.\n\n");
		printLeaders();
	}
}

/*-------------------------------------
 * getGuess()
 * returns a valid number from the user
 -------------------------------------*/
int getGuess()
{
	int guess;
	scanf("%d", &guess);
	while (guess < 10 || guess > 100)
	{
		printf("Please input a valid answer (must be from 10-100).\n ");
		fflush(stdin);
		scanf("%d", &guess);
	}
	return guess;
}

/*-------------------------------------
 * playGuessingGame()
 * uses time to generate random seed
 * plays out one round of the game
 -------------------------------------*/
void playGuessingGame()
{
	char name[20];
	printf("Please enter your name to begin: ");
	fflush(stdin);
	//name is limited to one word
	scanf("%s", &name);

	srand(time(0));
	int num = (rand() % 91) + 10;
	float root = sqrt(num);

	printf("%f is the square root of what number?\nYour guess: ", root);

	int numGuesses = 0;
	while (num > 0)
	{
		int guess = getGuess();
		numGuesses ++;
		if (guess > num)
		{
			printf("Too high, try again: ");
		}
		else if (guess < num)
		{
			printf("Too low, try again: ");
		}
		else
		{
			printf("YOU GOT IT!!\n");
			printf("You made %d guess(es).\n", numGuesses);
			num = 0;
		}
	}

	//creates the player data
	struct players p1;
	strcpy(p1.playerName, name);
	p1.numGuesses = numGuesses;

	//orders the leaders in the array
	for (int i = 0; i < 5; i++)
	{
		int guess = leadersList[i].numGuesses;
		if (guess >= p1.numGuesses || guess == NULL)
		{
			for (int j = i; j < 5; j++)
			{
				struct players temp = leadersList[j];
				leadersList[j] = p1;
				p1 = temp;
			}
			break;
		}
	}

	printLeaders();
}

/*-------------------------------------
 * fileReaeder()
 * reads the array and writes them into
 * a file if it exists, a new file is
 * created is made if it does not exist.
 -------------------------------------*/
int fileReader(const char* filename)
{
	FILE* fp = NULL;
	if ((fp = fopen(filename, "r+")))
	{

	}
	else
	{
		fp = fopen(filename, "w");
	}


	if (fp == NULL)
	{
		fprintf(stderr, "Cannot open &s.\n", filename);
		exit(1);
	}

	for (int i = 0; i < 5; i++)
	{
		if (leadersList[i].numGuesses != 0)
		{
			char buffer[50];
			snprintf(buffer, sizeof(buffer), "%s~%d\n", leadersList[i].playerName, leadersList[i].numGuesses);

			fputs(buffer, fp);
		}
	}

	printf("\n");

	fclose(fp);
	return 0;
}

/*-------------------------------------
 * main()
 * prompts user
 * plays games
 * prompts quit
 -------------------------------------*/
int main()
{

	fillLeadersList("file1.txt");

	printf("Welcome! Press any key to continue or 'q' to quit\n");

	char myC;
	scanf("%c", &myC);

	while (myC != 'q')
	{

		playGuessingGame();
		printf("Press any key to continue or 'q' to quit.\n");

		fflush(stdin);
		scanf("%c", &myC);
	}

	fileReader("file1.txt");
	printf("Bye! Play again soon.");
}
