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
int checkDiscardedHand(struct gameState *pre, int currentPlayer) {
    int check;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = minionCard(currentPlayer, &post, 1, 1, 1);
    assert(check==0);

    printf("\n\tDiscard count before: %d\n", pre->discardCount[currentPlayer]);
    printf("\tDiscard count after:  %d\n", post.discardCount[currentPlayer]);
    if (pre->discardCount[currentPlayer]+4 == post.discardCount[currentPlayer]) {
        return 1;
    } else {
        return 0;
    }
}
int checkCoinCount(struct gameState *pre, int currentPlayer) {
    int check;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = minionCard(currentPlayer, &post, 0, 1, 1);
    assert(check==0);
    printf("\n\tCoin count before: %d", pre->coins);
    printf("\n\tCoin count after:  %d\n", post.coins);
    if (post.coins - 2 == pre->coins) {
        return 0;
    } else {
        return 1;
    }
}
int actionCount(struct gameState *pre, int currentPlayer) {
    int check;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = minionCard(currentPlayer, &post, 0, 0, 1);
    assert(check==0);
    printf("\n\tNumber of player actions before: %d", pre->numActions);
    printf("\n\tNumber of player actions after:  %d\n", post.numActions);
    if (pre->numActions+1 == post.numActions) {
        return 0;
    } else {
        return 1;
    }
}

int main() {

    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    int i, r, players, player, seed, errors = 0;
    struct gameState state;
    struct gameState temp;
    srand(time(NULL));
    printf("******Begin Random Card Test Village*****\n");
    for (i = 0; i < MAX_TESTS; i++) {
        printf("----Test #%d-------------------\n", i);
        do {
            players = rand() % 4;
        } while (players < 2);

        seed = rand();        //pick random seed
        initializeGame(players, k, seed, &state);    //initialize Gamestate

        player = 0;
        state.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
        shuffle(0, &state);
        state.discardCount[player] = rand() % MAX_DECK;
        state.handCount[player] = rand() % 10;
        state.handCount[player] = state.handCount[player] + 3;

        state.hand[0][0] = minion;
        state.coins = countHandCoins(0, &state);
        state.numActions = rand() % 10;
        state.whoseTurn = 0;

        if (actionCount(&state, 0) != 0) {

            printf("action error\n");
            errors++;

        } else if (checkCoinCount(&state, 0) != 0) {
            printf("coin error\n");
            errors++;
        } else if (checkDiscardedHand(&state, 0) != 0) {
            printf("discard error\n");
            errors++;
        }

    }
    printf("Errors: %d\n", errors);
    printf("******Finish Random Card Test Village*****\n");
    return 0;
}