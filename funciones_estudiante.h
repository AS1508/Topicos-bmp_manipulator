#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED
#include "estructuras.h"
#define C_ARG 2
#define TAM 30
#define ARGS '-'
#define IMG '.'

typedef struct
{
    unsigned char tipoDato[2];
    t_metadata datos;
    t_pixel imagen;
} t_imagen;

void solucion(int argc, char* argv[]);
void menu(t_imagen* imagen, char args[][TAM], int cantidad, char nombre[]);
void cargaArchivo(t_imagen *imagen, char *nombreArchivo);
void copiaArchivo(t_pixel *pixel, t_metadata *datos, t_imagen *imagen);
void ordenarReflejo(t_pixel *pixel);
void rotarIzquierda(t_pixel *pixel);
void rotarDerecha(t_pixel *pixel);
int buscar(char *argv[], char comando, int cantidad);

void dump(t_imagen *imagen, char nombre[]);
//Continue


#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED
