#ifndef GESTION_SAISIE_H
#define GESTION_SAISIE_H

// Vide le buffer d'entree standard apres un scanf pour eviter
// que les caracteres residuels soient relus.
void viderBuffer(void);

// Lit un entier au clavier en validant le retour du scanf.
// Boucle tant que le retour n'est pas 1 (saisie valide).
int lireEntier(int *p);

// Lit un caractere au clavier en validant le retour du scanf.
// Boucle tant que le retour n'est pas 1 (saisie valide).
int lireCaractere(char *p);

// Lit une chaine de caracteres au clavier avec validation du retour.
// Boucle tant que le retour n'est pas 1.
int lireChaine(char *s, unsigned int n);

#endif /* GESTION_SAISIE_H */
