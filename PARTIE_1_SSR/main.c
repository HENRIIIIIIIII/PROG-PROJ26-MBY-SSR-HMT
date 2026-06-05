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

#include "GestionAffichage.h"
#include "GestionValeurlotoGagnante.h"

int Dir_scan_txt(int file_count, char meme[100][256]);
// This function scans the local directory and prints out all the files located there
// file_count counts the number of files found
// meme memorizes the name of the file
// This function gives back how many files are in the directory

int File_select(int move_over, char meme[100][256], int file_count, int Tb_compare[100]);
// This function reads what the user selected and shows what values are in the file
// move_over is because we read the values by 3 so it's to take that into consideration
// meme, file_count same as past function
// Tb_compare saves the values so we can compare them, gets converted before use

void Saisie_nouveau_loto(void);

bool fichier_loto_present(void)
{

}

bool fichier_present = true;
FILE* pointer;

char meme[100][256];    // Array to store up to 100 filenames of max length 255
int file_count = 0;
int move_over = 0;
int Tb_compare[100];

int main()
{
    int choix;

    printf("=== BIENVENUE DANS L'ANALYSEUR DE LOTO ===\n");

    // Boucle infinie correspondant au câblage externe de votre Flowchart
    while (true)
    {
        // fichier txt existant ?
        int file_count = Dir_scan_txt(0, meme);

        if (file_count > 0)
        {
            // Saisie du nom du fichier à ouvrir
            int move_over = File_select(0, meme, file_count, Tb_compare);

            if (move_over > 0)
            {
                // Affichages des informations contenues dans le fichier
                // On extrait les informations de Tb_compare pour remplir proprement 'monLoto'
                chargerDonneesLoto(&monLoto, Tb_compare, move_over);
                
                printf("\n--- CONFIGURATION DU LOTO CHARGÉ ---\n");
                printf("Nom : %s | Saisies enregistrees : %d\n", monLoto.nom, monLoto.nbValeurs);

                // Étape Flowchart : "Switchcase point 3"
                // Cette fonction gère l'affichage du menu et l'exécution des cas (pt 3)
                menu_principal(&monLoto, nomFichierActuel);
                
                break;
            }
            else
            {
                printf("Erreur lors de l'ouverture ou de la lecture du fichier.\n");
                break;
            }
        }
        else
        {
            // Cette fonction encapsule :
            // 1. Saisie du nom du loto et plage de valeurs
            // 2. Losange "Numéros complémentaires ?" -> Si oui, saisie plage
            // 3. Losange "Mode simulation ?" -> Si oui, saisie nb valeurs + génération aléatoire
            // 4. Étape "Création du fichier" physique sur le disque
            Saisie_nouveau_loto();

            printf("\nFichier de configuration cree avec succes.\n");
            
            // ATTENTION : On ne met pas de "break" ni de "return" ! 
            // La boucle 'while (true)' recommence instantanément depuis le début.
            // Au prochain tour, 'Dir_scan_txt' va détecter le fichier qu'on vient de créer,
        }
    }

    return 0;
}

void Saisie_nouveau_loto(void)
{
    bool numCompl = true;
    bool simMode = true;

    // Saisie du nom du loto + et plage des valeurs
    // Plage de valeurs possibles : Limite inferieure et superieure

    // Numeros complementaires ?
    if (numCompl) {
        // Saisie plage de valeurs
    }
    else
    {
        // Mode simulation ?
        if (simMode)
        {
            // Saisie du nombre de valeurs aleatoires
        }
        else
        {
            // Creation du fichier
            /* goto -> fichier texte existant ? */
        }
    }

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
int File_select(int move_over, char meme[100][256], int file_count, int Tb_compare[100])
{
    int UserAnswer; // were the users values are saved

    // if there are no files found
    if (file_count == 0)
    {
        printf("No .txt files found.\n");
        return 0;
    }

    // prints number of files found and ask user witch file to read
    printf("\nSelect a file number (1-%d): ", file_count);
    scanf("%d", &UserAnswer);

    // Validate the user input "supid proof"
    if (UserAnswer > 0 && UserAnswer <= file_count)
    {
        printf("You selected: %s\n", meme[UserAnswer - 1]);
        // Open and read your file here using meme[choice - 1]
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
    int Meme_val[255];

    // Pointing to the file destonation
    pointer = fopen(meme[UserAnswer - 1], "r");

    // file check
    if (pointer == NULL)
    {
        printf("Error!\n");
        return 0;
    }
    printf("Successfull\n");

    printf("Values are: \n");
    // Basic print of all file values
    while (fscanf(pointer, "%s%s%s", Text1, Text2, Text3) == 3) // the scan f returns  what it reads we can check that it reads 3 char, but the real problem is the end it reads 2 but it tryes to read if over and over.
        // But fscanf return EOF if there was a problem in returning 
    {
        // prints the values found
        printf("%s, %s, %s, ", Text1, Text2, Text3);
        // Now I need to store all the numbers to then compare them

        Tb_compare[move_over] = atoi(Text1); // atoi converts a string to an integer. https://cplusplus.com/reference/cstdlib/atoi/
        Tb_compare[move_over + 1] = atoi(Text2);
        Tb_compare[move_over + 2] = atoi(Text3);


        move_over += 3; // move over 3 to store the next 3 values in the next 3 spaces of the array
    }
    printf("\n");

    fclose(pointer);
    return move_over;
}


