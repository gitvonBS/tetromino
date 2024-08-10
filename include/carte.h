#ifndef CARTE_H
#define CARTE_H

/* Defining the enumerated structure which contains the names of the cards */
typedef enum {
    THUY_VO,
    DAVID_ROUSSEL,
    ABASS_SAGNA,
    RENAUD_RIOBOO,
    KEVIN_GOILARD,
    LAURENCE_BOURARD,
    MASSINISSA_MERABET,
    ANNE_LAURE_LIGOZAT,
    CHRISTOPHE_MOUILLERON,
    DJIBRIL_AURELIEN_DEMBELE_CABOT,
    LUCIENNE_PACAVE,
    LAWANDA_GAYDU,
    CHRISTINE_MATIAS,
    GUILLAUME_BUREL,
    CYRIL_BENEZET,
    MATHILDE_MOUGEOT,
    DIMITRI_WATEL,
    MARIE_SZAFRANSKI,
    JULIEN_FOREST,
    LAURENT_PREVEL
} nom_carte;

/* Defining the "carte" structure */
typedef struct {
    nom_carte nom;
} carte;

/* @requires a valid name of the enumerated structure 
   @assigns nothing
   @ensures creating a card with the name n
*/
carte* create_card(nom_carte n);
/* @requires a valid "carte" structure 
   @assigns nothing
   @ensures returning the name of the card c
*/
nom_carte get_name_card(carte* c);
/* @requires a valid "carte" structure 
   @assigns nothing
   @ensures freeing the allocated memory to the "carte" instance c
*/
void free_card(carte* c);

#endif /* CARTE_H */
