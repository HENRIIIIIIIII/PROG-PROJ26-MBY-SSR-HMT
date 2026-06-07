#include <stdio.h>
#include "GestionAffichage.h"
#include "GestionValeurlotoGagnante.h"

//----------------------------------------------------------------------------------//
// Nom de la fonction: afficherValeurPlusGagnante
// Entree / Sortie / I/O : I int valeurs[] (tableau des valeurs du Loto),
//                         I int nbValeurs (nombre de valeurs dans le tableau)
// Description: Affiche la valeur qui est sortie le plus de fois
// Date de modification: le 01.06.26
// Remarque: Si plusieurs valeurs ont le meme nombre de sorties max,
//           la valeur inferieure est selectionnee (premiere trouvee).
//----------------------------------------------------------------------------------//
void afficherValeurPlusGagnante(int valeurs[], int nbValeurs)
{
    int valeur = rechercherValeurPlusGagnante(valeurs, nbValeurs);
    int occ = compterOccurrences(valeurs, nbValeurs, valeur);

    printf(MSG_VAL_PLUS_GAG, valeur, occ);
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: afficherValeurMoinsGagnante
// Entree / Sortie / I/O : I int valeurs[] (tableau des valeurs du Loto),
//                         I int nbValeurs (nombre de valeurs dans le tableau)
// Description: Affiche la valeur qui est sortie le moins de fois
// Date de modification: le 01.06.26
// Remarque: Si plusieurs valeurs ont le meme nombre de sorties min,
//           la valeur inferieure est selectionnee (premiere trouvee).
//----------------------------------------------------------------------------------//
void afficherValeurMoinsGagnante(int valeurs[], int nbValeurs)
{
    int valeur = rechercherValeurMoinsGagnante(valeurs, nbValeurs);
    int occ = compterOccurrences(valeurs, nbValeurs, valeur);

    printf(MSG_VAL_MOINS_GAG, valeur, occ);
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: afficher6MeilleursNumeros
// Entree / Sortie / I/O : I int valeurs[] (tableau des valeurs du Loto),
//                         I int nbValeurs (nombre de valeurs dans le tableau)
// Description: Affiche les NUMERO_A_JOUER valeurs les plus frequentes en ordre croissant
// Date de modification: le 01.06.26
// Remarque: Utilise un tri par insertion pour maintenir l'ordre croissant des occurrences
//----------------------------------------------------------------------------------//
void afficher6MeilleursNumeros(int valeurs[], int nbValeurs)
{
    int numeros[NUMERO_A_JOUER];
    int occurrences[NUMERO_A_JOUER];

    // Initialisation des tableaux avec -1 pour marquer les cases vides
    for (int i = 0; i < NUMERO_A_JOUER; i++)
    {
        numeros[i] = -1;
        occurrences[i] = -1;
    }

    // Pour chaque valeur du loto, on calcule son nombre d'occurrences
    for (int i = 0; i < nbValeurs; i++)
    {
        int valeur = valeurs[i];
        int occ = compterOccurrences(valeurs, nbValeurs, valeur);

        int dejaPresent = false;

        // Verification que la valeur n'est pas deja dans le top
        for (int j = 0; j < NUMERO_A_JOUER; j++)
        {
            if (numeros[j] == valeur)
            {
                dejaPresent = true;
            }
        }

        // Si la valeur n'est pas deja presente, on la place au bon endroit
        // dans le top en decalant les elements vers la droite
        if (!dejaPresent)
        {
            for (int j = 0; j < NUMERO_A_JOUER; j++)
            {
                if (occ > occurrences[j])
                {
                    // Decale tous les elements du top vers la droite pour faire de la place
                    for (int k = NUMERO_A_JOUER - 1; k > j; k--)
                    {
						// Decalage des numeros et de leurs occurrences associees
                        numeros[k] = numeros[k - 1];
                        occurrences[k] = occurrences[k - 1];
                    }

					// Insertion de la nouvelle valeur plus frequente
                    numeros[j] = valeur;
                    occurrences[j] = occ;
                    break;
                }
            }
        }
    }

    // Tri croissant des numeros (demande du cahier des charges)
    // On utilise un tri par selection simple sur les numeros eux-memes
    for (int i = 0; i < NUMERO_A_JOUER - 1; i++)
    {
        for (int j = i + 1; j < NUMERO_A_JOUER; j++)
        {
			// On compare les numeros pour les mettre en ordre croissant, en ignorant les cases vides (-1)
            if (numeros[i] > numeros[j] && numeros[j] != -1)
            {
                int temp = numeros[i];
                numeros[i] = numeros[j];
                numeros[j] = temp;
            }
        }
    }

	// Affichage des numeros les plus frequents (ceux qui ont le plus d'occurrences)
    printf(MSG_6_MEILLEURS);

	// Affichage des numeros les plus frequents (ceux qui ont le plus d'occurrences)
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
// Nom de la fonction: afficher6MoinsBonsNumeros
// Entree / Sortie / I/O : I int valeurs[] (tableau des valeurs du Loto),
//                         I int nbValeurs (nombre de valeurs dans le tableau)
// Description: Affiche les NUMERO_A_JOUER valeurs les moins frequentes en ordre croissant
// Date de modification: le 01.06.26
// Remarque: Logique symetrique a afficher6MeilleursNumeros mais avec tri descendant
//----------------------------------------------------------------------------------//
void afficher6MoinsBonsNumeros(int valeurs[], int nbValeurs)
{
    int numeros[NUMERO_A_JOUER];
    int occurrences[NUMERO_A_JOUER];

    // Initialisation des tableaux avec -1 pour marquer les cases vides
    for (int i = 0; i < NUMERO_A_JOUER; i++)
    {
        numeros[i] = -1;
        occurrences[i] = 999999;
    }

    // Pour chaque valeur du loto, on calcule son nombre d'occurrences
    // puis on l'insere dans le bottom si elle a moins d'occurrences que le dernier du bottom
    for (int i = 0; i < nbValeurs; i++)
    {
        int valeur = valeurs[i];
        int occ = compterOccurrences(valeurs, nbValeurs, valeur);

        int dejaPresent = false;

        // Verification que la valeur n'est pas deja dans le bottom
        for (int j = 0; j < NUMERO_A_JOUER; j++)
        {
            if (numeros[j] == valeur)
            {
                dejaPresent = true;
            }
        }

        // Si la valeur n'est pas deja presente, on la place au bon endroit
        // dans le bottom en decalant les elements vers la droite
        if (!dejaPresent)
        {
            for (int j = 0; j < NUMERO_A_JOUER; j++)
            {
                if (occ < occurrences[j])
                {
                    // Decale tous les elements du bottom vers la droite pour faire de la place
                    for (int k = NUMERO_A_JOUER - 1; k > j; k--)
                    {
                        numeros[k] = numeros[k - 1];
                        occurrences[k] = occurrences[k - 1];
                    }

					// Insertion de la nouvelle valeur moins frequente
                    numeros[j] = valeur;
                    occurrences[j] = occ;
                    break;
                }
            }
        }
    }

    // Tri croissant des numeros
    for (int i = 0; i < NUMERO_A_JOUER - 1; i++)
    {
        for (int j = i + 1; j < NUMERO_A_JOUER; j++)
        {
            if (numeros[i] > numeros[j] && numeros[j] != -1)
            {
				// Echange des numeros pour les mettre en ordre croissant
                int temp = numeros[i];
                numeros[i] = numeros[j];
                numeros[j] = temp;
            }
        }
    }

    printf(MSG_6_MOINS_BONS);

	// Affichage des numeros les moins frequents (ceux qui ont le moins d'occurrences)
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
// Nom de la fonction: trierFichier
// Entree / Sortie / I/O :  Loto* loto structure contenant les valeurs a trier
// Description: Calcule la frequence d'apparition de chaque valeur unique,
//              puis affiche le resultat trie par frequence decroissante via
//              un algorithme de Tri a Bulles (Bubble Sort).
// Date de modification: 03.06.26
// Remarque: Utilise un tableau 2D Tb_compare[2][MAX_SCAN] :
//           - ligne 0 : les valeurs uniques
//           - ligne 1 : le nombre d'occurrences de chaque valeur
//----------------------------------------------------------------------------------//
void trierFichier(Loto* loto)
{
    // Tableau 2D pour le comptage des frequences :
    // Tb_compare[0][i] contient la valeur i (de 0 a MAX_SCAN-1)
    // Tb_compare[1][i] contient le nombre de fois ou cette valeur apparait
    int Tb_compare[2][MAX_SCAN] = { 0 };

    // Initialisation : on remplit la premiere ligne avec les indices 0, 1, 2, ..., MAX_SCAN-1
    // Cela permet de couvrir toutes les valeurs possibles dans la plage du loto
    for (int i = 0; i < MAX_SCAN; i++)
    {
        Tb_compare[0][i] = i;
    }

    // Algorithme de comptage des frequences :
    // Pour chaque valeur du loto, on parcourt le tableau de comparaison
    // et on incrémente le compteur correspondant a cette valeur
    int count = 0;
    while (count != loto->nbValeurs)
    {
        for (int i = 0; i < MAX_SCAN; i++)
        {
            // Nb_repeated stocke le compteur actuel pour la valeur Tb_compare[0][i]
            int Nb_repeated = 0;

            if (Tb_compare[0][i] == loto->valeurs[count])
            {
                // Recuperation du compteur actuel
                Nb_repeated = Tb_compare[1][i];
                // Incrémentation du compteur (une occurrence de plus)
                Nb_repeated++;
                // Sauvegarde du nouveau compteur
                Tb_compare[1][i] = Nb_repeated;
            }
        }
        // incrementations 
        count++;
    }

    // Tri a Bulles (Bubble Sort) sur les frequences (ligne 1) :
    // Parcours le tableau en comparant chaque paire d'elements adjacents.
    // Si la frequence courante est inferieure a la suivante, on inverse les deux lignes
    // (a la fois la valeur ET son compteur) pour faire remonter les plus frequentes.
    for (int i = 0; i < MAX_SCAN - 1; i++)
    {
        for (int j = 0; j < MAX_SCAN - i - 1; j++)
        {
            // Si la frequence en j est inferieure a celle en j+1, on inverse
            if (Tb_compare[1][j] < Tb_compare[1][j + 1])
            {
                // Echange des frequences
                int temp_count = Tb_compare[1][j];
                Tb_compare[1][j] = Tb_compare[1][j + 1];
                Tb_compare[1][j + 1] = temp_count;

                // Echange des valeurs associees
                int temp_val = Tb_compare[0][j];
                Tb_compare[0][j] = Tb_compare[0][j + 1];
                Tb_compare[0][j + 1] = temp_val;
            }
        }
    }

    // Affichage de toutes les valeurs avec leur frequence (triee par frequence decroissante)
    for (int i = 0; i < MAX_SCAN; i++)
    {
        if (Tb_compare[1][i] != 0)
        {
            printf(MSG_FILE_SORT_VAL, Tb_compare[0][i], Tb_compare[1][i]);
        }
    }

    // Affichage du top 6 des valeurs les plus frequentes
    printf(MSG_FILE_SORT_TOP);
    for (int i = 0; i < 6; i++)
    {
        if (Tb_compare[1][i] != 0)
        {
            printf("%d ", Tb_compare[0][i]);
        }
    }
    printf("\n");
}
