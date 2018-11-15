/*
 * randomtestcard2.c
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

#define TESTCARD "treasure_map"
#define NUMTESTS 1000

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

int main()
{
	int i, test;
	int randomNumPlayers, randomNumCards, randomCard, randomPlayer; // Random counts
	int numPlayedCard, numGold; // Deck requirements
	int seed = 1000;
	int choice1, choice2, choice3, handPos, bonus;
	int playedCardPos, returnValue;
	int drawnToDeck, trashedCards, expectedReturnValue;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, treasure_map,
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
		G.whoseTurn = randomPlayer;

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

				// Treasure map special cases
				if(randomCard == treasure_map)
				{
					// 9/10 chance that treasure_maps will be discarded
					if(rand() % 10 > 0)
					{
						G.handCount[randomPlayer]--;
						i--;
					}
					else // Add to played card count and track position of last drawn
					{
						numPlayedCard++;
						playedCardPos = i;
					}
				}
			}
		}while(numPlayedCard < 1); // Loop until there are enough of the tested card

		// Fill random player's deck and discard piles with a random number of random cards
		numGold = 0;
		do
		{
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

					// Add to treasure count if applicable else add to dicarded count for cards "in the way"
					if(randomCard == gold)
					{
						numGold++;
					}
				}
				else
				{
					G.discard[randomPlayer][G.discardCount[randomPlayer]] = randomCard;
					G.discardCount[randomPlayer]++;
				}
			}
		}while(numGold < 4); // Loop until there is enough gold cards in the deck

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		// Play the card
		choice1 = 0;
		choice2 = 0;
		choice3 = 0;
		handPos = playedCardPos;
		bonus = 0;
		returnValue = cardEffect(treasure_map, choice1, choice2, choice3, &testG, handPos, &bonus);

		// Set expectations
		// If there were at least 2 treasure maps
		if(numPlayedCard >= 2)
		{
			drawnToDeck = 4; // Drew +2 new gold cards to hand from supply
			trashedCards = 2; // Trashed both treasure maps
			expectedReturnValue = 1; // Return success
		}
		else
		{
			drawnToDeck = 0; // Dont' draw anything
			trashedCards = 0; // Don't trash anything
			expectedReturnValue = -1; // Return error
		}

		// Print the results
		printf("Number of drawn Treasure Maps: %d\n", numPlayedCard);
		printf("Hand Count: %d [Expect %d]\n", testG.handCount[randomPlayer], G.handCount[randomPlayer] - trashedCards);
		printf("Deck Count: %d [Expect %d]\n", 	testG.deckCount[randomPlayer], G.deckCount[randomPlayer] + drawnToDeck);
		printf("Discard Count: %d [Expect %d]\n", 	testG.discardCount[randomPlayer], G.discardCount[randomPlayer]);
		printf("Gold Supply Count: %d [Expect %d]\n", 	testG.supplyCount[gold], G.supplyCount[gold] - drawnToDeck);
		printf("Return Value: %d [Expect %d]\n", 	returnValue, expectedReturnValue);


		// Assert if test passed
		if(myAssert(testG.handCount[randomPlayer], G.handCount[randomPlayer] - trashedCards, eq, 0)
			&& myAssert(testG.deckCount[randomPlayer], G.deckCount[randomPlayer] + drawnToDeck, eq, 0)
			&& myAssert(testG.discardCount[randomPlayer], G.discardCount[randomPlayer], eq, 0)
			&& myAssert(testG.supplyCount[gold], G.supplyCount[gold] - drawnToDeck, eq, 0)
			&& myAssert(returnValue, expectedReturnValue, eq, 0))
		{
			printf("TEST PASSED\n\n");
		}
		else
		{
			printf("TEST FAILED\n\n");
		}
	}

	return 0;
}
