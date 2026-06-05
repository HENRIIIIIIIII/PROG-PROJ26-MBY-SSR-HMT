#include <stdbool.h>
#include "GestionValeurlotoGagnante.h"

//----------------------------------------------------------------------------------//
// Nom de la fonction: insererValeur
// Entrée / Sortie / I/O :  int valeurs[] (tableau comportant les valeurs du Loto), 
//                          int* nbValeurs (pointeur afin de compter le nombre de fois qu'un valeur est sortie)
//                          int nouvelleValeur (Valeur que l'on veut inscrire dans le fichier)
// Description: Fonction permettant d'insérer une nouvelle valeur dans le fichier loto
// Date modfification: le 01.06.26
// Remarque: Retourne true si succes, false si le tableau est plein
//----------------------------------------------------------------------------------//
bool insererValeur(int valeurs[], int* nbValeurs, int nouvelleValeur)
{
    if (*nbValeurs >= MAX_VALEURS) {
        return false;
    }
    valeurs[*nbValeurs] = nouvelleValeur;
    (*nbValeurs)++;
    return true;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: supprimerDerniereValeur
// Entrée / Sortie / I/O :  int valeurs[] (tableau comportant les valeurs du Loto), 
//                          int* nbValeurs (pointeur afin de compter le nombre de fois qu'un valeur est sortie)
// Description: Fonction permettant de supprimer la dernière valeur introduite dans le fichier loto
// Date modfification: le 01.06.26
// Remarque: Retourne true si succes, false si le tableau est vide
//----------------------------------------------------------------------------------//
bool supprimerDerniereValeur(int* nbValeurs)
{
    if (*nbValeurs <= 0) {
        return false;
    }
    (*nbValeurs)--;
    return true;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: insererValeur
// Entrée / Sortie / I/O :  int valeurs[] (tableau comportant les valeurs du Loto), 
//                          int* nbValeurs (pointeur afin de compter le nombre de fois qu'un valeur est sortie)
//                          int nouvelleValeur (Valeur que l'on veut inscrire dans le fichier)
// Description: Fonction permettant de remplacer la dernière valeur introduite avec la nouvelle valeur
// Date modfification: le 01.06.26
// Remarque: Retourne true si succes, false si le tableau est vide
//----------------------------------------------------------------------------------//
bool modifierDerniereValeur(int valeurs[], int nbValeurs, int nouvelleValeur)
{
    if (nbValeurs <= 0) {
        return false;
    }
    valeurs[nbValeurs - 1] = nouvelleValeur; //remplacement de la valeur dans le tableau
    return true;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: compterOccurrences
// Entrée / Sortie / I/O : I int valeurs[] (tableau comportant les valeurs du Loto), 
//                         I int nbValeurs val max de la plage de valeurs du Loto
//                         I int valeur (Valeur que l'on veut compter)
//                         O int compteur (nombre de fois que la valeur a été tirée)
// Description: Fonction permettant de compter le nombre de fois qu'une valeur est comptée
// Date modfification: le 01.06.26
// Remarque: -
//----------------------------------------------------------------------------------//
int compterOccurrences(int valeurs[], int nbValeurs, int valeur)
{
    int compteur = 0;

    for (int i = 0; i < nbValeurs; i++)
    {
        if (valeurs[i] == valeur)
        {
            compteur++;
        }
    }

    return compteur;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: rechercherValeurPlusGagnante
// Entrée / Sortie / I/O : I int valeurs[] (tableau comportant les valeurs du Loto), 
//                         I int nbValeurs val max de la plage de valeurs du Loto
//                         O int meilleureValeur (nombre de fois que la valeur la plus tirée a été tirée)
// Description: Fonction permettant de compter le nombre de fois que la valeur la plus ressortie à été tirée
// Date modfification: le 01.06.26
// Remarque: Si plusieurs valeurs ont le même nmbre de sortie max alors la valeur inférieur sera celle de sortie
//----------------------------------------------------------------------------------//
int rechercherValeurPlusGagnante(int valeurs[], int nbValeurs)
{
    int meilleureValeur = valeurs[0];
    int maxOcc = 0;

    for (int i = 1; i < nbValeurs; i++)
    {
        int occ = compterOccurrences(valeurs, nbValeurs, valeurs[i]);

        if (occ > maxOcc)
        {
            maxOcc = occ;
            meilleureValeur = valeurs[i];
        }
    }

    return meilleureValeur;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: rechercherValeurMoinsGagnante
// Entrée / Sortie / I/O : I int valeurs[] (tableau comportant les valeurs du Loto), 
//                         I int nbValeurs (pointeur afin de compter le nombre de fois qu'un valeur est sortie)
//                         O int pireValeur (nombre de fois que la valeur la moins tirée a été tirée)
// Description: Fonction permettant de compter le nombre de fois que la valeur la moins ressortie à été tirée
// Date modfification: le 01.06.26
// Remarque: Si plusieurs valeurs ont le même nombre de sortie max alors la valeur inférieur sera celle de sortie
//----------------------------------------------------------------------------------//
int rechercherValeurMoinsGagnante(int valeurs[], int nbValeurs)
{
    int pireValeur = valeurs[0];
    int minOcc = compterOccurrences(valeurs, nbValeurs, valeurs[0]);

    for (int i = 1; i < nbValeurs; i++)
    {
        int occ = compterOccurrences(valeurs, nbValeurs, valeurs[i]);

        if (occ < minOcc)
        {
            minOcc = occ;
            pireValeur = valeurs[i];
        }
    }

    return pireValeur;
}