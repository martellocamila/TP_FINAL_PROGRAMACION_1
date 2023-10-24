#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "respuesta.h"
#include "pregunta.h"

struct RespuestaE{

    char respuesta[200];
    int nroPreguntaAsociada;
    int correcta;

};

RespuestaPtr crearRespuesta(){

    RespuestaPtr r = (RespuestaPtr) malloc(sizeof(struct RespuestaE));

    r->correcta = -1;
    r->nroPreguntaAsociada = -1;
    strcpy(r->respuesta, "VACIO");

    return r;

}

RespuestaPtr* crearArrayRespuestas(int t){

    RespuestaPtr* r = (RespuestaPtr*) malloc(t * sizeof(struct RespuestaE));

    for(int i=0; i<t; i++){
        r[i] = crearRespuesta();
    }

    return r;

}

void leerRespuestas(RespuestaPtr* r){

    FILE *archivo = fopen("respuestas.txt", "r");

    int i = 0;
    while(!feof(archivo)){
        char respuesta[200] = " ";
        fgets(respuesta, 200, archivo);
        RespuestaPtr resp = charARespuesta(respuesta, strlen(respuesta));
        r[i] = resp;
        i++;
    }

    fclose(archivo);

}

RespuestaPtr charARespuesta(char* c, int n){

    //forma respuesta;nroPreguntaAsociada;correcta

    RespuestaPtr r = malloc(sizeof(struct RespuestaE));

    int pos1 = -1;
    int pos2 = -1;

    //Busco la posicion del delimitador
    for(int i=0; i<n; i++){

        if(c[i] == ';'){
            pos1 = i;
            break;
        }
    }
    //Busco la posicion del segundo delimitador
    for(int i=pos1+1; i<n; i++){

        if(c[i] == ';'){
            pos2 = i;
            break;
        }
    }

    char auxRespuesta[201] = "";
    char auxNroPreguntaAsociada[3] = "";
    char auxCorrecta[3] = "";

    for(int i=0; i<pos1; i++){
        auxRespuesta[i] = c[i];
    }

    for(int i=pos1+1; i<pos2; i++){
        auxNroPreguntaAsociada[i-pos1-1] = c[i];
    }

    for(int i=pos2+1; i<n; i++){
        auxCorrecta[i-pos2-1] = c[i];
    }

    strcpy(r->respuesta, auxRespuesta);
    r->nroPreguntaAsociada = atoi(auxNroPreguntaAsociada);
    r->correcta = atoi(auxCorrecta);

    return r;
};

void mostrarRespuesta(RespuestaPtr r){

    printf("%s \n", r->respuesta);

}

int getNumeroPreguntaAsociada(RespuestaPtr r){

    return r->nroPreguntaAsociada;

}

char* getRespuesta(RespuestaPtr r){

    return r->respuesta;

}

int getPosicionCorrecta(RespuestaPtr *r){

    int indice = -1;

    for(int i=0; i<4; i++){
        if(r[i]->correcta == 1){
            indice = i;
            i = 5;
        }
    }

    return indice;
}

void liberarArrayRespuestas(RespuestaPtr* r, int t){

    for(int i=0; i<t; i++){
        free(r[i]);
    }

    free(r);

}

