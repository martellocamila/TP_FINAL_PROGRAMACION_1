#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pregunta.h"
#include "respuesta.h"

struct PreguntaE{

    int nroPregunta;
    char pregunta[100];
    RespuestaPtr *posibles;

};

PreguntaPtr crearPregunta(){

    PreguntaPtr p = (PreguntaPtr) malloc(sizeof(struct PreguntaE));

    p->nroPregunta = -1;
    p->posibles = crearArrayRespuestas(4);
    strcpy(p->pregunta, "VACIO");

    return p;

}

PreguntaPtr* crearArrayPreguntas(int t){

    PreguntaPtr* p = (PreguntaPtr*) malloc(t * sizeof(struct PreguntaE));

    for(int i=0; i<t; i++){
        p[i] = crearPregunta();
    }

    return p;

}

void leerPreguntas(PreguntaPtr* p){

    FILE *archivo = fopen("preguntas.txt", "r");

    if(archivo == NULL){
        printf("\nError al abrir el archivo de preguntas. ");
        exit(1);
    }

    int i = 0;
    while(!feof(archivo)){
        char preguntas[200] = " ";
        fgets(preguntas, 200, archivo);
        PreguntaPtr preg = charAPegunta(preguntas, 200);
        p[i] = preg;
        i++;
    }


    fclose(archivo);

};

PreguntaPtr charAPegunta(char* c, int n){

    //nroPregunta;Pregunta

    PreguntaPtr p = (PreguntaPtr)malloc(sizeof(struct PreguntaE));

    int pos = -1;

    //Busco la posicion del delimitador
    for(int i=0; i<n; i++){

        if(c[i] == ';'){
            pos = i;
            i = n;
        }

    }

    //Variables para recuperar la info leida
    char auxPregunta[200] = " ";
    char auxNroPregunta[10] = " ";

    for(int i=0; i<pos; i++){

        auxNroPregunta[i] = c[i];
    }
    auxNroPregunta[pos] = '\0';

    for(int i=pos+1; i<n; i++){

        auxPregunta[i-pos-1] = c[i];
    }
     auxPregunta[n - pos - 1] = '\0';

    p->nroPregunta = atoi(auxNroPregunta); //Casteo array to int
    strcpy(p->pregunta, auxPregunta);


    return p;
};

void asociarRespuestas(PreguntaPtr* p, RespuestaPtr* r, int cantP, int cantR) {

    for (int i=0; i<cantP; i++) {
        int k = 0;
        p[i]->posibles = crearArrayRespuestas(4);
        for (int j=0; j<cantR; j++){
            if (p[i]->nroPregunta == getNumeroPreguntaAsociada(r[j])){
                p[i]->posibles[k]= r[j];
                k++;
            }
        }
    }

}

void mostrarPreguntaConRespuestas(PreguntaPtr* p, int pos) {

    printf("%s\n", p[pos]->pregunta);
    for (int j=0; j<4; j++) {
            printf("%d -> ", j+1);
            mostrarRespuesta(p[pos]->posibles[j]);
        }

}

int indicePreguntaAleatoria(int* preguntasUsadas){

    int indicePregunta;

    do{
        indicePregunta = rand() % contarRenglonesArchivo("preguntas.txt");

    }while(preguntasUsadas[indicePregunta] == 1);

    preguntasUsadas[indicePregunta] = 1;

    return indicePregunta;

}

int contarRenglonesArchivo(char *c){

    FILE * archivo = fopen(c, "r");

    int pos = 0;
    char renglon[200];

    while (fgets(renglon, sizeof(renglon), archivo) != NULL) {
        pos++;
    }

    fclose(archivo);

    return pos;
}

RespuestaPtr* getPosibles(PreguntaPtr *p, int pos){

    return p[pos]->posibles;

}

void liberarArrayPreguntas(PreguntaPtr* p, int t){

    for(int i=0; i<t; i++){
        liberarArrayRespuestas(p[i]->posibles, 4);
        free(p[i]);
    }

    free(p);

}

