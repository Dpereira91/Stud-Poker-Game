/* 
 * File:   header.h
 * Author: Darilys Pereira
 * Panther ID: 3456178
 * Created on February 24, 2016, 8:37 PM
 * 
 * This header file contains common constants that are used
 * by CardGame.c and DeckFunctions.c. It also includes all function
 * prototypes and type declarations such as struct and enum that will 
 * be used throughout the program. 
 * 
 *  "I hereby certify that this collective work is my own and 
 * none of it is the work of any other person or entity. DP 3456178 “ 
 */


//---INCLUDES---
#include <stdio.h> 
#include <time.h> // to allow use of time()
#include <stdlib.h>// to allow use of atoi(), rand(), srand(), and qsort()

//---DEFINES---
#define MINHANDS 1 //used to control min # of cards
#define MINCARDS 1 //used to control min # of players
#define MAXHANDS 7 //used to control max # of players
#define MAXCARDS 13 //used to control max # of cards
#define SUITS 4     //used to control min # of suits used
#define FACES 13    //used to control min # of faces used
#define DECKSIZE 52 //used to control deck size
#define STUDCARDS 5 //fix # of cards for Stud Poker
#define TWOKIND 2 //aux to call numberOfAkind function
#define THREEKIND 3 //aux to call numberOfAkind function
#define FOURKIND 4 //aux to call numberOfAkind function
#define WRONGINPUT -1 // used for input validation
#define MINARG 3 // # of inputs required


//struct declarations
struct card {
    int face;
    int suit;
};

struct winner {
    int playerNum;
    int rank;
    int highCard;
};

//enums used to create and display cards
enum faceEnum {
    None, One, Two, Three, Four, Five, Six, Seven, Eight,
    Nine, Ten, Jack, Queen, King, Ace
};

enum SuitEnum {
    Spade, Heart, Club, Diamond
};

enum ranks {
    NoRank, HighCard, OnePair, TwoPair, ThreeOfAkind, Straight, Flush,
    FullHouse, FourOfAkind, StraighFlush
};

typedef enum {
    FALSE, TRUE
} boolean;



//******Function prototypes******
int inputValidation(int, int);
void createDeck(struct card deck[]);
void printDeck(struct card deck[]);
void shuffleDeck(struct card deck[]);
void dealCardstoHands(struct card deck[], int players, int cards,
	struct card handsWcards[players][cards], int *lastCardDealt);
void printHand(int players, struct card handsWcards[][STUDCARDS]);
void sortHands(int players,struct card handsWcards[][STUDCARDS]);
int highCard(int player,
	struct card handsWcards[][STUDCARDS]);
int numberOfAkind(int kindNumber, int player, struct
card handsWcards[][STUDCARDS]);
int twoPair(int player, struct card handsWcards[][STUDCARDS]);
int lowStraight(int player, struct card handsWcards[][STUDCARDS]);
int straight(int player, struct card handsWcards[][STUDCARDS]);
int flush(int player, struct card handsWcards[][STUDCARDS]);
int fullHouse(int player, struct card handsWcards[][STUDCARDS]);
int straightFlush(int player, struct card handsWcards[][STUDCARDS]);
void rankPlayers(int players,
	struct card handsWcards[][STUDCARDS], struct winner winnerArray[]);
void fillWinnerArray (int playerNum, int rank, int rankHigh,
	struct winner winnerArray[]);
void findWinnerExtraCredit(int players, struct winner winnerArray[]);