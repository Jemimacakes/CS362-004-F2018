/*
 * randomtestcard1.c
 * Based on provided cardtest4.c
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "myAssert.h"
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "steward"
#define NUMTESTS 10000

int chooseRandomNumPlayers()
{
	// Return a random number of acceptable players
	return (rand() % (MAX_PLAYERS - 1)) + 2;
}

int chooseRandomPlayer(int numPlayers)
{
	// Return a random acceptable player
	return (rand() % numPlayers);
}

int chooseRandomNumCards(int maxNumber)
{
	// Return a random acceptable number of cards
	return (rand() % maxNumber) + 1;
}

int chooseRandomCard(int cards[])
{
	// Return a random valid card from any supplied deck with equal chance
	int cardIndex = rand() % 17;
	if(cardIndex > gold)
	{
		return cards[cardIndex - adventurer];
	}
	else
		return cardIndex;
}

int determineReplacement(struct gameState G, int currentPlayer, int cardPos, int offset)
{
	if(cardPos >= G.handCount[currentPlayer] - offset - 1)
	{
		return -1;
	}
	else
	{
		return G.hand[currentPlayer][G.handCount[currentPlayer] - offset - 1];
	}
}

int main()
{
	int i, test;
	int randomNumPlayers, randomNumCards, randomCard, randomPlayer; // Random counts
	int numPlayedCard; // Deck requirements
	int seed = 1000;
	int choice1, choice2, choice3, handPos, bonus;
	int playedCardPos;
	int drawnToHand, discardedFromHand, newCoins, trashedCards, choice2Replacement, choice3Replacement;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, steward,
		sea_hag, tribute, smithy, council_room};

	// Seed random number generator
	srand(time(NULL));

	randomNumPlayers = chooseRandomNumPlayers();

	// initialize a game state and player cards
	initializeGame(randomNumPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n\n", TESTCARD);

	for(test = 0; test < NUMTESTS; test++)
	{
		printf("Test Number: %d\n", test);

		// Choose a random player
		randomPlayer = chooseRandomPlayer(randomNumPlayers);
		G.whoseTurn=randomPlayer;

		// Fill random player's hand with random number of random cards
		numPlayedCard = 0;
		do
		{
			// Clear the hand
			G.handCount[randomPlayer] = 0;

			// Choose a random number of cards to generate, and do so
			randomNumCards = chooseRandomNumCards(MAX_HAND - 2);
			for(i = 0; i < randomNumCards; i++)
			{
				// Generate random card and add to hand
				randomCard = chooseRandomCard(k);
				G.hand[randomPlayer][i] = randomCard;
				G.handCount[randomPlayer]++;

				// Add to tested card count if applicable
				if(randomCard == steward)
				{
					numPlayedCard++;
					playedCardPos = i;
				}
			}
		}while(numPlayedCard < 1); // Loop until there are enough of the tested card

		// Fill random player's deck and discard piles with a random number of random cards
		// Clear both piles
		G.deckCount[randomPlayer] = 0;
		G.discardCount[randomPlayer] = 0;

		// Choose a random number of cards to generate, and do so
		randomNumCards = chooseRandomNumCards(MAX_DECK);
		for(i = 0; i < randomNumCards; i++)
		{
			// Generate random card, and add it to a random pile
			randomCard = chooseRandomCard(k);
			if(rand() % 2)
			{
				G.deck[randomPlayer][G.deckCount[randomPlayer]] = randomCard;
				G.deckCount[randomPlayer]++;
			}
			else
			{
				G.discard[randomPlayer][G.discardCount[randomPlayer]] = randomCard;
				G.discardCount[randomPlayer]++;
			}
		}

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		// Play the card
		choice1 = rand() % 3;
		choice2 = G.handCount[randomPlayer] == 0 ? 0 : rand() % G.handCount[randomPlayer];
		choice3 = G.handCount[randomPlayer] == 0 ? 0 : rand() % G.handCount[randomPlayer];
		handPos = playedCardPos;
		bonus = 0;
		cardEffect(steward, choice1, choice2, choice3, &testG, handPos, &bonus);

		if(choice1 == 1)
		{
			// Set expectations
			drawnToHand = 2; // Drew +2 new cards to hand from deck
			discardedFromHand = 1; // Discarded steward itself
			newCoins = 0;

			// Print the results
			printf("Hand Count: %d [Expect %d]\n", testG.handCount[randomPlayer], G.handCount[randomPlayer] + drawnToHand - discardedFromHand);
			printf("Deck Count: %d [Expect %d]\n", 	testG.deckCount[randomPlayer], G.deckCount[randomPlayer] - drawnToHand);
			printf("Discard Count: %d [Expect %d]\n", 	testG.discardCount[randomPlayer], G.discardCount[randomPlayer] + discardedFromHand);
			printf("Coin Count: %d [Expect %d]\n", testG.coins, G.coins + newCoins);

			// Assert if test passed
			if(myAssert(testG.handCount[randomPlayer], G.handCount[randomPlayer] + drawnToHand - discardedFromHand, eq, 0)
				&& myAssert(testG.deckCount[randomPlayer], G.deckCount[randomPlayer] - drawnToHand, eq, 0)
				&& myAssert(testG.discardCount[randomPlayer], G.discardCount[randomPlayer] + discardedFromHand, eq, 0)
				&& myAssert(testG.coins, G.coins + newCoins, eq, 0))
			{
				printf("TEST PASSED\n\n");
			}
			else
			{
				printf("TEST FAILED\n\n");
			}
		}
		else if(choice1 == 2)
		{
			// Set expectations
			drawnToHand = 0; // Draw no new cards
			discardedFromHand = 1; // Discard steward itself
			newCoins = 2; // Gain +2 coins

			// Print the results
			printf("Hand Count: %d [Expect %d]\n", testG.handCount[randomPlayer], G.handCount[randomPlayer] + drawnToHand - discardedFromHand);
			printf("Deck Count: %d [Expect %d]\n", 	testG.deckCount[randomPlayer], G.deckCount[randomPlayer] - drawnToHand);
			printf("Discard Count: %d [Expect %d]\n", 	testG.discardCount[randomPlayer], G.discardCount[randomPlayer] + discardedFromHand);
			printf("Coin Count: %d [Expect %d]\n", testG.coins, G.coins + newCoins);

			// Assert if test passed
			if(myAssert(testG.handCount[randomPlayer], G.handCount[randomPlayer] + drawnToHand - discardedFromHand, eq, 0)
				&& myAssert(testG.deckCount[randomPlayer], G.deckCount[randomPlayer] - drawnToHand, eq, 0)
				&& myAssert(testG.discardCount[randomPlayer], G.discardCount[randomPlayer] + discardedFromHand, eq, 0)
				&& myAssert(testG.coins, G.coins + newCoins, eq, 0))
			{
				printf("TEST PASSED\n\n");
			}
			else
			{
				printf("TEST FAILED\n\n");
			}
		}
		else
		{
			// Set expectations
			drawnToHand = 0; // Draw no new cards
			discardedFromHand = 1; // Discard steward itself
			newCoins = 0;
			trashedCards = 2; // Trash two cards

			// Determine which cards should replace the removed cards
			choice2Replacement = determineReplacement(G, randomPlayer, choice2, 0);
			choice3Replacement = determineReplacement(G, randomPlayer, choice3, 1);

			// Print the results
			printf("Hand Count: %d [Expect %d]\n", testG.handCount[randomPlayer], G.handCount[randomPlayer] + drawnToHand - discardedFromHand - trashedCards);
			printf("Deck Count: %d [Expect %d]\n", 	testG.deckCount[randomPlayer], G.deckCount[randomPlayer] - drawnToHand);
			printf("Discard Count: %d [Expect %d]\n", 	testG.discardCount[randomPlayer], G.discardCount[randomPlayer] + discardedFromHand);
			printf("Coin Count: %d [Expect %d]\n", testG.coins, G.coins + newCoins);
			printf("Choice2 Replacement: %d [Expect %d]\n", 	choice2 >= G.handCount[randomPlayer] - 1 ? -1 : testG.hand[randomPlayer][choice2],
															choice2Replacement);
			printf("Choice3 Replacement: %d [Expect %d]\n", 	choice3 >= G.handCount[randomPlayer] - 2 ? -1 : testG.hand[randomPlayer][choice3],
															choice3Replacement);

			// Assert if test passed
			if(myAssert(testG.handCount[randomPlayer], G.handCount[randomPlayer] + drawnToHand - discardedFromHand, eq, 0)
				&& myAssert(testG.deckCount[randomPlayer], G.deckCount[randomPlayer] - drawnToHand, eq, 0)
				&& myAssert(testG.discardCount[randomPlayer], G.discardCount[randomPlayer] + discardedFromHand, eq, 0)
				&& myAssert(testG.coins, G.coins + newCoins, eq, 0)
				&& myAssert(choice2 >= G.handCount[randomPlayer] - 1 ? -1 : testG.hand[randomPlayer][choice2], choice2Replacement, eq, 0)
				&& myAssert(choice3 >= G.handCount[randomPlayer] - 2 ? -1 : testG.hand[randomPlayer][choice3], choice3Replacement, eq, 0))
			{
				printf("TEST PASSED\n\n");
			}
			else
			{
				printf("TEST FAILED\n\n");
			}
		}
	}

	return 0;
}
