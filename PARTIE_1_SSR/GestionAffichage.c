#include <stdio.h>
#include "GestionAffichage.h"
#include "GestionValeurlotoGagnante.h"

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