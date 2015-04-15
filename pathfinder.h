#ifndef PATHFINDER_H
#define PATHFINDER_H

#include	<iostream>
#include 	<stdlib.h>

using namespace std;


struct Position
{
	int x,y;
	Position *P,*N;
	double Cost;
	void findCost(int, int);
};

class Stack
{
	private:
		int Count;
	
	public:
		Position *be, *en, *cu;		// Begin, End and Current position
	
						Stack(void);
		int 			GetCount(void);
		void		Pop(Position *);
		void 		Push(Position *);
};



class	Mouvement
{
	private:
		int pxo;	// origin
		int pyo;
		int pxe; // end
		int pye;

	public:
	
		Mouvement	*Next;
		Mouvement	*Prev;
		int Nb;
		
		Mouvement					(void);
		Mouvement					(int, int);
		~Mouvement					(void);
		
	
		void 			SetO(int, int);
		void			SetE(int, int);
	
		void	Move (int x, int y)
		{
			pxe = pxo + x;
			pye = pyo - y;
//			cout << pxo << pyo << " SET MOVE NEW: " << pxe << pye << endl;
		};
		
		int	GetXO(void) { return pxo; };
		int 	GetXE(void)	{ return pxe; };
		int	GetYO(void)	{ return pyo; };
		int	GetYE(void)	{ return pye; };
};


class	Trajet
{
	private:
	
		Mouvement	*be, *cu, *en;
	
	public:

		Trajet					(void);
		~Trajet				(void);
	
		void	AddMove	(Mouvement);
		void	DelMove	(void);
	
		int 	FindPath(int *, int, int, int, int, int, int);
		void 	AffGrid(int *, int, int, int, int, int, int);
	
		void	GetMove(int *, int *);
		void	ResetMove(void);

		
		int		GetNb		(void);
};

#endif
