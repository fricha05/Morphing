/*

 * Auteur : Florian Richard - Joachim Bocaz-coeffe

 * Creation : 18-12-2017

 */

#include "../include/Graphics.h"

Image initImage(){
	Image jeu;

	jeu.Image_left = MLV_load_image("images/Image_left.jpg");
	if(!jeu.Image_left){
		printf("Impossible de charger Image_left.jpg\n");
		exit(EXIT_FAILURE);
	}

	jeu.Image_right = MLV_load_image("images/Image_right.jpg");
	if(!jeu.Image_right){
		printf("Impossible de charger Image_right.jpg\n");
		exit(EXIT_FAILURE);
	}
	jeu.Add_constraint_point = MLV_load_image("images/Add_constraint_point.png");
	if(!jeu.Add_constraint_point){
		printf("Impossible de charger Add_constraint_point.png\n");
		exit(EXIT_FAILURE);
	}
	jeu.Hide_constraint_points = MLV_load_image("images/Hide_constraint_points.png");
	if(!jeu.Hide_constraint_points){
		printf("Impossible de charger Hide_constraint_points.png\n");
		exit(EXIT_FAILURE);
	}
	jeu.Start_rendering = MLV_load_image("images/Start_rendering.png");
	if(!jeu.Start_rendering){
		printf("Impossible de charger Start_rendering.png\n");
		exit(EXIT_FAILURE);
	}
	jeu.Left = MLV_load_image("images/Left.png");
	if(!jeu.Left){
		printf("Impossible de charger Left.png\n");
		exit(EXIT_FAILURE);
	}
	jeu.Right = MLV_load_image("images/Right.png");
	if(!jeu.Right){
		printf("Impossible de charger Right.png\n");
		exit(EXIT_FAILURE);
	}
	jeu.Frames = MLV_load_image("images/Frames.png");
	if(!jeu.Frames){
		printf("Impossible de charger Frames.png\n");
		exit(EXIT_FAILURE);
	}
	jeu.Quit = MLV_load_image("images/Quit.png");
	if(!jeu.Quit){
		printf("Impossible de charger Quit.png\n");
		exit(EXIT_FAILURE);
	}
	return jeu;
}



void drawAllTriangle(TriangleList* list){

	TriangleList* t = list;

	int point_x[3];
	int point_y[3];

	printf("drawAllTriangle : \n");
	printTriangleList(list);

	while(t != NULL){
		point_x[0] = t->current.A.X;
		point_x[1] = t->current.B.X;
		point_x[2] = t->current.C.X;
		point_y[0] = t->current.A.Y;
		point_y[1] = t->current.B.Y;
		point_y[2] = t->current.C.Y;

		MLV_draw_polygon(point_x, point_y, 3, MLV_COLOR_RED);

		t = t->next;
	}
	free(t);
}

void initFenetre(TriangleList* list_left, TriangleList* list_right){
	Image jeu;

	printf("initFenetre : \n");
	printTriangleList(list_left);
	printTriangleList(list_right);


	MLV_clear_window(MLV_COLOR_BLACK);

	jeu = initImage();

	MLV_draw_image(jeu.Image_left, 5, 5);
	MLV_draw_image(jeu.Image_right, 520, 5);  

	MLV_draw_image(jeu.Add_constraint_point, 100, 550); 
	MLV_draw_image(jeu.Hide_constraint_points, 250, 550);
	MLV_draw_image(jeu.Start_rendering, 400, 550);
	MLV_draw_image(jeu.Left, 550, 550); 
	MLV_draw_image(jeu.Frames, 605, 550); 
	MLV_draw_image(jeu.Right, 650, 550); 
	MLV_draw_image(jeu.Quit, 900, 550);

	drawAllTriangle(list_left);
	drawAllTriangle(list_right);
	
	MLV_update_window();
}


Point drawPointLeft(){
	int x, y;
	Point p;

	MLV_wait_mouse(&x, &y);
	
	while(!(x >= 5 && x <= 517 && y >= 5 && y <= 517)){
		MLV_wait_mouse(&x, &y);
	}

	MLV_draw_filled_circle(x, y, 5, MLV_COLOR_RED);
	p.X = x;
	p.Y = y;

	printf("point 1 dessiné\n");

	MLV_update_window();
	printf("P = (%d,%d)\n", p.X, p.Y);

	return p;
}

Point drawPointRight(){
	int x, y;
	Point p;

	MLV_wait_mouse(&x, &y);

	while(!(x >= 520 && x <= 1034 && y >= 5 && y <= 517)){
		MLV_wait_mouse(&x, &y);
	}

	MLV_draw_filled_circle(x, y, 5, MLV_COLOR_RED);
	p.X = x;
	p.Y = y;

	printf("point 2 dessiné\n");

	MLV_update_window();

	return p;
}

int checkMousePosition(TriangleList* list_left, TriangleList* list_right){
	int x, y;

	MLV_wait_mouse(&x, &y);

	if(x >= 900 && x <= 936 && y >= 550 && y <= 579){
		return 1;
	}

	else if(x >= 100 && x <= 250 && y >= 550 && y <= 579){
		printf("wait to draw a point\n");
		
		list_left = popTriangles(list_left, drawPointLeft());
		list_right = popTriangles(list_right, drawPointRight());

		drawAllTriangle(list_left);
		
		drawAllTriangle(list_right);
		
	}

	else if(x >= 100 && x <= 517 && y >= 5 && y <= 517){
		deletePoint();
	}

	return 0;
}


void deletePoint(){
}
