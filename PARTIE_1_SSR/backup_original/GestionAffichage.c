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

//----------------------------------------------------------------------------------//
// Nom de la fonction: File_sorting
// Entree / Sortie / I/O :  int move_over se souvient ou nous en sommes dans le texte
//                          int Tb_compare[MAX_SCAN] duplique les valeurs afin que nous puissions les comparer
//
// Description:  cette fonction duplique les valeurs dans une autre table afin que nous puissions scanner chaque nombre le nombre de fois qu'il y a des nombres
//               Pour ensuite mettre dans la deuxieme colonne combien de fois ce nombre a ete repete.
// Date modfification: 03.06.26
// Remarque: Need to change the type of memorazation
//----------------------------------------------------------------------------------//
void File_sorting(int move_over, int Tb_compare[MAX_SCAN])
{
    int Tb_compare_2[2][MAX_SCAN] = { 0 }; // Other Table to compare

    // Makes table
    for (int i = 0; i < MAX_SCAN; i++)
    {
        Tb_compare_2[0][i] = i; // Having 2 tables to compare the values to see the repeating numbers
    }

    int count = 0;  // Counter to go threw all the values
    while (count != move_over)  // Will go threw the table as many times as there is cases
    {
        for (int i = 0; i < MAX_SCAN; i++)
        {
            // We want this value to stay nuteral, it's a place holder
            int Nb_repeated = 0;

            if (Tb_compare_2[0][i] == Tb_compare[count])
            {
                // We save how many times the value is repeated in the file
                Nb_repeated = Tb_compare_2[1][i];
                // We add that the value is repeated one more time
                Nb_repeated++;
                // Save it into the second table
                Tb_compare_2[1][i] = Nb_repeated;
                // printf("%d was found, %d times\n", Tb_compare_2[0][count], Nb_repeated);
            }
        }
		count++;
    }
    // Bubble sorting source: https://www.geeksforgeeks.org/dsa/bubble-sort-algorithm/
    for (int i = 0; i < MAX_SCAN - 1; i++)
    {
        for (int j = 0; j < MAX_SCAN - i - 1; j++)
        {
            // If the current frequency is less than the next frequency, swap them
            if (Tb_compare_2[1][j] < Tb_compare_2[1][j + 1])
            {
                // Swap the frequencies
                int temp_count = Tb_compare_2[1][j];
                Tb_compare_2[1][j] = Tb_compare_2[1][j + 1];
                Tb_compare_2[1][j + 1] = temp_count;

                // Swap the actual values associated with them
                int temp_val = Tb_compare_2[0][j];
                Tb_compare_2[0][j] = Tb_compare_2[0][j + 1];
                Tb_compare_2[0][j + 1] = temp_val;
            }
        }
    }

	// prints the repeating numbers
    for (int i = 0; i < MAX_SCAN; i++)
    {
		if (Tb_compare_2[1][i] != 0)    // We dont a print the values that are not in the file, so if the value is repeated 0 times we dont print it
        {
            printf("value %d in table repeated: %d\n", Tb_compare_2[0][i], Tb_compare_2[1][i]);
        }
    }

    // prints the top 6 repeating numbers
    printf("The Top 6 numbers to bet on:\n");
    for (int i = 0; i < 6; i++)
    {
        if (Tb_compare_2[1][i] != 0)    // We dont a print the values that are not in the file, so if the value is repeated 0 times we dont print it
        {
            printf("%d ", Tb_compare_2[0][i]);
        }
    }
    printf("\n");

}