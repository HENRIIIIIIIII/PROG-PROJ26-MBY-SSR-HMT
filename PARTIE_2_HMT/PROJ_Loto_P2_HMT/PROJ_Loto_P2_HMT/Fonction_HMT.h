#pragma once

#ifndef FONCTION_HMT
#define FONCTION_HMT

//-----------------------------------------------------------------------------------//
// Nom du projet 		: FONCTION_HMT.h
// Date de cration 		: 03.06.26
// Date de modification : 03.06.26
//
// Auteur 				: Henri Mott
//
// Description          : This has all the prototypes for our function for part 2
//
// Remarques			: 
//
// Source				: https://github.com/tronkko/dirent/blob/master/include/dirent.h
//                        https://www.geeksforgeeks.org/c/c-program-list-files-sub-directories-directory/
//----------------------------------------------------------------------------------//

// for my functions
/*typedef struct
{
    char meme[100][256];    // Array to store up to 100 filenames of max length 255
    int file_count;
    int move_over;
    int Tb_compare[100];
}LotoData;
*/


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


void File_sorting(int move_over, int Tb_compare[100]);
// this function duplicates the values into another table so then we can scan each number the number of times there are numbers
// To then put in the second column how many times that number got repeated.
// move_over remembers where we are in the text
// Tb_compare duplicates the values so we can compare them


#endif