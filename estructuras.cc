//**************************************************************************
// Práctica 2
// Primitivas básicas para construir elementos sencillos que sirvan como 
// base para construir objetos más complejos por instanciación y jerarquías.
// calculo de las normales de caras y puntos
//
// Domingo Martin Perandres 2005-2012
// Pedro Cano Olivares 2012-2013
//          - Incluido estructuras y ejemplo de creacion de objeto jerárquico 
//
// GPL
//**************************************************************************

#include "estructuras.h"
#include "stdio.h"
#include "math.h"

/** Calcula el modulo del vector (x,y,z) **/
float modulo(float x,float y,float z)
{
   return sqrt(x*x+y*y+z*z);
}



//*************************************************************************
//* PRIMITIVAS BASICAS
//***********************************************************

/**
Construye un paralelepipedo alineado con los ejes de
dimension a x b x m. El objeto se construye en el semiespacio y>=0, con el origen en el
centro de la base. 
**/
void caja( float a, float b, float m, float a2, float m2)

{
	float x,y,z, x2, z2;
	
	if(a2 == -1 || m2 == -1){
		a2=a;
		m2=m;
	}
	x= a/2; x2=a2/2;
	z= m/2; z2=m2/2;
	y = b;



   glShadeModel( GL_FLAT );

   /* Caras transversales */
   glBegin( GL_QUAD_STRIP );{
      glNormal3f( 0.0, 0.0, -1.0 );   /* Vertical hacia atras */
      glVertex3f( x, 0, -z );
      glVertex3f( -x, 0, -z );
      glVertex3f( x2, y, -z2 );
      glVertex3f( -x2, y, -z2 );

	  glNormal3f( 0.0, 1.0, 0.0 );       /* Superior, horizontal */
	  glVertex3f( x2, y, z2 );
      glVertex3f( -x2, y, z2 );

	  glNormal3f( 0.0, 0.0, 1.0 );       /*Vertical delantera*/
      glVertex3f( x, 0, z );
      glVertex3f( -x, 0, z );
	  
	  glNormal3f( 0.0, -1.0, 0.0 );       /*Inferior */
      glVertex3f( x, 0, -z );
      glVertex3f( -x, 0, -z );  }
    glEnd();

   /* Costados */
   glBegin( GL_QUADS );{
      glNormal3f( 1.0, 0.0, 0.0 );
      glVertex3f( x, 0, -z );
      glVertex3f( x2, y, -z2 );
      glVertex3f( x2, y, z2 );
      glVertex3f( x, 0, z ); }
   glEnd();

   glBegin( GL_QUADS );{
      glNormal3f( -1.0, 0.0, 0.0 );
      glVertex3f( -x, 0, -z );
      glVertex3f( -x, 0, z );
      glVertex3f( -x2, y, z2 );
      glVertex3f( -x2, y, -z2 ); }
   glEnd();
}


/**

Crea un cilindro con centro de las bases en
x0,y0,z0 y x1,y1,z1, y radio de la base a.

**/
void cilindro(float x0, float y0, float z0,
		    float x1, float y1, float z1,
		    float a)
{
float a2,m;

m= modulo(x1-x0,y1-y0,z1-z0);
glPushMatrix();
	glTranslatef(x0,y0,z0);
	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);

	a2= a/2.0;
   glShadeModel( GL_SMOOTH );

   /* Caras transversales */
   glBegin( GL_QUAD_STRIP );{
      glNormal3f( 1.0, 0.0, -1.0 );

      glVertex3f(  a2, m, -a2 );
      glVertex3f(  a2, 0, -a2 );

     glNormal3f( -1.0, 0.0, -1.0 );

      glVertex3f( -a2, m, -a2 );
      glVertex3f( -a2, 0, -a2 );

     glNormal3f( -1.0, 0.0, 1.0 );

      glVertex3f( -a2, m, a2 );
      glVertex3f( -a2, 0, a2 );

    glNormal3f( 1.0, 0.0, 1.0 );

      glVertex3f(  a2, m, a2 );
      glVertex3f(  a2, 0, a2 );

     glNormal3f( 1.0, 0.0, -1.0 );

      glVertex3f(  a2, m, -a2 );
      glVertex3f(  a2, 0, -a2 );  }
    glEnd();
   glShadeModel( GL_FLAT );
  /* Tapas */
   glBegin( GL_QUADS );{
      glNormal3f( 0.0, 1.0, 0.0 );
      glVertex3f( -a2, m, -a2 );
      glVertex3f( -a2, m,  a2 );
      glVertex3f(  a2, m,  a2 );
      glVertex3f(  a2, m, -a2 ); }
   glEnd();


   glBegin( GL_QUADS );{
      glNormal3f( 0.0, -1.0, 0.0 );
      glVertex3f( -a2, 0, -a2 );
      glVertex3f(  a2, 0, -a2 );
      glVertex3f(  a2, 0,  a2 );
      glVertex3f( -a2, 0,  a2 ); }
   glEnd();
	
glPopMatrix();

}



/**
Crea un cilindro con centro de las bases en
x0,y0,z0 y x1,y1,z1, y radio de la base a, 
aproximado por n caras
**/
void cilindrof(float x0, float y0, float z0,
		    float x1, float y1, float z1,
		    float a, int n)
{
float m,x,z,i,xf,zf,da;

m= modulo(x1-x0,y1-y0,z1-z0);
glPushMatrix();
	glTranslatef(x0,y0,z0);
	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);


  glShadeModel( GL_SMOOTH );

   /* Caras transversales */
   xf = a;
   zf = 0;
   da = 2*M_PI/n;
   glBegin( GL_QUAD_STRIP );
   	for(i=0;i<=n;++i) {
		x=a*cos(da*i);
		z=a*sin(da*i);
  	    	glNormal3f( z, 0.0, x );
		glVertex3f(  x, 0, z );
      		glVertex3f(  x, m, z );
      		}
    glEnd();
   glShadeModel( GL_FLAT );

   // Tapaderas
 	glBegin( GL_POLYGON );
	glNormal3f( 0,-1,0 );
   	for(i=0;i<=n;++i) {
		x=a*cos(da*i);
		z=a*sin(da*i);
		glVertex3f(  x, 0, z );
      		}
    glEnd();
	glBegin( GL_POLYGON );
	glNormal3f( 0,1,0 );
   	for(i=n;i>=0;--i) {
		x=a*cos(da*i);
		z=a*sin(da*i);
		glVertex3f(  x, m, z );
      		}
    glEnd();
glPopMatrix();

}
