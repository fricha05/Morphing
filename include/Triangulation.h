/*

 * Auteur : Florian Richard - Joachim Bocaz-coeffe

 * Creation : 18-12-2017

 */

#ifndef __TRIANGULATION__

#define __TRIANGULATION__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * \struct Matrice
 * Structure contenant les 9 éléments d'une matrice 3x3
 */
typedef struct Matrice
{
	int A, B, C, D, E, F, G, H, I;
}Matrice;

/**
 * \struct Point
 * Structure contenant des entiers correspondants aux coordonnées d'un point
 */
typedef struct Point
{
	int X,Y;
}Point;

/**
 * \struct Triangle
 * Structure définissant un triangle à partir de trois Point
 */
typedef struct Triangle
{
	Point A, B, C;
}Triangle;


/**
 * \struct TriangleList
 * Liste chaînée de triangles
 */
typedef struct TriangleInList
{
	struct TriangleInList* next;
	Triangle current;
}TriangleList;

/**
 * alloue un triangle "T" a une liste de triangle "list"
 * renvoie une nouvelle liste de triangle
 */
TriangleList* addTriangleInList(TriangleList* list, Triangle T);

/**
 * Renvoie une matrice 3*3 calculée à partir d'un triangle "t" et d'un point "p"
 */
Matrice creationMatrice(Triangle t, Point p);

/**
 * Calcul le déterminant d'une matrice "m".
 * renvoie 1 si le déterminant de la matrice est positif 
 * et détermine que le point de la matrice est dans le cercle circonscrit au triangle
 * renvoie 0 sinon 
 */
int isInsideCircle(Matrice m);

/**
 * initialise un point "P" avec les coordonées "X" et "Y" 
 */
void initializePoint(Point* P, int X, int Y);

/**
 * initialise un triangle "t" de point "A", "B" et "C" 
 */
void initializeTriangle(Triangle* t, Point A, Point B, Point C);

/**
 * Calcule si un point "P" est dans un triangle T
 * renvoie 1 si le point est dans le triangle
 * renvoie 0 sinon
 */
int pointInTriangle(Point P, Triangle T);

/**
 * Regarde si un point "P" est dans un triangle 
 * appartenant à une liste de triangle "list"
 * renvoie le triangle où est situé le point
 */
Triangle inThisTriangle(TriangleList* list, Point P);

/**
 * Supprime un triangle "T" d'une liste de triangle "list" 
 * renvoie la liste de triangle modifié
 */
TriangleList* deleteTriangle(TriangleList* list, Triangle T);

void printTriangleList(TriangleList* list);

/**
 * Crée 3 triangles en fonction d'un nouveau point "P"
 * supprime le triangle appartenant à une liste de triangle "list" où était le point
 * renvoie la liste de triangle modifié
 */
TriangleList* popTriangles(TriangleList* list, Point P);

/**
 * Permet de faire flipper l'arrete d'un triangle pour remplacer les triangles 
 * et de faire une triangulation de Delauney
 * Non fonctionnelle
 */
TriangleList* flip(TriangleList* list, Point P);

/**
 * Initialise la liste de triangles de l'image de droite en fonction 
 * de la liste de triangle de l'image de gauche de gauche et des points cliqués par l'utilisateur
 * Non fonctionnelle
 */
TriangleList* initTrianglesRight(TriangleList* listLeft, Point PointLeft, Point PointRight);

#endif
