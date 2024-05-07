#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED
#include "estructuras.h"
#include "constantes.h"
#define TAM 30
#define WIDTH 360
#define HEIGHT 240
#define ARGS '-'
#define IMG '.'

typedef struct
{
    t_metadata datos;
    t_pixel pixeles;
} t_imagen;

//General
int solucion(int argc, char* argv[]);
int buscar(char arg[], char comando);

//menu
void menu(char args[][TAM], int cantidad, char nombre[]);

//Funciones
void copyData(FILE*archivoOriginal, FILE*archivoNuevo);

//Argumentos
void escalaGrises(char arg[][TAM], int posicion, char arch[]);
void ordenarReflejo(t_pixel pixel);
void rotarIzquierda(t_pixel pixel);
void rotarDerecha(t_pixel pixel);

void dump(char nombre[]);



#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED
