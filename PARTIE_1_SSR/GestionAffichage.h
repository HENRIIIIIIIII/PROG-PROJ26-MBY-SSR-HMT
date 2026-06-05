#ifndef GESTION_AFFICHAGE_H
#define GESTION_AFFICHAGE_H

#include "GestionValeurlotoGagnante.h"

#define NUMERO_A_JOUER 6
#define MAX_SCAN 100

// Affichage de la valeur qui est ressortie le plus de fois
void afficherValeurPlusGagnante(int valeurs[], int nbValeurs);

// Affichage de la valeur qui est ressortie le moins de fois
void afficherValeurMoinsGagnante(int valeurs[], int nbValeurs);

//Affichage des 6 valeurs qui sont sorties le plus souvent dans l'ordre croissant
void afficher6MeilleursNumeros(int valeurs[], int nbValeurs);

//Affichage des 6 valeurs qui sont sorties le moins souvent dans l'ordre croissant
void afficher6MoinsBonsNumeros(int valeurs[], int nbValeurs);

void File_sorting(Loto* loto);
// this function duplicates the values into another table so then we can scan each number the number of times there are numbers
// To then put in the second column how many times that number got repeated.
// move_over remembers where we are in the text
// Tb_compare duplicates the values so we can compare them.

#endif /* GESTION_AFFICHAGE_H */
