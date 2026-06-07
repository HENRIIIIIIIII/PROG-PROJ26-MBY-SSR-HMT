#ifndef GESTION_AFFICHAGE_H
#define GESTION_AFFICHAGE_H

#include "constantes.h"
#include "GestionValeurlotoGagnante.h"

// Affichage de la valeur qui est ressortie le plus de fois
void afficherValeurPlusGagnante(int valeurs[], int nbValeurs);

// Affichage de la valeur qui est ressortie le moins de fois
void afficherValeurMoinsGagnante(int valeurs[], int nbValeurs);

// Affichage des 6 valeurs qui sont sorties le plus souvent dans l'ordre croissant
void afficher6MeilleursNumeros(int valeurs[], int nbValeurs);

// Affichage des 6 valeurs qui sont sorties le moins souvent dans l'ordre croissant
void afficher6MoinsBonsNumeros(int valeurs[], int nbValeurs);

// Tri des fréquences de chaque valeur du loto
void trierFichier(Loto* loto);

#endif /* GESTION_AFFICHAGE_H */
