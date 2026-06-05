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

#define MAX_SCAN 100

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


void File_sorting(int move_over, int Tb_compare[MAX_SCAN]);
// this function duplicates the values into another table so then we can scan each number the number of times there are numbers
// To then put in the second column how many times that number got repeated.
// move_over remembers where we are in the text
// Tb_compare duplicates the values so we can compare them

void Saisie_new_loto(void);

bool fichier_present = true;
FILE* pointer;

int main()
{
    char meme[100][256];    // Array to store up to 100 filenames of max length 255
    int file_count = 0;
    int move_over = 0;
    int Tb_compare[100];

    /*
    if (!fichier_present)
    {
        // Saisie du nom du loto + et plage des valeurs
        Saisie_new_loto();
    }
    else
    {
        // Saisie nom du fichier a ouvrir
    }

    while (1)
    {
        file_count = Dir_scan_txt(file_count, meme);
        move_over = File_select(move_over, meme, file_count, Tb_compare);
        File_sorting(move_over, Tb_compare);
    }
        */

    return 0;
}

void Saisie_new_loto(void)
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
    pointer = fopen(meme[UserAnswer], "r");

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
