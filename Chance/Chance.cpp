// Chance.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

int take_wager(int available_credits, int previous_wager)
{
	int wager;
	int total_wager;

	printf("How many of your %d credits would you like to wager? ", available_credits);
	scanf_s("%d", &wager);
	if (wager < 1) 
	{
		printf("Must be positive number...");
		return -1;
	}
	total_wager = previous_wager + wager;
	if (total_wager > available_credits)
	{
		printf("Your total wager of %d is more than you have!\n", total_wager);
		printf("Your only have %d available credits!\n", available_credits);
		return -1;
	}

	return wager;
}

int print_cards(char *message, char *cards, int user_pick)
{
	int i;
	printf("\n\t*** %s ***\n", message);
	printf("Cards:\t|%c|\t|%c|\t|%c|\n\t", cards[0], cards[1], cards[2]);
	if (user_pick < 0) printf(" 1\t 2 \t 3\n");
	else
	{
		for (i = 0; i < user_pick; ++i) printf("\t");
		printf(" ^--your pick\n");
	}
	return 3;
}

int find_the_ace(int credits)
{
	int i = 0;
	int ace = rand() % 3;
	int total_wager;

	int invalid_choice = 1;
	int pick = -1;
	int wager_one = -1;
	int wager_two = -1;

	char choice_two = '\n';
	char cards[3] = { 'X','X','X' };

	printf("***FIND-THE-ACE***\n");

	if (credits <= 0)
	{
		printf("You do not have any credits to wager!");
		return -1;
	}

	while (wager_one == -1) wager_one = take_wager(credits, 0);

	print_cards("Dealing cards", cards, -1);
	while (pick < 1 || pick > 3)
	{
		printf("Select a card: 1, 2 or 3 ");
		scanf_s("%d", &pick);
	}
	--pick;

	while (i == ace || i == pick) ++i;
	cards[i] = 'Q';

	print_cards("Revealing a queen", cards, pick);

	while (invalid_choice)
	{
		printf("would you like to:\n[c]hange your pick\tot\t[i]ncrease your wager?\n");
		printf("Select c or i :");
		while (choice_two == '\n') scanf_s("%c", &choice_two);
		if (choice_two == 'i')
		{
			invalid_choice = 0;
			while (wager_two < 0) wager_two = take_wager(credits, wager_one);
		}

		if (choice_two == 'c')
		{
			invalid_choice = 0;
			i = 0;
			while (i == pick || cards[i] == 'Q')++i;
			pick = i;
			printf("Your card pick was changed to card %d\n", pick + 1);
		}
		choice_two = '\n';
	}

	for (i = 0; i < 3; ++i)
	{
		if (ace == i) cards[i] = 'A';
		else cards[i] = 'Q';
	}

	print_cards("End Result", cards, pick);
	if (pick == ace)
	{
		printf("You have won %d credits from your first wager\n", wager_one);
		credits += wager_one;
		if (wager_two > 0)
		{
			printf("and additional %d credits from your second wager!\n", wager_two);
			credits += wager_two;
		}
	}
	else
	{
		printf("You have lost %d credits from your first wager\n", wager_one);
		credits -= wager_one;
		if (wager_two > 0)
		{
			printf("and additional %d credits from your second wager!\n", wager_two);
			credits -= wager_two;
		}
	}
	return credits;
}

bool playAgain()
{
	printf("Would you like to play again? y\n ");
	char choice;
	while (true)
	{
	scanf_s("%c", &choice);
	if (choice == 'n') return false;
	if (choice == 'y') return true;
	}
}

int main()
{
	int credits = 100;
	srand(time(0));
	do
	{
		credits = find_the_ace(credits);
	} while (playAgain());
	return 0;
}