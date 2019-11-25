//
// Created by Kara Manseau on 11/17/19.
//
#include "dominion.h"
#include "interface.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX_TESTS 10000
int tributeCheck(struct gameState *pre, int currentPlayer) {
    int check = 0;
    int check2 = 0;
    int checkHand = 0;
    int checkCoin = 0;
    int tributeCount = 2;
    int i;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));

    int nextPlayer = currentPlayer + 1;
    int tributeRevealedCards[2] = {-1, -1};
    tributeCard(nextPlayer, &post, tributeRevealedCards, 2);

    tributeRevealedCards[0] = post.discard[1][post.discardCount[1]-1];
    tributeRevealedCards[1] = post.discard[1][post.discardCount[1]-2];
    char name[MAX_STRING_LENGTH];
    cardNumToName(tributeRevealedCards[0], name);
    printf("\n\tTribute card: %s", name);
    cardNumToName(tributeRevealedCards[1], name);
    printf("\n\tTribute card: %s\n", name);

    if (tributeRevealedCards[0] == tributeRevealedCards[1]) { //If we have a duplicate card, just drop one
        pre->playedCards[pre->playedCardCount] = tributeRevealedCards[1];
        pre->playedCardCount++;
        tributeCount--;

    }
    for (i = 0; i < tributeCount; i ++) {

        if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) { //Treasure cards
            printf("\n\tCoin count before: %d", pre->coins);
            printf("\n\tCoin count after:  %d\n", post.coins);
            printf("%d", i);
            if (checkCoin == 1) {
                check--;
                if (pre->coins != (post.coins - 4)) {check++;}
            } else if (i==0) {
                checkCoin = 1;
                if (pre->coins != (post.coins - 2)) {check++;}
            }
        }

        else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) { //Victory Card Found
            printf("\n\tHand count before: %d", pre->handCount[0]);
            printf("\n\tHand count after:  %d\n", post.handCount[0]);
            if (checkHand == 1) {
                check--;
                if (pre->handCount[0] != (post.handCount[0] -4)) {check++;}
            } else if (i==0) {
                checkHand = 1;
                if (pre->handCount[0] != (post.handCount[0] -2)) {check++;}
            }

        }
        else { //Action Card
            printf("\n\tAction count before: %d", pre->numActions);
            printf("\n\tAction count after:  %d\n", post.numActions);
            if (check2 == 1) {
                check--;
                if (pre->numActions != (post.numActions -4)) {check++;}
            } else if (i==0) {
                check2 = 1;
                if (pre->numActions != (post.numActions - 2)) {check++; }
            }

        }
    }
    if (check == 0) {return 0;} else {return 1;}
}


int main() {

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    int s, r, players, player, seed, errors = 0;
    struct gameState state;
    struct gameState temp;
    srand(time(NULL));
    printf("******Begin Random Card Test Village*****\n");
    for (s = 0; s < MAX_TESTS; s++) {
        printf("----Test #%d-------------------\n", s);
        do {
            players = rand() % 4;
        } while (players < 2);

        seed = rand();        //pick random seed
        initializeGame(players, k, seed, &state);    //initialize Gamestate

        player = 0;
        state.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
        shuffle(0, &state);
        state.discardCount[player] = rand() % MAX_DECK;
        state.discardCount[player+1] = state.discardCount[player+1] + 2;
        for (r = 0; r < state.deckCount[0]; r++) {
                state.deck[1][r] = rand() % 26;
        }

        state.handCount[player] = rand() % 10;
        state.handCount[player] = state.handCount[player] + 3;

        state.hand[0][0] = tribute;
        state.coins = countHandCoins(0, &state);
        state.numActions = rand() % 10;
        state.whoseTurn = 0;

        if (tributeCheck(&state, 0) != 0) {
            errors++;
            printf("error/n");

        }


    }
    printf("Errors: %d\n", errors);
    printf("******Finish Random Card Test Village*****\n");
    return 0;
}