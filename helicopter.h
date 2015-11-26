/*
 * Helicopter.h
 *
 *  Created on: Nov 9, 2012
 *      Author: inaki
 */

#ifndef HELICOPTER_H_
#define HELICOPTER_H_

#include <stdlib.h>
#include <GL/glut.h>

class Helicopter{
private:
	float inclTotX;
	float inclTotZ;
	float inclVel;

	float vueloY;
	float vueloX;
	float vueloZ;

	float disparo;
	float movMisil[2];
	float sacarAspasMisil[2];
	float nMisil;

	bool alturaMinAlcanzada;
	bool disparoEfectuado;
	bool misilFuera[2];
	bool soltandoMisil[2];

	float ametrallVH;
	float ametrallVVX;
	float ametrallRot;
	float ametrallVVY;

	float helicesRot;

public:
	float velRotHelices;
	float velRotAmetralladora;
	float giro;



			Helicopter();
    void draw();

    void base();
    void morro();
    void techo();
    void cola();
    void rueda();
    void helices(float scaleX=1, float scaleY=1, float scaleZ=1, float scaleStickX=1, float scaleStickY=1, float scaleStickZ=1);
    void proyectil();
    void misil(int numeroMisil);

    void ametralladora();
    void canyon(int nCanyon);

    void posRuedas();
    void posHelices();
    void posAmetralladora();
    void posCanyones();

    void moverAmetralladora(float velHoriz=0, float velVertX=0, float velVertY=0);

    void inclinar(float inclX, float inclZ);
    void estabilizar();

    void disparar();
    void soltarMisil(int numeroMisil=0);

    void flyControl();
		void inclinationControl();
		void groundControl();
    void rotationControl();
    void shootControl();
};

#endif /* HELICOPTER_H_ */
