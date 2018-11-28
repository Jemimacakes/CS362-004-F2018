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

#define TESTFUNC "gainCard"

int main()
{
	int ret, oldCount;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNC);

	// Empty Card Piles
	G.handCount[G.whoseTurn] = 0;
	G.deckCount[G.whoseTurn] = 0;
	G.discardCount[G.whoseTurn] = 0;

	// ----------- TEST 1: Draw an adventurer to hand --------------
	printf("\nTEST 1: Draw an adventurer to hand\n");

	// Capture old supplyCount for adventurer
	oldCount = G.supplyCount[adventurer];

	// Call gainCard to draw an adventurer to 2 (hand)
	gainCard(adventurer, &G, 2, G.whoseTurn);

	// Print test values
	printf("New Hand Count: %d [Expect 1]\nCard Type: %d [Expect %d]\nNew supplyCount: %d [Expect %d]\n", 
			 G.handCount[G.whoseTurn], G.hand[G.whoseTurn][G.handCount[G.whoseTurn] - 1],
			 adventurer, G.supplyCount[adventurer], oldCount - 1);

	// Assert if test passed
	if(myAssert(G.hand[G.whoseTurn][G.deckCount[G.whoseTurn]], 7, eq, 0) 
		&& myAssert(G.handCount[G.whoseTurn], 1, eq, 0)
		&& myAssert(G.supplyCount[adventurer], oldCount - 1, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}
	
	// ----------- TEST 2: Draw a minion to deck --------------
	printf("\nTEST 2: Draw a minion to deck\n");

	// Capture old supplyCount for adventurer
	oldCount = G.supplyCount[minion];

	// Call gainCard to draw a minion to 1 (deck)
	gainCard(minion, &G, 1, G.whoseTurn);

	// Print test values
	printf("New Deck Count: %d [Expect 1]\nCard Type: %d [Expect %d]\nNew supplyCount: %d [Expect %d]\n", 
			 G.deckCount[G.whoseTurn], G.deck[G.whoseTurn][G.deckCount[G.whoseTurn] - 1],
			 minion, G.supplyCount[minion], oldCount - 1);

	// Assert if test passed
	if(myAssert(G.deck[G.whoseTurn][G.deckCount[G.whoseTurn] - 1], minion, eq, 0) 
		&& myAssert(G.deckCount[G.whoseTurn], 1, eq, 0)
		&& myAssert(G.supplyCount[minion], oldCount - 1, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}

	// ----------- TEST 3: Draw a tribute to discard --------------
	printf("\nTEST 3: Draw a tribute to discard\n");

	// Capture old supplyCount for adventurer
	oldCount = G.supplyCount[tribute];

	// Call gainCard to draw a tribute to 0 (discard)
	gainCard(tribute, &G, 0, G.whoseTurn);

	// Print test values
	printf("New Deck Count: %d [Expect 1]\nCard Type: %d [Expect %d]\nNew supplyCount: %d [Expect %d]\n", 
			 G.discardCount[G.whoseTurn], G.discard[G.whoseTurn][G.discardCount[G.whoseTurn] - 1],
			 tribute, G.supplyCount[tribute], oldCount - 1);

	// Assert if test passed
	if(myAssert(G.discard[G.whoseTurn][G.discardCount[G.whoseTurn] - 1], tribute, eq, 0) 
		&& myAssert(G.discardCount[G.whoseTurn], 1, eq, 0)
		&& myAssert(G.supplyCount[tribute], oldCount - 1, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}
	
	// ----------- TEST 4: Draw an adventurer to deck --------------
	printf("\nTEST 4: Draw an adventurer to deck\n");

	// Capture old supplyCount for adventurer
	oldCount = G.supplyCount[adventurer];

	// Call gainCard to draw an adventurer to 1 (deck)
	gainCard(adventurer, &G, 1, G.whoseTurn);

	// Print test values
	printf("New Deck Count: %d [Expect 2]\nCard Type: %d [Expect %d]\nNew supplyCount: %d [Expect %d]\n", 
			 G.deckCount[G.whoseTurn], G.deck[G.whoseTurn][G.deckCount[G.whoseTurn] - 1],
			 adventurer, G.supplyCount[adventurer], oldCount - 1);

	// Assert if test passed
	if(myAssert(G.deck[G.whoseTurn][G.deckCount[G.whoseTurn] - 1], adventurer, eq, 0) 
		&& myAssert(G.deckCount[G.whoseTurn], 2, eq, 0)
		&& myAssert(G.supplyCount[adventurer], oldCount - 1, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}

	// ----------- TEST 5: Draw an unused card to hand --------------
	printf("\nTEST 5: Draw an unused card to hand\n");

	// Call gainCard to attempt to draw a salvager  to 2 (hand)
	ret = gainCard(salvager, &G, 2, G.whoseTurn);

	// Print test values
	printf("gainCard Return Value: %d [Expect -1]\n", ret); 

	// Assert if test passed
	if(myAssert(ret, -1, eq, 0)) 
	{
		printf("TEST PASSED\n\n");
	}
	else
	{
		printf("TEST FAILED\n\n");
	}
}

