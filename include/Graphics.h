/*

 * Auteur : Florian Richard - Joachim Bocaz-coeffe

 * Creation : 18-12-2017

 */

#ifndef __GRAPHICS__

#define __GRAPHICS__

#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "../include/Triangulation.h"

#define WIDTH 1040
#define HEIGHT 600
/*
#define X_UP_LEFT 5
#define X_DOWN_LEFT 517
#define Y_UP_LEFT 5
#define Y_DOWN_LEFT 517

#define X_UP_RIGHT 520
#define X_DOWN_RIGHT 1034
#define Y_UP_RIGHT 5
#define Y_DOWN_RIGHT 517
*/

/**
 * \struct Image
 * Structure contenant les définitions des images permettant l'affiche de l'interface
 */
typedef struct Image{
	MLV_Image *Image_left;
	MLV_Image *Image_right;
	MLV_Image *Add_constraint_point;
	MLV_Image *Hide_constraint_points;
	MLV_Image *Start_rendering;
	MLV_Image *Left;
	MLV_Image *Right;
	MLV_Image *Frames;
	MLV_Image *Quit;
}Image;

/**
 *\fn
 * Permet de charger toute les images de base. Renvoi une variable de type IMAGE 
 */
Image initImage();

/**
 *\fn
 * Dessine tout les triangles stockés dans la liste "list"
 */
void drawAllTriangle(TriangleList* list);

/**
 *\fn
 * Initialise la fenetre du programme en affichant les différentes images
 * et les triangles de départ contenue dans "list_left" et "list_right" 
 */
void initFenetre(TriangleList* list_left, TriangleList* list_right);

/**
 *\fn
 * Permet de regarder la position de la souris pour intéragir avec le programme 
 */
int checkMousePosition(TriangleList* list_left, TriangleList* list_right);

/**
 *\fn
 * Permet à l'utilisateur de dessiner un point sur l'image de droite
 * renvoie les coordonnées du point placé
 */
Point drawPointRight();

/**
 *\fn
 *Permet à l'utilisateur de dessiner un point sur l'image de gauche
 * renvoie les coordonnées du point placé
 */
Point drawPointLeft();

void deletePoint();

#endif
