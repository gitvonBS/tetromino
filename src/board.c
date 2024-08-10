#include <time.h>    /* For seeding rand with time */
#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"
#include "../include/tetromino.h"
#include "../include/carte.h"
#include "../include/constantes.h"
#include "../include/carte.h"


/* Defining the board structure */
struct struct_board {
    int** g;
    int r;
    int c;
    int p;
    tetromino* bag;
    struct tuple* tuples;
    int bag_count;
    int score;
    int nb_placed;
    carte* hand[MAX_CARDS_IN_HAND];
    tetromino reserve; // Réserve contenant un tétromino ou 0 tétromino (NULL dans ce cas)
};
/* g : the grid which is representing the board
    r : number of rows of the board
    c : number of columns of the board
    p : number of places available in the board
    bag : bag which contains the tetrominos
    bag_count : the current number of tetrominos in the bag
    score : the current score of the player
    hand : a list of pointers to cards  */


board create_board(int n, int m, int k){
     board b = malloc(sizeof(struct struct_board));
     if( b == NULL){
         fprintf(stderr, "Error while allocating the memory for the board \n");
         exit(1);
     } ;
     b->score = 0;
/* Assigning n,m and k to the components of the board */
     b-> r = n;
     b-> c = m ;
     b -> p = k ;
     b->bag = malloc(k * sizeof(tetromino));
     b->reserve = create_random_tetromino();
     if( b-> bag == NULL){
         fprintf(stderr, "Error while allocating the memory for the bag of the board \n");
         free_board(b);
         exit(2);
     }
/* Initializing the grid of the game */
     b->g = malloc(n * sizeof(int*));
     for(int i=0; i<n; i+=1){
         b->g[i]=malloc(m * sizeof(int));
     }
/* Initializing the bag which contains the tetrominos */
    b->bag = malloc(k * sizeof(tetromino));
    b->bag_count = 0;
    b->nb_placed = -1;
    b->tuples = (struct tuple*)malloc(sizeof(struct tuple) * MAX_SIZE_TUPLE); // Allocation pour 100 tuples
    for (int i = 0 ;  i < MAX_SIZE_TUPLE ; i += 1){
     b->tuples[i].pr = 0;
     b->tuples[i].pr = 0;
    }
/* Initializing the grid */
    for(int i = 0; i < b->r ; i += 1 )
         for(int j = 0 ; j < b->c ; j += 1)
             b->g[i][j] = 0;
    return b;
}

void free_board(board b){
/* Freeing the allocated memory to the grid, the bag of the board and 
the board itself */
     for(int i=0;i<b->r;i+=1){
         free(b->g[i]);
     }
     free(b->bag);
     free(b);
}
tetromino* list_tetrominos_in_bag(board b){
/* Returning the bag of the board */
     return b->bag;
}

void add_tetromino_to_bag(board b, tetromino t){
/* Adding a tetromino to the bag of the board  and incrementing the 
number of tetrominos in the bag */
     if (b->bag_count < b->p) {
         b->bag[b->bag_count] = t;
/*Incrementing the bag count */
         b->bag_count += 1;
     } else {
         fprintf(stderr, "Bag is full. Cannot add more tetrominos.\n");
     }
}

void remove_tetromino_from_bag(board b, tetromino t) {
     for (int i = 0; i < b->bag_count; i+=1) {
         if (get_id(b->bag[i]) == get_id(t)) {
             for (int j = i; j < b->bag_count - 1; j+=1) {
                 b->bag[j] = b->bag[j + 1];
             }
             b->bag_count-=1;
             break;
         }
     }
}

int min_row(tetromino t) {
/* Returning the maximum relative row coordinate */
     int min_r = 0 ;
     for(int i = 0 ; i < 4 ; i+=1) {
         if(get_cells(t)[2*i] < min_r) {
             min_r = get_cells(t)[2*i];
         }
     }
     return min_r;
  }

int max_col(tetromino t) {
/* Returning the maximum relative column coordinate */
     int max_c = 0 ;
     for(int i = 0 ; i < 4 ; i+=1) {
         if(get_cells(t)[2*i+1] > max_c) {
             max_c = get_cells(t)[2*i+1];
         }
     }
     return max_c;
}

int min_col(tetromino t) {
/* Returning the minimum relative column coordinate */
     int min_c = 0 ;
     for(int i = 0 ; i < 4 ; i+=1) {
         if(get_cells(t)[2*i+1] < min_c) {
             min_c = get_cells(t)[2*i+1];
         }
     }
     return min_c;
}

int check_place_tetromino(board b, int r, int c, tetromino t) {
/* Checking if this position exists in the board */
     if ( r > b->r || min_col(t) + c < 0 || c + max_col(t) > b->c || 
min_row(t) + r < 0 ) {
         return 0;
     }

/* Checking if this position is already full */
     for (int i = 0; i < 4; i+=1) {
         int row = r + get_cells(t)[i * 2];
         int col = c + get_cells(t)[i * 2 + 1];
         if (b->g[row][col] != 0) {
/* This position is already by a tetromino */
             return 0;
         }
     }
/* The tetromino can be placed in this position */
     return 1;
}

/*definition des cases spéciales*/
const int cases_speciales[8] = {7, 1, 5, 3, 4, 2, 6, 0};

int place_tetromino(board b, int r, int c, tetromino t) {
/* Checking if this position exists in the board */
     if (!check_place_tetromino(b, r, c, t)) {
/* The tetromino cannot be placed in this position */
         printf("Impossible de placer le tetromino ici");
         return 0;
     }

/* Placing the tetromino on the grid of the board */
     for (int i = 0; i < 4; i+=1) {
         int row = r + get_cells(t)[i * 2];
         int col = c + get_cells(t)[i * 2 + 1];
         /*if (col == cases_speciales[row]){
            add_random_card_to_hand(hand);
         }*/
         if (i == 0) 
            b->g[row][col] = -(get_id(t));
         else
         b->g[row][col] = get_id(t);
     }

  /* The tetromino has been placed successfully */
     b->nb_placed +=1;
     b->tuples[b->nb_placed].pr = r;
     b->tuples[b->nb_placed].pc = c;
     b->tuples[b->nb_placed].t = t;
     return get_id(t);
}

void remove_tetromino(board b, int* pr, int* pc, tetromino t){
/* Trying to find the tetromino and removing it from the bag */
/* Moving the next tetrominos in order to fill the void in the grid */
     b->g[*pr][*pc] = 0;
     for (int i = 0; i < b->r; i+=1) {
         for (int j = 0; j < b->c ;j+=1) {
             if (abs(b->g[i][j]) == get_id(t)){
/* This space is considered empty */
                 b->g[i][j] = 0;
                     if (pr != NULL && pc != NULL) {
/* Saving the last position encoutered */
                         *pr = i;
                         *pc = j;
                     }
             }
         }
     }
     b->nb_placed -=1;
}

tetromino get_tetromino(board b, int r, int c){
/* We need to use the ID of the tetromino to determine it on the board */
/* Checking if the the cell is empty or if the ID does not correspond 
to a tetromino */
     if (r < 0 || r > b->r || c <0 || c > b->c) {
     fprintf(stderr,"It is impossible to have a tetromino at this position of the board\n");
     exit(3);
     }
     else{
     for(int i = 0 ; i< b->nb_placed+1; i++){
        /* Testing the content of b->tuples[i] */
         printf(" c = %d , r = %d, ",(b->tuples[i].pc),(b->tuples[i].pr));
         if(b->tuples[i].pc == c && b->tuples[i].pr == r){
             return b->tuples[i].t;
         }
     }
     fprintf(stderr,"Il n'y a aucun tetromino sur cette case");
     return NULL;
     }
}

void update_current_score(board b) {
     b->score = 0;
     if (b->nb_placed == -1)
         printf("la grille est encore vide \n");
     for (int i = 0 ; i < b->nb_placed + 1 ; i += 1){
         b->score += get_nb_points(b->tuples[i].t);
     }
     printf("score updated \n");
}

int get_score(board b){
/* Returning the current score of the player */
     update_current_score(b);
     return b->score;
}

int get_r(board b) {
     return b->r;
}

int get_c(board b) {
     return b->c;
}

int get_p(board b) {
     return b->p;
}

int get_bag_count(board b) {
     return b->bag_count;
}

tetromino* get_bag(board b) {
     return b->bag;
}

int** get_grid(board b) {
     return b->g;
}

int get_nb_placed(board b) {
     return b->nb_placed;
}

struct tuple* get_tuples(board b) {
     return b->tuples;
}

int get_pr(struct tuple elem_tuples) {
     return elem_tuples.pr;
}

int get_pc(struct tuple elem_tuples) {
     return elem_tuples.pc;
}

void add_card_to_hand(board b, carte* c) {
     /* Using a loop in order to add a card to the hand of the player */
     for (int i = 0; i < MAX_CARDS_IN_HAND; i+=1) {
         b->hand[i] = malloc(sizeof(carte));
         if (b->hand[i] == NULL){
             b->hand[i] = c;
             break;
         }
     }
}

carte** list_cards_in_hand(board b) {
     return b->hand;
}

void remove_card_from_hand(board b, carte* c) {
    /* Using a loop in order to remove a card from the hand of the player */
     for (int i = 0; i < MAX_CARDS_IN_HAND; i+=1) {
         if (b->hand[i] == c) {
             b->hand[i] = NULL;
             free_card(c);
     /* Freeing the allocated memory */
             break;
         }
     }
}
/* Special card : Lucienne Pacave */
void apply_random_normal_to_special_case(board b) {
     /* Seed the random number generator */
     srand(time(NULL));

     /* Generate random row and column indices within the board dimensions */
     int random_row = rand() % get_r(b);
     int random_col = rand() % get_c(b);

     /* Change a random normal cell to special (if it's currently normal) */
     if (get_grid(b)[random_row][random_col] == 0) {
         get_grid(b)[random_row][random_col] = 1;
     /* Assuming '1' represents a special cell */
         printf("Une case normale aléatoire du plateau est devenue spéciale.\n");
     } else {
         printf("La case sélectionnée est déjà spéciale.\n");
     }
}
/* Special card : Marie Szafranski */
void add_extra_tetromino_to_bag(board b) {
     /* Seed the random number generator */
     srand(time(NULL));
     /* Creating a new tetromino with the random ID */
     tetromino new_tetromino = create_random_tetromino();
     /* Adding the new tetromino to the bag */
     add_tetromino_to_bag(b, new_tetromino);
     printf("Une nouvelle pièce a été ajoutée au sac.\n");
     /* Freeing the allocated memory */
     free(new_tetromino);
}
/* Special card : Cyril Benezet */
void replace_bag_with_selected_tetromino(board b, tetromino t) {
     /* Replacing all tetrominos in the bag with the specified tetromino */
     for (int i = 0; i < get_bag_count(b); i++) {
         remove_tetromino_from_bag(b, get_bag(b)[i]);
     }
     /* Adding the selected tetromino to the bag */
     add_tetromino_to_bag(b, t);
     printf("Le sac a été remplacé par un nouveau tétromino.\n");
}
/* Special card : Renaud Rioboo */
void remove_selected_pieces_from_board(board b) {
     /* Asking the player to remove some tetrominos */
     printf("Choisissez les tetrominos à supprimer du plateau.\n");
     printf("Entrez les coordonnées (ligne colonne) de chaque pièce à supprimer (ou -1 pour terminer) :\n");
     int row, col;
     int total_penalty = 0;
    /* Reading the chosen tetrominos to remove */
     while (1) {
         scanf("%d %d", &row, &col);
         /* Verify if the player doesn't want to stop */
         if (row == -1 && col == -1) {
             break;
         }
         /* Checking the coordinates */
         if (row < 0 || row >= get_r(b) || col < 0 || col >= get_c(b)) {
             printf("Coordonnées invalides. Veuillez réessayer.\n");
             continue;
         }
         /* Checking if we have a tetromino in this specific space */
         tetromino selected_tetromino = get_tetromino(b, row, col);
         if (selected_tetromino == NULL) {
             printf("Aucune tetro à cet emplacement. Veuillez réessayer.\n");
             continue;
         }
         /* Calculating the penalty */
         int piece_value = get_nb_points(selected_tetromino);
         total_penalty += 1 + piece_value;
         /* One point penalty + the number of points of the tetromino*/
         /* Removing the tetromino */
         remove_tetromino(b, &row, &col, selected_tetromino);
     }
     /* Updating the score*/
     b->score -= total_penalty;

     printf("Tetros sélectionnées supprimées du plateau. Pénalité de score appliquée : %d points.\n", total_penalty);
} 
/* Special card : Massinissa Merabet */
void add_piece_to_reserve(board b, int row, int col) {
    if (b->reserve == NULL) {
        tetromino t = get_tetromino(b, row, col);
        if (t != NULL) {
            set_reserve_tetromino(b, t);
            printf("Massinissa Merabet effect: Added a new identical piece to the reserve.\n");
        } else {
            printf("No tetromino at the specified location to add to the reserve.\n");
        }
    } else {
        printf("Reserve is full. Massinissa Merabet effect cannot be applied.\n");
    }
}
/* Special card : Laurent Bourard */
void switch_card_bag_reserve(board b, tetromino t) {
    if (b->reserve != NULL) {
        remove_tetromino_from_bag(b, t);
        tetromino temp = b->reserve;
        b->reserve = t;
        add_tetromino_to_bag(b, temp);
        printf("Laurence Bourard effect: Exchanged a piece from the bag with the reserve.\n");
    } else {
        printf("Reserve is empty. Laurence Bourard effect cannot be applied.\n");
    }
}
/* Special card : David Roussel */
void remove_card_from_reserve(board b) {
    if (b->reserve != NULL) {
        b->reserve = NULL;
        printf("David Roussel effect: Removed the tetromino from the reserve.\n");
    } else {
        printf("Reserve is empty. David Roussel effect cannot be applied.\n");
    }
}

void set_reserve_tetromino(board b, tetromino t) { 
    if (b->reserve == NULL) { 
        b->reserve = t;
    }

    else { 
        printf("the reserve is full, clear it before setting");
    }
}

tetromino get_reserve(board b) { 
    return b->reserve;
}


void place_in_reserve(board b, int row, int col) {
    int r = row;
    int c = col;
    tetromino t = get_tetromino(b, r, c);
        if (t) {
            set_reserve_tetromino(b, t);
            printf("Placed in reserve: Tetromino ID %d\n", get_id(t));
        }
        else {
            printf("Reserve is full\n");
        }
}

void remove_from_reserve(board b, int row, int col) {
    int r = row;
    int c = col;
    if (b->reserve) {
            place_tetromino(b, r, c, b->reserve);
            printf("Placed from reserve onto the board.\n");
            b->reserve = NULL;
        } else {
            printf("Reserve is empty!\n");
        }
        
}

void remove_tetromino_from_reserve(board b) {
    if (b->reserve) {  
        b->reserve = NULL;  
        printf("Tetromino in reserve has been removed\n");
    } else {
        printf("No tetromino in reserve to remove\n");
    }
}



// int main() {
// /* Creating a new board with 4 rows, 4 columns, and a bag size of 2 */
//     board b = create_board(4, 4, 2);
// /* Creating some tetrominos and add them to the bag */
//     tetromino t1 = malloc(sizeof(struct struct_tetromino));
//     t1->id = 1;
//     add_tetromino_to_bag(b, t1);

//     tetromino t2 = malloc(sizeof(struct struct_tetromino));
//     t2->id = 2;
//     add_tetromino_to_bag(b, t2);
// /* Listing tetrominos in the bag */
//     printf("Tetrominos in the bag:\n");
//     tetromino* bag = list_tetrominos_in_bag(b);
//     for (int i = 0; i < b->bag_count; i++) {
//         printf("ID of the tetromino : %d\n", bag[i]->id);
//     }

// /* Attempt to add another tetromino to a full bag */
//     tetromino t3 = malloc(sizeof(struct struct_tetromino));
//     t3->id = 3;
// /* When adding the third tetromino , the bag became full */   
//     add_tetromino_to_bag(b, t3); 
// /* Removing a tetromino from the bag */
//     remove_tetromino_from_bag(b, t1);

// /* Listing tetrominos in the bag after removal */
//     printf("\nCurrent tetrominos in the bag :\n");
//     bag = list_tetrominos_in_bag(b);
//     for (int i = 0; i < b->bag_count; i++) {
//         printf("ID of the tetromino : %d\n", bag[i]->id);
//     }
// /* Placing a tetromino on the grid of the board */
//     place_tetromino(b, 0, 0, t1);
// /* Printing the tetromino in the center of the board */
//     tetromino t = get_tetromino(b, 0, 0);
//     if (t != NULL) {
//         printf("Tetromino found in the center position with the ID : %d\n", t->id);
//     } 
//     else {
//         printf("No tetromino found in the center position\n");
//     }
// /* Printing the current score of the player */
//     update_current_score(b, 2);
//     printf("Current score of the player : %d\n", get_score(b));
// /* Freeing the memory */
//     free_board(b);

//     return 0;
// } 
