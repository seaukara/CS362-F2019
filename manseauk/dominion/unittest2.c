// CS 362 F19 400
// 11/07/19
// Assignment 3
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

void printCards(int player, struct gameState *game, char pileType[]) {

    if (strcmp(pileType, "discard")==0) {
        int discardCount = game->discardCount[player];
        int discardIndex;
        if (discardCount == 0) {
            printf("The discard pile is currently empty.\n");
        } else {
            for (discardIndex = 0; discardIndex < discardCount; discardIndex++) {
                int card = game->discard[player][discardIndex];
                char name[MAX_STRING_LENGTH];
                cardNumToName(card, name);
                if (discardIndex == 0) printf("\tDiscard card %-2d: %-13s\n", discardIndex, name);
                else printf("\t\t\t\tDiscard card %-2d: %-13s\n", discardIndex, name);
            }
        }
    } else if (strcmp(pileType, "hand")==0) {
        int handCount = game->handCount[player];
        int handIndex;
        if (handCount == 0) {
            printf("The players hand is currently empty.\n");
        } else {
            for (handIndex = 0; handIndex < handCount; handIndex++) {
                int card = game->hand[player][handIndex];
                char name[MAX_STRING_LENGTH];
                cardNumToName(card, name);
                if (handIndex == 0) printf("\tHand card %-2d: %-13s\n", handIndex, name);
                else printf("\t\t\t\tHand card %-2d: %-13s \n", handIndex, name);
            }
        }

    }

}

int buyCount(struct gameState *pre) {
    int check;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = baronEffect(1, &post);
    assert(check==0);
    printf("\n\tNumber of player buys before: %d", pre->numBuys);
    printf("\n\tNumber of player buys after:  %d\n", post.numBuys);
    if (pre->numBuys+1 == post.numBuys) {
        return 0;
    } else {
        return 1;
    }
}
int checkCoinCount(struct gameState *pre) {
    int check;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = baronEffect(1, &post);
    assert(check==0);
    if (post.coins - 4 == pre->coins) {
        printf("\tCoin count before: %d\n", pre->coins);
        printf("\tCoin count after: %d\n", post.coins);
        return 0;
    } else {
        printf("Coin count before: %d", pre->coins);
        printf("Coin count after: %d", post.coins);
        return 1;
    }
}
int checkEstateCount(struct gameState *pre)
{
    int check;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));


    check = baronEffect(0, &post);
    assert(check==0);

    if (supplyCount(estate, pre)-supplyCount(estate, &post) == 1) {
        printf("\n\tEstate supply count before: %d\n", supplyCount(estate, pre));
        printf("\tEstate supply count before: %d\n", supplyCount(estate, &post));
        return 0;
    } else {
        printf("\n\tEstate supply count before: %d\n", supplyCount(estate, pre));
        printf("\tEstate supply count before: %d\n", supplyCount(estate, &post));
        return 1;
    }
}


int checkDiscardCount(struct gameState *pre, int currentPlayer, int choice)
{
    int check;
    int i;
    int countPre=0;
    int countPost=0;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));

    check = baronEffect(choice, &post);
    assert(check==0);
    printf("\n\tDiscard content before: ");
    printCards(currentPlayer, pre, "discard");

    for (i = 0; i < pre->discardCount[currentPlayer]; i++)
    {
        if (post.discard[currentPlayer][i] == estate) {
            countPre++;
        }
    }
    printf("\tDiscard content after: ");
    printCards(currentPlayer, &post, "discard");
    for (i = 0; i < post.discardCount[currentPlayer]; i++)
    {

        if (post.discard[currentPlayer][i] == estate) {
            countPost++;
        }
    }
    if (countPre + 1 == countPost) {return 0;} else {return 1;}
}


int checkHandCount(struct gameState *pre, int currentPlayer, int choice)
{
    int i;
    int check;
    int countPre=0;
    int countPost=0;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = baronEffect(choice, &post);
    assert(check==0);
    printf("\n\tHand content before: ");
    printCards(currentPlayer, pre, "hand");

    for (i = 0; i < pre->handCount[currentPlayer]; i++)
    {
        if (pre->hand[currentPlayer][i] == estate) {
            countPre++;
        }
    }
    printf("\tHand content after: ");
    printCards(currentPlayer, &post, "hand");
    for (i = 0; i < post.handCount[currentPlayer]; i++)
    {

        if (post.hand[currentPlayer][i] == estate) {
            countPost++;
        }
    }
    if (countPre + 1 == countPost) {return 0;} else {return 1;}

}


int main(int argc, char** argv)
{

    struct gameState game1, game2;



    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    int currentPlayer;

    initializeGame(2, k, 1000, &game1);

    game1.handCount[0] = 3;
    game1.hand[0][0] = baron;
    game1.hand[0][1] = silver;


    initializeGame(2, k, 1000, &game2);

    game2.handCount[0] = 3;
    game2.hand[0][0] = baron;
    game2.hand[0][1] = estate;

    currentPlayer = whoseTurn(&game1);

    printf("\n\nTest 1: Estate card added to discard **************************************** \n\n");
    printf("\tVerify that if the player chooses to gain an estate, that an \n\testate is added to their discard pile.\n");
    if (checkDiscardCount(&game1, currentPlayer, 0) == 0) {
        printf("\n\tSUCCESS: Estate added succesfully.\n");
    } else {
        printf("\n\tFAILURE: failed and estate card was not added.\n");
    }

    /*---------------------------------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------------------------------*/
    printf("\nTest 2: Estate supply count reduced by 1 *********************************** \n\n");
    printf("\n\tVerify that if the player chooses to gain an estate, that an \n\testate is subtracted from the supply.\n");
    if (checkEstateCount(&game1) == 0)
    {
        printf("\n\tSUCCCESS: Estate removed succesfully.\n");
    } else {
        printf("\n\tFAILURE: Test failed and estate card was not removed correctly.\n");
    }

    /*---------------------------------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------------------------------*/
    printf("\nTest 3: Estate card added to discard **************************************** \n\n");
    printf("\tVerify that if the player doesn't choose to gain an estate and \n\tdoesn't have an estate card in hand, "
           "that it defaults back to \n\toption 0 and adds an estate card to the players discard pile.\n");
    if (checkDiscardCount(&game1, currentPlayer, 1) == 0)
    {
        printf("\n\tSUCCCESS: Estate added succesfully.\n");
    } else {
        printf("\n\tFAILURE: Test failed and estate card was not added.\n");
    }

    /*---------------------------------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------------------------------*/
    printf("\nTest 4: Add 4 coins to coin count ******************************************** \n\n");
    printf("\tVerify that if the player doesn't choose to gain an estate card \n\tand they have an estate card, that 4 "
           "coins are added to coin count.\n\n");

    if (checkCoinCount(&game2) == 0)
    {

        printf("\n\tSUCCCESS: Coins added succesfully.\n");
    } else {
        printf("\n\tFAILURE: Test failed and coins were not added.\n");
    }

    /*---------------------------------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------------------------------*/
    printf("\nTest 5: Add estate in hand to discard pile ********************************** \n\n");
    printf("\tVerify that if the player selects an estate to discard from their \n\thand, that the card is successfully "
           "removed from their hand and \n\tadded to the discard pile.\n");

    if (checkDiscardCount(&game2, currentPlayer, 1) == 0)
    {
        printf("\n\tSUCCCESS: Estate added succesfully to discard.\n");
    } else {
        printf("\n\tFAILURE: Test failed and estate was not discarded.\n");
    }
    printf("\n\t----------------------------------------\n");
    if (checkHandCount(&game2, currentPlayer, 1) == 1)
    {
        printf("\n\tSUCCCESS: Estate card removed from hand succesfully.\n");
    } else {
        printf("\n\tFAILURE: Test failed and estate card still in hand.\n");
    }

    /*---------------------------------------------------------------------------------------------------*/
    /*---------------------------------------------------------------------------------------------------*/
    printf("\nTest 6: Add an additional buy *********************************************** \n\n");
    printf("\tVerify that an additional buy is added to the players buy count.\n");

    if (buyCount(&game2) == 0)
    {
        printf("\n\tSUCCCESS: An additional buy was added to the players buy count.\n");
    } else {
        printf("\n\tFAILURE: Test failed and buy was not added to buy count.\n");
    }



    return 0;

}