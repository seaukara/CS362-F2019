// CS 362 F19 400
// 11/07/19
// Assignment 3 - Tests minionEffect
// Created by: Kara Manseau

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
int checkDiscardedHand(struct gameState *pre, int currentPlayer) {
    int check;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = minionEffect(1, 1, &post, 1);
    assert(check==0);

    printf("\n\tDiscard count before: %d\n", pre->discardCount[currentPlayer]);
    printf("\n\tDiscard count after:  %d\n", post.discardCount[currentPlayer]);
    if (pre->discardCount[currentPlayer]+4 == post.discardCount[currentPlayer]) {
        return 1;
    } else {
        return 0;
    }
}
int checkCoinCount(struct gameState *pre) {
    int check;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = minionEffect(0, 1, &post, 1);
    assert(check==0);
    printf("\n\tCoin count before: %d", pre->coins);
    printf("\n\tCoin count after:  %d\n", post.coins);
    if (post.coins - 2 == pre->coins) {
        return 0;
    } else {
        return 1;
    }
}
int actionCount(struct gameState *pre) {
    int check;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = minionEffect(0, 0, &post, 1);
    assert(check==0);
    printf("\n\tNumber of player actions before: %d", pre->numActions);
    printf("\n\tNumber of player actions after:  %d\n", post.numActions);
    if (pre->numActions+1 == post.numActions) {
        return 0;
    } else {
        return 1;
    }
}

int main(int argc, char** argv) {

    struct gameState game1, game2;


    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    int currentPlayer;

    initializeGame(2, k, 1000, &game1);

    game1.handCount[0] = 3;
    game1.hand[0][0] = minion;
    game1.hand[0][1] = silver;


    initializeGame(2, k, 1000, &game2);

    game2.handCount[0] = 3;
    game2.hand[0][0] = minion;
    game2.hand[0][1] = estate;

    currentPlayer = whoseTurn(&game1);
    /*---------------------------------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------------------------------*/
    printf("\nTest 1: Add an additional buy *********************************************** \n\n");
    printf("\tVerify that an additional action is added to the players buy count.\n");

    if (actionCount(&game1) == 0) {
        printf("\n\tSUCCCESS: An additional action was added to the players action count.\n");
    } else {
        printf("\n\tFAILURE: Test failed and action was not added to the action count.\n");
    }
    /*---------------------------------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------------------------------*/
    printf("\nTest 2: Add 2 coins to coin count ******************************************** \n\n");
    printf("\tVerify that if the player chooses option 1, 2 coins are added to count.\n");


    if (checkCoinCount(&game2) == 0)
    {

        printf("\n\tSUCCCESS: Coins added succesfully.\n");
    } else {
        printf("\n\tFAILURE: Test failed and coins were not added.\n");
    }
    /*---------------------------------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------------------------------*/
    printf("\nTest 3: Discard hand and draw 4 ******************************************** \n\n");
    printf("\tVerify that if the player chooses option 2, that their hand is discarded\n\tand 4 additional cards are drawn.\n");


    if (checkDiscardedHand(&game2, currentPlayer) == 0)
    {

        printf("\n\tSUCCCESS: Cards were discarded and added successfully.\n");
    } else {
        printf("\n\tFAILURE: Test failed and cards were not successfully discarded or drawn.\n");
    }
}
