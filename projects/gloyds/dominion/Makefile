CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
	# To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

# Tests
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

drawcardtestresults: testDrawCard 
	./testDrawCard &> drawcardtestresult.out
	gcov dominion.c >> drawcardtestresult.out
	cat dominion.c.gcov >> drawcardtestresult.out

# Random Tests
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestresults: randomtestadventurer randomtestcard1 randomtestcard2
	./randomtestadventurer &> randomtestresults.out
	./randomtestcard1 &>> randomtestresults.out
	./randomtestcard2 &>> randomtestresults.out
	echo -e "----------------- gcov results ----------------\n" >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	echo -e "----------------- dominion.c.gcno ----------------\n" >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out

# All and Clean
all: playdom player

clean:
	rm -f *.o playdom.exe playdom player player.exe randomtestadventurer randomtestcard1 randomtestcard2 *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
