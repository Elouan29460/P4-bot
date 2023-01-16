#include <stdbool.h>
#include <stdlib.h>

#define LIGNE 6
#define COLONNE 7
#define MAX_STRATS 200
#define MAX_LENGTH 100

const int VIDE = 0;
const int J1 = 1;
const int J2 = 2;

typedef int t_grille[LIGNE][COLONNE]; 

int trouverLigne(t_grille grille, int colonne);
bool estVainqueur(t_grille grille, int ligne, int colonne);
bool estVainqueur2(t_grille grille, int ligne, int colonne);
int maStrategie(t_grille laGrille);
void chargerGrille(char** argv, t_grille grille);

int main(int argc, char** argv) 
{
    t_grille grille;

    chargerGrille(argv, grille);

    return maStrategie(grille);
}

void chargerGrille(char** argv, t_grille grille) 
{
    for(int i = 0; i < LIGNE; i++)
        for(int j = 0; j < COLONNE; j++)
            grille[i][j] = atoi(argv[i * COLONNE + j + 1]);
}

int trouverLigne(t_grille grille, int colonne)
{
    for(int j = LIGNE - 1; j >= 0; j--) {
        if(grille[j][colonne] == VIDE) return j;
    }
    return -1;
}

bool estVainqueur(t_grille grille, int ligne, int colonne) 
{
    int aligne;

    // Horizontal
    aligne = 0;
    for(int j = colonne - 3; j <= colonne + 3; j++) {
        if(j >= 0 && j < COLONNE){
            if(grille[ligne][j] == grille[ligne][colonne]) aligne++;
            else aligne = 0;
        }
        if(aligne == 4) return true;
    }

    // Vertical
    aligne = 0;
    for(int i = ligne - 3; i <= ligne + 3; i++) {
        if(i >= 0 && i < LIGNE){
            if(grille[i][colonne] == grille[ligne][colonne]) aligne++;
            else aligne = 0;
        }
        if(aligne == 4) return true;
    }

    // Diagonale 1
    aligne = 0;
    for(int i = -3; i <= 3; i++) {
        if(i + ligne >= 0 && i + ligne < LIGNE){
            if(i + colonne >= 0 && i + colonne < COLONNE){
                if(grille[i + ligne][i + colonne] == grille[ligne][colonne]) aligne++;
                else aligne = 0;
            }
        }
        if(aligne == 4) return true;
    }

    // Diagonale 2
    aligne = 0;
    for(int i = -3; i <= 3; i++) {
        if(ligne - i >= 0 && ligne - i < LIGNE){
            if(i + colonne >= 0 && i + colonne < COLONNE){
                if(grille[ligne - i][i + colonne] == grille[ligne][colonne]) aligne++;
                else aligne = 0;
            }
        }
        if(aligne == 4) return true;
    }

    return false;
}

bool estVainqueur2(t_grille grille, int ligne, int colonne) 
{
    int aligne;

    // Horizontal
    aligne = 0;
    for(int j = colonne - 3; j <= colonne + 3; j++) {
        if(j >= 0 && j < COLONNE){
            if(grille[ligne][j] == grille[ligne][colonne]) aligne++;
            else aligne = 0;
        }
        if(aligne >= 3) return true;
    }

    // Vertical
    aligne = 0;
    for(int i = ligne - 3; i <= ligne + 3; i++) {
        if(i >= 0 && i < LIGNE){
            if(grille[i][colonne] == grille[ligne][colonne]) aligne++;
            else aligne = 0;
        }
        if(aligne >= 3) return true;
    }

    // Diagonale 1
    aligne = 0;
    for(int i = -3; i <= 3; i++) {
        if(i + ligne >= 0 && i + ligne < LIGNE){
            if(i + colonne >= 0 && i + colonne < COLONNE){
                if(grille[i + ligne][i + colonne] == grille[ligne][colonne]) aligne++;
                else aligne = 0;
            }
        }
        if(aligne >= 3) return true;
    }

    // Diagonale 2
    aligne = 0;
    for(int i = -3; i <= 3; i++) {
        if(ligne - i >= 0 && ligne - i < LIGNE){
            if(i + colonne >= 0 && i + colonne < COLONNE){
                if(grille[ligne - i][i + colonne] == grille[ligne][colonne]) aligne++;
                else aligne = 0;
            }
        }
        if(aligne >= 3) return true;
    }

    return false;
}

int maStrategie(t_grille laGrille)
{
    bool trouve = false;
    int colonneRes;
    int col,lig;

//On a enlever la procedure copieGrille pour optimiser le temps d'execution
    
    /**************************************************************************
     * Pose des jetons si on peut annuler une suite de 3 pions alignés.
     * Grâce à cette méthode le bot peut annuler une ligne de 3 pions alignés
     * comme aussi 2 pions alignés, une case vide puis encore un pion identique.
     **************************************************************************/

    if (!trouve)
    {
        col = 0;
        while (!trouve && col<COLONNE)
        {
            lig = trouverLigne(laGrille,col);
            if (lig!=-1)
            {
                laGrille[lig][col]=J1;
                trouve = estVainqueur(laGrille,lig,col);
                laGrille[lig][col]=VIDE;
                colonneRes = col;
            }
            col++;
        }
    }


    if (!trouve)
    {
        col = 0;
        while (!trouve && col<COLONNE)
        {
            lig = trouverLigne(laGrille,col);
            if (lig!=-1)
            {
                laGrille[lig][col]=J2;
                trouve = estVainqueur(laGrille,lig,col);
                laGrille[lig][col]=VIDE;
                colonneRes = col;
            }
            col++;
        }
    }

    /******************************************************************
     * Pose des jetons si on peut annuler une suite de 2 pions alignés.
     * On fait ce test après celui di-dessus car moins important.
     *****************************************************************/

    if (!trouve)
    {
        col = 0;
        while (!trouve && col<COLONNE)
        {
            lig = trouverLigne(laGrille,col);
            if (lig!=-1)
            {
                laGrille[lig][col]=J1;
                trouve = estVainqueur2(laGrille,lig,col);
                laGrille[lig][col]=VIDE;
                colonneRes = col;
            }
            col++;
        }
    }


    if (!trouve)
    {
        col = 0;
        while (!trouve && col<COLONNE)
        {
            lig = trouverLigne(laGrille,col);
            if (lig!=-1)
            {
                laGrille[lig][col]=J2;
                trouve = estVainqueur2(laGrille,lig,col);
                laGrille[lig][col]=VIDE;
                colonneRes = col;
            }
            col++;
        }
    }

    /*****************************************************************************
     * Pose des jetons au milieu de la grille si on peut.
     * Si on ne peut pas, alors on pose sur la colonne la plus proche du milieu
     * pour ça on fait de la colonne de gauche puis droite si pleine
     ****************************************************************************/

    //On a modifier le fait de poser de la colonne la plus à gauche à la plus à droite quand
    //il ne trouve rien à cette méthode plus efficiente pour gagnere
    if (!trouve)
    {
        col = 3;
        if (trouverLigne(laGrille,col)==-1)
        {
            if (trouverLigne(laGrille,2)!=-1)
            {
                col = 2;
            }
            else if (trouverLigne(laGrille,4)!=-1)
            {
                col = 4;
            }
            else if (trouverLigne(laGrille,1)!=-1)
            {
                col = 1;
            }
            else if (trouverLigne(laGrille,5)!=-1)
            {
                col = 5;
            }
            else if (trouverLigne(laGrille,0)!=-1)
            {
                col = 0;
            }
            else if (trouverLigne(laGrille,6)!=-1)
            {
                col = 6;
            }
        }
        colonneRes = col;
    }


    //On return la colonne ou poser le pion à la fin.
    return colonneRes;
}