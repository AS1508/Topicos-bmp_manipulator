#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED
#include "estructuras.h"
#include "constantes.h"
#define C_ARG 2
#define TAM 30
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
//void cargaArchivo(t_imagen imagen, char *nombreArchivo);
t_metadata copyData(FILE* archivo);

//Argumentos
void escalaGrises(char arg[][TAM], int posicion, char arch[]);
void ordenarReflejo(t_pixel pixel);
void rotarIzquierda(t_pixel pixel);
void rotarDerecha(t_pixel pixel);
//void dump(char nombre[]);
//Continue



#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED
