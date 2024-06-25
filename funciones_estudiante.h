#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "constantes.h"
#include "estructuras.h"

#define ARGS '-'
#define IMG '.'
#define DERECHA 'D'
#define IZQUIERDA 'I'

#define T_PIXEL 3
#define B_IMG 10
#define B_BMP 14
#define B_WIDTH 18
#define B_HEIGHT 22
#define B_ANCHO 18
#define B_ALTO 22
#define B_TAM 34

#define LEGHT 128
#define L_DATA 54

#define MAXIMO(x,y) ( (x < y) ? x : y )
#define MINIMO(x,y) ( (x > y) ? x : y )

/*Funciones*/

int solucion(int argc, char* argv[]);
int buscar(const char *arg);
void reset(int *arg, int cantidad);
void mostrar(const int *arg, int cantidad);
int identificar(const char *arg);
int buscarFuncion(const char **f, const char *a);
void copiarData(FILE **imgO, FILE **imgN, unsigned int *byte);
void posicionData(FILE**img, unsigned int *dataPosicion);
void calcularNegativo(t_pixel *p);
void calcularEscalaDeGrises(t_pixel *p);
void calcularContraste(t_pixel *p, const char type);
void calcularColores(t_pixel *p, const char type);
void dimesiones(FILE**img, t_metadata*data);
void rotarDimensiones(FILE**img, t_metadata*data);
void actualizarDimensiones(FILE**img, t_metadata*data);
void imagenRecortada(FILE **imgO, FILE **imgN, t_metadata *data, t_pixel *pixel);
void calcularGiro(FILE **imgO, FILE **imgN, t_metadata *data, t_pixel *pixel, char type);
unsigned char **CrearMatriz(unsigned int *fila, unsigned int *columna);
void liberarMatriz(unsigned char **m, unsigned int *ancho);

/*Argumentos*/
void menu(const char *nombre, const int *argumento, const int status);
void help();
void dump(const char *nombre);
void negativo(const char *nombre, const char *arg, FILE**imgO, FILE**imgN);
void escalaDeGrises(const char *nombre, const char *arg, FILE**imgO, FILE**imgN);
void aumentarContraste(const char *nombre, const char *arg, FILE**imgO, FILE**imgN);
void reducirContraste(const char *nombre, const char *arg, FILE **imgO, FILE **imgN);
void azul(const char *nombre, const char *arg, FILE **imgO, FILE **imgN);
void verde(const char *nombre, const char *arg, FILE **imgO, FILE **imgN);
void rojo(const char *nombre, const char *arg, FILE **imgO, FILE **imgN);
void recortar(const char *nombre, const char *arg, FILE **imgO, FILE **imgN);
void rotarIzquierda(const char *nombre, const char *arg, FILE **imgO, FILE **imgN);
void rotarDerecha(const char *nombre, const char *arg, FILE **imgO, FILE **imgN);

#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED
