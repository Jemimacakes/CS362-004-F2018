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

#define TESTCARD "remodel"

int main()
{
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int handPos;
	int bonus = 0;
	int gainedToDiscard, discarded, trashed, actualReturn, expectedReturn;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// Get the current player to work on
	thisPlayer = G.whoseTurn;

	// ----------- TEST 1: Remodel a feast into an adventurer --------------
	printf("\nTEST 1: Remodel a feast into an adventurer\n");

	/************************************************************
	 * Set cards to desired state
	 * Hand: 1 Remodel, 1 Feast
	 * Deck: Empty
	 * Discard: Empty
	 ************************************************************/
	G.hand[thisPlayer][0] = remodel;
	G.hand[thisPlayer][1] = feast; // (Cost 4)
	G.handCount[thisPlayer] = 2;
	
	G.deckCount[thisPlayer] = 0;
	
	G.discardCount[thisPlayer] = 0;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// Play the card
	handPos = 0; // Remodel in space 0
	choice1 = 1; // Feast to trash in space 1
	choice2 = adventurer; // Ask for an adventurer (Cost 6)
	cardEffect(remodel, choice1, choice2, choice3, &testG, handPos, &bonus);

	// Set expectations
	gainedToDiscard = 1; // +1 Adventurer from supply to discard
	discarded = 1; // Discarded Remodel itself
	trashed = 1; // Feast is trashed to it completely leaves all decks

	// Print the results
	printf("Hand Count: %d [Expect %d]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded - trashed);
	printf("Discard Count: %d [Expect %d]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + gainedToDiscard + discarded);
	printf("Adventurer Supply Count: %d [Expect %d]\n", testG.supplyCount[adventurer], G.supplyCount[adventurer] - gainedToDiscard);

	// Assert if test passed
	if(myAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded - trashed, eq, 0)
		&& myAssert(testG.discardCount[thisPlayer], G.deckCount[thisPlayer] + gainedToDiscard + discarded, eq, 0)
		&& myAssert(testG.supplyCount[adventurer], G.supplyCount[adventurer] - gainedToDiscard, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}

	// ----------- TEST 2: Remodel an estate into a duchy --------------
	printf("\nTEST 2: Remodel an estate into a duchy\n");

	/************************************************************
	 * Set cards to desired state
	 * Hand: 1 Remodel, 1 Estate
	 * Deck: Empty
	 * Discard: Empty
	 ************************************************************/
	G.hand[thisPlayer][0] = remodel;
	G.hand[thisPlayer][1] = estate; // (Cost 2)
	G.handCount[thisPlayer] = 2;
	
	G.deckCount[thisPlayer] = 0;
	
	G.discardCount[thisPlayer] = 0;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// Play the card
	handPos = 0; // Remodel in space 0
	choice1 = 1; // Estate to trash in space 1
	choice2 = duchy; // Ask for a duchy (Cost 5)
	actualReturn = cardEffect(remodel, choice1, choice2, choice3, &testG, handPos, &bonus);

	// Set expectations
	gainedToDiscard = 0; // No cards should be gained
	discarded = 0; // No cards should be discarded
	trashed = 0; // No cards should be trashed
	expectedReturn = -1; // cardEffect() function should return -1

	// Print the results
	printf("Hand Count: %d [Expect %d]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded - trashed);
	printf("Discard Count: %d [Expect %d]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + gainedToDiscard + discarded);
	printf("Adventurer Supply Count: %d [Expect %d]\n", testG.supplyCount[duchy], G.supplyCount[duchy] - gainedToDiscard);
	printf("cardEffect() Return Value: %d [Expect %d]\n", actualReturn, expectedReturn);

	// Assert if test passed
	if(myAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded - trashed, eq, 0)
		&& myAssert(testG.discardCount[thisPlayer], G.deckCount[thisPlayer] + gainedToDiscard + discarded, eq, 0)
		&& myAssert(testG.supplyCount[adventurer], G.supplyCount[adventurer] - gainedToDiscard, eq, 0)
		&& myAssert(actualReturn, expectedReturn, eq, 0))
	{
		printf("TEST PASSED\n\n");
	}
	else
	{
		printf("TEST FAILED\n\n");
	}
	return 0;
}

