#include <stdio.h>
#include <stdlib.h>
#include "../include/interface.h"
#include "../include/board.h"
#include "../include/constantes.h"
#include "../include/carte.h"
#include "../include/tetromino.h"
int choose_action() { 
    int nb;
    printf("Tapez : \n 0: Pour arrêter le jeu \n 1: Pour prendre un tétromino dans le sac et le placer \n 2: Pour déplacer un tétromino présent sur la grille et éventuellement changer son orientaion:\n 3: Manipuler les cartes \n");
    scanf("%i", &nb);
    return nb;
}


int handle_reserve_actions() {
    int nb;
    printf("Tapez : \n 0: Pour ne faire aucune action sur la réserve \n 1: Pour ajouter une pièce à la réserve \n 2: Pour retirer la pièce de la réserve et la replacer sur le plateau:\n ");
    scanf("%i", &nb);
    return nb;
}

/*definition des cases spéciales*/
const int cases_speciales[8] = {7, 1, 5, 3, 4, 2, 6, 0};
/*
On affiche les infos du jeu : le plateau, le sac, le score, le nombre de lignes, le nombre de colonnes, et
le nombre d'emplacements dans le sac (capacité du sac), le nombre actuel de tétrominos dans le sac.
 */
void display_board(board b) {
    printf("Le nombre de lignes est %i\n", get_r(b));
    printf("Le nombre de colonnes est %i\n", get_c(b));
    printf("Le nombre d'emplacements dans le sac est de %i\n", get_p(b));
    printf("Le nombre actuel de tétrominos dans le sac est de %i\n", get_bag_count(b));

    // Affichage du sac = Affichage des tétrominos
    // Affichage des tétrominos du sac (sac = tetromino* = tableau de tétrominos)
    for (int i = 0; i < get_bag_count(b); i++) {
        printf("Tetromino %i :\n", i + 1);
        int type_tetromino = get_type(get_bag(b)[i]);
        printf("  Type : %i\n", type_tetromino);
        printf("  Nombre de rotations : %i\n", get_nb_rotations(get_bag(b)[i]));
        printf("  ID : %i\n", get_id(get_bag(b)[i]));
        printf("  Nombre de points : %i\n", get_nb_points(get_bag(b)[i]));
        printf("  Coordonnées des cellules : ");
        for (int j = 0; j < BOARD_SIZE; j += 2) {
            printf("(%d, %d) ", get_cells(get_bag(b)[i])[j],get_cells(get_bag(b)[i])[j+1]);
        }
        int coord[8];
        for (int j = 0; j < 8; j += 2) {
            coord[j] =get_cells(get_bag(b)[i])[j];
            coord[j+1] = get_cells(get_bag(b)[i])[j+1];
        }
        affiche_tetromino(type_tetromino, coord);
        printf("\n");
    }

    printf("Votre score est : %i\n", get_score(b));


    // Affichage de la grille
    printf("--");
    for (int k = 0; k < get_c(b); k+=1) {
        printf("%2d", k);
    }
    printf("-\n");

    for (int i = 0; i < get_r(b); i++) {
        printf("%d-", i);
        for (int j = 0; j < get_c(b); j++) {
            //place_tetromino donne des cases valant +id ou -id
            if (get_grid(b)[i][j] < 0) 
                printf("\033[%dm  \033[0m", 40 + ( (- get_grid(b)[i][j]) % 7)); //cellule de référence (seules cases strictement négatives, les autres valent 0 ou +id où id est un identifiant entre 1 et 32766)
            else if (get_grid(b)[i][j] > 0){
                printf("\033[%dm  \033[0m", 40 + ( (get_grid(b)[i][j]) % 7)); //cellule qui n'est pas de référence
            }
            else if(j == cases_speciales[i]){
                printf("\033[41m  \033[0m");
            }
            else {
                printf("\033[47m  \033[0m");
                    }
        }
        printf("\n");
    }
    //test
    for (int i = 0; i < get_r(b); i++) {
        for (int j = 0; j < get_c(b); j++) {
            printf("%3d", get_grid(b)[i][j]);
        }
        printf("\n");
    }
}

void affiche_tetromino(int type, int* coord) {
    int** grille = malloc(4 * sizeof(int*));
    for (int i = 0; i < 4; i++) {
        grille[i] = malloc(6 * sizeof(int)); // Allocation de mémoire pour chaque ligne
        for (int j = 0; j < 6; j++) {
            grille[i][j] = 0;
        }
    }
    
    for (int i = 0; i < 8; i += 2) {
        grille[L_REF + coord[i]][C_REF + coord[i+1]] = 1; //Voir définition dans constantes.h
    }

    printf("\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            if (grille[i][j] == 0)
                printf("\033[47m  \033[0m");
            else
                printf("\033[4%dm  \033[0m", type);
        }
        printf("\n");
    }
    
    for (int i = 0; i < 4; i++)
        free(grille[i]);
    free(grille);
}

tetromino select_tetromino_on_grid(board b) {
    int r;
    printf(" Choisissez un tétromino sur la grille en donnant pour l'instant le numéro de la ligne de sa cellule de référence : ");
    scanf("%i", &r);
    int c;
    printf(" Puis, donnez le numéro de la colonne de sa cellule de référence : ");
    scanf("%i", &c);
    return get_tetromino(b,r,c);
}

tetromino select_tetromino_in_bag(board b) {
    tetromino* l = list_tetrominos_in_bag(b); //l = liste des tétrominos dans le sac
    int id;
    printf(" Choisissez un tétromino dans le sac en donnnant son identifiant id : ");
    scanf("%i", &id);

    for (int i = 0 ;  i < get_bag_count(b) ; i+=1){ 
        if (get_id(l[i]) == id)
            return l[i];
    }
    
    printf("id introuvable \n");
    return select_tetromino_in_bag(b);

}


void ask_place_tetromino(board b, int* pr, int* pc, tetromino t) {
    int r;
    printf(" Sélectionnez une ligne où placer le tétromino dans la grille : ");
    scanf("%i", &r);
    int c;
    printf(" Sélectionnez une colonne où placer le tétromino dans la grille : ");
    scanf("%i", &c);
    ask_orientation_tetromino(t);
    if (check_place_tetromino(b,r,c,t) == 1){

        *pr = r;
        *pc = c;
    }

    else { 
        printf("Impossible de le placer ici refaire un choix");
        ask_place_tetromino(b,pr,pc,t);
        // *pr = -1; si on laisse pr et pc pointer vers -1, on ne pourra plus placer de tétrominos via place_tetromino (cf test avec main.c : aucun affichage de tétrominos).
        // *pc = -1;
    }

}


int get_reference_cells_count(board b) { 
    int acc = 0; //nb de cellules de références = nb de tétrominos placés
    for (int i = 0 ; i < get_r(b) ; i++){
        for (int j = 0 ; j < get_c(b) ; j++){
            if (get_grid(b)[i][j] < 0) //dès qu'il y a une cellule de référence, on la compte dans acc.
                acc++;
        }
    }
    return acc;
}

int get_completed_lines_count(board b) { 
    int acc = 0; //nb de lignes complétées
    for (int i = 0 ; i < get_r(b) ; i++){
        int is_line_completed = 1;
        for (int j = 0 ; j < get_c(b) ; j++){
            if (get_grid(b)[i][j] == 0) { //dès qu'il y a une case vide (sans O ou X), on sort et on ne compte pas la ligne i dans acc.
                is_line_completed = 0;
                break; }
        }
        if (is_line_completed)
            acc++;
    }
    return acc;
}


void display_end_game(board b) {
    // Affichage de la grille
    printf("--");
    for (int k = 0; k < get_c(b); k+=1) {
        printf("%2d", k);
    }
    printf("-\n");

    for (int i = 0; i < get_r(b); i++) {
        printf("%d-", i);
        for (int j = 0; j < get_c(b); j++) {
            //place_tetromino donne des cases valant +id ou -id
            if (get_grid(b)[i][j] < 0) 
                printf("\033[%dm  \033[0m", 40 + ( (- get_grid(b)[i][j]) % 7)); //cellule de référence (seules cases strictement négatives, les autres valent 0 ou +id où id est un identifiant entre 1 et 32766)
            else if (get_grid(b)[i][j] > 0){
                printf("\033[%dm  \033[0m", 40 + ( (get_grid(b)[i][j]) % 7)); //cellule qui n'est pas de référence
            }
            else {
                printf("\033[47m  \033[0m");
                    }
        }
        printf("\n");
    }
    
    printf("FIN DU JEU\n");
    printf("Score final : %i\n", get_score(b));
    printf("Nombre total de tétrominos placés : %i\n", get_reference_cells_count(b));
    printf("Nombre total de lignes complétées : %i\n", get_completed_lines_count(b));
}

void display_message(char* msg) { 
    printf("%s\n", msg);
}

void ask_orientation_tetromino(tetromino tetro){
    int orientation;
    printf(" donner l'orientation de votre tetromino : ");
    scanf("%i", &orientation);
    set_orientation_tetromino(orientation, tetro);
}



void display_reserve(board b) {
    printf("Reserve:\n ");
    if (get_reserve(b)!= NULL) { 
        printf("  Type : %i\n", get_type(get_reserve(b)));
        printf("  Nombre de rotations : %i\n", get_nb_rotations(get_reserve(b)));
        printf("  ID : %i\n", get_id(get_reserve(b)));
        printf("  Nombre de points : %i\n", get_nb_points(get_reserve(b)));
        printf("  Coordonnées des cellules : ");
        for (int j = 0; j < 8; j += 2) {
            printf("(%d, %d) ", get_cells(get_reserve(b))[j],get_cells(get_reserve(b))[j+1]);
        }
    }
    else { 
        printf("Reserve is empty\n");
    }

}

void ask_place_in_reserve(board b, int* pr, int*pc){ 
        int r, c;
        printf("Enter position to place in reserve (row col): ");
        scanf("%d %d", &r, &c);
        if (get_reserve(b) == NULL) {
        *pr = r; 
        *pc = c;
        }

}

void ask_remove_from_reserve(board b, int* pr, int*pc) { 
        int r, c;
        printf("Enter position to remove from reserve (row col): ");
        scanf("%d %d", &r, &c);
        if (get_reserve(b) != NULL) { 
            *pr = r; 
            *pc = c;
        }
}



/* Tests de l'interface */
/*
int main() { 
    choose_action();
    //exemple de l'énoncé : grille 4x4 avec un tétromino Z en (2,2)//
    board b = create_board(4,4,5); 
    tetromino t = create_tetromino(6,0,2);
    add_tetromino_to_bag(b,t);
    place_tetromino(b,2,2,t);
    update_current_score(b,2);
    display_board(b);
*/
    /* Affichage  

Tapez : 
 0: Pour arrêter le jeu 
 1: Pour prendre un tétromino dans le sac et le placer 
 2: Pour déplacer un tétromino présent sur la grille :
 1
Le nombre de lignes est 4
Le nombre de colonnes est 4
Le nombre d'emplacements dans le sac est de 5
Le nombre actuel de tétrominos dans le sac est de 1
Tetromino 1 :
  Type : 6
  Nombre de rotations : 0
  ID : 29594
  Nombre de points : 2
  Coordonnées des cellules : (0, 0) (0, 1) (-1, 0) (-1, -1) 
Votre score est : 100
--0123------
0-....
1-.OO.
2-..XO
3-....
    */
/*
   board b1 = create_board(8,8,4);
   tetromino t1 = create_tetromino(3,3,2);
   add_tetromino_to_bag(b1,t1);
   place_tetromino(b1,6,6,t1);
   display_board(b1);
*/
/* 
Le nombre de lignes est 8
Le nombre de colonnes est 8
Le nombre d'emplacements dans le sac est de 4
Le nombre actuel de tétrominos dans le sac est de 1
Tetromino 1 :
  Type : 3
  Nombre de rotations : 3
  ID : 28085
  Nombre de points : 2
  Coordonnées des cellules : (0, 0) (0, 1) (-1, 0) (-2, 0) 
Votre score est : 100
--01234567------
0-........
1-........
2-........
3-........
4-......O.
5-......O.
6-......XO
7-........
*/
/*
char msg[] = "Ceci est un message test";
printf("%s\n", msg);
display_message(msg);



    return 0;
}
*/
