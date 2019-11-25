// CS 362 F19 400
// 11/07/19
// Assignment 5 Ambassador card
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
int ambassadorFailure(int choice1, int choice2, int handPos, struct gameState *pre, int currentPlayer){
    int check;
    int i;
    int countPre=0;
    int countPost=0;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = ambassadorCard(choice1, choice2, handPos, &post, currentPlayer);
    printf("\n\tcheck: %d", check);
    printf("\n\tcheck: %d", check);
//    assert(check);
    return check;
}
int main(int argc, char** argv) {

    struct gameState game1, game2, game3;


    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    int currentPlayer;

    initializeGame(2, k, 1000, &game1);

    game1.handCount[0] = 5;
    game1.hand[0][2] = copper;
    game1.hand[0][3] = copper;
    game1.hand[0][1] = ambassador;


//    initializeGame(2, k, 1000, &game2);

//    game2.handCount[0] = 3;
//    game2.hand[0][0] = mine;
//    game2.hand[0][1] = silver;
//
//    initializeGame(2, k, 1000, &game3);
//
//    game3.handCount[0] = 3;
//    game3.hand[0][0] = mine;
//    game3.hand[0][1] = gold;

    currentPlayer = whoseTurn(&game1);
    printf("\n\nTest 1: Runs with anything **************************************** \n\n");
    printf("\tVerify that if the ambassadorCard is played it runs. \n");
    if (ambassadorFailure(copper, 2, 0, &game1, 0) == 0) {
        printf("\n\tSUCCESS: Ambassador worked succesfully.\n");
    } else {
        printf("\n\tFAILURE: Ambassador function fails.\n");
    }
    printf("\n\nTest 1: Runs with anything **************************************** \n\n");
    printf("\tVerify that if the ambassadorCard is played it runs. \n");
    if (ambassadorFailure(copper, 1, 2, &game1, 0) == 0) {
        printf("\n\tSUCCESS: Ambassador worked succesfully.\n");
    } else {
        printf("\n\tFAILURE: Ambassador function fails.\n");
    }
//    if (
//    if (checkForFailure(1, gold, &game2, currentPlayer, 1) == 0) {
//        printf("\n\tSUCCESS: Silver worked succesfully.\n");
//    } else {
//        printf("\n\tFAILURE: Silver card fails.\n");
//    }
//    if (checkForFailure(1, gold+3, &game3, currentPlayer, 1) == 1) {
//        printf("\n\tSUCCESS: Gold worked succesfully.\n");
//    } else {
//        printf("\n\tFAILURE: Gold card fails.\n");
//    }
}