/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
    (Sólo para grupos de tres integrantes)
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------

    Comentarios (opcionales) que deseen hacer al docente sobre el TP:

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "estructuras.h"
#include "funciones_estudiante.h"

int solucion(int argc, char* argv[])
{
    int i=0, cantidadArgumentos = 0;
    char argumentos[12][TAM], nombreArchivo[TAM] = {0}, buffer[TAM] = {0};


    while(i<argc)
    {
        printf("%s: ", argv[i]);
        strcpy(buffer, argv[i]);

        if((buscar(buffer, ARGS)) == 0 && (buscar(buffer, IMG)) == 0)
            printf("Argumento/imagen invalido\n");

        if(buscar(buffer, ARGS) == 1)
        {
            cantidadArgumentos++;
            strcpy(argumentos[i], argv[i]);
        }
        if(buscar(buffer, IMG) == 2)
        {
            strcpy(nombreArchivo, argv[i]);
            menu(argumentos, cantidadArgumentos, nombreArchivo);
            cantidadArgumentos = 0;
        }

        i++;
    }

    return TODO_OK;
}


/*######## Menu ########*/

void menu(char args[][TAM], int cantidad, char nombre[])
{
    int i=0;
    char funciones[12][TAM] = { {"--dump"},
        {"--negativo"},
        {"--escala-de-grises"},
        {"--aumentar-contraste"},
        {"--reducir-contraste"},
        {"--tonalidad-azul"},
        {"--tonalidad-verde"},
        {"--tonalidad-roja"},
        {"--recortar"},
        {"--rotar-izquierda"},
        {"--rotar-derecha"},
        {"--comodin"}
    };
    while(i<cantidad)
    {
        if(strcmp(args[i], funciones[i]) == 0)
            dump(nombre);
        if(strcmp(args[i], funciones[i]) == 0)
            escalaGrises(funciones, 2, nombre);
        if(strcmp(args[i], funciones[i]) == 0)
            aumentarContraste(funciones, 3, nombre);
        if(strcmp(args[i], funciones[i]) == 0)
            reducirContraste();
        if(strcmp(args[i], funciones[i]) == 0)
            tonalidadAzul();
        if(strcmp(args[i], funciones[i]) == 0)
            tonalidadVerde();
        if(strcmp(args[i], funciones[i]) == 0)
            tonalidadRoja();
        if(strcmp(args[i], funciones[i]) == 0)
            recortar();
        if(strcmp(args[i], funciones[i]) == 0)
            rotarIzquierda();
        if(strcmp(args[i], funciones[i]) == 0)
            rotarDerecha();
        if(strcmp(args[i], funciones[i]) == 0)
            comodin();

        i++;
    }
}

/*######## Argumentos ########*/


void escalaGrises(char arg[][TAM], int posicion, char arch[])
{
    t_metadata metadataOriginal;
    t_pixel pixelOriginal;
    t_pixel nuevoPixel;

    FILE* archivo = fopen(arch, "rb");
    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }

    strcat(arch, arg[posicion]);

    FILE* archivoNuevo = fopen(arch, "wb");
    if(archivoNuevo == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }

    printf("Creando Archivo \"%s\"\n", arg[posicion]);

    metadataOriginal = copyData(archivo);

    fwrite(&metadataOriginal, sizeof(t_metadata), 1, archivoNuevo);
    while(!feof(archivo))
        fwrite(&metadataOriginal, sizeof(t_metadata), 1, archivoNuevo);

    while(!feof(archivo))
    {
        //Problema: loopea infinitamente
        fread(&pixelOriginal, sizeof(pixelOriginal), 1, archivo);
        nuevoPixel.pixel[0] = (pixelOriginal.pixel[0] + pixelOriginal.pixel[1] + pixelOriginal.pixel[2])/3;
        nuevoPixel.pixel[1] = (pixelOriginal.pixel[0] + pixelOriginal.pixel[1] + pixelOriginal.pixel[2])/3;
        nuevoPixel.pixel[2] = (pixelOriginal.pixel[0] + pixelOriginal.pixel[1] + pixelOriginal.pixel[2])/3;
        nuevoPixel.profundidad = pixelOriginal.profundidad;
        fwrite(&nuevoPixel, sizeof(nuevoPixel), 1, archivoNuevo);

    }

    printf("Archivo creado \"%s\"con exito", arch);
    fclose(archivo);
    fclose(archivoNuevo);

}

void aumentarConstrate(char arg[][TAM], int posicion, char nombre[])
{

}

/*######## Funcionalidades ########*/

void dump(t_imagen* imagen, char nombre[])
{

}

int buscar(char arg[], char comando)
{
    int i = 0, cont = strlen(arg);

    if(arg[i] == comando && arg[i+1] == comando)
    {
        return 1;
    }
    if(arg[cont-4] == comando && arg[cont-3] == 'b' && arg[cont-2] == 'm' && arg[cont-1] == 'p')
    {
        return 2;
    }
    return 0;
}

t_metadata copyData(FILE* archivo)
{
    t_metadata metadata;
    fread(&metadata, sizeof(t_metadata), 1, archivo);
    return metadata;
}
