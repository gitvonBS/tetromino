#include "../include/tetromino.h"
#include "../include/carte.h"


#ifndef _BOARD_H
#define _BOARD_H


/* Abstract type defining a board. */
/* Defining the board structure */
typedef struct struct_board* board;

struct tuple {
    tetromino t;
    int pr;
    int pc;
};
 
/* @requires 3 integers n,m and k (number of rows, columns and available spaces in the bag of the board)
   @assigns nothing
   @ensures returning a board of n rows, m columns and k spaces
   */
  board create_board(int n, int m, int k);

 /* @requires a valid board type as an input;
    @assigns nothing;
    @ensures returning nothing and freeing the allocated memory to the input board; */
  void free_board(board b);

  /* @requires a valid board type as an input;
     @assigns nothing;
     @ensures returning a pointer to an instance of a tetromino type; */
  tetromino* list_tetrominos_in_bag(board b); 

  /* @requires a valid board type and a valid tetromino type as an input ;
     @assigns nothing;
     @ensures returning nothing and adding a tetromino to the bag; */
  void add_tetromino_to_bag(board b, tetromino t);
  
  /* @requires a valid board type and a tetromino type as an input ;
     @assigns nothing ;
     @ensures returning nothing and removing the tetromino from the bag; */
  void remove_tetromino_from_bag(board b, tetromino t);

  /* @requires a valid board type, two integers (r & c) and a tetromino ;
     @assigns nothing ; 
     @ensures returning 1 if it is possible to put the tetromino in the line r and the column c of the board and 0 if not; */
  int check_place_tetromino(board b, int r, int c, tetromino t);

  /* @requires a valid board type, two integers (r & c) and a tetromino;
     @assigns a place to the tetromino in the board at the line r and the column c; 
     @ensures returning 1 if the tetromino was placed successfully and 0 if not; */
  int place_tetromino(board b, int r, int c, tetromino t);

  /* @requires a valid board type, *pr and *pc to be valid addresses and a valid tetromino type ;
     @assigns nothing ;
     @ensures removing the tetromino from the board; if the operation is successful the pointers pr and pc should point to the line and the column where the reference cell of the tetromino was before its removal*/ 
 void remove_tetromino(board b, int *pr, int *pc, tetromino t);

 /* @requires a valid board type, two integers (r & c) and a tetromino ;
    @assigns nothing ;
    @ensures returning the tetromino if its cell is on the line r and the column c and NULL if not;*/
 tetromino get_tetromino(board b, int r, int c);

 /* @requires a valid board type ;
    @assigns nothing ;
    @ensures returning the current score of the player; */
 int get_score(board b); 
 

///////////////////////////////////////////////////////////////
/* @requires a valid board type ;
   @assigns nothing ;
   @ensures returing the row of the board */
int get_r(board b);
/* @requires a valid board type ;
   @assigns nothing ;
   @ensures returing the column of the board ; */
int get_c(board b);

int get_p(board b);

/* @requires a valid board structure ;
   @assigns nothing ;
   @ensures returing the numbers of tetromino in the bag ; */ 
int get_bag_count(board b);

/* @requires a valid board structure ;
   @assigns nothing ;
   @enusres returning the bag which contains the tetrominos ; */
tetromino* get_bag(board b);

/* @requires a valid board structure ;
   @assigns nothing ;
   @enusres returning the grid of the game ; */
int** get_grid(board b);

/* @requires a valid board structure ;
   @assigns nothing ;
   @enusres returning the numbers of tetrominos placed ; */
int get_nb_placed(board b);

struct tuple* get_tuples(board b);
/* @requires a valid elem_tuples structure ;
   @assigns nothing ;
   @ensures returning the pr element of elem_tuples ; */
int get_pr(struct tuple elem_tuples);

/* @requires a valid elem_tuples structure ;
   @assigns nothing ;
   @ensures returning the pc element of elem_tuples ; */
int get_pc(struct tuple elem_tuples);

/* @requires a valid board instance and c to be a valid address;
   @assigns nothing ;
   @ensures adding a card to the player; */
void add_card_to_hand(board b, carte* c);

/* @requires a valid card structure ;
   @assings nothing ; 
   @ensures returning all the cards in the hand of the player ; */
carte** list_cards_in_hand(board b);

/* @requires a valid board instance, a number of row and column ;
   @assigns nothing 
   @ensures getting the card placed in the case (r,c) of the board ; */
carte* get_card_from_board(board b, int r, int c);

/* @requires a valid board instance and c to be a valid address ;
   @assigns nothing ;
   @ensures removing a card from the hand of the player ; */
void remove_card_from_hand(board b, carte* c);

/* @requires a valid board instance and c to be a valid address ;
   @assgins nothing ;
   @ensures playing with the corresponding card ( placing it in the board ) and applying its effect ; */
void apply_special_card_effect(board b, carte* c);

 
/* @requires a valid board and tetromino structure  ;
   @assigns board b ;
   @ensures fills the reserve ; */
void set_reserve_tetromino(board b, tetromino t);

/* @requires a valid board structure ;
   @assigns nothing ;
   @ensures returning the tetromino in the reserve; */
tetromino get_reserve(board b);

 /* @requires a valid board type, two integers (row & col);
     @assigns a place to the tetromino in the board at the line row and the column col; 
     @ensures places the tetromino (at (row,col) position on the board) in the reserve; */
void place_in_reserve(board b, int row, int col);


 /* @requires a valid board type, two integers (row & col);
     @assigns a place to the tetromino in the board at the line row and the column col; 
     @ensures places the tetromino of the reserve at (row,col) position on the board and removes it from the reserve ; */
void remove_from_reserve(board b, int row, int col);


/* @requires a valid board structure ;
   @assigns nothing ;
   @ensures removes the tetromino from the reserve if it is possible; */
void remove_tetromino_from_reserve(board b);

 #endif
