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
#include "Fonction_HMT.h" // Functions for part 2


int main(void)
{
    // Global variables

    char meme[100][256];    // Array to store up to 100 filenames of max length 255
    int file_count = 0;
    int move_over = 0;
    int Tb_compare[100];

    while (1)
    {
        file_count = Dir_scan_txt(file_count, meme);
        move_over = File_select(move_over, meme, file_count, Tb_compare);
        File_sorting(move_over, Tb_compare);
    }

}



