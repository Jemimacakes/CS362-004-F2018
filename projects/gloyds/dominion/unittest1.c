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

#define TESTFUNC "fullDeckCount"

int main()
{
	int i;
	int count;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNC);

	/************************************************************
	 * Set cards to desired state
	 * Hand: 2 Adventurer, 1 Embargo, 2 Village, 2 Sea Hag
	 * Deck: 3 Minion, 2 Embargo, 2 Mine, 3 Sea Hag
	 * Discard: 2 Cutpurse, 3 Village, 2 Mine, 1 Sea Hag
	 ************************************************************/
	G.handCount[G.whoseTurn] = 0;
	for(i = 0; i < 7; i++)
	{
		if(i < 2)
		{
			G.hand[G.whoseTurn][i] = adventurer;
		}
		else if(i < 3)
		{
			G.hand[G.whoseTurn][i] = embargo;
		}
		else if(i < 5)
		{
			G.hand[G.whoseTurn][i] = village;
		}
		else
		{
			G.hand[G.whoseTurn][i] = sea_hag;
		}
		
		G.handCount[G.whoseTurn]++;
	}

	G.deckCount[G.whoseTurn] = 0;
	for(i = 0; i < 10; i++)
	{
		if(i < 3)
		{
			G.deck[G.whoseTurn][i] = minion;
		}
		else if(i < 5)
		{
			G.deck[G.whoseTurn][i] = embargo;
		}
		else if(i < 7)
		{
			G.deck[G.whoseTurn][i] = mine;
		}
		else
		{
			G.deck[G.whoseTurn][i] = sea_hag;
		}
		
		G.deckCount[G.whoseTurn]++;
	}
	
	G.discardCount[G.whoseTurn] = 0;
	for(i = 0; i < 8; i++)
	{
		if(i < 2)
		{
			G.discard[G.whoseTurn][i] = cutpurse;
		}
		else if(i < 5)
		{
			G.discard[G.whoseTurn][i] = village;
		}
		else if(i < 7)
		{
			G.discard[G.whoseTurn][i] = mine;
		}
		else
		{
			G.discard[G.whoseTurn][i] = sea_hag;
		}
	
		G.discardCount[G.whoseTurn]++;
	}
	
	// ----------- TEST 1: Cards located in deck only --------------
	printf("TEST 1: Cards located in deck only\n");
	count = fullDeckCount(G.whoseTurn, adventurer, &G);
	if(myAssert(count, 2, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}

	// ----------- TEST 2: Cards located in hand only --------------
	printf("TEST 2: Cards located in hand only\n");
	count = fullDeckCount(G.whoseTurn, minion, &G);
	if(myAssert(count, 3, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}

	// ----------- TEST 3: Cards located in discard only --------------
	printf("TEST 3: Cards located in discard only\n");
	count = fullDeckCount(G.whoseTurn, cutpurse, &G);
	if(myAssert(count, 2, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}
	
	// ----------- TEST 4: Cards located in both deck and hand --------------
	printf("TEST 4: Cards located in both deck and hand\n");
	count = fullDeckCount(G.whoseTurn, embargo, &G);
	if(myAssert(count, 3, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}
	
	// ----------- TEST 5: Cards located in both deck and discard --------------
	printf("TEST 5: Cards located in both deck and discard\n");
	count = fullDeckCount(G.whoseTurn, mine, &G);
	if(myAssert(count, 4, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}
	
	// ----------- TEST 6: Cards located in both hand and discard --------------
	printf("TEST 6: Cards located in both hand and discard\n");
	count = fullDeckCount(G.whoseTurn, village, &G);
	if(myAssert(count, 5, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}
	
	// ----------- TEST 7: Cards located in all piles --------------
	printf("TEST 7: Cards located in all piles\n");
	count = fullDeckCount(G.whoseTurn, sea_hag, &G);
	if(myAssert(count, 6, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}
}

