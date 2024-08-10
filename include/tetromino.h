#ifndef _TETROMINO_H
#define _TETROMINO_H

/*la cellule de référence est la cellule la plus en bas à gauche du 
tétromino*/

/*type absatrait pour les tetromino*/
typedef struct struct_tetromino* tetromino ;

/*@ requires available memory;
  assigns nothing;
  ensures allocates a memory for a random tetromino and returns it */
tetromino create_random_tetromino();

/*@ requires available memory;
  assigns nothing;
  ensures returns a tetromino of type 'type', orientation that does 90° * 'orientation' with the base one
  (available in the wikipedia page) and a number of points that equals 'points' */
tetromino create_tetromino(int type, int orientation, int points);

/*@ requires tetro not NULL;
  assigns nothing;
  ensures  frees the memory allocated for a tetromino*/
void free_tetromino(tetromino tetro);

/*@ requires nothing;
  assigns nothing;
  ensures returns the type of the tetromino*/
int get_type(tetromino tetro);

/*@ requires nothing;
  assigns nothing;
  ensures returns a unique id for the tetro*/
int get_id(tetromino tetro);

/*@ requires nothing;
  assigns nothing;
  ensures returns the points count of the tetromino*/
int get_nb_points(tetromino tetro);

/*@ requires available memory;
  assigns nothing;
  ensures returns the coordinates of the tetro cells in this form {x1,y1,x2,y2,...}*/
int* get_cells(tetromino tetro);

/*@requires nothing
  @assigns nothing
  @ensures set a seed for rand() function
*/
void randomize();

/*@requires nothing
  @assigns nothing
  @ensures returns a random integer between min and max
*/
int random_int(int min, int max);

/*@requires nothing
  @assigns nothing
  @ensures returns 1 if the integer n is within the list l, 0 otherwhise*/
int exists_in_list(int n, int* l);

/*@requires nothing
  @assigns nothing
  @ensures returns the number of rotations for a tetromino*/
int get_nb_rotations(tetromino tetro);

/*
@ requires orientation to be integer, t valid tetromino
@ assigns tetro
@ ensures changes the orientation on the tetromino.
*/
void set_orientation_tetromino(int orientation, tetromino tetro);

#endif
