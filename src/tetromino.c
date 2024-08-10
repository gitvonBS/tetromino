#include <stdio.h>
#include <stdlib.h>
#include "../include/tetromino.h"
#include <time.h>
#include "../include/constantes.h"


struct struct_tetromino {
    int type ; //un chiffre compris entre 1 et 6
    int nb_rotations; //le nb de fois que le tetromino à été tourné dans le sens horaire de 90°
    int id; // un entier entre 1 et max_id
    int nb_points; //le score apporté par le tétromino
    int cells[COORD_CELLS];//liste des coordonnées des cellules du tetromino sous cette forme (l1,c1,l2,c2,l3,c3,l4,c4)
};

/* le type tetromino est déjà défini dans tetromino.h ainsi:
typedef struct_tetromino * tetromino ;
*/


/*variable globale du id*/
int identifiant = 1; //cette variable va etre incrémentée de 1 à chaque nouvelle création de tétromino

void randomize() {
    srand(time(NULL));
}

int random_int (int min ,int max) {
    if (min > max){ //le cas où la borne inférieure est supérieure à la borne supérieure
        printf("minimum bound is greater than the maximum bound");
        exit(1);
    }
    else
        return min + rand() % (max - min + 1);
}

tetromino create_random_tetromino(){
    return create_tetromino(random_int(0,6), 0, random_int(1,3));
}

tetromino create_tetromino(int type_tetro, int orientation, int points){
    tetromino created_tetromino = malloc(sizeof(struct struct_tetromino));;
    created_tetromino->type = type_tetro;
    set_orientation_tetromino(orientation, created_tetromino);
    created_tetromino->nb_points = points;
    created_tetromino->id = identifiant;
    identifiant += 1 ;
    if (identifiant > MAX_ID){
        printf("la taille du id dépasse la taille d'un int");
        exit(3);
    }
    return created_tetromino;
}


void free_tetromino(tetromino tetro){
    free(tetro);
}


int get_type(tetromino tetro){
    return tetro->type;
}

int get_id(tetromino tetro){
    return tetro->id ;
}


int get_nb_points(tetromino tetro){
    return tetro->nb_points;
}

int* get_cells(tetromino tetro){
    return tetro->cells;
}

int exists_in_list(int n, int* l){
    int length = sizeof(l);
    if (length <= 0)
        return 0;
    for(int i = 0 ; i < length ; i += 1)
        if (l[i] == n)
            return 1;
    return 0;
}

int get_nb_rotations(tetromino tetro){
    return tetro->nb_rotations;
}

void set_orientation_tetromino(int orientation, tetromino created_tetromino){
    created_tetromino->nb_rotations = orientation ; 
    int type_tetro = created_tetromino->type;
    switch (type_tetro) //une inplémentation exhaustive de tous les tetrominos sous différentes orientations
    {
    case 0: //I
        switch (orientation % 2)
        {
        case 0:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = 0;
            created_tetromino->cells[3] = 1;
            created_tetromino->cells[4] = 0;
            created_tetromino->cells[5] = 2;
            created_tetromino->cells[6] = 0;
            created_tetromino->cells[7] = 3;
            break;
        case 1:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = -1;
            created_tetromino->cells[3] = 0;
            created_tetromino->cells[4] = -2;
            created_tetromino->cells[5] = 0;
            created_tetromino->cells[6] = -3;
            created_tetromino->cells[7] = 0;
            break;
        default:
            break;
        }
        break;
    case 1: //O
        created_tetromino->cells[0] = 0;
        created_tetromino->cells[1] = 0;
        created_tetromino->cells[2] = 0;
        created_tetromino->cells[3] = 1;
        created_tetromino->cells[4] = -1;
        created_tetromino->cells[5] = 0;
        created_tetromino->cells[6] = -1;
        created_tetromino->cells[7] = 1;
        break;
    case 2: //T
        switch (orientation % 4)
        {
        case 0:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = -1;
            created_tetromino->cells[3] = -1;
            created_tetromino->cells[4] = -1;
            created_tetromino->cells[5] = 0;
            created_tetromino->cells[6] = -1;
            created_tetromino->cells[7] = 1;
            break;
        case 1:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = -1;
            created_tetromino->cells[3] = -1;
            created_tetromino->cells[4] = -1;
            created_tetromino->cells[5] = 0;
            created_tetromino->cells[6] = -2;
            created_tetromino->cells[7] = 0;
            break;
        case 2:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = -1;
            created_tetromino->cells[3] = 1;
            created_tetromino->cells[4] = 0;
            created_tetromino->cells[5] = 1;
            created_tetromino->cells[6] = 0;
            created_tetromino->cells[7] = 2;
            break;
        case 3:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = -1;
            created_tetromino->cells[3] = 1;
            created_tetromino->cells[4] = -1;
            created_tetromino->cells[5] = 0;
            created_tetromino->cells[6] = -2;
            created_tetromino->cells[7] = 0;
            break;
        default:
            break;
        }
        break;
    case 3: //L
        switch (orientation % 4)
        {
        case 0:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = -1;
            created_tetromino->cells[3] = 2;
            created_tetromino->cells[4] = -1;
            created_tetromino->cells[5] = 0;
            created_tetromino->cells[6] = -1;
            created_tetromino->cells[7] = 1;
            break;
        case 1:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = -1;
            created_tetromino->cells[3] = 0;
            created_tetromino->cells[4] = -2;
            created_tetromino->cells[5] = 0;
            created_tetromino->cells[6] = -2;
            created_tetromino->cells[7] = -1;
            break;
        case 2:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = 0;
            created_tetromino->cells[3] = 1;
            created_tetromino->cells[4] = 0;
            created_tetromino->cells[5] = 2;
            created_tetromino->cells[6] = -1;
            created_tetromino->cells[7] = 2;
            break;
        case 3:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = 0;
            created_tetromino->cells[3] = 1;
            created_tetromino->cells[4] = -1;
            created_tetromino->cells[5] = 0;
            created_tetromino->cells[6] = -2;
            created_tetromino->cells[7] = 0;
            break;
        default:
            break;
        }
        break;
    case 4: //J
        switch (orientation % 4)
        {
        case 0:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = -1;
            created_tetromino->cells[3] = 0;
            created_tetromino->cells[4] = -1;
            created_tetromino->cells[5] = -1;
            created_tetromino->cells[6] = -1;
            created_tetromino->cells[7] = -2;
            break;
        case 1:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = 0;
            created_tetromino->cells[3] = 1;
            created_tetromino->cells[4] = -1;
            created_tetromino->cells[5] = 1;
            created_tetromino->cells[6] = -2;
            created_tetromino->cells[7] = 1;
            break;
        case 2:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = 0;
            created_tetromino->cells[3] = 1;
            created_tetromino->cells[4] = 0;
            created_tetromino->cells[5] = 2;
            created_tetromino->cells[6] = -1;
            created_tetromino->cells[7] = 0;
            break;
        case 3:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = -1;
            created_tetromino->cells[3] = 0;
            created_tetromino->cells[4] = -2;
            created_tetromino->cells[5] = 0;
            created_tetromino->cells[6] = -2;
            created_tetromino->cells[7] = 1;
            break;
        default:
            break;
        }
        break;
    case 5: //S
        switch (orientation % 2)
        {
        case 0:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = 0;
            created_tetromino->cells[3] = 1;
            created_tetromino->cells[4] = -1;
            created_tetromino->cells[5] = 1;
            created_tetromino->cells[6] = -1;
            created_tetromino->cells[7] = 2;
            break;
        case 1:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = -1;
            created_tetromino->cells[3] = 0;
            created_tetromino->cells[4] = -1;
            created_tetromino->cells[5] = -1;
            created_tetromino->cells[6] = -2;
            created_tetromino->cells[7] = -1;
            break;
        default:
            break;
        }
        break;
    case 6: //Z
        switch (orientation % 2)
        {
        case 0:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = 0;
            created_tetromino->cells[3] = 1;
            created_tetromino->cells[4] = -1;
            created_tetromino->cells[5] = 0;
            created_tetromino->cells[6] = -1;
            created_tetromino->cells[7] = -1;
            break;
        case 1:
            created_tetromino->cells[0] = 0;
            created_tetromino->cells[1] = 0;
            created_tetromino->cells[2] = -1;
            created_tetromino->cells[3] = 0;
            created_tetromino->cells[4] = -1;
            created_tetromino->cells[5] = 1;
            created_tetromino->cells[6] = -2;
            created_tetromino->cells[7] = 1;
            break;
        default:
            break;
        }
        break;
    default:
        printf("the tetromino type is not valid");
        exit(2);
        break;
    }
}

/*
Exemple de création d'un tetromino

    randomize();
    int N = 100;
    int* int_table = malloc(N * sizeof(int));
    for(int i = 0 ; i < N ; i += 1 )
        int_table[i] = -1 ;
    tetromino* tetromino_table = malloc(N * sizeof(struct struct_tetromino));
    for(int i = 0 ; i < N ; i += 1 ){
        tetromino tetro = create_random_tetromino();
        tetromino_table[i] = tetro;
    }
    free(int_table);
    free(tetromino_table);
*/
