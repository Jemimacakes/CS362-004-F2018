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

# Unit Tests
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest1results: unittest1
	./unittest1 &> testresults.out
	echo -e "----------------- gcov results ----------------\n" >> testresults.out
	gcov -b -f dominion.c >> testresults.out
	echo -e "----------------- dominion.c.gcno ----------------\n" >> testresults.out
	cat dominion.c.gcov >> testresults.out


unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest2results: unittest2
	./unittest2 &> testresults.out
	echo -e "----------------- gcov results ----------------\n" >> testresults.out
	gcov -b -f dominion.c >> testresults.out
	echo -e "----------------- dominion.c.gcno ----------------\n" >> testresults.out
	cat dominion.c.gcov >> testresults.out


unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest3results: unittest3
	./unittest3 &> testresults.out
	echo -e "----------------- gcov results ----------------\n" >> testresults.out
	gcov -b -f dominion.c >> testresults.out
	echo -e "----------------- dominion.c.gcno ----------------\n" >> testresults.out
	cat dominion.c.gcov >> testresults.out


unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

unittest4results: unittest4
	./unittest4 &> testresults.out
	echo -e "----------------- gcov results ----------------\n" >> testresults.out
	gcov -b -f dominion.c >> testresults.out
	echo -e "----------------- dominion.c.gcno ----------------\n" >> testresults.out
	cat dominion.c.gcov >> testresults.out


# Card Unit Tests
cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest1results: cardtest1
	./cardtest1 &> testresults.out
	echo -e "----------------- gcov results ----------------\n" >> testresults.out
	gcov -b -f dominion.c >> testresults.out
	echo -e "----------------- dominion.c.gcno ----------------\n" >> testresults.out
	cat dominion.c.gcov >> testresults.out


cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest2results: cardtest2
	./cardtest2 &> testresults.out
	echo -e "----------------- gcov results ----------------\n" >> testresults.out
	gcov -b -f dominion.c >> testresults.out
	echo -e "----------------- dominion.c.gcno ----------------\n" >> testresults.out
	cat dominion.c.gcov >> testresults.out


cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest3results: cardtest3
	./cardtest3 &> testresults.out
	echo -e "----------------- gcov results ----------------\n" >> testresults.out
	gcov -b -f dominion.c >> testresults.out
	echo -e "----------------- dominion.c.gcno ----------------\n" >> testresults.out
	cat dominion.c.gcov >> testresults.out


cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

cardtest4results: cardtest4
	./cardtest4 &> testresults.out
	echo -e "----------------- gcov results ----------------\n" >> testresults.out
	gcov -b -f dominion.c >> testresults.out
	echo -e "----------------- dominion.c.gcno ----------------\n" >> testresults.out
	cat dominion.c.gcov >> testresults.out


# Random Tests
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestadventurerresults: randomtestadventurer
	./randomtestadventurer &> testresults.out
	echo -e "----------------- gcov results ----------------\n" >> testresults.out
	gcov -b -f dominion.c >> testresults.out
	echo -e "----------------- dominion.c.gcno ----------------\n" >> testresults.out
	cat dominion.c.gcov >> testresults.out


randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard1results: randomtestcard1
	./randomtestcard1 &> testresults.out
	echo -e "----------------- gcov results ----------------\n" >> testresults.out
	gcov -b -f dominion.c >> testresults.out
	echo -e "----------------- dominion.c.gcno ----------------\n" >> testresults.out
	cat dominion.c.gcov >> testresults.out


randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestcard2results: randomtestcard2
	./randomtestcard2 &> testresults.out
	echo -e "----------------- gcov results ----------------\n" >> testresults.out
	gcov -b -f dominion.c >> testresults.out
	echo -e "----------------- dominion.c.gcno ----------------\n" >> testresults.out
	cat dominion.c.gcov >> testresults.out


testresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard2
	./unittest1 &> testresults.out
	./unittest2 &>> testresults.out
	./unittest3 &>> testresults.out
	./unittest4 &>> testresults.out
	./cardtest1 &>> testresults.out
	./cardtest2 &>> testresults.out
	./cardtest3 &>> testresults.out
	./cardtest4 &>> testresults.out
	./randomtestadventurer &>> testresults.out
	./randomtestcard1 &>> testresults.out
	./randomtestcard2 &>> testresults.out
	echo -e "----------------- gcov results ----------------\n" >> testresults.out
	gcov -b dominion.c >> testresults.out
	echo -e "----------------- dominion.c.gcno ----------------\n" >> testresults.out
	cat dominion.c.gcov >> testresults.out

# All and Clean
all: playdom player

clean:
	rm -f *.o playdom.exe playdom player player.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard2 *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
