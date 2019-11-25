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

int checkEstateCount(struct gameState *pre)
{
    int check;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));


    check = baronCard(0, &post, 0);
    assert(check==0);
    printf("\n\tEstate supply count before: %d\n", supplyCount(estate, pre));
    printf("\tEstate supply count before: %d\n", supplyCount(estate, &post));
    if (supplyCount(estate, pre)-supplyCount(estate, &post) == 1) {
        return 0;
    } else {
        return 1;
    }
}


int checkHandCount(struct gameState *pre, int currentPlayer, int choice)
{
    int i;
    int check;
    int countPre=0;
    int countPost=0;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = baronCard(currentPlayer, &post, choice);
    assert(check==0);
//    printf("\n\tHand content before: ");
//    printCards(currentPlayer, pre, "hand");
    printf("Hand count before: %d\n", pre->handCount[0]);
    printf("Hand count after: %d\n", post.handCount[0]);

    for (i = 0; i < pre->handCount[currentPlayer]; i++)
    {
        if (pre->hand[currentPlayer][i] == estate) {
            countPre++;
        }
    }
//    printf("\tHand content after: ");
//    printCards(currentPlayer, &post, "hand");
    for (i = 0; i < post.handCount[currentPlayer]; i++)
    {

        if (post.hand[currentPlayer][i] == estate) {
            countPost++;
        }
    }
    if (countPre + 1 == countPost) {return 0;} else {return 1;}

}
int checkDiscardCount(struct gameState *pre, int currentPlayer, int choice)
{
    int check;
    int i;
    int countPre=0;
    int countPost=0;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));

    check = baronCard(currentPlayer, &post, choice);
    assert(check==0);
    printf("Discard count before: %d\n", pre->discardCount[0]);
    printf("Discard count after: %d\n", post.discardCount[0]);
//    printf("\n\tDiscard content before: ");
//    printCards(currentPlayer, pre, "discard");

    for (i = 0; i < pre->discardCount[currentPlayer]; i++)
    {
        if (post.discard[currentPlayer][i] == estate) {
            countPre++;
        }
    }
//    printf("\tDiscard content after: ");
//    printCards(currentPlayer, &post, "discard");
    for (i = 0; i < post.discardCount[currentPlayer]; i++)
    {

        if (post.discard[currentPlayer][i] == estate) {
            countPost++;
        }
    }
    if (countPre + 1 == countPost) {return 0;} else {return 1;}
}

int checkCoinCount(struct gameState *pre) {
    int check;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
    check = baronCard(0, &post, 1);
    assert(check==0);
    printf("\tCoin count before: %d\n", pre->coins);
    printf("\tCoin count after: %d\n", post.coins);
    if (post.coins - 4 == pre->coins) {
        return 0;
    } else {
        return 1;
    }
}
int main() {

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
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

        seed = rand();		//pick random seed
        initializeGame(players, k, seed, &state);	//initialize Gamestate

        player = 0;
        state.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
        shuffle(0, &state);
        state.discardCount[player] = rand() % MAX_DECK;
        state.handCount[player] = rand() % 10;
        state.handCount[player] = state.handCount[player] + 3;

        state.hand[0][0] = baron;
        state.coins = countHandCoins(0, &state);
        state.numActions = rand() % 10;
        state.whoseTurn = 0;

        if (checkCoinCount(&state) != 0) {
            if (checkDiscardCount(&state, 0, 1) != 0) {
                printf("discard error\n");
                errors++;
            }
        }
        else {
            if (checkHandCount(&state, 0, 1) != 1) {
                printf("hand error\n");
                errors++;
            }
            if (checkEstateCount(&state) == 0) {
                printf("estate error\n");
                errors++;
            }
        }
    }
    printf("Errors: %d\n", errors);
    printf("******Finish Random Card Test Village*****\n");
    return 0;
}