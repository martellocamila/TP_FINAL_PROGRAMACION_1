#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puntos.h"

struct PuntosE{

    int actuales;
    int puntuacionMaxima;

};

PuntosPtr crearPuntos(){

    PuntosPtr p = malloc(sizeof(struct PuntosE));

    p->actuales = 0;
    p->puntuacionMaxima = 0;

    return p;

}

void liberarPuntos(PuntosPtr p){

    free(p);

}

void setPuntosActuales(PuntosPtr p, int nuevosPuntosActuales){

    p->actuales = nuevosPuntosActuales;

}

void setPuntuacionMaxima(PuntosPtr p, int nuevaPuntuacionMaxima){

    p->puntuacionMaxima = nuevaPuntuacionMaxima;

}

int getPuntuacionMaxima(PuntosPtr p){

    return p->puntuacionMaxima;

}

int getPuntosActuales(PuntosPtr p){

    return p->actuales;

}
