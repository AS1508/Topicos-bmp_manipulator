/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Martinez Rodio
    Nombre: Alan Sebastian
    DNI: 45206315
    Entrega:
    -----------------
    Apellido: Risso
    Nombre:Santiago Nicolas
    DNI: 44552484
    Entrega:
    -----------------
    (Sólo para grupos de tres integrantes)
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------

    Comentarios (opcionales) que deseen hacer al docente sobre el TP:

    **
        Aquí deben hacer el código que solucione lo solicitado.
        Todas las funciones utilizadas deben estar declaradas en este archivo, y en su respectivo .h
    **

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_estudiante.h"


int solucion(int argc, char* argv[])
{
    int i=0, cantidadArgumentos = 0;
    char argumentos[12][TAM], nombreArchivo[TAM];
    t_imagen imagen;

    while(i<argc)
    {
        if((!buscar(&argv, ARGS, C_ARG)) && (!buscar(&argv, IMG, TAM)))
                printf("Argumento/imagen invalido\n");

        if(buscar(&argv, ARGS, C_ARG))
        {
            cantidadArgumentos++;
            strcpy(argumentos[i], argv[i]);
            i++;
        }
        if(buscar(argv, IMG, TAM))
        {
            strcpy(nombreArchivo, argv[i]);
            cargaArchivo(&imagen, &nombreArchivo);
            Menu(&imagen, &argumentos, cantidadArgumentos, &nombreArchivo);
            cantidadArgumentos = 0;
        }

        i++;
    }
    return 1;
}

/*######## Menu ########*/

void menu(t_imagen* imagen, char* args[][TAM], int cantidad, char* nombre[])
{
    int i=0;
    char funciones[12][TAM] = { {"--dump"}, {"--negativo"}, {"--escala-de-grises"}, {"--aumentar-contraste"}, {"--reducir-contraste"}, {"--tonalidad-azul"}, {"--tonalidad-verde"}, {"--tonalidad-roja"}, {"--recortar"}, {"--rotar-izquierda"}, {"--rotar-derecha"}, {"--comodin"} };
    while(!args)
    {
        for(int i=0; i<12; i++)
            if(strcmp(args[i], funciones[i]) != 0)
        if(strcmp(args[i], funciones[i]) == 0)
            dump(&imagen, &nombre);

        args++;
        i++;
    }

}

/*######## Argumentos ########*/



/*######## Funcionalidades ########*/

void dump(t_imagen* imagen, char nombre[])
{
    //FILE file;
    //file = fopen( nombre ,"rb");
    printf("Paso por dump");
}

int buscar(char* argv[], char* comando[], int cantidad)
{
    printf("Pase por Buscar ");

    return 1;
}

void cargaArchivo(t_imagen *imagen, char *nombreArchivo)
{
    FILE *file = fopen(nombreArchivo, "rb");
    if(file == NULL){ exit(1); }

    while(!feof(file))
        fwrite(&imagen, sizeof(t_imagen), 1, file);

    fclose(file);

}
//void copiaArchivo(t_pixel* pixel, t_metadata* datos, t_imagen* imagen) {    /*continue*/    }
