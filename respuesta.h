#ifndef RESPUESTA_H_INCLUDED
#define RESPUESTA_H_INCLUDED

struct RespuestaE;
typedef struct RespuestaE * RespuestaPtr;

//contructores
RespuestaPtr crearRespuesta();
RespuestaPtr* crearArrayRespuestas(int t);

//archivo
RespuestaPtr charARespuesta(char* c, int n);
void leerRespuestas(RespuestaPtr* r);

void mostrarRespuesta(RespuestaPtr r);

//getters
int getNumeroPreguntaAsociada(RespuestaPtr r);
char* getRespuesta(RespuestaPtr r);
int getPosicionCorrecta(RespuestaPtr *r);

//destructor
void liberarArrayRespuestas(RespuestaPtr* r, int t);

#endif // RESPUESTA_H_INCLUDED
