//-----------------------------------------------------------------------------------//
// Nom du projet 		: Functions_HMT.c
// Date de cration 		: 18.05.26
// Date de modification : 20.05.26
//
// Auteur 				: Henri Mott
//
// Description          : This code has the goal to Show the user what files there able to read.
//						  and then it will paste all the values that are in the file
//
// Remarques			: 
//
// Source				: https://github.com/tronkko/dirent/blob/master/include/dirent.h
//                        https://www.geeksforgeeks.org/c/c-program-list-files-sub-directories-directory/
//----------------------------------------------------------------------------------//
// Directives de compilation
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>	// pour printf
#include <string.h>	// pour strcat
#include "dirent.h" // Pour la conversion des valeur, atoi
#include "Fonction_HMT.h" // Functions for part 2

FILE* pointer;

//----------------------------------------------------------------------------------//
// Nom de la fonction: Dir_scan_txt
// Entrée / Sortie / I/O :  int file_count compte le nombre de fichiers trouvés
//                          char meme[100][256] mémorise le nom du fichier
//                         
// Description: Cette fonction scanne le répertoire local et affiche tous les fichiers qui s’y trouvent
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
                strcpy(meme[file_count + 1], de->d_name);  // is a built-in function used to copy one string into another. https://www.geeksforgeeks.org/c/strcpy-in-c/
                file_count++;
            }

        }
    closedir(dr);
    return file_count;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: File_select
// Entrée / Sortie / I/O :  int move_over est parce que nous lisons les valeurs avant 3, donc c’est pour en tenir compte
//                          char meme[100][256] mémorise le nom du fichier 
//                          int file_count enregistre le nombre de fichiers dans le répertoire
//                          int Tb_compare[100] enregistre les valeurs afin que nous puissions les comparer, puis les convertit avant utilisation
// Description: Cette fonction lit ce que l’utilisateur a sélectionné et affiche les valeurs du fichier, puis les convertir pour que l'on puisse donner aux prochaines fonctions
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
        return;
    }

    // prints number of files found and ask user witch file to read
    printf("\nSelect a file number (1-%d): ", file_count);
    scanf_s("%d", &UserAnswer);

    // Validate the user input "supid proof"
    if (UserAnswer > 0 && UserAnswer <= file_count)
    {
        printf("You selected: %s\n", meme[UserAnswer]);
        // Open and read your file here using meme[choice - 1]
    }
    else
    {
        printf("Invalid selection.\n");
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
        return 1;
    }
    printf("Successfull\n");

    printf("Values are: \n");
    // Basic print of all file values
    while (fscanf(pointer, "%s%s%s", Text1, Text2, Text3) != -1) // the scan f returns  what it reads we can check that it reads 3 char, but the real problem is the end it reads 2 but it tryes to read if over and over.
        // But fscanf return -1 if there was a problem in returning 
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

    return move_over;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: File_sorting
// Entrée / Sortie / I/O :  int move_over se souvient où nous en sommes dans le texte
//                          int Tb_compare[100] duplique les valeurs afin que nous puissions les comparer
//
// Description:  cette fonction duplique les valeurs dans une autre table afin que nous puissions scanner chaque nombre le nombre de fois qu’il y a des nombres
//               Pour ensuite mettre dans la deuxième colonne combien de fois ce nombre a été répété.
// Date modfification: 03.06.26
// Remarque: Need to change the type of memorazation
//----------------------------------------------------------------------------------//
void File_sorting(int move_over, int Tb_compare[100])
{
    int Tb_compare_2[2][100] = { 0 }; // Other Table to compare

    // Copy the values to another table to compare them and the repeating numbers
    for (int i = 0; i < move_over; i++)
    {
        Tb_compare_2[0][i] = Tb_compare[i]; // Having 2 tables to compare the values to see the repeating numbers
    }

    int count = 0;  // Counter to go threw all the values

    while (count != move_over)  // Will go threw the table as many times as there is cases
    {
        // This loop compares the values of the 2 tables and if it finds a match it saves the value in a new table to then print the repeating numbers
        for (int i = 0; i < move_over; i++)
        {
            // We want this value to stay nuteral, it's a place holder
            int Nb_repeated = 0;

            if (Tb_compare_2[0][count] == Tb_compare[i])
            {
                // We save how many times the value is repeated in the file
                Nb_repeated = Tb_compare_2[1][count];
                // We add that the value is repeated one more time
                Nb_repeated++;
                // Save it into the second table
                Tb_compare_2[1][count] = Nb_repeated;
                // printf("%d was found, %d times\n", Tb_compare_2[0][count], Nb_repeated);
            }
        }
        count++;
    }

    // prints the repeating numbers
    for (int i = 0; i < move_over; i++)
    {
        printf("The value %d Repeated %d\n", Tb_compare_2[0][i], Tb_compare_2[1][i]);
    }

}