/*
 * unittest2.c
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

#define TESTFUNC "updateCoins"

int main()
{
	int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNC);

	/************************************************************
	 * Set cards to desired state
	 * Hand: 3 Copper
	 ************************************************************/
	G.handCount[G.whoseTurn] = 0;
	for(i = 0; i < 3; i++)
	{
		G.hand[G.whoseTurn][i] = copper;
		G.handCount[G.whoseTurn]++;
	}

	// ----------- TEST 1: 3 Copper Pieces --------------
	printf("\nTEST 1: 3 Copper Pieces\n");
	updateCoins(G.whoseTurn, &G, 0);
	printf("Updated Coin Value: %d [Expect 3]\n", G.coins);
	if(myAssert(G.coins, 3, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}

	/************************************************************
	 * Set cards to desired state
	 * Hand: 6 Copper, 15 Silver
	 ************************************************************/
	G.handCount[G.whoseTurn] = 0;
	for(i = 0; i < 21; i++)
	{
		if(i < 6)
		{
			G.hand[G.whoseTurn][i] = copper;
		}
		else
		{
			G.hand[G.whoseTurn][i] = silver;
		}

		G.handCount[G.whoseTurn]++;
	}

	// ----------- TEST 2: 6 Copper Pieces, 15 Silver Pieces --------------
	printf("\nTEST 2: 6 Copper Pieces, 15 Silver Pieces\n");
	updateCoins(G.whoseTurn, &G, 0);
	printf("Updated Coin Value: %d [Expect 36]\n", G.coins);
	if(myAssert(G.coins, 36, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}

	/************************************************************
	 * Set cards to desired state
	 * Hand: 1 Copper, 9 Silver, 1 Gold
	 ************************************************************/
	G.handCount[G.whoseTurn] = 0;
	for(i = 0; i < 11; i++)
	{
		if(i < 1)
		{
			G.hand[G.whoseTurn][i] = copper;
		}
		else if(i < 10)
		{
			G.hand[G.whoseTurn][i] = silver;
		}
		else
		{
			G.hand[G.whoseTurn][i] = gold;
		}

		G.handCount[G.whoseTurn]++;
	}

	// ----------- TEST 3: 1 Copper Pieces, 9 Silver Pieces, 1 Gold Piece --------------
	printf("\nTEST 3: 1 Copper Pieces, 9 Silver Pieces, 1 Gold Piece\n");
	updateCoins(G.whoseTurn, &G, 0);
	printf("Updated Coin Value: %d [Expect 22]\n", G.coins);
	if(myAssert(G.coins, 22, eq, 0))
	{
		printf("TEST PASSED\n");
	}
	else
	{
		printf("TEST FAILED\n");
	}

	// ----------- TEST 4: 1 Copper Pieces, 9 Silver Pieces, 1 Gold Piece, 100 Bonus Coins --------------
	printf("\nTEST 4: 1 Copper Pieces, 9 Silver Pieces, 1 Gold Piece, 100 Bonus Coins\n");
	updateCoins(G.whoseTurn, &G, 100);
	printf("Updated Coin Value: %d [Expect 122]\n", G.coins);
	if(myAssert(G.coins, 122, eq, 0))
	{
		printf("TEST PASSED\n\n");
	}
	else
	{
		printf("TEST FAILED\n\n");
	}
}

