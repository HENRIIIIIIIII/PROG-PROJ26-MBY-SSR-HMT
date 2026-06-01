//-----------------------------------------------------------------------------------//
// Nom du projet 		: Projet_LOTO
// Nom du fichier 		: GestionsFonctions.c
// Date de création 	: 18.05.26
// Date de modification : 01.06.26
//
// Auteur 				: MBY
//
// Version				: x.x
//
// Description          : Point 3 du projet
//
//
// Remarques :            lien pour la table ASCII :
// 						  -> http://www.asciitable.com/
// 						  lien pour la saisie de clavier avec getc & getchar pour ne pas
//                        avoir des erreurs d'interprétation
// 						  -> http://fr.openclassrooms.com/informatique/cours/utiliser-les-bonnes-fonctions-d-entree
// 						  lien vers différents
// 						  -> http://fr.wikipedia.org/wiki/String.h
//----------------------------------------------------------------------------------//

//--- librairie standart ---//
#include <stdio.h>	// pour usage printf et scanf_s
                    // Nouveauté du VC++ 2005, 2008, 2010 et 2015 : le scanf_s remplace scanf

// GestionFonctions.c

#include <stdio.h>
#include "GestionFonctions.h"

//----------------------------------------------------------------------------------//
// Nom de la fonction: insererValeur
// Entrée / Sortie / I/O :  int valeurs[] (tableau comportant les valeurs du Loto), 
//                          int* nbValeurs (pointeur afin de compter le nombre de fois qu'un valeur est sortie)
//                          int nouvelleValeur (Valeur que l'on veut inscrire dans le fichier)
// Description: Fonction permettant d'insérer une nouvelle valeur dans le fichier loto
// Date modfification: le 01.06.26
// Remarque: -
//----------------------------------------------------------------------------------//
void insererValeur(int valeurs[], int* nbValeurs, int nouvelleValeur)
{
    valeurs[*nbValeurs] = nouvelleValeur;
    (*nbValeurs)++;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: supprimerDerniereValeur
// Entrée / Sortie / I/O :  int valeurs[] (tableau comportant les valeurs du Loto), 
//                          int* nbValeurs (pointeur afin de compter le nombre de fois qu'un valeur est sortie)
// Description: Fonction permettant de supprimer la dernière valeur introduite dans le fichier loto
// Date modfification: le 01.06.26
// Remarque: -
//----------------------------------------------------------------------------------//
void supprimerDerniereValeur(int valeurs[], int* nbValeurs)
{
    if (*nbValeurs > 0) //vérification que la valeur a déjà été tirée
    {
        (*nbValeurs)--;
    }
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: insererValeur
// Entrée / Sortie / I/O :  int valeurs[] (tableau comportant les valeurs du Loto), 
//                          int* nbValeurs (pointeur afin de compter le nombre de fois qu'un valeur est sortie)
//                          int nouvelleValeur (Valeur que l'on veut inscrire dans le fichier)
// Description: Fonction permettant de remplacer la dernière valeur introduite avec la nouvelle valeur
// Date modfification: le 01.06.26
// Remarque: -
//----------------------------------------------------------------------------------//
void modifierDerniereValeur(int valeurs[], int nbValeurs, int nouvelleValeur)
{
    if (nbValeurs > 0) //vérification que la valeur a déjà été tirée
    {
        valeurs[nbValeurs - 1] = nouvelleValeur; //remplacement de la valeur dans le tableau
    }
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

//----------------------------------------------------------------------------------//
// Nom de la fonction: afficherValeurPlusGagnante
// Entrée / Sortie / I/O : I int valeurs[] (tableau comportant les valeurs du Loto), 
//                         I int nbValeurs (pointeur afin de compter le nombre de fois qu'un valeur est sortie)
// Description: Affiche la valeur qui est sortie le plus de fois
// Date modfification: le 01.06.26
// Remarque: Si plusieurs valeurs ont le même nombre de sortie max alors la valeur inférieur sera celle de sortie
//----------------------------------------------------------------------------------//
void afficherValeurPlusGagnante(int valeurs[], int nbValeurs)
{
    int valeur = rechercherValeurPlusGagnante(valeurs, nbValeurs);
    int occ = compterOccurrences(valeurs, nbValeurs, valeur);

    printf("\nValeur la plus gagnante : %d (%d occurrences)\n",
        valeur, occ);
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: afficherValeurMoinsGagnante
// Entrée / Sortie / I/O : I int valeurs[] (tableau comportant les valeurs du Loto), 
//                         I int nbValeurs (pointeur afin de compter le nombre de fois qu'un valeur est sortie)
// Description: Fonction permettant d'afficher le nombre de fois que la valeur la plus sortie est sortie
// Date modfification: le 01.06.26
// Remarque: Si plusieurs valeurs ont le même nombre de sortie min alors la valeur inférieur sera celle de sortie
//----------------------------------------------------------------------------------//
void afficherValeurMoinsGagnante(int valeurs[], int nbValeurs)
{
    int valeur = rechercherValeurMoinsGagnante(valeurs, nbValeurs);
    int occ = compterOccurrences(valeurs, nbValeurs, valeur);

    printf("\nValeur la moins gagnante : %d (%d occurrences)\n",
        valeur, occ);
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: afficher6MeilleursNumeros
// Entrée / Sortie / I/O : I int valeurs[] (tableau comportant les valeurs du Loto), 
//                         I int nbValeurs (pointeur afin de compter le nombre de fois qu'un valeur est sortie)
// Description: Fonction permettant d'afficher les 6 valeurs les plus sorties
// Date modfification: le 01.06.26
// Remarque: Si plusieurs valeurs ont le même nombre de sortie min alors la valeur inférieur sera celle de sortie
//----------------------------------------------------------------------------------//
void afficher6MeilleursNumeros(int valeurs[], int nbValeurs)
{
    int numeros[NUMERO_A_JOUER];
    int occurrences[NUMERO_A_JOUER];

    for (int i = 0; i < NUMERO_A_JOUER; i++)
    {
        numeros[i] = -1;
        occurrences[i] = -1;
    }

    for (int i = 0; i < nbValeurs; i++)
    {
        int valeur = valeurs[i];
        int occ = compterOccurrences(valeurs, nbValeurs, valeur);

        int dejaPresent = 0;

        for (int j = 0; j < NUMERO_A_JOUER; j++)
        {
            if (numeros[j] == valeur)
            {
                dejaPresent = 1;
            }
        }

        if (!dejaPresent)
        {
            for (int j = 0; j < NUMERO_A_JOUER; j++)
            {
                if (occ > occurrences[j])
                {
                    for (int k = 5; k > j; k--)
                    {
                        numeros[k] = numeros[k - 1];
                        occurrences[k] = occurrences[k - 1];
                    }

                    numeros[j] = valeur;
                    occurrences[j] = occ;
                    break;
                }
            }
        }
    }

    // Tri croissant demandé par le cahier des charges
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < NUMERO_A_JOUER; j++)
        {
            if (numeros[i] > numeros[j] && numeros[j] != -1)
            {
                int temp = numeros[i];
                numeros[i] = numeros[j];
                numeros[j] = temp;
            }
        }
    }

    printf("\n6 meilleurs numeros : ");

    for (int i = 0; i < NUMERO_A_JOUER; i++)
    {
        if (numeros[i] != -1)
        {
            printf("%d ", numeros[i]);
        }
    }

    printf("\n");
}

void afficher6MoinsBonsNumeros(int valeurs[], int nbValeurs)
{
    int numeros[NUMERO_A_JOUER];
    int occurrences[NUMERO_A_JOUER];

    for (int i = 0; i < NUMERO_A_JOUER; i++)
    {
        numeros[i] = -1;
        occurrences[i] = 999999;
    }

    for (int i = 0; i < nbValeurs; i++)
    {
        int valeur = valeurs[i];
        int occ = compterOccurrences(valeurs, nbValeurs, valeur);

        int dejaPresent = 0;

        for (int j = 0; j < NUMERO_A_JOUER; j++)
        {
            if (numeros[j] == valeur)
            {
                dejaPresent = 1;
            }
        }

        if (!dejaPresent)
        {
            for (int j = 0; j < NUMERO_A_JOUER; j++)
            {
                if (occ < occurrences[j])
                {
                    for (int k = 5; k > j; k--)
                    {
                        numeros[k] = numeros[k - 1];
                        occurrences[k] = occurrences[k - 1];
                    }

                    numeros[j] = valeur;
                    occurrences[j] = occ;
                    break;
                }
            }
        }
    }

    // Tri croissant demandé
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < NUMERO_A_JOUER; j++)
        {
            if (numeros[i] > numeros[j] && numeros[j] != -1)
            {
                int temp = numeros[i];
                numeros[i] = numeros[j];
                numeros[j] = temp;
            }
        }
    }

    printf("\n6 moins bons numeros : ");

    for (int i = 0; i < NUMERO_A_JOUER; i++)
    {
        if (numeros[i] != -1)
        {
            printf("%d ", numeros[i]);
        }
    }

    printf("\n");
}