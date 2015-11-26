/*
 * Helicopter.cpp
 *
 *  Created on: Nov 9, 2012
 *      Author: inaki
 */

#include "helicopter.h"
#include "estructuras.h"
#include "math.h"

#define alturaMinima 2
#define velRotMinima 12 // Helices
#define velRotElevMinima 13 // Helices
#define velMaxRotacion 25 // Helices + Ametralladora
#define inclMaxima 35 // En grados

#define velDisparo 3
#define velMisil 0.5
#define alcanceMisil 40

#define amarillo 0
#define gris 1
#define rojo 2
#define	marron 3
#define celeste 4
#define marron2 5
#define verde 6
#define azul 7
#define verde2 8
#define verde3 9
#define marron3 10
#define marron4 11
#define gris2 12
#define gris3 13
#define blanco 14
#define PI 3.14159265

/** Definicion de los colores usados.**/
float color[15][4]={{1,.8,.3,1.},{0.7,0.7,0.7,1},{1.0,0.0,0.0,1},
   		   {0.7,0.6,0.2,1},{0.2,1.0,1.0,1},{1.0,0.86,0.3,1},
		   {0.0,1.0,0.0,1.0}, {0.0,0.0,1.0,1.0}, {.128,.128,.0,1}, {.47,.79,.79,1}, {.210,.180,0.140,1.0},
		   {0.5,0.3,0.1,1.0}, {.105,.105,.105,1.0}, {.119,0.136,0.153,1.0}, {1,1,1,1}};

static GLUquadric *qobj;

Helicopter::Helicopter(){
	qobj = gluNewQuadric();
	gluQuadricDrawStyle( qobj, GL_FILL );
	vueloX=0;
	vueloY=0;
	vueloZ=0;
	giro=0;
	nMisil=0;

	alturaMinAlcanzada=false;
	disparoEfectuado=false;
	misilFuera[0]=false; misilFuera[1]=false;
	soltandoMisil[0]=false; soltandoMisil[2]=false;

	helicesRot=0;
	velRotHelices=0;
	velRotAmetralladora=0;

	ametrallVH=0;
	ametrallVVX=0;
	ametrallVVY=0;
	ametrallRot=0;

	inclTotX=0;
	inclTotZ=0;
	inclVel=0;

	disparo=0;
	movMisil[0]=0; movMisil[1]=0;
	sacarAspasMisil[0]=0; sacarAspasMisil[1]=0;
}

void Helicopter::base(){
	// dibuja base
	glPushMatrix();
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris2]);
			glTranslatef(0,0.5,0.5);
			caja(1,0.5,1);
		glPopMatrix();
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris3]);
			glTranslatef(0,0.5,-0.5);
			caja(1,0.5,1);
		glPopMatrix();
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris2]);
			glTranslatef(0,0,-0.5);
			caja(1,0.5,1);
		glPopMatrix();
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris3]);
			glTranslatef(0,0,0.5);
			caja(1,0.5,1);
		glPopMatrix();
	glPopMatrix();
	//
}
void Helicopter::morro(){
	// dibuja morro
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[marron3]);
		glTranslatef(0,0.5,1);
		glRotatef(90,1,0,0);
		caja(1,0.6,1,0.3,0.3);
	glPopMatrix();

}
void Helicopter::techo(){
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[verde2]);
		glTranslatef(0,1,0);
		caja(1,0.25,2,0.5,1);
	glPopMatrix();
}
void Helicopter::cola(){

	// dibuja base de cola
	glPushMatrix();
		glTranslatef(0,0.5,-1);
		glRotatef(-90,1,0,0);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[marron3]);
		caja(1,0.45,1,0.6,0.6);
	glPopMatrix();


	// dibujar largo de cola
	glPushMatrix();
		glTranslatef(0,0.5,-1.45);
		glRotatef(-90,1,0,0);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[verde2]);
		caja(0.6,3,0.6,0.2,0.4);
	glPopMatrix();

	// dibuja final de cola
	glPushMatrix();
		glTranslatef(0,0.5,-4.25);
		glRotatef(-25,1,0,0);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[marron3]);
		caja(0.2,0.7,0.3,0.2,0.2);
	glPopMatrix();
}
void Helicopter::rueda(){
	// Soporte de rueda
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris3]);
		glTranslatef(0,0.05,0.05);
		glRotatef(-45,1,0,0);
		gluCylinder( qobj, 0.02,0.02,0.9, 4,1);
	glPopMatrix();

	// Rueda
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris2]);
		glRotatef(-90,0,1,0);
		glutSolidTorus(0.03, 0.07, 20, 20);
	glPopMatrix();
}
void Helicopter::helices(float scaleX, float scaleY, float scaleZ, float scaleStickX, float scaleStickY, float scaleStickZ){
	// Soporte
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris3]);
		glScalef(scaleStickX,scaleStickY,scaleStickZ);
		cilindrof(0,0,0,0,-0.9,0,0.03,25);
	glPopMatrix();

	// Helices
	glPushMatrix();
	for(int i=0; i<5; i++){
		glRotatef(90,0,1,0);
		glPushMatrix();
			glRotatef(90,0,0,1);
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris2]);
			caja(0.01,0.3,0.05,0.01,0.05);
			glTranslatef(0,0.3,0);
			glScalef(scaleX, scaleY, scaleZ);
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris]);
			caja(0.01,4.5,0.3,0.01,0.17);
		glPopMatrix();
	}
	glPopMatrix();
}
void Helicopter::proyectil(){
	cilindrof(0,0,0,0,0,0.5,0.01,25);
}
void Helicopter::misil(int numeroMisil){
	// Cabeza
	glPushMatrix();
		glTranslatef(0,0,1.1);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[verde2]);
		glutSolidCone(0.05,0.25,40,2);
	glPopMatrix();

	// Culo
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[verde2]);
		cilindrof(0,0,0,0,0,0.1,0.05,35);
	glPopMatrix();

	// Aspas
	glPushMatrix();
		glScalef(sacarAspasMisil[numeroMisil],sacarAspasMisil[numeroMisil],sacarAspasMisil[numeroMisil]);
		glTranslatef(0,0,0.1);
		for(int i=0; i<5; i++){
			glRotatef(-90,0,0,1);
			glPushMatrix();
				glTranslatef(0,0,0.05);
				caja(0.02,0.2,0.1,0.02,0.05);
			glPopMatrix();
		}
	glPopMatrix();

	// Cuerpo
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[marron4]);
		glTranslatef(0,0,0.1);
		cilindrof(0,0,0,0,0,1,0.05,35);
	glPopMatrix();
}

void Helicopter::ametralladora(){
	//Rail
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[verde2]);
		glTranslatef(0,0.4,-0.04);
		caja(2,0.1,0.1);
	glPopMatrix();

	// Soporte
	glTranslatef(ametrallVH,0,0);
	glPushMatrix();
		glRotatef(-95,1,0,0);
		gluCylinder( qobj, 0.025,0.025,0.5, 25, 1);
	glPopMatrix();

	// Ametralladora
	glPushMatrix();
		glRotatef(ametrallVVY,0,1,0);
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris2]);
			glRotatef(ametrallVVX,1,0,0);

			// Base esferica
			glutSolidSphere(0.3,25,25);

			glPushMatrix();
				glRotatef(ametrallRot,0,0,1);

				// Platillos
				glPushMatrix();
					cilindrof(0,0,1.03,0,0,1.10,0.18,25);
					cilindrof(0,0,1.45,0,0,1.47,0.20,25);
					cilindrof(0,0,1.60,0,0,1.62,0.20,25);
					cilindrof(0,0,1.75,0,0,1.77,0.20,25);
				glPopMatrix();

				// Canyones
				glPushMatrix();
					glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris3]);
					for(int i = 0; i<8; i++){
						glRotatef(-45,0,0,1);
						glPushMatrix();
							glTranslatef(0,0.13,0);
							cilindrof(0,0,0,0,0,1.8,0.03,25);
						glPopMatrix();
					}
				glPopMatrix();

				// Proyectiles
				glPushMatrix();
				for(int i = 0; i<8; i++){
					if(disparoEfectuado){
						glTranslatef((velRotAmetralladora*0.001)*(disparo*2),(velRotAmetralladora*0.001)*(disparo*2),0);
					}
					glTranslatef(0,0,disparo);
					glPushMatrix();
						glTranslatef(0,0.13,0);
						glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[amarillo]);
						proyectil();
					glPopMatrix();
				}
				glPopMatrix();

			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
void Helicopter::canyon(int nCanyon){
	glPushMatrix();
		// Tapa
		glPushMatrix();
			glTranslatef(0,0,2.13);
			if(!misilFuera[nCanyon]){
				glTranslatef(0,0.12,0.1);
				glRotatef(90,1,0,0);
			}
			glRotatef(-45,0,1,0);
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris3]);
			cilindrof(0,0,0,0.02,0,0.02,0.1,35);
		glPopMatrix();

		// Culo
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris3]);
			glRotatef(-45,0,1,0);
			cilindrof(0,0,0,0.02,0,0.02,0.1,35);
		glPopMatrix();

		// Tubo
		glPushMatrix();
			glTranslatef(0,0,0.03);
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris3]);
			gluCylinder( qobj, 0.1,0.1,2.1, 35,1);
		glPopMatrix();

		// Misil
		glPushMatrix();
			switch(nCanyon){
				case 0:
					glTranslatef(0,0,movMisil[0]+0.04);
					break;
				case 1:
					glTranslatef(0,0,movMisil[1]+0.04);
					break;
			}

			glScalef(1.9,1.9,1.9);
			misil(nCanyon);
		glPopMatrix();
	glPopMatrix();
}

void Helicopter::posRuedas(){
	// Delanteras
	glPushMatrix();
		glTranslatef(0.35,-0.3,0.25);
		rueda();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.35,-0.3,0.25);
		rueda();
	glPopMatrix();

	// Trasera
	glPushMatrix();
		glTranslatef(0,-0.3,-3.3);
		rueda();
	glPopMatrix();
}
void Helicopter::posHelices(){
	// Helice principal
	glPushMatrix();
		glRotatef(helicesRot,0,1,0);
		glTranslatef(0,2,0);
		helices();
	glPopMatrix();

	// Helice trasera
	glPushMatrix();
		glTranslatef(-0.3,0.8,-4.40);
		glRotatef(helicesRot,1,0,0);
		glRotatef(90,0,0,1);
		helices(0.2,0.19,0.5,1,0.35);
	glPopMatrix();
}
void Helicopter::posAmetralladora(){
	glPushMatrix();
		glTranslatef(0,-0.25,0.9);
		glScalef(0.5,0.5,0.5);
		ametralladora();
	glPopMatrix();
}
void Helicopter::posCanyones(){
	glPushMatrix();
		glTranslatef(0.6,0.2,-1);
		canyon(0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.6,0.2,-1);
		canyon(1);
	glPopMatrix();
}

void Helicopter::moverAmetralladora(float velHoriz, float velVertX, float velVertY){
	if(ametrallVH+velHoriz < 0.96 && ametrallVH+velHoriz > -0.96){
		ametrallVH+=velHoriz;
	}
	if(alturaMinAlcanzada && ametrallVVX+velVertX <= 90 && ametrallVVX+velVertX >= 0){
		ametrallVVX+=velVertX;
	}
	if(ametrallVVY+velVertY <= 90 && ametrallVVY+velVertY >= -90){
		ametrallVVY+=velVertY;
	}
}

void Helicopter::inclinar(float inclX, float inclZ){


	if(alturaMinAlcanzada && abs(velRotHelices) > velRotMinima){
		inclVel=0;

		//if(giro < 90){
			int multiplier;
			if(inclZ != 0){
				multiplier=inclZ;
				inclZ = -multiplier * cos(giro*PI/180);
				inclX = multiplier * sin(giro*PI/180);
			}
			else if(inclX != 0){
				multiplier=inclX;
				inclX = multiplier * cos(giro*PI/180);
				inclZ = multiplier * sin(giro*PI/180);
			}
		//}

		if(abs(inclTotX+inclX) <= inclMaxima){
			inclTotX+=inclX;
		}
		if(abs(inclTotZ+inclZ) <= inclMaxima){
			inclTotZ+=inclZ;
		}
	}
}
void Helicopter::estabilizar(){
	if(velRotHelices > velRotMinima){
		velRotHelices = (velRotMinima + (velRotElevMinima - velRotMinima));
	}
	else if(abs(velRotHelices) > velRotMinima){
		velRotHelices = -(velRotMinima + (velRotElevMinima - velRotMinima));
	}
}

void Helicopter::disparar(){
	if(!disparoEfectuado){
		disparo=0;
		disparoEfectuado=true;
	}
}
void Helicopter::soltarMisil(int numeroMisil){
	soltandoMisil[numeroMisil]=true;
}

void Helicopter::flyControl(){
	if(abs(velRotHelices) > velRotMinima){
			if(inclTotX != 0){
				vueloX-=(abs(velRotHelices)*0.0001) * (inclTotX+0.2);
			}
			if(inclTotZ != 0){
				vueloZ+=(abs(velRotHelices)*0.0001) * (inclTotZ+0.2);
			}

		if(abs(velRotHelices) > velRotElevMinima){
			vueloY+=(abs(velRotHelices)*0.0005);
		}
	}

	else if(abs(velRotHelices) < velRotMinima && vueloY > 0){
		vueloY-=((velRotMinima/abs(velRotHelices))*0.005);
	}


	inclinationControl();
	groundControl();
}
void Helicopter::inclinationControl(){

	if(inclTotX > 0)
		inclTotX-=inclVel;
	if(inclTotX < 0)
		inclTotX+=inclVel;
	if(inclTotZ > 0)
		inclTotZ-=inclVel;
	if(inclTotZ < 0)
		inclTotZ+=inclVel;



	if(inclVel > 0.1 || inclVel < -0.1 ){
		if(inclTotX > 0 && inclTotX < 1)
			inclTotX = 0;
		else if(inclTotZ > 0 && inclTotZ < 1)
			inclTotZ = 0;
		else if(inclVel > 5)
			inclVel = 5;
	}

	inclVel+=0.009;
}
void Helicopter::groundControl(){
	if( vueloY < 0){ vueloY = 0; }
	if(!alturaMinAlcanzada && ametrallVVX>0){
		ametrallVVX-=0.3*velMaxRotacion/velRotHelices;
	}
	if(vueloY > alturaMinima){alturaMinAlcanzada = true;}
	else{alturaMinAlcanzada = false;}
}
void Helicopter::rotationControl(){
	if(velRotAmetralladora > velMaxRotacion){
		velRotAmetralladora = velMaxRotacion;
	}
	if(velRotHelices > velMaxRotacion){
		velRotHelices = velMaxRotacion;
	}
	ametrallRot+=velRotAmetralladora;
	helicesRot+=velRotHelices;
}
void Helicopter::shootControl(){
	if(disparoEfectuado){
		if(disparo<25){ disparo+=velDisparo; }
		else{ disparo=0; disparoEfectuado=false; }
	}
	for(int i=0; i<2; i++){
		if(soltandoMisil[i]){
			movMisil[i]+=velMisil;
			if(movMisil[i] > 2.2){
				misilFuera[i]=true;
				soltandoMisil[i]=false;
			}
		}
		else if(misilFuera[i]){
			if(movMisil[i]<alcanceMisil){
				movMisil[i]+=velMisil;
				if(sacarAspasMisil[i]<1){
					sacarAspasMisil[i]+=0.1;
				}
			}
			else{
				sacarAspasMisil[i]=0;
				movMisil[i]=0;
				misilFuera[i]=false;
			}
		}

	}
}

void Helicopter::draw(){
	// introducir posicion de la fuente de luz
	GLfloat Light_position[4]={5.0, 5.0, 10.0, 0.0};
	GLfloat Ambient_component[4]={0.4,0.4,0.4,1};

	glEnable(GL_CULL_FACE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,Ambient_component);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glLightfv(GL_LIGHT0,GL_POSITION,Light_position);
	glPopMatrix();
	glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	// inicio del modelado del custom
	glPushMatrix();
		glScalef(2,2,2);
		//glPushMatrix();
			glTranslatef(0+vueloX,0.4+vueloY,0+vueloZ);
			glRotatef(inclTotX,0,0,1);
			glRotatef(inclTotZ,1,0,0);
			//glPushMatrix();
				glRotatef(giro,0,1,0);

				base();
				morro();
				techo();
				cola();

				posRuedas();
				posAmetralladora();
				posHelices();
				posCanyones();

			//glPopMatrix();
		//glPopMatrix();

	glPopMatrix();
}

