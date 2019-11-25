// CS 362 F19 400
// 11/07/19
// Assignment 5 Mine card
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
int checkForFailure(int choice1, int choice2, struct gameState *pre, int currentPlayer, int handPos){
    int check;
    int i;
    int countPre=0;
    int countPost=0;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = mineCard(choice1, choice2, &post, currentPlayer, handPos);
    assert(check);
    return check;
}
int main(int argc, char** argv) {

    struct gameState game1, game2, game3;


    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    int currentPlayer;

    initializeGame(2, k, 1000, &game1);

    game1.handCount[0] = 3;
    game1.hand[0][0] = mine;
    game1.hand[0][1] = copper;


    initializeGame(2, k, 1000, &game2);

    game2.handCount[0] = 3;
    game2.hand[0][0] = mine;
    game2.hand[0][1] = silver;

    initializeGame(2, k, 1000, &game3);

    game3.handCount[0] = 3;
    game3.hand[0][0] = mine;
    game3.hand[0][1] = gold;

    currentPlayer = whoseTurn(&game1);
    printf("\n\nTest 1: Runs with copper **************************************** \n\n");
    printf("\tVerify that if the mineCard is played with copper it runs. \n");
    if (checkForFailure(1, silver, &game1, currentPlayer, 1) == 0) {
        printf("\n\tSUCCESS: Copper worked succesfully.\n");
    } else {
        printf("\n\tFAILURE: Copper card fails.\n");
    }
    if (checkForFailure(1, gold, &game2, currentPlayer, 1) == 0) {
        printf("\n\tSUCCESS: Silver worked succesfully.\n");
    } else {
        printf("\n\tFAILURE: Silver card fails.\n");
    }
    if (checkForFailure(1, gold+3, &game3, currentPlayer, 1) == 1) {
        printf("\n\tSUCCESS: Gold worked succesfully.\n");
    } else {
        printf("\n\tFAILURE: Gold card fails.\n");
    }
}