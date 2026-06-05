#ifndef GESTION_VALEUR_LOTO_GAGNANTE_H
#define GESTION_VALEUR_LOTO_GAGNANTE_H

#include <stdbool.h>

#define MAX_NOM_LOTO 50
#define MAX_VALEURS 100

// Structure unique regroupant toutes les donnees d'un loto
typedef struct {
    char nom[MAX_NOM_LOTO];
    int  minVal;
    int  maxVal;
    int  nbComplementaires;
    int  minComp;
    int  maxComp;
    int  valeurs[MAX_VALEURS];
    int  nbValeurs;
} Loto;

// Insertion d'un nouveau tirage
bool insererValeur(int valeurs[], int* nbValeurs, int nouvelleValeur);

// Suppression de la derni�re valeur saisie
bool supprimerDerniereValeur(int valeurs[], int* nbValeurs);

// Modification de la derni�re valeur saisie
bool modifierDerniereValeur(int valeurs[], int nbValeurs, int nouvelleValeur);

// Recherche de la valeur la plus gagnante
int rechercherValeurPlusGagnante(int valeurs[], int nbValeurs);

// Recherche de la valeur la moins gagnante
int rechercherValeurMoinsGagnante(int valeurs[], int nbValeurs);

// Nombre d'occurrences d'une valeur
int compterOccurrences(int valeurs[], int nbValeurs, int valeur);

#endif /* GESTION_VALEUR_LOTO_GAGNANTE_H */

