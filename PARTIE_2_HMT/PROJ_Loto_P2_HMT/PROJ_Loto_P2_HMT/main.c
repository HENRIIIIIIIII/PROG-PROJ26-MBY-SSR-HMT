//-----------------------------------------------------------------------------------//
// Nom du projet 		: PROJ_Loto_P2_HMT.c
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
#include "dirent.h"

// Global variables
char meme[100][256];    // Array to store up to 100 filenames of max length 255
int file_count = 0;

FILE* pointer;

void Dir_scan_txt()
// This function scans the local directory and prints out all the files located there
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
            if(extension != NULL && strcmp(extension, ".txt") == 0) // Compare two strings to see which is greater. https://www.w3schools.com/c/ref_string_strcmp.php
            {
                printf("%s\n", de->d_name);
                strcpy(meme[file_count + 1 ], de->d_name);  // is a built-in function used to copy one string into another. https://www.geeksforgeeks.org/c/strcpy-in-c/
                file_count++;
            }
          
        }
    closedir(dr);
    return 0;
}
void File_select()
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
        printf("You selected: %s\n", meme[UserAnswer - 1]);
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
    int Tb_compare[100];

    // Pointing to the file destonation
    pointer = fopen(meme[UserAnswer - 1], "r");

    // file check
    if (pointer == NULL)
    {
        printf("Error!\n");
        return 1;
    }
    printf("Successfull\n");

    int move_over = 0;

    // Basic print of all file values
    while (fscanf(pointer, "%s%s%s", Text1, Text2, Text3) != -1) // the scan f returns  what it reads we can check that it reads 3 char, but the real problem is the end it reads 2 but it tryes to read if over and over.
        // But fscanf return -1 if there was a problem in returning 
    {
        // prints the values found
        printf("%s, %s, %s \n", Text1, Text2, Text3);
        // Now I need to store all the numbers to then compare them
		
        Tb_compare[move_over] = atoi(Text1); // atoi converts a string to an integer. https://cplusplus.com/reference/cstdlib/atoi/
        Tb_compare[move_over+1] = atoi(Text2);
        Tb_compare[move_over+2] = atoi(Text3);


		move_over += 3; // move over 3 to store the next 3 values in the next 3 spaces of the array
    }
	int Tb_compare_2[100] = Tb_compare; // Having 2 tables to compare the values to see the repeating numbers

	int count = 0;

    for (int i = 0; i < move_over; i++)
    {
        count += 2;
        printf("The value entered is %d \n", Tb_compare[i]);
		if (Tb_compare_2[count] == Tb_compare[i])
		{
			printf("The value %d is in the file \n", Tb_compare[i]);
		}
    }
    
}
int main(void)
{
    Dir_scan_txt();
    File_select();
}




