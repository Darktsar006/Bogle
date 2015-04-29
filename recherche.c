#define _POSIX_C_SOURCE 1

/*
 NOM: TRAORE
 PRENOM: Oumar
 DATE DE CREATION: 2 MARS 2013
 DATE DE DERNIERE MODIFICATION: 25 Mars 2013
 MOTIF DE MODIFICATION: Codage DFS
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/* Bibliotheque pour gerer le temps */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TAILLE_MAX_MOT 25
#define TAILLE_MIN_MOT 3
#define NOMBRE_SECONDE 180

/*CETTE FONCTION PERMET D'AFFICHER LA GRILLE ELLE PREND POUR PARAMÈTRE
 UNE UN POINTEUR VERS UN TYPE DE TABLEAU DE DEUX DIMENSION, DEUX ENTIERS 
 REPRESENTANT LE NOMBRE DE LIGNES ET DE COLONNES */

/* Procedure qui dimmensionne la taille de la grille */

void solveur_de_boggle_dimension(int *ligne, int *colonne)
{
     int choix;
     printf(" _________________________________________________________\n");
     printf("|      		TAPER :         			 |\n");
     printf("|1 si vous sohaitez redimensionner la grille de jeux      |\n");
     printf("|2 si vous ne souhaitez rien changer                      |\n");
     printf("|_________________________________________________________| \n");
     
     do
     {
	  printf("Votre choix : ");
	  scanf("%d",&choix);
     }while(choix < 1 || choix >2);
     
     if(choix == 1)
     {
	  printf("Donner le nombre de lignes : ");
	  scanf("%d", ligne);
	  printf("Donner le nombre de colonnes : ");
	  scanf("%d", colonne);
     }
}

void solveur_de_boggle_afficher_grille(char **tab, int lig, int col)
{
     int i;
     int j;
     printf("------------------------\n");
     for(i=0; i<lig; i++)
     {
	  for(j=0; j<col; j++)
	  {
	  printf("| %c ", tab[i][j]);
	  
	  }
	  printf("\n------------------------\n");
     }
}

void solveur_de_boggle_afficher_grilleAlterer(int **tab, int lig, int col)
{
     int i;
     int j;
     printf("------------------------\n");
     for(i=0; i<lig; i++)
     {
	  for(j=0; j<col; j++)
	  {
	       printf("| %d ", tab[i][j]);
	       
	  }
	  printf("\n------------------------\n");
     }
}

/*CETTE FONCTION PERMET DE CREER ET DE REMPLIR LA GRILLE DE JEUX*/

void solveur_de_boggle_creer_grille(char **tab, int ligne, int colonne)
{
     int i;
     int j;
     srand(time(NULL));
     for(i=0; i<ligne; i++)
     {    
	  for(j=0; j<colonne; j++)
	       tab[i][j] = rand () % 26 + 'A';
     }
     
     solveur_de_boggle_afficher_grille(tab,ligne,colonne);
}

/* On initialise une grille de Vue pour le parcours des mots formés dans la grille */

void solveur_de_boggle_Grille_Vue(int **grilleVue, int ligne, int colonne)
{
     int i;
     int j;
   
     for(i=0; i<ligne; i++)
     {    
	  for(j=0; j<colonne; j++)
	       grilleVue[i][j] = 0;
     }
     
}

/* Procedure qui Altere la grille des vues */

void solveur_de_boggle_Altere_Grille_Vue(int **grille, int i, int j)
{
     grille[i][j] = 1;
}

/* Droite = 0, 	Diagonale Droite Haut = 1, Haut = 2, Diagonale Gauche Haut = 3, Gauche = 4
 * Diagonale Gauche Bas = 5, Bas = 6, Diagonale Droite Bas = 7 */

/* procedure qui verifie si on peut se deplacer */

bool solveur_de_boggle_Peut_Se_Deplacer(int **grilleVue, int i, int j, int ligne, int colonne)
{
     /* Element centraux */
     
     if((i>0 && i<ligne-1) && (j>0 && j<colonne-1))
     {
	  if(grilleVue[i-1][j-1] == 0) /* Diagonale Gauche Haut */
	       return true;
	  if(grilleVue[i-1][j] == 0) /* Haut */
	       return true;
	  if(grilleVue[i-1][j-1] == 0) /* Diagonale Droite Haut */
	       return true;
	  if(grilleVue[i][j-1] == 0) /* Gauche */
	       return true;
	  if(grilleVue[i][j+1] == 0) /* Droite */
	       return true;
	  if(grilleVue[i+1][j-1] == 0) /* Diagonale Gauche Bas */
	       return true;    
	  if(grilleVue[i+1][j] == 0) /* Bas */
	       return true;
	  if(grilleVue[i+1][j+1] == 0) /* Diagonale Droite Bas */
	       return true;
     }
     
     /* Element Haut */
     
     if(i == 0 && j < colonne-1)
     {
	  if(grilleVue[i][j+1] == 0) /* Droite */
	       return true;
	  if(grilleVue[i+1][j] == 0) /* Bas */
	       return true;
	  if(grilleVue[i+1][j+1] == 0) /* Diagonale Droite Bas */
	       return true;
	  if(j > 0 && j < colonne-1)
	  {
	       if(grilleVue[i][j-1] == 0) /* Gauche */
		    return true;
	       if(grilleVue[i+1][j-1] == 0) /* Diagonale Gauche Bas */
		    return true;
	  }
     }
     
     /* Element Droite */
     
     if(i < ligne-1 && j == colonne-1)
     {
	  if(grilleVue[i][j-1] == 0) /* Gauche */
	       return true;
	  if(grilleVue[i+1][j-1] == 0) /* Diagonale Gauche Bas */
	       return true;
	  if(grilleVue[i+1][j] == 0) /* Bas */
	       return true;
	  if(i > 0)
	  {
	       if(grilleVue[i-1][j] == 0   ) /* Haut */
		    return true;
	       if(grilleVue[i-1][j-1] == 0) /* Diagonale Gauche Haut */
		    return true;
	  }
     }
     
     /* Element Bas */
     
     if(i == ligne-1 && j > 0)
     {
	  if(grilleVue[i-1][j] == 0    ) /* Haut */
	       return true;
	  if(grilleVue[i-1][j-1] == 0    ) /* Diagonale Gauche Haut */
	       return true;
	  if(grilleVue[i][j-1] == 0    ) /* Gauche */
	       return true;
	  if(j!= colonne-1)
	  {
	       if(grilleVue[i][j+1] == 0    ) /* Droite */
		    return true;
	       if(grilleVue[i-1][j-1] == 0    ) /* Diagonale Droite Haut */
		    return true;
	  }
     }
     
     /* Element Gauche */
     
     if(j==0 && i > 0)
     {
	  if(grilleVue[i-1][j] == 0    ) /* Haut */
	       return true;
	  if(grilleVue[i][j+1] == 0    ) /* Droite */
	       return true;
	  if(grilleVue[i-1][j-1] == 0    ) /* Diagonale Droite Haut */
	       return true;
	  if(i < ligne-1)
	  {
	       if(grilleVue[i+1][j] == 0   ) /* Bas */
		    return true;
	       if(grilleVue[i+1][j+1] == 0    ) /* Diagonale Droite Bas */
		    return true;
	  }
     }
     
     return false;
}

/* Procedure de choix de Direction */

bool solveur_de_boggle_Direction(int **grilleVue, int i, int j, int ligne, int colonne, int Direction)
{    
     /* Element centraux */
     
     if((i>0 && i<ligne-1) && (j>0 && j<colonne-1))
     {
	  if(grilleVue[i-1][j-1] == 0 && Direction == 3) /* Diagonale Gauche Haut */
	  {
	       i = i-1;
	       j = j-1;
	       printf("Direction : Diagonale Gauche Haut\n");
	       return true;
	  }
	  if(grilleVue[i-1][j] == 0 && Direction == 2) /* Haut */
	  {
	       i = i-1;
	       printf("Direction : Haut\n");
	       return true;
	  }
	  if(grilleVue[i-1][j-1] == 0 && Direction == 1) /* Diagonale Droite Haut */
	  {
	       i = i-1;
	       j = j+1;
	       printf("Direction : Diagonale Droite Haut\n");
	       return true;
	  }
	  if(grilleVue[i][j-1] == 0  && Direction == 4) /* Gauche */
	  {
	       j = j-1;
	       printf("Direction : Gauche\n");
	       return true;
	  }
	  if(grilleVue[i][j+1] == 0 && Direction == 0) /* Droite */
	  {
	       j = j+1;
	       printf("Direction : Droite\n");
	       return true;
	  }
	  if(grilleVue[i+1][j-1] == 0 && Direction == 5) /* Diagonale Gauche Bas */
	  {
	       i = i+1;
	       j = j-1;
	       printf("Direction : Diagonale Gauche Bas\n");
	       return true;
	  }    
	  if(grilleVue[i+1][j] == 0 && Direction == 6) /* Bas */
	  {
	       j = j-1;
	       printf("Direction : Bas\n");
	       return true;
	  }
	  if(grilleVue[i+1][j+1] == 0 && Direction == 7) /* Diagonale Droite Bas */
	  {
	       i = i+1;
	       j = j-1;
	       printf("Direction : Diagonale Droite bas\n");
	       return true;
	  }
     }
     
     /* Element Haut */
    /* Droite = 0, 	Diagonale Droite Haut = 1, Haut = 2, Diagonale Gauche Haut = 3, Gauche = 4
      Diagonale Gauche Bas = 5, Bas = 6, Diagonale Droite Bas = 7 */
     
     
     if(i == 0 && j < colonne-1)
     {
	  if(grilleVue[i][j+1] == 0 && Direction == 0) /* Droite */
	  {
	       j = j+1;
	       printf("Direction : Droite\n");
	       return true;
	  }
	  if(grilleVue[i+1][j] == 0 && Direction == 6) /* Bas */
	  {
	       j = j-1;
	       printf("Direction : Bas\n");
	       return true;
	  }
	  if(grilleVue[i+1][j+1] == 0 && Direction == 7) /* Diagonale Droite Bas */
	  {
	       i = i+1;
	       j = j-1;
	       printf("Direction : Diagonale Droite bas\n");
	       return true;
	  }
	  if(j > 0 && j < colonne-1)
	  {
	       if(grilleVue[i][j-1] == 0 && Direction == 4) /* Gauche */
	       {
		    j = j-1;
		    printf("Direction : Gauche\n");
		    return true;
	       }
	       if(grilleVue[i+1][j-1] == 0 && Direction == 5) /* Diagonale Gauche Bas */
	       {
		    i = i+1;
		    j = j-1;
		    printf("Direction : Diagonale Gauche Bas\n");
		    return true;
	       }
	  }
     }
    /* Droite = 0, 	Diagonale Droite Haut = 1, Haut = 2, Diagonale Gauche Haut = 3, Gauche = 4
     * Diagonale Gauche Bas = 5, Bas = 6, Diagonale Droite Bas = 7 */
     
     /* Element Droite */
     
     if(i < ligne-1 && j == colonne-1)
     {
	  if(grilleVue[i][j-1] == 0 && Direction == 4) /* Gauche */
	  {
	       j = j-1;
	       printf("Direction : Gauche\n");
	       return true;
	  }
	  if(grilleVue[i+1][j-1] == 0 && Direction == 5) /* Diagonale Gauche Bas */
	  {
	       i = i+1;
	       j = j-1;
	       printf("Direction : Diagonale Gauche Bas\n");
	       return true;
	  }
	  if(grilleVue[i+1][j] == 0 && Direction == 6) /* Bas */
	  {
	       j = j-1;
	       printf("Direction : Bas\n");
	       return true;
	  }
	  if(i > 0)
	  {
	       if(grilleVue[i-1][j] == 0 && Direction == 2) /* Haut */
	       {
		    i = i-1;
		    printf("Direction : Haut\n");
		    return true;
	       }
	       if(grilleVue[i-1][j-1] == 0 && Direction == 3) /* Diagonale Gauche Haut */
	       {
		    i = i-1;
		    j = j-1;
		    printf("Direction : Diagonale Gauche Haut\n");
		    return true;
	       }
	  }
     }
     
     /* Element Bas */
     /* Droite = 0, 	Diagonale Droite Haut = 1, Haut = 2, Diagonale Gauche Haut = 3, Gauche = 4
     * Diagonale Gauche Bas = 5, Bas = 6, Diagonale Droite Bas = 7 */
     if(i == ligne-1 && j > 0)
     {
	  if(grilleVue[i-1][j] == 0 && Direction == 2) /* Haut */
	  {
	       i = i-1;
	       printf("Direction : Haut\n");
	       return true;
	  }
	  if(grilleVue[i-1][j-1] == 0 && Direction == 3) /* Diagonale Gauche Haut */
	  {
	       i = i-1;
	       j = j-1;
	       printf("Direction : Diagonale Gauche Haut\n");
	       return true;
	  }
	  if(grilleVue[i][j-1] == 0 && Direction == 4) /* Gauche */
	  {
	       j = j-1;
	       printf("Direction : Gauche\n");
	       return true;
	  }
	  if(j!= colonne-1)
	  {
	       if(grilleVue[i][j+1] == 0 && Direction == 0) /* Droite */
	       {
		    j = j+1;
		    printf("Direction : Droite\n");
		    return true;
	       }
	       if(grilleVue[i-1][j-1] == 0 && Direction == 1) /* Diagonale Droite Haut */
	       {
		    i = i-1;
		    j = j+1;
		    printf("Direction : Diagonale Droite Haut\n");
		    return true;
	       }
	  }
     }
     
     /* Element Gauche */
     /* Droite = 0, 	Diagonale Droite Haut = 1, Haut = 2, Diagonale Gauche Haut = 3, Gauche = 4
     * Diagonale Gauche Bas = 5, Bas = 6, Diagonale Droite Bas = 7 */
     
     if(j==0 && i > 0)
     {
	  if(grilleVue[i-1][j] == 0 && Direction == 2) /* Haut */
	  {
	       i = i-1;
	       printf("Direction : Haut\n");
	       return true;
	  }
	  if(grilleVue[i][j+1] == 0 && Direction == 0) /* Droite */
	  {
	       j = j+1;
	       printf("Direction : Droite\n");
	       return true;
	  }
	  if(grilleVue[i-1][j-1] == 0 && Direction == 1) /* Diagonale Droite Haut */
	  {
	       i = i-1;
	       j = j+1;
	       printf("Direction : Diagonale Droite Haut\n");
	       return true;
	  }
	  if(i < ligne-1)
	  {
	       if(grilleVue[i+1][j] == 0 && Direction == 6) /* Bas */
	       {
		    j = j-1;
		    printf("Direction : Bas\n");
		    return true;
	       }
	       if(grilleVue[i+1][j+1] == 0 && Direction == 7) /* Diagonale Droite Bas */
	       {
		    i = i+1;
		    j = j-1;
		    printf("Direction : Diagonale Droite bas\n");
		    return true;
	       }
	  }
     }
     return false;
}

/* Procedure qui duplique une gille */

void solveur_de_boggle_dupliquer_grille(int **grilleVue, int **grilleVue2, int ligne, int colonne)
{
     int i;
     int j;
     for(i=0; i<ligne; i++)
     {
	  for(j=0; j<colonne; j++)
	  {
	       grilleVue2[i][j] = grilleVue[i][j];
	  }
     }
}

/*Procedure qui modifie dans la direction suivante */

void solveur_de_boggle_Direction_Suivante(int Direction, int *i, int *j)
{
     switch(Direction)
     {
	  case 0: /* Droite */ 
	       *j = *j+1;
	       break;
	  case 1: /* Diagonale Droite Haut */
	       *i = *i-1;
	       *j = *j+1;
	       break;
	  case 2: /* Haut */
	       *i = *i-1;
	       break;
	  case 3: /* Diagonale Gauche Haut */
	       *i = *i-1;
	       *j = *j-1;
	       break;
	  case 4: /* Gauche */
	       *j = *j-1;
	       break;
	  case 5: /* Diagonale Gauche Bas */
	       *i = *i+1;
	       *j = *j-1;
	       break;
	  case 6: /* Bas */
	       *i = *i+1;
	       break;
	  case 7: /* Diagonale Droite Bas */
	       *i = *i+1;
	       *j = *j+1;
	       break;
	  default : /* Pas de direction */
	       printf("Direction Impossible \n");
	       break;       
     }
}

/* Procedure qui verifie si le debut de la chaine correspond à un mot dans le fichier */

bool solveur_de_boggle_Valide(char motTrouve[25], FILE *fichier)
{
     fseek(fichier, 0, SEEK_SET); /* On positionne le curseur au debut du fichier */
     char chaine[TAILLE_MAX_MOT] = "";
     int longuerMotTrouver = strlen(motTrouve);
     
     while (fgets(chaine, longuerMotTrouver, fichier) != NULL) /* On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL) */
     {
	  if(strcmp(chaine, motTrouve)==0)
	  {
	       printf("%s\n", chaine);
	       return true;
	  }
     }
     printf("\nTout c bien passer\n");
     return false;
}

/* Procedure qui parcours la grille pour former un mot */

void solveur_de_boggle_Recherche(FILE *fichier, char **grille, int **grilleVue1, int **grilleVue2, int ligne, int colonne, int i, int j, char chaine[100], int Direction, int *hist[3])
{
     int cpt = 0;
     chaine[cpt] = '\0';
     int x, y;
     
     /* Si on peut se deplacer on Marque les coordonnées de cette case comme vue */
     solveur_de_boggle_Altere_Grille_Vue(grilleVue1, i, j);
     
     /* Procedure qui stocke une grille vue pour repartir de ce point et faire une recherche */
     solveur_de_boggle_dupliquer_grille(grilleVue1, grilleVue2, ligne, colonne);
     
     /* Histoire de stocker les coordonnées précendentes pour revenir */
     x = i;
     y = j;
     
     do
     {
	  while(solveur_de_boggle_Direction(grilleVue2, x, y, ligne, colonne, hist[cpt][2]))
	  {	  
	       /* on peut se deplacer on Marque les coordonnées de cette case comme vue */
	       solveur_de_boggle_Altere_Grille_Vue(grilleVue2, x, y);
	       solveur_de_boggle_afficher_grilleAlterer(grilleVue2, ligne, colonne);
	       
	       hist[cpt][2] += 1; /* cette case vas marquer sur sa coordonnées une direction vue en fonction d'ou elle est dans le parcours */
	       
	       /* Choix de direction */
	       solveur_de_boggle_Direction_Suivante(Direction, &x, &y);
	       
	       /* Formation du mot */
	       
	       chaine[cpt] = grille[x][y];
	       
	       /* Si on a au minimum un mot de 3 lettres */
	       if(strlen(chaine) >= 3)
	       {
		    /* Formation du mot */
		    if(solveur_de_boggle_Valide(chaine, fichier))
			 break;     
	       }
	       cpt++;
	  }
	  
	  while(solveur_de_boggle_Direction(grilleVue2, x, y, ligne, colonne, hist[cpt][2]) == false)
	  {
	       if(solveur_de_boggle_Peut_Se_Deplacer(grilleVue2, x, y, ligne, colonne))
	       {
		    hist[cpt][2]++;
	       }
	  }
	  /* on peut se deplacer on Marque les coordonnées de cette case comme vue */
	  solveur_de_boggle_Altere_Grille_Vue(grilleVue2, x, y);
	  solveur_de_boggle_afficher_grilleAlterer(grilleVue2, ligne, colonne);
	  /* Choix de direction */
	  solveur_de_boggle_Direction_Suivante(hist[cpt][2], &x, &y);
     }while(solveur_de_boggle_Peut_Se_Deplacer(grilleVue2, x, y, ligne, colonne));
     if(hist[i+j][3] <= 3)
     {
	  solveur_de_boggle_Recherche(fichier, grille, grilleVue1, grilleVue2, ligne, colonne, x, y, chaine, Direction, hist);
     }
}

void savehist(int **hist, int ligne, int colonne)
{
     int i, j;
     int cpt = 0;
     for(i=0; i<ligne; i++)
     {
	  for(j=0; j<ligne; j++)
	  {
	       hist[cpt][0] = i;
	       hist[cpt][1] = j;
	       hist[cpt][2] = 0;
	       cpt++;
	  }
     }
}

int main()
{
     /*int pid;*/
     
     FILE *fichier = NULL;
     
     fichier = fopen("dictionaire.txt", "r");
     
     if(fichier == NULL)
     {
	  exit(0);
     }
     char **grille = NULL; /* C'est la grille du jeu */
     int **grilleVue1 = NULL, **grilleVue2 = NULL; /* c'est la grille des Vue */
     char chaine[1000];
          
     int ligne = 4, colonne = 4;
     int i;
     solveur_de_boggle_dimension(&ligne, &colonne);
     
     /* Allocation de la grille */
     grille = malloc(sizeof(char*)*ligne);
     grilleVue1 = malloc(sizeof(int*)*ligne);
     grilleVue2 = malloc(sizeof(int*)*ligne);
     for(i=0; i<ligne; i++)
     {
	  grilleVue1[i] = malloc(sizeof(int)*colonne);
	  grilleVue2[i] = malloc(sizeof(int)*colonne);
	  grille[i] = malloc(sizeof(char)*colonne);
     }
     
     int **hist;
     hist = malloc(sizeof(int *)*(ligne*colonne));
     for(i=0; i<(ligne*colonne); i++)
	  hist[i] = malloc(sizeof(int)*3);
     
     savehist(hist, ligne, colonne);
     
     solveur_de_boggle_creer_grille(grille, ligne, colonne);
     
     /* Procedure qui restaure la grille de vue */
     solveur_de_boggle_Grille_Vue(grilleVue1, ligne, colonne);
    
     solveur_de_boggle_Recherche(fichier, grille, grilleVue1, grilleVue2, ligne, colonne, 0, 0, chaine, 0, hist);
     
     for(i=0; i<ligne; i++)
     { 
	  free(grille[i]);
	  free(grilleVue1[i]);
	  free(grilleVue2[i]);
     }
     free(grille);
     free(grilleVue1);
     free(grilleVue2);
     
     fclose(fichier);
     
     return 0;
}