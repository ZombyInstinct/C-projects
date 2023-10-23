/*
 * game.c
 *
 *  Created on: Sep 10, 2023
 *      Author: Zaki Ilyas
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

void playGuessingGame()
{
	srand(time(0));
	int num = (rand() % 91) + 10;
	float root = sqrt(num);

	printf("%f is the square root of what number?\nYour guess: ", root);

	while (num > 0)
	{
		int guess = getGuess();
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
			num = 0;
		}
	}

}

int main()
{
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

	printf("Bye! Play again soon.");
}
