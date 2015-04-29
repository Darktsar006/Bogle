#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
typedef struct cord
{
  int abs;
  int ord;
}Cord;

/*CETTE FONCTION PERMET D'AFFICHER LA GRILLE ELLE PREND POUR PARAMÈTRE
 UNE UN POINTEUR VERS UN TYPE DE TABLEAU DE DEUX DIMENSION, DEUX ENTIERS 
 REPRESENTANT LE NOMBRE DE LIGNES ET DE COLONNES */

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

/* Procedure qui dimmensionne la taille de la grille */

void solveur_de_boggle_dimension(int *ligne, int *colonne)
{
     int choix;
     printf(" _________________________________________________________\n");
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

void solveur_de_boggle_voisins(char **tab, int i, int j, int n, int m, char voisins[8])
{
     int cpt = 0;
     int k = 0;
     

     
     /* Element centraux */
     
     if((i>0 && i<n-1) && (j>0 && j<m-1))
     {
	  for(k=j-1; k<=j+1; k++)
	  {
	       voisins[cpt] = tab[i-1][k];
	       cpt++;
	       if(tab[i][k]!=tab[i][j])
	       {
		    voisins[cpt] = tab[i][k];
			 cpt++;
	       }
	       voisins[cpt] = tab[i+1][k];
	       cpt++;
	  }
     }
     
     /* Element Haut */
     
     if(i == 0 && j < m-1)
     {
	  for(k=j; k<=j+1; k++)
	  {
	       if(tab[i][k]!=tab[i][j])
	       {
		    voisins[cpt] = tab[i][k];
		    cpt++;
	       }
	       voisins[cpt] = tab[i+1][k];
	       cpt++;
	  }
	  if(j > 0 && j < m-1)
	  {
	       voisins[cpt] = tab[i][j-1];
	       cpt++;
	       voisins[cpt] = tab[i+1][j-1];
	       cpt++;
	  }
     }
     
     /* Element Droite */
     
     if(i < n-1 && j == m-1)
     {
	  if(i > 0)
	  {
	       voisins[cpt] = tab[i-1][j-1];
	       cpt++;
	       voisins[cpt] = tab[i-1][j];
	       cpt++;
	  }
	  
	  for(k=j-1; k<=j+1; k++)
	  {
	       if(tab[i][k]!=tab[i][j])
	       {
		    voisins[cpt] = tab[i][k];
		    cpt++;
	       }
	       voisins[cpt] = tab[i+1][k];
		  cpt++;
	  }
     }
     
     /* Element Bas */
     
     if(i == n-1 && j > 0)
     {
	  if(j!= m-1)
	  {
	       voisins[cpt] = tab[i-1][j+1];
	       cpt++;
	       voisins[cpt] = tab[i][j+1];
	       cpt++;
	  }
	  for(k=j-1; k<j+1; k++)
	  {
	       voisins[cpt] = tab[i-1][k];
	       cpt++;
	       if(tab[i][k]!=tab[i][j])
	       {
		    voisins[cpt] = tab[i][k];
		    cpt++;
	       }
	  }
     }
     
     /* Element Gauche */
     
     if(j==0 && i > 0)
     {
	  for(k=j; k<=j+1; k++)
	  {
	       voisins[cpt] = tab[i-1][k];
	       cpt++;
	       if(tab[i][k]!=tab[i][j])
	       {
		    voisins[cpt] = tab[i][k];
		    cpt++;
	       }
	  }
	  if(i < n-1)
	  {
	       voisins[cpt] = tab[i+1][j+1];
	       cpt++;
	       voisins[cpt] = tab[i+1][j];
	       cpt++;
	  }
	  
     }
}
void trouver_lettre_de_mot_dans_grille(char caract, Cord *cordonnee, char **grille, int ligne, int colonne, int indice[2])
{
  int i;
  int j;
  int k=0;
  cordonnee = malloc(sizeof(struct cord));
  for(i=0; i<ligne; i++)
  {
    for(j=0; j<colonne; j++)
    {
      if(grille[i][j] == caract)
      {
	printf("%c\n",caract);
	cordonnee[k].abs = i;
	cordonnee[k].ord = j;
	printf("%d\n",i);
	printf("%d\n",j);
	realloc(cordonnee, sizeof(Cord));
      }
    }
  }
}

void trouver_mot_dans_grille(char *mot, int ligne, int colonne, int k,char *lettre_trouve, char **grille)
{
  int cpt=0;
  int k=0;
  int j=0;
  int cptr;
  Cord *cordonnee;
  trouver_lettre_de_mot_dans_grille(mot[k], cordonnee, grille, ligne, colonne, indice);
  while(cptr == 0)
  {
    cpt = sizeof(cordonnee);
    if(cpt !=0)
    {
      while(cpt !=0)
      {
	if((cordonnee[k].abs>0 && cordonnee[k].abs<n-1) && (cordonnee[k].ord>0 && cordonnee[k].ord<m-1))
	{
	  if( mot[k+1]==Diag_Gauche_Haut(mot[k], cordonnee[k].abs, cordonnee[k].ord, grille)|| mot[k+1]==Diag_Droit_Haut(mot[k],cordonnee[k].abs, cordonnee[k].ord, grille)
	  || mot[k+1]==Diag_Droit_Bas(mot[k], cordonnee[k].abs, cordonnee[k].ord, grille) || mot[k+1]==Diag_Gauche_Bas(mot[k],cordonnee[k].abs,cordonnee[k].ord, grille)
	  || mot[k+1]==Haut(mot[k], cordonnee[k].abs, cordonnee[k].ord, grille) || mot[k+1]==Bas(mot[k], cordonnee[k].abs, cordonnee[k].ord, grille)
	  || mot[k+1]==Gauche(mot[k], cordonnee[k].abs, cordonnee[k].ord,grille) || mot[k+1]==Droit(mot[k], cordonnee[k].abs, cordonnee[k].ord, grille))
	  {
	    lettre_trouve[j] =  mot[k+1];
	    cptr = 0;
	    k++;
	    j++;
	  }
	  else
	    if()
	   
	}
      }
    }
    
  }
}
int main()
{
  int i;
  char caract='C';
  char **grille = NULL;
  int ligne = 4;
  int colonne = 4;
  int indice[2];
  solveur_de_boggle_dimension(&ligne, &colonne);
  grille = malloc(sizeof(char*)*ligne);
     for(i=0; i<ligne; i++)
	  grille[i] = malloc(sizeof(char)*colonne);
  solveur_de_boggle_creer_grille(grille, ligne, colonne);
  trouver_lettre_de_mot_dans_grille(caract,grille, ligne,colonne, indice);
  return 0;
}