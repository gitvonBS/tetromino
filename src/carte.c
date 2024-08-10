#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/carte.h"

/* Definition of the create_card function */
carte* create_card(nom_carte n) {
    carte* new_card = (carte*)malloc(sizeof(carte));
    if (new_card != NULL) {
        new_card->nom = n;
    }
    return new_card;
}

/* Definition of the get_name_card function */
nom_carte get_name_card(carte* c) {
    return c->nom;
}

/* Definition of the free_card function */
void free_card(carte* c) {
    free(c);
}

// int main() {
/* Creating a card with the name THUY_VO */
//    carte* my_card = create_card(THUY_VO);
//      if (my_card != NULL) {
/* Getting the name of the card
        nom_carte card_name = get_name_card(my_card);

        // Displaying the name of the card
        switch (card_name) {
            case THUY_VO:
                printf("Card: THUY_VO\n");
                break;
            case DAVID_ROUSSEL:
                printf("Card: DAVID_ROUSSEL\n");
                break;
            default:
                printf("Unknown card\n");
        }

/* Freeing the memory allocated for the card */
//        free_card(my_card);
//    } 
//    else {
//    printf("Error creating card\n");
//    }
//      return 0;
//   } 
