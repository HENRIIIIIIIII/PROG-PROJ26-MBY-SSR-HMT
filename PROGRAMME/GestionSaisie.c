#include <stdio.h>
#include "constantes.h"

//----------------------------------------------------------------------------------//
// Nom de la fonction: viderBuffer
// Description: Vide le buffer d'entree standard apres un scanf pour eviter
//              que les caracteres residuels soient relus.
//----------------------------------------------------------------------------------//
void viderBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: lireEntier
// Description: Lit un entier au clavier avec validation du retour scanf.
//              Boucle tant que le retour n'est pas 1 (saisie valide).
//----------------------------------------------------------------------------------//
int lireEntier(int *p) {
    while (scanf(FORMAT_SCANF_INT, p) != 1) {
        viderBuffer();
        printf(ERR_SAISIE_INT);
    }
    viderBuffer();
    return 1;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: lireCaractere
// Description: Lit un caractere au clavier avec validation du retour scanf.
//              Boucle tant que le retour n'est pas 1 (saisie valide).
//----------------------------------------------------------------------------------//
int lireCaractere(char *p) {
    while (scanf(FORMAT_SCANF_CHAR, p) != 1) {
        viderBuffer();
        printf(ERR_SAISIE_CHAR);
    }
    viderBuffer();
    return 1;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: lireChaine
// Description: Lit une chaine de caracteres au clavier avec validation du retour.
//              Boucle tant que le retour n'est pas 1 (saisie valide).
//----------------------------------------------------------------------------------//
int lireChaine(char *s, unsigned int n) {
    (void)n; // taille max fournie pour compatibilite future
    while (scanf(FORMAT_SCANF_STR49, s) != 1) {
        viderBuffer();
        printf(ERR_SAISIE_STR);
    }
    viderBuffer();
    return 1;
}
