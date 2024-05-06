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
    t_imagen imagen;


    while(i<argc)
    {
        printf("%s: ", argv[i]);
        strcpy(buffer, argv[i]);

        if((buscar(buffer, ARGS)) == 0 && (buscar(buffer, IMG)) == 0)
            printf("Argumento/imagen invalido\n");

        if(buscar(buffer, ARGS) == 1)
        {
            printf("paso por arg\n");
            cantidadArgumentos++;
            strcpy(argumentos[i], argv[i]);
        }
        if(buscar(buffer, IMG) == 2)
        {
            strcpy(nombreArchivo, argv[i]);
            //cargaArchivo(&imagen, nombreArchivo);
            menu(&imagen, argumentos, cantidadArgumentos, nombreArchivo);
            cantidadArgumentos = 0;
            printf("Paso por img\n");
        }

        i++;
    }

    return TODO_OK;
}


/*######## Menu ########*/

void menu(t_imagen* imagen, char args[][TAM], int cantidad, char nombre[])
{
    int i=0;
    char funciones[12][TAM] = { {"--dump"}, {"--negativo"}, {"--escala-de-grises"}, {"--aumentar-contraste"}, {"--reducir-contraste"}, {"--tonalidad-azul"}, {"--tonalidad-verde"}, {"--tonalidad-roja"}, {"--recortar"}, {"--rotar-izquierda"}, {"--rotar-derecha"}, {"--comodin"} };
    while(!args)
    {
        for(int i=0; i<12; i++)
            if(strcmp(args[i], funciones[i]) != 0)
                printf("Error");
        if(strcmp(args[i], funciones[i]) == 0)
            dump(imagen, nombre);
        if(strcmp(args[i], funciones[i]) == 0)
            escalaGrises(funciones, 3, nombre);

        args++;
        i++;
    }

}

/*######## Argumentos ########*/


void escalaGrises(char arg[][TAM], int posicion, char arch[])
{
    int i = 0, cont = 0;

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

    printf("Creando Archivo \"%s\"\n", arg);

    metadataOriginal = copyData(archivo);

    fwrite(&metadataOriginal, sizeof(t_metadata), 1, archivoNuevo);
    while(!feof(archivo))
        fwrite(&metadataOriginal, sizeof(t_metadata), 1, archivoNuevo);

    fread(&pixelOriginal, sizeof(t_pixel), 1, archivo);
    while(!feof(archivo))
    {
        printf("Paso");
        cont++;
        fread(&pixelOriginal, sizeof(t_pixel), 1,archivo);
    }
    printf("%d\n", cont);
    while(!feof(archivo))
    {
        printf("Paso");
        nuevoPixel.pixel[0] = (pixelOriginal.pixel[0] + pixelOriginal.pixel[1] + pixelOriginal.pixel[2])/3;
        nuevoPixel.pixel[1] = (pixelOriginal.pixel[0] + pixelOriginal.pixel[1] + pixelOriginal.pixel[2])/3;
        nuevoPixel.pixel[2] = (pixelOriginal.pixel[0] + pixelOriginal.pixel[1] + pixelOriginal.pixel[2])/3;
        nuevoPixel.profundidad = pixelOriginal.profundidad;
        fwrite(&nuevoPixel, sizeof(nuevoPixel), 1, archivoNuevo);
        fread(&pixelOriginal, sizeof(pixelOriginal), 1, archivo);
    }

    printf("Archivo creado \"%s\"con exito", grises);
    fclose(archivo);
    fclose(archivoNuevo);

}

/*######## Funcionalidades ########*/

//void dump(t_imagen* imagen, char nombre[])
{
    //FILE file;
    //file = fopen( nombre ,"rb");
    printf("Paso por dump");
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

void cargaArchivo(t_imagen* imagen, char *nombreArchivo)
{
    FILE *file = fopen(nombreArchivo, "rb");
    if(file == NULL)
    {
        exit(1);
    }

    while(!feof(file))
        fwrite(&imagen, sizeof(t_imagen), 1, file);

    fclose(file);

}

t_metadata copyData(FILE* archivo)
{
    t_metadata metadata;
    fread(&metadata, sizeof(t_metadata), 1, archivo);
    while(!feof(archivo))
        fread(&metadata, sizeof(t_metadata), 1, archivo);
    return metadata;
}
