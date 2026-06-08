#ifndef GESTION_FICHIERS_LOTO_H
#define GESTION_FICHIERS_LOTO_H

#include "constantes.h"

// Scanne le repertoire courant et retourne le nombre de fichiers .txt
int scannerRepertoireTxt(char meme[MAX_FICHIERS][TAILLE_MAX_FICHIER]);

// Affiche la liste des fichiers, lit le choix de l'utilisateur, ouvre le fichier selectionne et lit les valeurs numeriques une par une.
int selectionnerFichier(char meme[MAX_FICHIERS][TAILLE_MAX_FICHIER], int file_count, Loto* loto);

// Ecrit les valeurs du loto dans un fichier texte
void sauvegarderFichierLoto(Loto* loto, const char* nomFichier);

#endif /* GESTION_FICHIERS_H */
