/*
 * cardtest1.c
 * Based on provided cardtest4.c
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "myAssert.h"
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main()
{

	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int handPos;
	int bonus = 0;
	int newCards, discarded;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
					 sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// Get the current player to work on
	thisPlayer = G.whoseTurn;

	// Give the player the smithy card
	G.hand[thisPlayer][G.handCount[thisPlayer]] = smithy;
	G.handCount[thisPlayer]++;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	// Play the card
	handPos = testG.handCount[thisPlayer] - 1;
	cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);

	// Set expectations
	newCards = 3; // Drew +3 new cards
	discarded = 1; // Discarded smithy itself
	
	// ----------- TEST 1: +3 cards in hand --------------
	printf("\nTEST 1: +3 cards in hand\n");

	// Print the results
	printf("Hand Count: %d [Expect %d]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("Deck Count: %d [Expect %d]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	printf("Discard Count: %d [Expect %d]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
	
	// Assert if test passed
	if(myAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded, eq, 0)
		&& myAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards, eq, 0)
		&& myAssert(testG.discardCount[thisPlayer], G.deckCount[thisPlayer] + discarded, eq, 0))
	{
		printf("TEST PASSED\n\n");
	}
	else
	{
		printf("TEST FAILED\n\n");
	}

	return 0;
}

