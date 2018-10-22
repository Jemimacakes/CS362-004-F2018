/*
 * unittest1.c
 * Based on example cardtest4.c

*/

/*
 * Include the following lines in your makefile:
 *
 * unittest1.c: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "myAssert.h"
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "scoreFor"

int main()
{
	int i;
	int score;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNC);


	/*************************************************************************
	 * Set cards to desired state
	 * Hand: 1 of each curse, estate, duchy, province, great hall, gardens
	 * Deck: 1 of each curse, estate, duchy, province, great hall, gardens
	 * Discard: 1 of each curse, estate, duchy, province, great hall, gardens
	 *************************************************************************/
	for(i = 0; i < 6; i++)
	{
		if(i == 4)
		{
			G.hand[G.whoseTurn][i] = great_hall;
			G.deck[G.whoseTurn][i] = great_hall;
			G.discard[G.whoseTurn][i] = great_hall;
		}
		else if(i == 5)
		{
			G.hand[G.whoseTurn][i] = gardens;
			G.deck[G.whoseTurn][i] = gardens;
			G.discard[G.whoseTurn][i] = gardens;
		}
		else
		{
			G.hand[G.whoseTurn][i] = i;
			G.deck[G.whoseTurn][i] = i;
			G.discard[G.whoseTurn][i] = i;
		}
	}

	// Set card counts to desired state
	G.handCount[G.whoseTurn] = 6;
	G.deckCount[G.whoseTurn] = 6;
	G.discardCount[G.whoseTurn] = 6;

	// ----------- TEST 1: All card scores --------------
	printf("\nTEST 1: All card scores\n");

	// Call scoreFor on current player to get score
	score = scoreFor(G.whoseTurn, &G);

	// Print out test results
	printf("Player Score: %d [Expect 33]\n", score);

	// Assert if test passed
	if(myAssert(score, 33, eq, 0)) 
	{
		printf("TEST PASSED\n\n");
	}
	else
	{
		printf("TEST FAILED\n\n");
	}
}

