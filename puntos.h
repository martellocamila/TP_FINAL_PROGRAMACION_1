#ifndef PUNTOS_H_INCLUDED
#define PUNTOS_H_INCLUDED

struct PuntosE;
typedef struct PuntosE * PuntosPtr;

//constructor
PuntosPtr crearPuntos();

//getters
int getPuntuacionMaxima(PuntosPtr p);
int getPuntosActuales(PuntosPtr p);

//setters
void setPuntosActuales(PuntosPtr p, int nuevosPuntosActuales);
void setPuntuacionMaxima(PuntosPtr p, int nuevaPuntuacionMaxima);

//destructor
void liberarPuntos(PuntosPtr p);

#endif // PUNTOS_H_INCLUDED
