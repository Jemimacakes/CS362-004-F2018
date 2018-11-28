/*
 * randomtestadventurer.c
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

#define TESTCARD "adventurer"
#define NUMTESTS 1000000

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
	int numPlayedCard, numTreasure; // Deck requirements
	int seed = 1000;
	int choice1, choice2, choice3, handPos, bonus;
	int playedCardPos;
	int drawnToHand, discardedFromHand, discardedFromDeck;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
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
				if(randomCard == adventurer)
				{
					numPlayedCard++;
					playedCardPos = i;
				}
			}
		}while(numPlayedCard < 1); // Loop until there are enough of the tested card

		// Fill random player's deck and discard piles with a random number of random cards
		numTreasure = 0;
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
					if(randomCard == copper || randomCard == silver || randomCard == gold)
					{
						numTreasure++;
					}
				}
				else
				{
					G.discard[randomPlayer][G.discardCount[randomPlayer]] = randomCard;
					G.discardCount[randomPlayer]++;
				}
			}
		}while(numTreasure < 2); // Loop until there is enough treasure cards in the deck

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		// Play the card
		choice1 = 0;
		choice2 = 0;
		choice3 = 0;
		handPos = playedCardPos;
		bonus = 0;
		cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);

		// Set expectations
		drawnToHand = 2; // Drew +2 new cards to hand from deck
		discardedFromHand = 1; // Discarded adventurer itself

		// Count all the cards at the end of the deck that are not treasure until 2 treasure is found
		numTreasure = 0;
		discardedFromDeck = 0;
		for(i = G.deckCount[randomPlayer] - 1; i >= 0; i--)
		{
			if(G.deck[randomPlayer][i] == copper || G.deck[randomPlayer][i] == silver || G.deck[randomPlayer][i] == gold)
			{
				numTreasure++;

				if(numTreasure >= 2)
				{
					break;
				}
			}
			else
			{
				discardedFromDeck++;
			}
		}

		// Print the results
		printf("Hand Count: %d [Expect %d]\n", testG.handCount[randomPlayer], G.handCount[randomPlayer] + drawnToHand - discardedFromHand);
		printf("Deck Count: %d [Expect %d]\n", 	testG.deckCount[randomPlayer], G.deckCount[randomPlayer] - drawnToHand - discardedFromDeck);
		printf("Discard Count: %d [Expect %d]\n", 	testG.discardCount[randomPlayer], G.discardCount[randomPlayer] + discardedFromHand + discardedFromDeck);


		// Assert if test passed
		if(myAssert(testG.handCount[randomPlayer], G.handCount[randomPlayer] + drawnToHand - discardedFromHand, eq, 0)
			&& myAssert(testG.deckCount[randomPlayer], G.deckCount[randomPlayer] - drawnToHand - discardedFromDeck, eq, 0)
			&& myAssert(testG.discardCount[randomPlayer], G.discardCount[randomPlayer] + discardedFromHand + discardedFromDeck, eq, 0))
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
