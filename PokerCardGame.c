/* 
 * File:   CardGame.c
 * Author: Darilys Pereira
 * Panther ID: 3456178
 * Created on February 22, 2016, 6:51 PM
 * 
 * This program creates a deck of 52 cards using 4 suits
 * (Spade , Heart, Club , Diamond) and 13 faces (A, 2, 3,..10, J, Q, K)
 * After the deck is created and displayed it is shuffled and 
 * displayed again. At this point we are ready to deal the cards. 
 * The cards are dealt to the hands, then we sorted the hands and ranked them
 * After we ranked the hands we then determine the winner. 
 * The input to this program will be the 
 * number or cards per player and the number of players provided via
 * the prompt command line. This input will allow us distribute the 
 * specific number of cards to the specific players. 
 * A 2D array will be used to represent players and their cards. 
 *  
 * "I hereby certify that this collective work is my own and 
 * none of it is the work of any other person or entity. DP 3456178 “  
 */



/*---Pseudocode---
 * 1. Receive input from command line a validate
 * 2. Create a deck of cards (array of structs)
 * 3. Display deck
 * 4. Shuffle deck (using srand() and rand())
 * 5. Display deck after shuffle
 * 6. Create a 2D array where rows are hands and columns are
 * number of cards per player.
 * 7. Populate the 2D array (deal cards) and remove cards from deck 
 * at the same time.
 * 8. Display Hand.
 * 9. Verify the cards were removed from the deck by displaying deck
 * again (optional)
 * 10. Sort hands
 * 11. Displayed sorted hands
 * 12. Rank cards
 * 13.Display ranked cards
 * 14.Find winner * 
 */


#include "header.h" /*to provide all common defines, types and 
 	             function prototypes*/


int main(int argc, char** argv) {

    //initialize srand() for future use of rand()
    time_t theTime = 0;
    srand((unsigned) time(&theTime));
    
    if (argc != MINARG) {
	printf("Incorrect number of inputs. Please try again");
	return -1;
    }

    //constants declaration
    const int CARDNUM = atoi(argv[1]);
    const int PLAYERSNUM = atoi(argv[2]);

    int lastCardDealt = 0;

    //input validation
    
    if (inputValidation( CARDNUM, PLAYERSNUM) == WRONGINPUT) {
	return WRONGINPUT; // Invalid input. Exit execution
    }
    
    struct card deck[DECKSIZE]; //deck array
    struct card handsWcards[PLAYERSNUM][STUDCARDS]; //2D for player/card
    struct winner winnerArray[PLAYERSNUM]; // winners array

    createDeck(deck);
    printf("Deck of Cards: \n");
    printDeck(deck);


    shuffleDeck(deck);
    printf("\nDeck of Cards after shuffle: \n");
    printDeck(deck);

    printf("\nHands:");
    dealCardstoHands(deck, PLAYERSNUM, STUDCARDS, handsWcards,
	    &lastCardDealt);
    printHand(PLAYERSNUM, handsWcards);

    sortHands(PLAYERSNUM, handsWcards);
    printf("\nSorted Hands: ");
    printHand(PLAYERSNUM, handsWcards);

    
    printf("\nRanked Hands: \n");
    rankPlayers(PLAYERSNUM, handsWcards, winnerArray);

    printf("\nWinner(s): \n");
    findWinnerExtraCredit(PLAYERSNUM, winnerArray);

    //printf("Last card dealt: %i", lastCardDealt);
    //printf("\nDeck of Cards after deal: \n");
    //printDeck(deck);

    return 0;
}
