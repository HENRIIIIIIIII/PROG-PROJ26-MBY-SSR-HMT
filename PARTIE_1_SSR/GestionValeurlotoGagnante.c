#include <stdbool.h>
#include "GestionValeurlotoGagnante.h"

//----------------------------------------------------------------------------------//
// Nom de la fonction: insererValeur
// Entree / Sortie / I/O :  int valeurs[] (tableau des valeurs du Loto),
//                          int* nbValeurs (nombre de valeurs courantes dans le tableau)
//                          int nouvelleValeur (valeur a ajouter)
// Description: Ajoute une nouvelle valeur a la fin du tableau si celui-ci n'est pas plein.
// Date de modification: le 01.06.26
// Remarque: Retourne true si succes, false si le tableau est plein.
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
// Entree / Sortie / I/O :  int* nbValeurs (nombre de valeurs courantes dans le tableau)
// Description: Supprime la derniere valeur du tableau en decrementant le compteur.
// Date de modification: le 01.06.26
// Remarque: Retourne true si succes, false si le tableau est vide.
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
// Nom de la fonction: modifierDerniereValeur
// Entree / Sortie / I/O :  int valeurs[] (tableau des valeurs du Loto),
//                          int nbValeurs (nombre de valeurs courantes dans le tableau)
//                          int nouvelleValeur (nouvelle valeur a placer)
// Description: Remplace la derniere valeur du tableau par une nouvelle valeur.
// Date de modification: le 01.06.26
// Remarque: Retourne true si succes, false si le tableau est vide.
//----------------------------------------------------------------------------------//
bool modifierDerniereValeur(int valeurs[], int nbValeurs, int nouvelleValeur)
{
    if (nbValeurs <= 0) {
        return false;
    }
    valeurs[nbValeurs - 1] = nouvelleValeur;  // Remplacement de la derniere valeur
    return true;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: compterOccurrences
// Entree / Sortie / I/O : I int valeurs[] (tableau des valeurs du Loto),
//                         I int nbValeurs (nombre de valeurs dans le tableau)
//                         I int valeur (valeur a compter)
//                         O int (nombre d'occurrences de la valeur)
// Description: Compte combien de fois une valeur apparait dans le tableau.
// Date de modification: le 01.06.26
//----------------------------------------------------------------------------------//
int compterOccurrences(int valeurs[], int nbValeurs, int valeur)
{
    int compteur = 0;

    // Parcours sequentiel de toutes les valeurs
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
// Entree / Sortie / I/O : I int valeurs[] (tableau des valeurs du Loto),
//                         I int nbValeurs (nombre de valeurs dans le tableau)
//                         O int (valeur la plus frequente)
// Description: Trouve la valeur qui apparait le plus de fois dans le tableau.
//              Si plusieurs valeurs ont le meme nombre de sorties max,
//              la valeur inferieure est selectionnee (premiere trouvee).
// Date de modification: le 01.06.26
//----------------------------------------------------------------------------------//
int rechercherValeurPlusGagnante(int valeurs[], int nbValeurs)
{
    if (nbValeurs <= 0) {
        return -1;
    }
    int meilleureValeur = valeurs[0];
    int maxOcc = 0;

    // On parcourt chaque valeur et on compare son nombre d'occurrences
    // avec le maximum trouve jusqu'a present
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
// Entree / Sortie / I/O : I int valeurs[] (tableau des valeurs du Loto),
//                         I int nbValeurs (nombre de valeurs dans le tableau)
//                         O int (valeur la moins frequente)
// Description: Trouve la valeur qui apparait le moins de fois dans le tableau.
//              Si plusieurs valeurs ont le meme nombre de sorties min,
//              la valeur inferieure est selectionnee (premiere trouvee).
// Date de modification: le 01.06.26
//----------------------------------------------------------------------------------//
int rechercherValeurMoinsGagnante(int valeurs[], int nbValeurs)
{
    if (nbValeurs <= 0) {
        return -1;
    }
    int pireValeur = valeurs[0];
    int minOcc = compterOccurrences(valeurs, nbValeurs, valeurs[0]);

    // On parcourt chaque valeur et on compare son nombre d'occurrences
    // avec le minimum trouve jusqu'a present
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
