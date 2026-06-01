#pragma once
// GestionFonctions.h

#ifndef GESTION_FONCTIONS
#define GESTION_FONCTIONS

#define NUMERO_A_JOUER 6

// Insertion d'un nouveau tirage
void insererValeur(int valeurs[], int* nbValeurs, int nouvelleValeur);

// Suppression de la dernière valeur saisie
void supprimerDerniereValeur(int valeurs[], int* nbValeurs);

// Modification de la dernière valeur saisie
void modifierDerniereValeur(int valeurs[], int nbValeurs, int nouvelleValeur);

// Recherche de la valeur la plus gagnante
int rechercherValeurPlusGagnante(int valeurs[], int nbValeurs);

// Recherche de la valeur la moins gagnante
int rechercherValeurMoinsGagnante(int valeurs[], int nbValeurs);

// Nombre d'occurrences d'une valeur
int compterOccurrences(int valeurs[], int nbValeurs, int valeur);

// Affichage de la valeur qui est ressortie le plus de fois
void afficherValeurPlusGagnante(int valeurs[], int nbValeurs);

// Affichage de la valeur qui est ressortie le moins de fois
void afficherValeurMoinsGagnante(int valeurs[], int nbValeurs);

//Affichage des 6 valeurs qui sont sorties le plus souvent dans l'ordre croissant
void afficher6MeilleursNumeros(int valeurs[], int nbValeurs);

//Affichage des 6 valeurs qui sont sorties le moins souvent dans l'ordre croissant
void afficher6MoinsBonsNumeros(int valeurs[], int nbValeurs);

#endif