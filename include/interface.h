#ifndef _INTERFACE_H
#define _INTERFACE_H


/* /////////////////////////////////////////////////////////////// */


/*======================================*/
/*Librairie des objets pour l'interface */
/*======================================*/


#include "../include/board.h"
/* les types de board.h qui sont utilisés ici sont nommés ici: */
/* ; board ; */

/* ====================================== */

#include "../include/tetromino.h"
/* les types de tetromino.h qui sont utilisés ici sont nommés ici: */
/* ; tetromino ; */

/* ====================================== */



/* /////////////////////////////////////////////////////////////// */

/*======================================*/
/*        Signature des fonctions       */
/*======================================*/


/*
@ requires (as interaction after calling: the answer of the player on [0,1,2])
@ assigns an integer containing the player's choice
@ ensures return this integer
*/
int choose_action();

/* ====================================== */


/*
@ requires a board b
@ assigns nothing
@ ensures to print all the information of the game (map,bag,score,...)
*/
void display_board(board b);



/* ====================================== */

/*
@ requires valid coord
@ assigns nothing
@ ensures to print the tetromino
*/
void affiche_tetromino(int type, int* coord);

/* ====================================== */


/*
@ requires (as a parameter: an board b)
           (as interaction after calling: the tetromino chosen on the grid by the player).
@ assigns a tetromino which is the player's answer.
@ ensures return the chosen tetromino (if there is one) else NULL (no one chose).
*/
tetromino select_tetromino_on_grid(board b);

/* ====================================== */


/*
@ requires (as a parameter: an board b)
           (as interaction after calling: the tetromino chosen on the bag by the player).
@ assigns a tetromino which is the player's choice.
@ ensures return the chosen tetromino (if there is one) else NULL (no one chose).
*/
tetromino select_tetromino_in_bag(board b);

/* ====================================== */


/*
@ requires (as a parameter: an board b, two int* pr and pc that are the number of the selected column and line, and a tetromino)
           (as interaction after calling: the number of column and line chosen by the player).
@ assigns nothing
@ ensures return nothing but change the int value pointed by "pr" and "pc" by player answer.
*/
void ask_place_tetromino(board b, int* pr, int* pc, tetromino t);


/* ====================================== */


/*
@ requires an board b
@ assigns nothing
@ ensures return nothing, display an message at the end of the game with all associated information.
*/
void display_end_game(board b);

/* ====================================== */


/*
@ requires an message writed on a char *
@ assigns nothing
@ ensures return nothing, but print the message entered in parameter.
*/
void display_message(char* msg);

/* ====================================== */

/*
@ requires a valid tetromino
@ assigns nothing
@ ensures ask the orientation of the tetromino and call the function set_orientation_teromino.
*/
void ask_orientation_tetromino(tetromino tetro);


/* ====================================== */

/*
@ requires a valid tetromino
@ assigns nothing
@ ensures display the tetomino in a visible way.
*/
void display_tetromino(tetromino tetro);


/* ====================================== */

/*
@ requires a valid board structure 
@ assigns nothing
@ ensures prints the informations (type, ID, rotations number, value, cells coordinates) of the reserve 
*/
void display_reserve(board b);


/* ====================================== */

/*
@ requires a valid board structure 
@ assigns nothing
@ ensures returns the number of placed tetrominos in the board
*/
int get_reference_cells_count(board b);

/* ====================================== */



/*
@ brief asks the column and line number of the tetromino to place in the reserve
@ requires (as a parameter: an board b, two int* pr and pc that are the number of the selected column and line)
           (as interaction after calling: the number of column and line chosen by the player).
@ assigns nothing
@ ensures return nothing but change the int value pointed by "pr" and "pc" by player answer.
*/
void ask_place_in_reserve(board b, int* pr, int*pc);

/* ====================================== */



/*
@ brief asks the column and line number of the tetromino to remove from the reserve
@ requires (as a parameter: an board b, two int* pr and pc that are the number of the selected column and line)
           (as interaction after calling: the number of column and line chosen by the player).
@ assigns nothing
@ ensures return nothing but change the int value pointed by "pr" and "pc" by player answer.
*/
void ask_remove_from_reserve(board b, int* pr, int*pc);


/* ====================================== */


/*
@ requires (as interaction after calling: the answer of the player on [0,1,2])
@ assigns an integer containing the player's choice on the reserve
@ ensures return this integer
*/
int handle_reserve_actions();


/* /////////////////////////////////////////////////////////////// */



#endif
