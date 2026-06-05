#if defined(_MSC_VER)
    #define _CRT_SECURE_NO_WARNINGS
    // If compiling in Visual Studio, use the local Windows wrapper
    #include "dirent.h" 
#else
    // Compilation sur linux
    #include <dirent.h> 
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "GestionAffichage.h"
#include "GestionValeurlotoGagnante.h"

int Dir_scan_txt(int file_count, char meme[100][256]);
// This function scans the local directory and prints out all the files located there
// file_count counts the number of files found
// meme memorizes the name of the file
// This function gives back how many files are in the directory

int File_select(int move_over, char meme[100][256], int file_count, Loto* loto);
// This function reads what the user selected and shows what values are in the file
// move_over is because we read the values by 3 so it's to take that into consideration
// meme, file_count same as past function
// Tb_compare saves the values so we can compare them, gets converted before use

void Saisie_nouveau_loto(void);

void viderBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void Saisie_nouveau_loto(void)
{
    Loto nouveauLoto = { 0 };
    char nomFichier[256];
    char reponse;

    printf("\n--- CREATION D'UN NOUVEAU LOTO ---\n");
    printf("Nom du loto : ");
    scanf("%s", nouveauLoto.nom);
    viderBuffer();

    printf("Plage de valeur (min) : ");
    scanf("%d", &nouveauLoto.minVal);
    viderBuffer();

    printf("Plage de valeur (max) : ");
    scanf("%d", &nouveauLoto.maxVal);
    viderBuffer();

    printf("Numeros complementaires ? (o/n) : ");
    scanf("%c", &reponse);
    viderBuffer();

    if (reponse == 'o' || reponse == 'O') {
        nouveauLoto.nbComplementaires = 1;
        printf("Plage complementaire (min) : ");
        scanf("%d", &nouveauLoto.minComp);
        viderBuffer();

        printf("Plage complementaire (max) : ");
        scanf("%d", &nouveauLoto.maxComp);
        viderBuffer();
    }

    printf("Mode simulation ? (o/n) : ");
    scanf("%c", &reponse);
    viderBuffer();

    if (reponse == 'o' || reponse == 'O') {
        int nbSimul;
        printf("Combien de tirages a generer ? : ");
        scanf("%d", &nbSimul);
        viderBuffer();

        for (int i = 0; i < nbSimul && i < MAX_VALEURS; i++) {
            nouveauLoto.valeurs[nouveauLoto.nbValeurs++] = nouveauLoto.minVal + rand() % (nouveauLoto.maxVal - nouveauLoto.minVal + 1);
        }
    }

    // Création du fichier
    snprintf(nomFichier, sizeof(nomFichier), "log%s.txt", nouveauLoto.nom);
    sauvegarderFichierLoto(&nouveauLoto, nomFichier);
}

void menu_principal(Loto* loto, const char* nomFichierActuel)
{
    int choix;
    int valeur;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Inserer une nouvelle valeur\n");
        printf("2. Modifier la derniere valeur\n");
        printf("3. Supprimer la derniere valeur\n");
        printf("4. Afficher les statistiques\n");
        printf("5. Quitter et sauvegarder\n");
        printf("Votre choix : ");
        
        if (scanf("%d", &choix) != 1) {
            viderBuffer();
            continue;
        }

        switch (choix) {
            case 1:
                printf("Valeur a inserer : ");
                scanf("%d", &valeur);
                insererValeur(loto->valeurs, &loto->nbValeurs, valeur);
                printf("Valeur inseree !\n");
                break;
            case 2:
                printf("Nouvelle valeur pour remplacer la derniere : ");
                scanf("%d", &valeur);
                modifierDerniereValeur(loto->valeurs, loto->nbValeurs, valeur);
                break;
            case 3:
                supprimerDerniereValeur(loto->valeurs, &loto->nbValeurs);
                printf("Derniere valeur supprimee.\n");
                break;
            case 4:
                if (loto->nbValeurs > 0) {
                    afficherValeurPlusGagnante(loto->valeurs, loto->nbValeurs);
                    afficherValeurMoinsGagnante(loto->valeurs, loto->nbValeurs);
                    afficher6MeilleursNumeros(loto->valeurs, loto->nbValeurs);
                    afficher6MoinsBonsNumeros(loto->valeurs, loto->nbValeurs);
                    File_sorting(loto); 
                } else {
                    printf("Aucune donnee.\n");
                }
                break;
            case 5:
                printf("Sauvegarde en cours...\n");
                sauvegarderFichierLoto(loto, nomFichierActuel);
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 5);
}

void sauvegarderFichierLoto(Loto* loto, const char* nomFichier)
{
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur : impossible de sauvegarder dans le fichier %s\n", nomFichier);
        return;
    }

    // Sauvegarde des valeurs par blocs de 3 (Voir la fonction File_select)
    for (int i = 0; i < loto->nbValeurs; i++) {
        fprintf(fichier, "%d ", loto->valeurs[i]);
        if ((i + 1) % 3 == 0) {
            fprintf(fichier, "\n");
        }
    }
    
    // Si la dernière ligne n'était pas un multiple de 3, on rajoute un saut de ligne
    if (loto->nbValeurs % 3 != 0) {
        fprintf(fichier, "\n");
    }

    fclose(fichier);
    printf("Fichier %s mis a jour avec succes.\n", nomFichier);
}

int main(void)
{
    char meme[100][256];    // Array to store up to 100 filenames of max length 255

    // Initialisation du générateur aléatoire pour la simulation
    srand((unsigned int)time(NULL));

    Loto monLoto = { 0 }; 
    char nomFichierLotoActuel[256] = "";

    printf("=== BIENVENUE DANS L'ANALYSEUR DE LOTO ===\n");

    while (true)
    {
        int file_count = Dir_scan_txt(0, meme);

        if (file_count > 0)
        {
            int move_over = File_select(0, meme, file_count, &monLoto);

            if (move_over > 0)
            {
                strcpy(nomFichierLotoActuel, monLoto.nom);
                                
                printf("\n--- CONFIGURATION DU LOTO CHARGÉ ---\n");
                printf("Nom : %s | Saisies enregistrees : %d\n", monLoto.nom, monLoto.nbValeurs);

                menu_principal(&monLoto, nomFichierLotoActuel);
                
                // Fin du programme après avoir quitté le menu
                break;
            }
            else
            {
                printf("Erreur lors de l'ouverture ou fichier vide.\n");
                break;
            }
        }
        else
        {
            Saisie_nouveau_loto();
            printf("\nFichier de configuration cree avec succes.\n");
            // La boucle recommence et Dir_scan_txt trouvera le nouveau fichier
        }
    }

    return 0;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: Dir_scan_txt
// Entree / Sortie / I/O :  int file_count compte le nombre de fichiers trouves
//                          char meme[100][256] memorise le nom du fichier
//                         
// Description: Cette fonction scanne le repertoire local et affiche tous les fichiers qui s'y trouvent
// Date modfification: 03.06.26
// Remarque: -
//----------------------------------------------------------------------------------//
int Dir_scan_txt(int file_count, char meme[100][256])
{
    struct dirent* de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type. 
    DIR* dr = opendir(".");

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory");
        return 0;
    }

    // Refer https://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    file_count = 0;
    while ((de = readdir(dr)) != NULL)
        //printf("%s\n", de->d_name);
        if (de->d_type == DT_REG)
        {

            // Look for ".txt" anywhere inside the file name
            char* extension = strstr(de->d_name, ".txt"); // Get a pointer to the first occurrence of a string in another string. https://www.w3schools.com/c/ref_string_strstr.php

            // If found, make sure it's at the very end of the string
            if (extension != NULL && strcmp(extension, ".txt") == 0) // Compare two strings to see which is greater. https://www.w3schools.com/c/ref_string_strcmp.php
            {
                printf("%s\n", de->d_name);
                strcpy(meme[file_count], de->d_name);  // is a built-in function used to copy one string into another. https://www.geeksforgeeks.org/c/strcpy-in-c/
                file_count++;
            }

        }
    closedir(dr);
    return file_count;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: File_select
// Entree / Sortie / I/O :  int move_over est parce que nous lisons les valeurs avant 3, donc c'est pour en tenir compte
//                          char meme[100][256] memorise le nom du fichier 
//                          int file_count enregistre le nombre de fichiers dans le repertoire
//                          int Tb_compare[100] enregistre les valeurs afin que nous puissions les comparer, puis les convertit avant utilisation
// Description: Cette fonction lit ce que l'utilisateur a sélectionné et affiche les valeurs du fichier, puis les convertir pour que l'on puisse donner aux prochaines fonctions
// Date modfification: 03.06.26
// Remarque: -
//----------------------------------------------------------------------------------//
int File_select(int move_over, char meme[100][256], int file_count, Loto* loto)
{
    FILE* pointer;
    int userAnswer; // were the users values are saved

    // if there are no files found
    if (file_count == 0)
    {
        printf("No .txt files found.\n");
        return 0;
    }

    // prints number of files found and ask user witch file to read
    printf("\nSelect a file number (1-%d): ", file_count);
    scanf("%d", &userAnswer);

    // Validate the user input "supid proof"
    if (userAnswer > 0 && userAnswer <= file_count)
    {
        printf("You selected: %s\n", meme[userAnswer - 1]);
        strncpy(loto->nom, meme[userAnswer - 1], MAX_NOM_LOTO - 1);
    }
    else
    {
        printf("Invalid selection.\n");
        return 0;
    }

    // Setup to read files
    char Text1[40];
    char Text2[40];
    char Text3[40];

    // Pointing to the file destonation
    pointer = fopen(meme[userAnswer - 1], "r");

    // file check
    if (pointer == NULL)
    {
        printf("Error!\n");
        return 0;
    }
    printf("Successfull\n");

    printf("Values are: \n");
    loto->nbValeurs = 0;
    // Basic print of all file values
    while (fscanf(pointer, "%s%s%s", Text1, Text2, Text3) == 3 && loto->nbValeurs < MAX_VALEURS - 3) // the scan f returns  what it reads we can check that it reads 3 char, but the real problem is the end it reads 2 but it tryes to read if over and over.
        // But fscanf return EOF if there was a problem in returning 
    {
        // prints the values found
        printf("%s, %s, %s, ", Text1, Text2, Text3);
        // Now I need to store all the numbers to then compare them

        loto->valeurs[loto->nbValeurs++] = atoi(Text1); // atoi converts a string to an integer. https://cplusplus.com/reference/cstdlib/atoi/
        loto->valeurs[loto->nbValeurs++] = atoi(Text2);
        loto->valeurs[loto->nbValeurs++] = atoi(Text3);

        move_over += 3; // move over 3 to store the next 3 values in the next 3 spaces of the array
    }
    printf("\n");

    fclose(pointer);
    return move_over;
}


