/*
 * cardtest2.c
 * Based on provided cardtest4.c
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "myAssert.h"
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main()
{
	int i;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int handPos;
	int bonus = 0;
	int newCards, discardedFromHand, discardedFromDeck;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// Get the current player to work on
	thisPlayer = G.whoseTurn;

	// ----------- TEST 1: +2 Treasure cards from the bottom of deck --------------
	printf("\nTEST 1: +2 Treasure cards from the bottom of the deck\n");

	/************************************************************
	 * Set cards to desired state
	 * Hand: 1 Adventurer
	 * Deck: 1 Copper, 1 Silver, 3 Minion
	 * Discard: Empty
	 ************************************************************/
	G.hand[thisPlayer][0] = adventurer;
	G.handCount[thisPlayer] = 1;

	G.deckCount[thisPlayer] = 0;
	for(i = 0; i < 5; i++)
	{
		if(i < 1)
		{
			G.deck[thisPlayer][i] = copper;
		}
		else if(i < 2)
		{
			G.deck[thisPlayer][i] = silver;
		}
		else
		{
			G.deck[thisPlayer][i] = minion;
		}

		G.deckCount[thisPlayer]++;
	}

	G.discardCount[thisPlayer] = 0;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// Play the card
	handPos = 0;
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);

	// Set expectations
	newCards = 2; // Drew +2 new cards to hand from deck
	discardedFromHand = 1; // Discarded adventurer itself
	discardedFromDeck = 3; // Discarded the 3 Minions in the way of the treasure (cuthroat!)

	// Print the results
	printf("Hand Count: %d [Expect %d]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discardedFromHand);
	printf("Deck Count: %d [Expect %d]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards - discardedFromDeck);
	printf("Discard Count: %d [Expect %d]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discardedFromHand + discardedFromDeck);

	// Assert if test passed
	if(myAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discardedFromHand, eq, 0)
		&& myAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards - discardedFromDeck, eq, 0)
		&& myAssert(testG.discardCount[thisPlayer], G.deckCount[thisPlayer] + discardedFromHand + discardedFromDeck, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}

	// ----------- TEST 2: +2 Treasure cards from the middle of a deck with extra treasure --------------
	printf("\nTEST 2: +2 Treasure cards from the middle of a deck with extra treasure\n");

	/************************************************************
	 * Set cards to desired state
	 * Hand: 1 Adventurer
	 * Deck: 1 Copper, 1 Silver, 1 Gold, 3 Minion
	 * Discard: Empty
	 ************************************************************/
	G.hand[thisPlayer][0] = adventurer;
	G.handCount[thisPlayer] = 1;

	G.deckCount[thisPlayer] = 0;
	for(i = 0; i < 6; i++)
	{
		if(i < 1)
		{
			G.deck[thisPlayer][i] = copper;
		}
		else if(i < 2)
		{
			G.deck[thisPlayer][i] = silver;
		}
		else if(i < 3)
		{
			G.deck[thisPlayer][i] = gold;
		}
		else
		{
			G.deck[thisPlayer][i] = minion;
		}

		G.deckCount[thisPlayer]++;
	}

	G.discardCount[thisPlayer] = 0;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// Play the card
	handPos = 0;
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);

	// Set expectations
	newCards = 2; // Drew +2 new cards to hand from deck
	discardedFromHand = 1; // Discarded adventurer itself
	discardedFromDeck = 3; // Discarded the 3 Minions in the way of the treasure (cuthroat!)

	// Print the results
	printf("Hand Count: %d [Expect %d]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discardedFromHand);
	printf("Deck Count: %d [Expect %d]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards - discardedFromDeck);
	printf("Discard Count: %d [Expect %d]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discardedFromHand + discardedFromDeck);

	// Assert if test passed
	if(myAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discardedFromHand, eq, 0)
		&& myAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards - discardedFromDeck, eq, 0)
		&& myAssert(testG.discardCount[thisPlayer], G.deckCount[thisPlayer] + discardedFromHand + discardedFromDeck, eq, 0))
	{
		printf("TEST PASSED\n\n");
	}
	else
	{
		printf("TEST FAILED\n\n");
	}

	return 0;
}

