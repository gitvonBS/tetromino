#include "../include/interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/constantes.h"

board Initialisation_Board(){
    board b = create_board(BOARD_SIZE , BOARD_SIZE , BOARD_SIZE * BOARD_SIZE);
    for(int i = 0; i< NB_GENERATED_TETROMINOS ;i++){ 
        tetromino t = create_random_tetromino();
        add_tetromino_to_bag(b,t);
    }
    return b;
}


void Tour_Joueur(board b,int *sel_pr,int *sel_pc, int *score){
    int nulval1 = -1;
    int nulval2 = -1;
    int choix;
    int handle;
    char msg[MAX_MESSAGE_SIZE];
    choix = choose_action();
    handle = handle_reserve_actions();

    if (choix == 0){
        *score = get_score(b);
        sprintf(msg, "Le joueur a décidé de terminer la partie son score est : %d", *score);
        display_end_game(b);
        display_message(msg);
        free_board(b);
        exit(1);
    }

    if (choix == 1){
        tetromino new_t = create_random_tetromino();
        tetromino t = select_tetromino_in_bag(b);
        remove_tetromino_from_bag(b,t);
        add_tetromino_to_bag(b,new_t);
        strcpy(msg, "Entrer la position du tetromino:");
        ask_place_tetromino(b, sel_pr, sel_pc, t);
        place_tetromino(b, *sel_pr, *sel_pc , t);
        if (handle == 0){ 
            printf("Aucune action sur la réserve");
        }
        if (handle == 1){ 
            ask_place_in_reserve(b,sel_pr, sel_pc); //choix du tétromino à ajouter dans la réserve
            place_in_reserve(b,*sel_pr, *sel_pc);
        }

        if (handle == 2){ 
            ask_remove_from_reserve(b,sel_pr, sel_pc);//choix de la case du plateau à laquelle on va ajouter le tétromino que l'on aura retiré de la réserve
            remove_from_reserve(b,*sel_pr, *sel_pc);
        }

    }

    if (choix == 2){
        if (get_nb_placed(b) == -1){
            printf("Il n'y a aucun tetromino sur la grille \n");
            Tour_Joueur(b, sel_pc , sel_pc, score);
        }
        else {
        tetromino t = select_tetromino_on_grid(b);
        nulval2 = get_pc(get_tuples(b)[get_id(t)]);
        nulval1 = get_pr(get_tuples(b)[get_id(t)]);
        remove_tetromino(b,&nulval1 , &nulval2,t);
        strcpy(msg, "Entrer la nouvelle position du tetromino ainsi qu'une nouvelle rotation:\n");
        ask_place_tetromino(b, sel_pr, sel_pc, t);
        place_tetromino(b, *sel_pr, *sel_pc , t);
        }
        
        if (handle == 0){ 
            printf("Aucune action sur la réserve");
        }
        if (handle == 1){ 
            ask_place_in_reserve(b,sel_pr, sel_pc);
            place_in_reserve(b,*sel_pr, *sel_pc);
        }

        if (handle == 2){ 
            ask_remove_from_reserve(b,sel_pr, sel_pc);
            remove_from_reserve(b,*sel_pr, *sel_pc);
        }
    }
}


int main(){

    randomize();

    int sel_pr;
    int sel_pc;
    int score;
    board b;

    b = Initialisation_Board();
    display_board(b);
    while(1){
        Tour_Joueur(b, &sel_pr, &sel_pc, &score);
        display_board(b);
        // si un tétromino est dans la réserve et que deux pièces du sac sont placées sur le plateau
        if (get_reference_cells_count(b) == 2 && get_reserve(b) != NULL) {  
            remove_tetromino_from_reserve(b);  // la pièce de réserve disparaît et la réserve est de nouveau libre 
            }
        display_reserve(b); //affiche les informations de la réserve
    }
    free_board(b);
}
