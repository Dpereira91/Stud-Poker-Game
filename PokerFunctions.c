/* File: PokerFunctions.c
 * Author: Darilys Pereira
 * Panther ID: 3456178
 * 
 * This file contains the most common functions to play poker. You can
 * determine the basic rankings and then decide the winner of the game 
 * accordingly. The rankings implemented through the functions of this file
 * are:
 * 1. High Card
 * 2.One Pair
 * 3.Two Pair
 * 4.Three of a Kind
 * 5.Straight
 * 6.Flush
 * 7.Full House
 * 8.Four of a Kind
 * 9. Straight Flush
 */
/*"I hereby certify that this collective work is my own and 
 * none of it is the work of any other person or entity. DP 3456178 “ */



#include "header.h" /*to provide all common defines, types and 
 	             function prototypes*/


const char *rankArray[] = {"", "High Card", "One Pair", "Two Pair",
    "Three Of A Kind", "Straight", "Flush", "Full House", "Four Of A Kind",
    "Straight Flush"};


/*--------Function rankPlayers---------
 * This function is used to rank each hand. It has several auxiliar functions
 * to break the problem into smaller pieces. The possible rank are: 
 * Hight Card, One Pair, Two Pairs, 3 of a Kind, Straight, Flush, Full House,
 * Four of a Kind, and Straight Flush.
 * 
 * When it determines  the raking of a hand it calls function fillWinnerArray
 * which will store each player number, the rank, and the highest card for
 * the specify ranking. 
 * Parameters: number of hands, 2 struct arrays 
 * Return: void
 * Side effects: This method modifies the array being passed to the
 * function by initializing the members of the structure
 */
void rankPlayers(int players,
	struct card handsWcards[][STUDCARDS], struct winner winnerArray[]) {
    int playerCount = 0;
    int rankHigh;

    for (playerCount = 0; playerCount < players; playerCount++) {
	printf("%s%d ", "Player: ", playerCount + 1);

	if (rankHigh = straightFlush(playerCount, handsWcards)) {
	    fillWinnerArray(playerCount, StraighFlush, rankHigh,
		    winnerArray);
	    printf(rankArray[StraighFlush]);
	} else if (rankHigh = numberOfAkind(FOURKIND, playerCount,
		handsWcards)) {
	    fillWinnerArray(playerCount, FourOfAkind, rankHigh, winnerArray);
	    printf(rankArray[FourOfAkind]);
	} else if (rankHigh = fullHouse(playerCount, handsWcards)) {
	    fillWinnerArray(playerCount, FullHouse, rankHigh, winnerArray);
	    printf(rankArray[FullHouse]);
	} else if (rankHigh = flush(playerCount, handsWcards)) {
	    fillWinnerArray(playerCount, Flush, rankHigh, winnerArray);
	    printf(rankArray[Flush]);
	} else if (rankHigh = straight(playerCount, handsWcards)) {
	    fillWinnerArray(playerCount, Straight, rankHigh, winnerArray);
	    printf(rankArray[Straight]);
	} else if (rankHigh = numberOfAkind(THREEKIND, playerCount,
		handsWcards)) {
	    fillWinnerArray(playerCount, ThreeOfAkind, rankHigh, winnerArray);
	    printf(rankArray[ThreeOfAkind]);
	} else if (rankHigh = twoPair(playerCount, handsWcards)) {
	    fillWinnerArray(playerCount, TwoPair, rankHigh, winnerArray);
	    printf(rankArray[TwoPair]);
	} else if (rankHigh = numberOfAkind(TWOKIND, playerCount,
		handsWcards)) {
	    fillWinnerArray(playerCount, OnePair, rankHigh, winnerArray);
	    printf(rankArray[OnePair]);
	} else {
	    rankHigh = highCard(playerCount, handsWcards);
	    fillWinnerArray(playerCount, HighCard, rankHigh, winnerArray);
	    printf(rankArray[HighCard]);
	}
	printf("\n");
    } // end of for
} // end of rankPlayers function


/*-------Function fillWinnerArray--------
 * This function initializes a struct array with each player's info
 * after ranking has been determined. 
 * Parameters: the player, an array of structs 
 * Return: void
 * Side effects: This method modifies the array being passed to the
 * function by initializing the members of the structure
 */
void fillWinnerArray(int playerNum, int rank, int rankHigh,
	struct winner winnerArray[]) {
    winnerArray[playerNum].playerNum = playerNum + 1;
    winnerArray[playerNum].highCard = rankHigh;
    winnerArray[playerNum].rank = rank;
}

/*------Function findWinnerExtraCredit-----------
 * This function finds the closest result of the winner of the game. 
 * It starts by searching in the array of players and determining the 
 * highest rank. After the higher rank is known, if there is more than
 * one player with such ranking it performs a second search by high card.
 * Each element of the winnerArray has the rank and the highest card for 
 * each player. The second search determines from the winning rank
 * what is the highest existing card. It then prints all the players
 * that meet both criteria (rank AND highest card)
 * Parameters: the number of player, an array of structs 
 * Return: void
 * Side effects: None
 */

void findWinnerExtraCredit(int players, struct winner winnerArray[]) {
    int higherRank = 0;
    int higherRankCount = 0;
    int singleWinner;
    int higherHigh = 0;
    int higherHighCount = 0;
    int hand;


    //first search: find highest rank
    for (hand = 0; hand < players; hand++) {
	if (winnerArray[hand].rank > higherRank) {
	    higherRank = winnerArray[hand].rank;
	}
    }

    //search for highest card for that rank
    for (hand = 0; hand < players; hand++) {
	if (winnerArray[hand].rank == higherRank) {
	    if (winnerArray[hand].highCard > higherHigh) {
		higherHigh = winnerArray[hand].highCard;
		// higherHighCount = 1;
		//singleWinner = winnerArray[hand].playerNum;
	    }
	}
    }

    //loop and print all highest cards players
    for (hand = 0; hand < players; hand++) {
	if ((winnerArray[hand].rank == higherRank)&&
		(winnerArray[hand].highCard == higherHigh)) {
	    printf("%s%d ", "Player ", (hand + 1));
	    printf("with %s  ", rankArray[higherRank]);
	    printf("\n");
	}
    }
} // end of findWinnerExtra Credit function

/* ------Function: highCard--------------
 * This function is asserted only when the hand have different cards of 
 * different suits. It's an aux function to rankPlayers.
 * Parameters: the player, an array of structs 
 * Return: the highest card for this rank = last hand card
 * Side effects: None
 */
int highCard(int player, struct card handsWcards[][STUDCARDS]) {

    return handsWcards[player][STUDCARDS - 1].face;
}

/* ------Function: numberOfAkind--------------
 * This function is used to determine if a specified number of card is
 * present in the hand. Since the array is sorted the order of the cards
 * is consecutive.
 * It's an aux function to rankPlayers. It finds One Pair, 3 of a Kind, 
 * and Four of a Kind rankings.
 * Parameters: number of cards looked for ,the player, an array of structs 
 * Return: the highest card for this rank = position where one of the
 * sequential cards was found
 * Side effects: None
 */
int numberOfAkind(int kindNumber, int player,
	struct card handsWcards[][STUDCARDS]) {
    int cardsTraversal;
    int cardCount = 1;

    for (cardsTraversal = 0; cardsTraversal < STUDCARDS - 1;
	    cardsTraversal++) {
	if ((handsWcards[player][cardsTraversal].face) ==
		(handsWcards[player][cardsTraversal + 1].face)) {
	    cardCount++;
	    {
		if (cardCount == kindNumber)
		    return handsWcards[player][cardsTraversal].face;
	    }
	} else cardCount = 1;
    }
    return FALSE;

}// end of onePair function

/* --------Function: twoPairs-----------
 * This function is asserted when the hand has 2 different pairs. It's
 * implemented by calling function numberOfAkind to verify is a pair
 * exists in the hand. I then hard coded a traversal to the
 * hand backwards to avoid reaching the same pair instantly. If the high
 * card for the second pair is different from the first pair means there
 * are two pair in the hand.
 * Parameters:player, an array of structs 
 * Return: the highest card for this rank = highest card of the 2 pairs
 * Side effects: None
 */
int twoPair(int player, struct card handsWcards[][STUDCARDS]) {

    int cardsTraversal;
    int found, found2;

    //if one pair
    if (found = (numberOfAkind(TWOKIND, player, handsWcards))) {

	//and another different pair
	for (cardsTraversal = STUDCARDS; cardsTraversal > 0;
		cardsTraversal--) {
	    if ((handsWcards[player][cardsTraversal].face) ==
		    (handsWcards[player][cardsTraversal - 1].face)) {
		found2 = handsWcards[player][cardsTraversal].face;
		if (found != handsWcards[player][cardsTraversal].face)

		    return (found > found2 ? found : found2);
	    }
	}
    }
    return FALSE;
}// end of twoPair function

/*------------Function: lowStraight-----------
 * This function was designed to catch the special case of a Straight 
 * (5 consecutive card from different suit) which is A2345.
 *  Parameters:player, an array of structs 
 * Return: the highest card for this rank = the last card of the hand
 * Side effects: None
 */
int lowStraight(int player, struct card handsWcards[][STUDCARDS]) {

    int cardsTraversal;
    int firstCard = handsWcards[player][0].face;

    if (firstCard == Ace) {
	firstCard = 1;

	for (cardsTraversal = 1; cardsTraversal < STUDCARDS - 1;
		cardsTraversal++) {
	    if ((handsWcards[player][cardsTraversal].face) !=
		    ((handsWcards[player][cardsTraversal + 1].face) - 1))

		return FALSE;
	}

	return handsWcards[player][0].face;
    }

    return FALSE;
}

/*-------------Function: straight-----------------
 * This function will determine if there are 5 consecutive cards with 
 * different suits. The special case of A2345 is handled by calling 
 * function lowStraigh from inside this function (straight). 
 * Parameters:player, an array of structs 
 * Return: the highest card for this rank = the last card of the hand
 * Side effects: None
 */
int straight(int player, struct card handsWcards[][STUDCARDS]) {
    int cardsTraversal;
    int lowStraightOut;


    if (lowStraightOut = lowStraight(player, handsWcards)) {
	return lowStraightOut; //combination A2345 returns A
    }

    for (cardsTraversal = 0; cardsTraversal < STUDCARDS - 1;
	    cardsTraversal++) {
	if ((handsWcards[player][cardsTraversal].face) !=
		((handsWcards[player][cardsTraversal + 1].face) - 1))

	    return FALSE;
    }
    return handsWcards[player][STUDCARDS - 1].face;
} // end of straight function

/*----------Function: flush------------------
 * This function is asserted when all the cards of the hand have the same
 * suit but they are not in order. 
 * Parameters:player, an array of structs 
 * Return: the highest card for this rank = the last card of the hand
 * Side effects: None
 */
int flush(int player, struct card handsWcards[][STUDCARDS]) {
    int cardsTraversal;

    for (cardsTraversal = 0; cardsTraversal < STUDCARDS; cardsTraversal++) {
	if (handsWcards[player][cardsTraversal].suit !=
		(handsWcards[player][cardsTraversal + 1].suit))

	    return FALSE;
    }
    return handsWcards[player][STUDCARDS - 1].face;
}

/*-----------Function:fullHouse-------------
 * Full house if defined in Poker as having 3 of a Kind and One Pair. 
 * To accomplish this result I used function numberOfAkind to determine
 * if the hand contains a 3 of a kind. I then hard coded a One pair 
 * within fullHouse going reverse (from 5 to 0) to find a paid 
 * different from the 3 kind. 
 * Parameters:player, an array of structs 
 * Return: the highest card for this rank = the highest card for the 3 Kind
 * Side effects: None
 */
int fullHouse(int player, struct card handsWcards[][STUDCARDS]) {
    int found = 0;
    int cardsTraversal = 0;
    int cardCount = 1;

    if (found = (numberOfAkind(THREEKIND, player, handsWcards))) {

	for (cardsTraversal = STUDCARDS; cardsTraversal > 0;
		cardsTraversal--) {
	    if ((handsWcards[player][cardsTraversal].face) ==
		    (handsWcards[player][cardsTraversal - 1].face)) {
		cardCount++;
		if (found != handsWcards[player][cardsTraversal].face)

		    return found;
	    }
	}
    }
    return FALSE;
} // end of fullHouse

/*----------Function: straightFlush---------------------
 * This function is asserted when the hand contains 5 cards in sequence and
 * they are from the same suit. I accomplished the results by combining 
 * functions calls to straight and flush.
 * * Parameters:player, an array of structs 
 * Return: the highest card for this rank = the last card of the hand.
 * Side effects: None
 */
int straightFlush(int player, struct card handsWcards[][STUDCARDS]) {

    int straightOut = straight(player, handsWcards);
    if (straightOut && (flush(player, handsWcards)))
	return straightOut;
    else
	return FALSE;

}// end of straightFlush function