#include "pathfinder.h"

#define NB_LIGNES        11
#define NB_COLONNES      15

#define LIG_ENTREE 9
#define COL_ENTREE 1
#define LIG_SORTIE 9
#define COL_SORTIE 13


int Laby[NB_LIGNES][NB_COLONNES] =
{
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},     // 0 = VIDE
                    {1,0,0,0,1,0,0,0,0,0,1,0,0,0,1},     // 1 = MUR
                    {1,0,1,1,1,1,1,0,1,0,1,0,1,0,1},     // 2 = ENTREE
                    {1,0,1,0,0,0,0,0,1,0,1,0,1,0,1},     // 3 = SORTIE
                    {1,0,1,0,1,1,1,1,1,0,1,0,1,0,1},     // 4 = PION 
                    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
                    {1,1,1,0,1,0,1,1,1,0,1,0,1,1,1},
                    {1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
                    {1,0,1,1,1,0,1,1,1,1,1,0,1,1,1},
                    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


int main (void)
{
	Trajet *pf = new Trajet();
	pf->FindPath(&Laby[0][0], NB_COLONNES, NB_LIGNES, COL_SORTIE, LIG_SORTIE, COL_ENTREE, LIG_ENTREE);
	return 0;
}

