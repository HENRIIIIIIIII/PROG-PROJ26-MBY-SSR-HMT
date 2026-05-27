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
            }
        }
    closedir(dr);
    return 0;
}
void File_select()
{
    char UserAnswer[40];


    printf("Select a file\n");
    scanf_s("%c%*c", &UserAnswer, 2);
    //printf("file selected: %c\n", UserAnswer);
    while (fscanf(UserAnswer, "%s%s%s", Text1, Text2, Text3) != -1) // the scan f returns  what it reads we can check that it reads 3 char, but the real problem is the end it reads 2 but it tryes to read if over and over.
        // But fscanf return -1 if there was a problem in returning 
    {
        // prints the values found
        printf("%s, %s, %s \n", Text1, Text2, Text3);
    }
}

int main(void)
{
    Dir_scan_txt();
    File_select();
}




