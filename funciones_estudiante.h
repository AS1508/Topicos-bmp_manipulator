#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED
#include "estructuras.h"
#include "constantes.h"
#define TAM 30
#define WIDTH 360
#define HEIGHT 240
#define ARGS '-'
#define IMG '.'
#define B_HEADER 14
#define B_IMG 10
#define B_WIDTH 18
#define B_HEIGHT 22
#define B_x 38
#define B_y 42

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
int promedioPixel(unsigned char valor1, unsigned char valor2,unsigned char valor3);
void copiarHeader(FILE**archivoOriginal, FILE**archivoNuevo, int inicioDeImagen);
void obtenerPosicion(FILE**archivo, int byte, int*posicion);

//Argumentos
void escalaGrises(char arg[][TAM], int posicion, char arch[]);
void ordenarReflejo(char arg[][TAM], int posicion, char nombre[]);
void rotarIzquierda(char arg[][TAM], int posicion, char nombre[]);
void rotarDerecha(char arg[][TAM], int posicion, char nombre[]);
void aumentarContraste(char arg[][TAM], int posicion, char nombre[]);
void reducirContraste(char arg[][TAM], int posicion, char nombre[]);
void recortar(char arg[][TAM], int posicion, char nombre[]);


void dump(char nombre[]);



#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED
