// by wildcat
//
// pathfinder.cpp
//
//
//  02/02/2004
//


#include 	"pathfinder.h"
#include	<iostream>
#include	<string>
#include 	<stdlib.h>

using namespace std;


#define	CLEAR()	cout << "\033[2J"

void Position::findCost(int xx, int yy)
{
	float xd = float( ( (float)this->x - (float)xx) );
	float yd = float( ( (float)this->y - (float)yy) );
	Cost = ((xd*xd) + (yd*yd));
	return;
}


Stack::		Stack(void)
{
	be = NULL;
	en = NULL;
	cu = NULL;
	Count = 0;
}


int 				Stack::GetCount(void)
{
	return Count;
}


void			Stack::Pop(Position *p)
{
	if (cu == NULL)
		return;
	p->x = cu->x;
	p->y = cu->y;
	p->N = cu->N;
	p->P = cu->P;
	//memcpy(p, cu, sizeof(cu));
	if (cu->P == NULL)
	{
		delete cu;
		cu = NULL;
		en = NULL;
		be = NULL;
	} else
	{	
		cu = cu->P;
		delete cu->N;
		cu->N = NULL;
	}
	Count--;
	return;
}



void		Stack::Push(Position *p)
{
	if (cu != NULL)
	{
		cu->N = new Position;
		cu->N->x = p->x;
		cu->N->y = p->y;
		cu->N->N = p->N;
		cu->N->P = p->P;
		//memcpy(cu->N, p, sizeof(p));
		cu->N->P = cu;
		cu = cu->N;
		en = cu;
	} else
	{
		cu = new Position;
		cu->x = p->x;
		cu->y = p->y;
		cu->N = p->N;
		cu->P = p->P;
		//memcpy(cu, p, sizeof(p));
		cu->P = NULL;
		be = cu;		
	}	
	Count++;
	return;
}



Mouvement::Mouvement					(void)
{
	Next = NULL;
	Prev = NULL;
}


Mouvement::Mouvement					(int x, int y)
{
	Next = NULL;
	Prev = NULL;
	pxo = x;
	pxe = y;
	Nb = 0;
}


Mouvement::~Mouvement					(void)
{
	return;
}


void 	Mouvement::SetO(int x, int y)
{
			pxo = x;
			pyo = y;
}
		
void	Mouvement::SetE(int x, int y)
{
			pxe = x;
			pye = y;
			return;
}

Trajet::Trajet					(void)
{
	be = NULL;
	en = NULL;
	cu = NULL;
}


Trajet::~Trajet				(void)
{
	return;
}


void	Trajet::AddMove	(Mouvement m)
{
	cu = en;
	if (cu == NULL)
	{
		cu = new Mouvement;
		cu->SetO(m.GetXO(), m.GetYO());
		cu->SetE(m.GetXE(), m.GetYE());
		//cu->Move((m.GetXE() - m.GetXO()), (m.GetYE() - m.GetYO()));
		cu->Nb = 1;
		en = cu;
		be = cu;
	}
	else
	{
		cu->Next = new Mouvement;
		cu->Next->SetO(m.GetXO(), m.GetYO());
		cu->Next->SetE(m.GetXE(), m.GetYE());
		//cu->Next->Move(m.GetXE() - m.GetXO(), m.GetYE() - m.GetYO());
		cu->Next->Nb = cu->Nb + 1;
		cu->Next->Prev = cu;
		cu = cu->Next;
		en = cu;
	}
	return;
}

void	Trajet::DelMove(void)
{
	cu = en;
	cu->Prev->Next = NULL;
	en = cu->Prev;
	delete cu;
	cu = en;
	return;
}

void	Trajet::GetMove(int *x, int *y)
{
	*x = cu->GetXE();
	*y = cu->GetYE();
	
	//cout << "REQUEST XY: " << cu->GetXE() << cu->GetYE() << endl;
	
	if (cu->Next != NULL)
		cu = cu->Next;
}

void	Trajet::ResetMove(void)
{
	cu = be;
	return;
}

		
int		Trajet::GetNb		(void)
{
	if (en)
		return en->Nb;
	else
		return 0;
}


void 	Trajet::AffGrid(int *po, int bx, int by, int dx, int dy, int x, int y)
{
	int i,j;
	for (i=0; i<y; i++)
	{
		for (j=0; j<x; j++, po++)
		{
			if ((i == by) && (j == bx))
				cout << 'Y';
			else if ((i == dy) && (j == dx))
				cout << 'X';
			else
				cout << *po;
		}
		cout << endl;
	}
	cout << endl << endl;
	return;	
}

int Trajet::FindPath(int *grid, int x, int y, int xdest, int ydest, int xsource, int ysource)
{
	Position S = { xsource, ysource, NULL };
	Position T = { xdest, ydest, NULL };
	
	Position M,P;

	Position Set[4];
	int nb=0;
	
	int *closed = new int [(y*x)];
	
	for (int i=0; i< (x*y); i++)
		*(closed+i) = 0;
	
	Mouvement m;

	Stack	*OS,*FS;
	OS = new Stack;
	FS = new Stack;
	
	OS->Push(&S);
	*(closed+((OS->cu->y * x) + OS->cu->x)) = 1;
	
	while (1)
	{
		nb=0;
//		fflush(stdin);
//		getchar();
		OS->Pop(&M);	// get the top node pos
		if ((M.x == T.x) && (M.y == T.y))
		{
			FS->Push(&M);
			m.SetO(FS->cu->P->x,FS->cu->P->y);
			m.SetE(FS->cu->x,FS->cu->y);
			AddMove(m);
			break;	// We found a path
		}
		M.N = NULL;
		if (FS->cu)
			M.P = FS->cu;
		else
			M.P = NULL;
		FS->Push(&M);	// If not, push into final stack
		
		if (FS->cu->P)
		{
			m.SetO(FS->cu->P->x,FS->cu->P->y);
			m.SetE(FS->cu->x,FS->cu->y);
			AddMove(m);
		}			
		P.N = OS->cu;
		if ((*(grid+((M.y+1)*x)+(M.x)) == 0 ) && ((M.x) <= (x-1)) && ((M.y + 1) <= (y-1)) && ((M.y) >= 0) && (M.x >= 0) && (*(closed+((M.y+1)*x)+(M.x)) != 1))
		{
			P.x = M.x;
			P.y = M.y + 1;
			P.findCost(xdest, ydest);
			Set[nb++] = P;
			*(closed+((P.y*x)+(P.x))) = 1;
		}
		if ((*(grid+((M.y)*x)+(M.x-1)) == 0 ) && ((M.x - 1) <= (x-1)) && ((M.y) <= (y-1)) && ((M.y) >= 0) && ((M.x - 1) >= 0) && (*(closed+((M.y)*x)+(M.x-1)) != 1))
		{
			P.x = M.x - 1;
			P.y = M.y;
			P.findCost(xdest, ydest);
			Set[nb++] = P;
			*(closed+((P.y*x)+(P.x))) = 1;
		}
		if (M.y>0) // ADDING
		if ((*(grid+((M.y-1)*x)+(M.x)) == 0 ) && ((M.x) <= (x-1)) && ((M.y - 1) <= (y-1)) && ((M.y- 1) >= 0) && (M.x >= 0) && (*(closed+((M.y-1)*x)+(M.x)) != 1))
		{
			P.x = M.x;
			P.y = M.y - 1;
			P.findCost(xdest, ydest);
			Set[nb++] = P;
			*(closed+((P.y*x)+(P.x))) = 1;
		}
		if ((*(grid+((M.y)*x)+(M.x+1)) == 0) && ((M.x+1) <= (x-1)) && ((M.y) <= (y-1)) && ((M.y) >= 0) && ((M.x+1) >= 0) && (*(closed+((M.y)*x)+(M.x+1)) != 1))
		{
			P.x = M.x+1;
			P.y = M.y;
			P.findCost(xdest, ydest);
			Set[nb++] = P;
			*(closed+((P.y*x)+(P.x))) = 1;
		}
		if (nb == 0)
		{
			FS->Pop(&P);
			if (OS->GetCount() == 0) return 0;
			FS->Push(OS->cu);
			if (FS->GetCount() == 0) return 0;
			//if (OS->GetCount() == 0) return -1;
		}
		for (int i=0; i<nb;i++)
			for (int j=i+1;j<nb;j++)
				if (Set[j].Cost > Set[i].Cost)
				{
					Position tmp = Set[j];
					Set[j] = Set[i];
					Set[i] = tmp;
				}
		for (int i=0; i<nb;i++)
		{
			OS->Push(&Set[i]);
		}
//		CLEAR();
//		AffGrid(closed, 0,0, 0,0, x, y);
	}
	return 0;	

}
