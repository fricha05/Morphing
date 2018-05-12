/*

 * Auteur : Florian Richard - Joachim Bocaz-coeffe

 * Creation : 18-12-2017

 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/Graphics.h"

int main(int argc, char const *argv[])
{
	int status = 0;
	Point A, B, C, D, E, F, G, H;
	Triangle T1, T2, T3, T4;
	TriangleList* list_left = NULL;
	TriangleList* list_right = NULL;

	MLV_create_window("Morphing", "Morphing", WIDTH, HEIGHT);

	initializePoint(&A, 5, 5);
	initializePoint(&B, 5, 517);
	initializePoint(&C, 517, 517);
	initializePoint(&D, 517, 5);

	initializePoint(&E, 520, 5);
	initializePoint(&F, 520, 517);
	initializePoint(&G, 1032, 517);
	initializePoint(&H, 1032, 5);
	
	initializeTriangle(&T1, A, B, C);
	initializeTriangle(&T2, A, C, D);
	initializeTriangle(&T3, E, F, G);
	initializeTriangle(&T4, E, G, H);

	
	list_left = addTriangleInList(list_left, T1);
	list_left = addTriangleInList(list_left, T2);
	
	list_right = addTriangleInList(list_right, T3);
	list_right = addTriangleInList(list_right, T4);
	
	initFenetre(list_left, list_right);


	while(status != 1){
		int x, y;
		Point left;
		MLV_wait_mouse(&x, &y);
		if(x >= 900 && x <= 936 && y >= 550 && y <= 579){
			return 1;
		}
		else if(x >= 100 && x <= 250 && y >= 550 && y <= 579){
			printf("wait to draw a point\n");
			left = drawPointLeft();
			list_left = popTriangles(list_left, left);
			list_right = popTriangles(list_right, drawPointRight());
			initFenetre(list_left, list_right);
		
		}
		else if(x >= 100 && x <= 517 && y >= 5 && y <= 517){
			deletePoint();
		}
		status = 0;
		MLV_update_window();
	}
	return 0;
}
