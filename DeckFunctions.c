/* File: DeckFunctions.c
 * Author: Darilys Pereira
 * Panther ID: 3456178
 * 
 * This file contains the most common functions to manipulate a
 * deck of cards. You can create a deck, display a deck, and shuffle a deck.
 * We can deal a specific number of cards to specific number of players, 
 * display hands, and sort them. It also allows to control and validate that  
 * user input of cards and players is correct. 
 */
/*"I hereby certify that this collective work is my own and 
 * none of it is the work of any other person or entity. DP 3456178 “ */

#include "header.h" /*to provide all common defines, types and 
 	             function prototypes*/
const char *suitArray[] = {"0", "S", "H", "C", "D"};
const char *faceArray[] = {"", "One", "2", "3", "4", "5", "6", "7", "8",
    "9", "10", "J", "Q", "K", "A"};

/*------Function: inputValidation------
 * This method is used to validate input received from the command 
 * prompt to our program. The input requirements are:
 * 1.# or cards is 5.
 * 2.# of players at least 1 and max 7.
 * 3.# Number of cards dealt cannot exceed deck size (52).
 * Parameters: Number or cards per players, number of players
 * Return: 1 if both inputs satisfied the requirements
 *        -1 if one of the conditions failed. 
 * Side Effects: None.
 */
int inputValidation(int numCards, int numPlayers) {
    if (numCards < MINCARDS || numPlayers < MINHANDS) {
	printf("Number of card and/or number of players \n");
	printf("is below the min");
	return WRONGINPUT;
    } else if (numCards > MAXCARDS || numPlayers > MAXHANDS) {
	printf("Number of card and/or number of players \n");
	printf("is over the max");
	return WRONGINPUT;
    } else if ((numCards * numPlayers) > DECKSIZE) {
	printf("Number of card and players exceed the \n");
	printf("deck size (DECKSIZE)");
	return WRONGINPUT;
    } else {
	return 1; //input is as expected
    }
}//end of inputValidation method

/*------Function: createDeck------
 * This method initializes an array of 52 cards (a deck). It uses the faces
 * A, 2, 3 ... 10, J, Q, K and suits Diamonds, Spades, Clubs, and Hearts.
 * It's implemented as an array of 52 elements [0..51]. Each index 
 * represents a card where its suit references an index of a constant 
 * array with such values and its face references the index of
 * constant face values. 
 * Parameters: an array of structs (the empty deck)
 * Return: void
 * Side effects: This method modifies the array being passed to the
 * function by initializing the members of the structure
 */
void createDeck(struct card deck[]) {
    int cardCount = 0;
    int suitCard = 1;
    int faceCard = 1;

    for (suitCard = 1; suitCard <= SUITS; suitCard++) {
	for (faceCard = 1; faceCard <= FACES; faceCard++) {
	    deck[cardCount].face = faceCard;
	    deck[cardCount].suit = suitCard;
	    cardCount++;
	} //loop of all the faces
    } //loop to get all the suits

    suitCard = faceCard = 0;
    for (; suitCard < SUITS; suitCard++, faceCard += FACES)
	deck[faceCard].face += FACES;
} // end of createDeck method

/*------Function: printDeck------
 * This function displays the deck of cards. Each card (or array element)
 * has stored the index of a constant array where the value of suits
 * and faces are stored.   
 * Parameters: an array of structs (the deck)
 * Return: void 
 * Side effects: None
 */
void printDeck(struct card deck[]) {
    int cardsOnDeck = 0;

    for (cardsOnDeck = 0; cardsOnDeck < DECKSIZE; cardsOnDeck++) {

	printf("%2s%1s  ", faceArray[deck[cardsOnDeck].face],
		suitArray[deck[cardsOnDeck].suit]);

	//formats the output to show 13 cards per line
	if ((cardsOnDeck + 1) % FACES == 0)
	    printf("\n");
    } //end of while

}// end of printDeck method

/*------Function: shuffleDeck------
 * This method shuffles a deck by traversing the array of cards and
 * swapping the card at each position of the array by another card at a 
 * random position. 
 * For my function, the random number needs to be generated 
 * from 0 to 51 since I'm using the random numbers to manipulate cards
 * by INDEX (Array of cards goes from index 0 to index 51).
 * Parameters: an array of structs (the deck)
 * Return: void
 * Side effects: This method modifies the array being passed to reorder
 * the cards.
 */
void shuffleDeck(struct card deck[]) {
    int random = 0;
    int index = 0;
    struct card tempCard;

    for (index = 0; index < DECKSIZE; index++) {
	random = (rand() % DECKSIZE); //random from 0 to 51

	tempCard = deck[index];
	deck[index] = deck[random];
	deck[random] = tempCard;
    }
} //end of shuffleDeck method

/*------Function: dealCardstoHands------
 * dealCards is a function designed to distribute the cards of the
 * deck to the players. The number of players and number of cards per
 * player is determined from the user input in the command prompt.
 * The accomplish this task I'll use a 2D array to represent players
 * (by row) and their cards(by colum).At the same time the cards 
 * are deal to the players I'm resting that card value to '00' in the
 * deck to represent the card is not in the deck anymore.
 * Parameter:  an array of structs (the deck), the number of players,
 * and the cards per  player assuming these value were validated already. 
 * It also receives the declared empty 2D array. The last parameter is
 * a reference to a variable that store the last card dealt.
 * Return: void
 * Side Effects: It modifies the 2D array passed as parameter. Passed as
 * reference.
 */
void dealCardstoHands(struct card deck[], int players, int cards,
	struct card handsWcards[players][cards], int *lastCardDealt) {
    int cardsDealed = 0;
    int rowPlayer = 0;
    int columnCard = 0;

    for (rowPlayer; rowPlayer < players; rowPlayer++) {
	for (columnCard = 0; columnCard < cards; columnCard++) {
	    handsWcards[rowPlayer][columnCard] = deck[cardsDealed];

	    //reseting values of card on deck
	    deck[cardsDealed].face = 0;
	    deck[cardsDealed].suit = 0;

	    cardsDealed++;
	} // end of inner loop
    } // end of outer loop

    //record last card dealt
    (*lastCardDealt) += cardsDealed;

}// end of dealCards method

/*------Function: printHands------
 *This function displays the deck of player. Each card (or array element)
 *has stored the index of a constant array where the value of suits
 *and faces are stored. 
 * Parameters: # of players and the 2D array with this info.
 * Return: void 
 * Side effects: None
 */
void printHand(int players, struct card handsWcards[][STUDCARDS]) {

    printf("\n");
    int row = 0;
    int col = 0;

    for (row; row < players; row++) {
	printf("Player%2i: ", row + 1);
	for (col = 0; col < STUDCARDS; col++) {
	    printf("%2s%1s  ", faceArray[handsWcards[row][col].face],
		    suitArray[handsWcards[row][col].suit]);
	}
	printf("\n");
    }

}// end of printDeck method

/*------Function: printHands------
 * This function sorts each hand of the game by implementing insertion
 * sort. This is useful to determine the ranking of each hand in 
 * function rankPlayers etc.
 *Parameters: # of players and the 2D array
 * Return: void 
 * Side effects: It modifies the 2D array passed as parameter. Passed as
 * reference.
 */
void sortHands(int players, struct card handsWcards[][STUDCARDS]) {
    int i, j, playerNum;
    for (playerNum = 0; playerNum < players; playerNum++) {
	for (i = 1; i < STUDCARDS; i++) {
	    struct card temp = handsWcards[playerNum][i];
	    for (j = i; (j > 0 && (temp.face < 
		    handsWcards[playerNum][j - 1].face))
		    ; j--) {
		handsWcards[playerNum][j] = handsWcards[playerNum][j - 1];
		handsWcards[playerNum][j - 1] = temp;
	    }
	}
    }
} //end of sort hands













