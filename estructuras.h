//**************************************************************************
// Estructuras para crear gruas
// 
// GPL
//**************************************************************************

#ifndef _ESTRUCTURAS
#define _ESTRUCTURAS

#include <vector>

#include <stdlib.h>
#include <GL/glut.h>

#define seccion 0.1 

//***********************************************************
//* PRIMITIVAS
//***********************************************************

void caja( float a, float b, float m, float a2=-1, float m2=-1);
/* 
	Construye un paralelepipedo alineado con los ejes de
	dimension a x b x m. El objeto se construye en el semiespacio y>=0, con el origen en el
    centro de la base. 
*/

void cilindro(float x0, float y0, float z0, 
		      float x1, float y1, float z1, 
		      float a);
/*
	Crea un cilindro con centro de las bases en
	x0,y0,z0 y x1,y1,z1, y radio de la base a.
*/

void cilindrof(float x0, float y0, float z0,
		    float x1, float y1, float z1,
		    float a, int n);
/**
	Crea un cilindro con centro de las bases en
	x0,y0,z0 y x1,y1,z1, y radio de la base a, 
	aproximado por n caras
**/


#endif


