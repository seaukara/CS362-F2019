/*********************************************
* CS362 - Assignment 3
* Author: Stephen Townsend
* File: unittest1.c
*********************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int main (int argc, char** argv)
{
    struct gameState state1;
    struct gameState state2;
    struct gameState state3;
    int supplyPos = 2;

    printf("\n----------Start Testing Buy Card----------\n");

    state1.numBuys = 2;
    state1.coins = 4;
    state2.numBuys = 2;
    state2.coins = 10;
    state3.numBuys = 0;
    state3.coins = 10;

    printf("\nTesting for not enough coins\n");
    if(buyCard(supplyPos, &state1) == -1)
        printf("Passed when testing %d coins\n", state1.coins);
    else
        printf("Failed when testing %d coins\n", state1.coins);


    printf("\nTest for enough coins\n");
    if(buyCard(supplyPos, &state2) == 0)
        printf("Passed when testing %d coins\n", state2.coins);
    else
        printf("Failed when testing %d coins\n", state2.coins);


    printf("\nTesting for enough coins and  no buy potential\n");
    if(buyCard(supplyPos, &state3) == -1)
        printf("Passed when testing %d coins & %d buy\n", state3.coins, state3.numBuys);
    else
        printf("Failed when testing %d coins\n", state3.coins);


    printf("\n----------End Testing Buy Card----------\n");
}