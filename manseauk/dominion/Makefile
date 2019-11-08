CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
unittest1: unittest1.c dominion.o
	gcc -o unittest1 dominion.c rngs.c unittest1.c $(CFLAGS)
unittestresults.out: unittest1
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 dominion.c rngs.c unittest1.c $(CFLAGS)
	./unittest1 &> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
unittest2: unittest2.c dominion.o interface.o
	gcc -o unittest2 dominion.c rngs.c interface.c unittest2.c $(CFLAGS)
unittestresults2.out: unittest2
	echo "unittest2.c:" >> unittestresults2.out
	gcc -o unittest2 dominion.c rngs.c interface.c unittest2.c $(CFLAGS)
	./unittest2 &> unittestresults2.out
	gcov dominion.c -b >> unittestresults2.out
testcard1: testcard1.c dominion.o rngs.o
	gcc -o testcard1 -g  testcard1.c dominion.o rngs.o $(CFLAGS)
testcard1results.out:  testcard1
	./testcard1 5 &> testcard1results.out
	gcov -b dominion.c >> testcard1results.out
	cat dominion.c.gcov >> testcard1results.out
# 	gcov -b refactor.c >> testcard1.out
	cat refactor.c.gcov >> testcard1results.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittestresult*
