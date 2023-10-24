#ifndef PREGUNTA_H_INCLUDED
#define PREGUNTA_H_INCLUDED
#include "respuesta.h"

struct PreguntaE;
typedef struct PreguntaE * PreguntaPtr;

//constructores
PreguntaPtr crearPregunta();
PreguntaPtr* crearArrayPreguntas(int t);

//archivos
void leerPreguntas(PreguntaPtr* p);
PreguntaPtr charAPegunta(char* c, int n);
int contarRenglonesArchivo(char *c);
void guardarPreguntasEnArchivo();

void asociarRespuestas(PreguntaPtr* p, RespuestaPtr* r, int cantP, int cantR);
int indicePreguntaAleatoria(int* preguntasUsadas);

void mostrarPreguntaConRespuestas(PreguntaPtr* p, int pos);

//getter
RespuestaPtr* getPosibles(PreguntaPtr *p, int pos);

//destructor
void liberarArrayPreguntas(PreguntaPtr* p, int t);

#endif // PREGUNTA_H_INCLUDED
