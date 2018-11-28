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

#define TESTCARD "steward"

int main()
{
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int handPos;
	int bonus = 0;
	int drawnToHand, discarded, gainedCoins, trashed;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// Get the current player to work on
	thisPlayer = G.whoseTurn;

	// ----------- TEST 1: Choose +2 cards --------------
	printf("\nTEST 1: Choose +2 cards\n");

	/************************************************************
	 * Set cards to desired state
	 * Hand: 1 Steward
	 * Deck: 1 Copper, 1 Silver, 1 Gold
	 * Discard: Empty
	 ************************************************************/
	G.hand[thisPlayer][0] = steward;
	G.handCount[thisPlayer] = 1;

	G.deck[thisPlayer][0] = copper;
	G.deck[thisPlayer][1] = silver;
	G.deck[thisPlayer][2] = gold;
	G.deckCount[thisPlayer] = 3;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// Play the card
	handPos = 0; // Steward in space 0
	choice1 = 1; // Choose +2 cards option
	choice2 = 0; // Nothing to trash
	choice3 = 0; // Nothing to trash
	cardEffect(steward, choice1, choice2, choice3, &testG, handPos, &bonus);

	// Set expectations
	drawnToHand = 2; // +2 cards from deck to ha
	discarded = 1; // Discarded Steward itself

	// Print the results
	printf("Hand Count: %d [Expect %d]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + drawnToHand - discarded);
	printf("Deck Count: %d [Expect %d]\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - drawnToHand);
	printf("Discard Count: %d [Expect %d]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);

	// Assert if test passed
	if(myAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + drawnToHand - discarded, eq, 0)
		&& myAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - drawnToHand, eq, 0)
		&& myAssert(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}

	// ----------- TEST 2: Choose +2 coins --------------
	printf("\nTEST 2: Choose +2 coins\n");

	/************************************************************
	 * Set cards to desired state
	 * Hand: 1 Steward
	 * Deck: Empty
	 * Discard: Empty
	 ************************************************************/
	G.hand[thisPlayer][0] = steward;
	G.handCount[thisPlayer] = 1;

	G.deckCount[thisPlayer] = 0;

	// Delete any leftover coins from initial draw
	G.coins = 0;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// Play the card
	handPos = 0; // Steward in space 0
	choice1 = 2; // Choose +2 coins option
	choice2 = 0; // Nothing to trash
	choice3 = 0; // Nothing to trash
	cardEffect(steward, choice1, choice2, choice3, &testG, handPos, &bonus);

	// Set expectations
	discarded = 1; // Discarded Steward itself
	gainedCoins = 2; // +2 cards from deck to ha
	
	// Print the results	
	printf("Discard Count: %d [Expect %d]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
	printf("Coin Count: %d [Expect %d]\n", testG.coins, G.coins + gainedCoins);

	// Assert if test passed
	if(myAssert(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded, eq, 0)
		&& myAssert(testG.coins, G.coins + gainedCoins, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}

	// ----------- TEST 3: Trash 2 cards, lower array value first --------------
	printf("\nTEST 3: Trash 2 cards, lower array value first\n");

	/************************************************************
	 * Set cards to desired state
	 * Hand: 1 Steward, 1 Adventurer, 1 Embargo, 1 Village
	 * Deck: Empty
	 * Discard: Empty
	 ************************************************************/
	G.hand[thisPlayer][0] = steward;
	G.hand[thisPlayer][1] = adventurer;
	G.hand[thisPlayer][2] = embargo;
	G.hand[thisPlayer][3] = village;
	G.handCount[thisPlayer] = 4;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// Play the card
	handPos = 0; // Steward in space 0
	choice1 = 0; // Choose trash 2 cards option
	choice2 = 1; // Trash space 1 (Adventurer)
	choice3 = 3; // Trash space 3 (Village)
	cardEffect(steward, choice1, choice2, choice3, &testG, handPos, &bonus);

	// Set expectations
	discarded = 1; // Discarded Steward itself
	trashed = 2; // Trashed 2 cards, leaving embargo behind

	// Print the results
	printf("Hand Count: %d [Expect %d]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded - trashed);
	printf("Discard Count: %d [Expect %d]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
	printf("Remaining Card ID: %d [Expect %d]\n", testG.hand[thisPlayer][0], embargo);

	// Assert if test passed
	if(myAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded - trashed, eq, 0)
		&& myAssert(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded, eq, 0)
		&& myAssert(testG.hand[thisPlayer][0], embargo, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}

	// ----------- TEST 4: Trash 2 cards, higher array value first --------------
	printf("\nTEST 4: Trash 2 cards, higher array value first\n");

	/************************************************************
	 * Set cards to desired state
	 * Hand: 1 Steward, 1 Adventurer, 1 Embargo, 1 Village
	 * Deck: Empty
	 * Discard: Empty
	 ************************************************************/
	G.hand[thisPlayer][0] = steward;
	G.hand[thisPlayer][1] = adventurer;
	G.hand[thisPlayer][2] = embargo;
	G.hand[thisPlayer][3] = village;
	G.handCount[thisPlayer] = 4;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// Play the card
	handPos = 0; // Steward in space 0
	choice1 = 0; // Choose trash 2 cards option
	choice2 = 2; // Trash space 2 (Embargo)
	choice3 = 1; // Trash space 1 (Adventurer)
	cardEffect(steward, choice1, choice2, choice3, &testG, handPos, &bonus);

	// Set expectations
	discarded = 1; // Discarded Steward itself
	trashed = 2; // Trashed 2 cards, leaving village behind

	// Print the results
	printf("Hand Count: %d [Expect %d]\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded - trashed);
	printf("Discard Count: %d [Expect %d]\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
	printf("Remaining Card ID: %d [Expect %d]\n", testG.hand[thisPlayer][0], village);

	// Assert if test passed
	if(myAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded - trashed, eq, 0)
		&& myAssert(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded, eq, 0)
		&& myAssert(testG.hand[thisPlayer][0], embargo, eq, 0))
	{
		printf("TEST PASSED\n\n");
	}
	else
	{
		printf("TEST FAILED\n\n");
	}

	return 0;
}

