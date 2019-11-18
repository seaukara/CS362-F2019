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
    int check, i;
    struct gameState post;
    memcpy (&post, pre, sizeof(struct gameState));
//    int currentPlayer = whoseTurn(pre);
    int nextPlayer = currentPlayer + 1;
    int tributeRevealedCards[2] = {-1, -1};
    if ((pre->discardCount[nextPlayer] + pre->deckCount[nextPlayer]) <= 1) {
        if (pre->deckCount[nextPlayer] > 0) {
            tributeRevealedCards[0] = pre->deck[nextPlayer][pre->deckCount[nextPlayer]-1];
            pre->deckCount[nextPlayer]--;
        }
        else if (pre->discardCount[nextPlayer] > 0) {
            tributeRevealedCards[0] = pre->discard[nextPlayer][pre->discardCount[nextPlayer]-1];
            pre->discardCount[nextPlayer]--;
        }
//        else {
//            //No Card to Reveal
//            if (DEBUG) {
//                printf("No cards to reveal\n");
//            }
//        }
    }

    else {
        if (pre->deckCount[nextPlayer] == 0) {
            for (i = 0; i < pre->discardCount[nextPlayer]; i++) {
                pre->deck[nextPlayer][i] = pre->discard[nextPlayer][i];//Move to deck
                pre->deckCount[nextPlayer]++;
                pre->discard[nextPlayer][i] = -1;
                pre->discardCount[nextPlayer]--;
            }

            shuffle(nextPlayer,pre);//Shuffle the deck
        }
        tributeRevealedCards[0] = pre->deck[nextPlayer][pre->deckCount[nextPlayer]-1];
        pre->deck[nextPlayer][pre->deckCount[nextPlayer]--] = -1;
        pre->deckCount[nextPlayer]--;
        tributeRevealedCards[1] = pre->deck[nextPlayer][pre->deckCount[nextPlayer]-1];
        pre->deck[nextPlayer][pre->deckCount[nextPlayer]--] = -1;
        pre->deckCount[nextPlayer]--;
    }
    char name[MAX_STRING_LENGTH];
    cardNumToName(tributeRevealedCards[0], name);
    printf("\n\tTribute card: %s", name);
    cardNumToName(tributeRevealedCards[1], name);
    printf("\n\tTribute card: %s", name);
    if (tributeRevealedCards[0] == tributeRevealedCards[1]) { //If we have a duplicate card, just drop one
        pre->playedCards[pre->playedCardCount] = tributeRevealedCards[1];
        pre->playedCardCount++;
        tributeRevealedCards[1] = -1;
    }
    for (i = 0; i <= 2; i ++) {
        cardNumToName(tributeRevealedCards[i], name);
        printf("\n\tTribute card: %s", name);
        if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) { //Treasure cards
            printf("\n\tCoin count before: %d", pre->coins);
            printf("\n\tCoin count after:  %d\n", post.coins);
            if (pre->coins == (post.coins - 2)) {return 0;} else {return 1;}
        }

        else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) { //Victory Card Found
            if (pre->handCount[0] == (post.handCount[0] -2)) {return 0;} else {return 1;}
        }
        else { //Action Card
            if (pre->numActions == (post.numActions -2)) {return 0;} else {return 1;}
        }
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

        seed = rand();        //pick random seed
        initializeGame(players, k, seed, &state);    //initialize Gamestate

        player = 0;
        state.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
        shuffle(0, &state);
        state.discardCount[player] = rand() % MAX_DECK;
        for (r = 0; r < state.deckCount[0]; i++) {
                state.deck[0][i] = rand() % 26;
        }
//        printDiscard(0, &state);
//        return 0;
        state.handCount[player] = rand() % 10;
        state.handCount[player] = state.handCount[player] + 3;

        state.hand[0][0] = tribute;
        state.coins = countHandCoins(0, &state);
        state.numActions = rand() % 10;
        state.whoseTurn = 0;
        printf("hi");
        if (tributeCheck(&state, 0) != 0) {
            errors++;
        }
//        if (actionCount(&state) != 0) {
//
//            printf("action error\n");
//            errors++;
//
//        } else if (checkCoinCount(&state) != 0) {
//            printf("coin error\n");
//            errors++;
//        } else if (checkDiscardedHand(&state, 0) != 0) {
//            printf("discard error\n");
//            errors++;
//        }

    }
    printf("Errors: %d\n", errors);
    printf("******Finish Random Card Test Village*****\n");
    return 0;
}