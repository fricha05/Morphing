/*

 * Auteur : Florian Richard - Joachim Bocaz-coeffe

 * Creation : 18-12-2017

 */


#include "../include/Triangulation.h"


TriangleList* addTriangleInList(TriangleList* list, Triangle T){
	TriangleList* new;
	new = malloc(sizeof(*new));
	new->current = T;
	new->next = list;
	return new;
}


Matrice creationMatrice(Triangle t, Point p){
	Matrice m;
	m.A = ((t.A).X)-(p.X);
	m.B = ((t.A).Y)-(p.Y);
	m.C = (pow((t.A).X, 2) - (pow((p.X), 2))) + (pow((t.A).Y, 2) - (pow((p.Y), 2)));
	m.D = ((t.B).X)-(p.X);
	m.E = ((t.B).Y)-(p.Y);
	m.F = (pow((t.B).X, 2) - (pow((p.X), 2))) + (pow((t.B).Y, 2) - (pow((p.Y), 2)));
	m.G = ((t.C).X)-(p.X);
	m.H = ((t.C).Y)-(p.Y);
	m.I = (pow((t.C).X, 2) - (pow((p.X), 2))) + (pow((t.C).Y, 2) - (pow((p.Y), 2)));
	return m;
}

int isInsideCircle(Matrice m){
	int det = (m.A*m.E*m.I + m.D*m.H*m.C + m.G*m.B*m.F) - (m.G*m.E*m.C + m.A*m.H*m.F + m.D*m.B*m.I);
	if(det > 0){
		printf("Le point est dans ce cercle\n");
		return 1;
	}
	printf("Le point n'est pas dans ce cercle\n");
	return 0;
}

void initializePoint(Point* P, int X, int Y){
	P->X = X;
	P->Y = Y;
}

void initializeTriangle(Triangle* t, Point A, Point B, Point C){
	if(C.X > B.X){
		t->A = A;
		t->C = B;
		t->B = C;	
	}
	t->A = A;
	t->B = B;
	t->C = C;
}

int pointInTriangle(Point P, Triangle T){
	int alpha = ((T.A.X - P.X) * (T.B.Y - P.Y) - (T.A.Y - P.Y) * (T.B.X - P.X));
	int beta = ((T.B.X - P.X) * (T.C.Y - P.Y) - (T.B.Y - P.Y) * (T.C.X - P.X));
	int gamma = ((T.C.X - P.X) * (T.A.Y - P.Y) - (T.C.Y - P.Y) * (T.A.X - P.X));
	
	if(alpha >= 0 && beta >= 0 && gamma >= 0){
		return 1;
	}
	if(alpha <= 0 && beta <= 0 && gamma <= 0){
		alpha = -alpha;
		beta = -beta;
		gamma = -gamma;
		return 1;
	}
	return 0;
}

Triangle inThisTriangle(TriangleList* list, Point P){
	TriangleList* tmp = list;
	Triangle t;
	while(tmp){
		if(pointInTriangle(P, tmp->current) == 1){
			return tmp->current;
		}
		else{
			tmp = tmp->next;
		}
	}
	fprintf(stderr, "The point is not in any triangle\n");
	return t;
}

void printTriangleList(TriangleList* list){
	while(list){
		printf("A(%d,%d), B(%d,%d), C(%d,%d)\n", list->current.A.X, list->current.A.Y, list->current.B.X, list->current.B.Y, list->current.C.X, list->current.C.Y);
		list = list->next;
	}
	printf("\n");
}

TriangleList* deleteTriangle(TriangleList* list, Triangle T){
	TriangleList* tmp = list;
	TriangleList* supp;
	if(T.A.X == list->current.A.X && T.B.X == list->current.B.X && T.C.X == list->current.C.X){
		list = list->next;
		free(tmp);
		return list;
	}
	while(T.A.X != tmp->next->current.A.X && T.B.X != tmp->next->current.B.X && T.C.X != tmp->next->current.C.X){
		tmp = tmp->next;
	}
	supp = tmp->next;
	tmp->next = supp->next;
	supp->next = NULL;
	free(supp);
	return list;
}

TriangleList* popTriangles(TriangleList* list, Point P){
	Triangle T = inThisTriangle(list, P);
	Triangle new1, new2, new3;
	Point TA = T.A;
	Point TB = T.B;
	Point TC = T.C;
	
	initializeTriangle(&new1, TA, TB, P);
	initializeTriangle(&new2, TB, TC, P);
	initializeTriangle(&new3, TC, TA, P);
	
	list = deleteTriangle(list, T);

	list = addTriangleInList(list, new1);
	list = addTriangleInList(list, new2);
	list = addTriangleInList(list, new3);


	
	return list;
}

TriangleList* flip(TriangleList* list, Point P){
	Matrice m;
	Triangle t, T1, T2, T3, T4;
	TriangleList* tmp = list;
	while(tmp){
		t = tmp->current;
		m = creationMatrice(t, P);
		if(isInsideCircle(m) == 1){
			initializeTriangle(&T1, tmp->current.A, P, tmp->current.C);
			initializeTriangle(&T2, tmp->current.C, P, tmp->current.B);
			initializeTriangle(&T3, tmp->current.A, P, tmp->current.B);
			T4 = inThisTriangle(list, P);
			
			list = addTriangleInList(list, T1);
			list = addTriangleInList(list, T2);

			list = deleteTriangle(list, tmp->current);
			list = deleteTriangle(list, T3);
			list = deleteTriangle(list, T4);
			flip(list, P);
		}
		else{
			tmp = tmp->next;
		}
	}
	printf("après while flip\n");
	printTriangleList(list);
	return list;
}

TriangleList* initTrianglesRight(TriangleList* listLeft, Point PointLeft, Point PointRight){
	TriangleList* listRight = listLeft;
	while(listRight){
		if(listRight->current.A.X == PointLeft.X && listRight->current.A.Y == PointLeft.Y){
			listRight->current.A = PointRight;
		}
		if(listRight->current.B.X == PointLeft.X && listRight->current.B.Y == PointLeft.Y){
			listRight->current.B = PointRight;
		}
		if(listRight->current.C.X == PointLeft.X && listRight->current.C.Y == PointLeft.Y){
			listRight->current.C = PointRight;
		}
		listRight = listRight->next;
	}
	return listRight;
}
