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
        printf("\n%s: ", argv[i]);
        strcpy(buffer, argv[i]);

        if((buscar(buffer, ARGS)) == 0 && (buscar(buffer, IMG)) == 0)
            printf("Argumento/imagen invalido\n");

        if(buscar(buffer, ARGS) == 1)
        {
            cantidadArgumentos++;
            strcpy(argumentos[cantidadArgumentos], argv[i]);
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
    char funciones[12][TAM] = { {"--dump"},                 //0
                                {"--negativo"},             //1
                                {"--escala-de-grises"},     //2
                                {"--aumentar-contraste"},   //3
                                {"--reducir-contraste"},    //4
                                {"--tonalidad-azul"},       //5
                                {"--tonalidad-verde"},      //6
                                {"--tonalidad-roja"},       //7
                                {"--recortar"},             //8
                                {"--rotar-izquierda"},      //9
                                {"--rotar-derecha"},        //10
                                {"--comodin"} };            //11
    while(i<cantidad)
    {
        if(strcmp(args[i], funciones[i]) == 0)
            dump(nombre);
        if(strcmp(args[i], funciones[i]) == 0)
            escalaGrises(funciones, 2, nombre);
        if(strcmp(args[i], funciones[i]) == 0)
        aumentarContraste(funciones, 3, nombre);
        if(strcmp(args[i], funciones[i]) == 0)
            reducirContraste(funciones, 4, nombre);
        if(strcmp(args[i], funciones[i]) == 0)
            //tonalidadAzul();
        if(strcmp(args[i], funciones[i]) == 0)
            //tonalidadVerde();
        if(strcmp(args[i], funciones[i]) == 0)
            //tonalidadRoja();
        if(strcmp(args[i], funciones[i]) == 0)
            //recortar();
        if(strcmp(args[i], funciones[i]) == 0)
            //rotarIzquierda();
        if(strcmp(args[i], funciones[i]) == 0)
            //rotarDerecha();
        if(strcmp(args[i], funciones[i]) == 0)
            //comodin();
        i++;
    }
}

/*######## Argumentos ########*/

void escalaGrises(char arg[][TAM], int posicion, char nombre[])
{
    char nArchivo[] = {0};
    t_pixel pixelOriginal[WIDTH][HEIGHT], temp[WIDTH][HEIGHT], pixelNuevo[WIDTH][HEIGHT];


    FILE*archivo = fopen(nombre, "rb");
    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }

    strcpy(nArchivo, arg[posicion]);
    strcat(nArchivo,"-");
    strcat(nArchivo, nombre);

    FILE*archivoNuevo = fopen(nArchivo, "wb");
    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }

    printf("Creando Archivo \"%s\"\n", arg[posicion]);

    //Lecturas y Escrituras
    copyData(archivo, archivoNuevo);

    for(int f = 0; f < WIDTH; f++)
    {
        for(int c = 0; c < HEIGHT; c++)
        {
            fread(&pixelOriginal[f][c], sizeof(t_pixel), 1, archivo);
            temp[f][c] = pixelOriginal[f][c];
        }
    }

    for(int f = 0; f < WIDTH; f++)
    {
        for(int c = 0; c < HEIGHT; c++)
        {
            pixelNuevo[f][c].pixel[0] = (temp[f][c].pixel[0] + temp[f][c].pixel[1] + temp[f][c].pixel[2])/3;
            pixelNuevo[f][c].pixel[1] = (temp[f][c].pixel[0] + temp[f][c].pixel[1] + temp[f][c].pixel[2])/3;
            pixelNuevo[f][c].pixel[2] = (temp[f][c].pixel[0] + temp[f][c].pixel[1] + temp[f][c].pixel[2])/3;
            pixelNuevo[f][c].profundidad = temp[f][c].profundidad;
            fwrite(&pixelNuevo[f][c], sizeof(t_pixel), 1, archivoNuevo);
        }
    }

    printf("Archivo \"%s\" creado con exito", nArchivo);
    fclose(archivo);
    fclose(archivoNuevo);
}

void aumentarContraste(char arg[][TAM], int posicion, char nombre[])
{
    int promedio;
    char nArchivo[] = {0};
    t_pixel pixelOriginal[WIDTH][HEIGHT], temp[WIDTH][HEIGHT], pixel[WIDTH][HEIGHT];

    FILE*archivoOriginal = fopen(nombre, "rb");
    if(archivoOriginal == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }

    strcpy(nArchivo, arg[posicion]);
    strcat(nArchivo,"-");
    strcat(nArchivo, nombre);

    FILE*archivo = fopen(nArchivo, "wb");
    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }

    printf("Creando Archivo \"%s\"\n", arg[posicion]);

    //Lecturas y Escrituras
    copyData(archivoOriginal, archivo);

    for(int f = 0; f < WIDTH; f++)
    {
        for(int c = 0; c<HEIGHT; c++)
        {
            fread(&pixelOriginal[f][c], sizeof(t_pixel), 1, archivoOriginal);
            temp[f][c] = pixelOriginal[f][c];
        }
    }

    for(int f = 0; f < WIDTH; f++)
    {
        for(int c = 0; c<HEIGHT; c++)
        {
            pixel[f][c].profundidad = temp[f][c].profundidad;
            promedio = promedioPixel(temp[f][c].pixel[0], temp[f][c].pixel[1], temp[f][c].pixel[2]);
            if(promedio >= 127)
            {
                pixel[f][c].pixel[0] = temp[f][c].pixel[0] - (temp[f][c].pixel[0] * 0.25);
                pixel[f][c].pixel[1] = temp[f][c].pixel[1] - (temp[f][c].pixel[1] * 0.25);
                pixel[f][c].pixel[2] = temp[f][c].pixel[2] - (temp[f][c].pixel[2] * 0.25);
            }
            else
            {
                pixel[f][c].pixel[0] = temp[f][c].pixel[0] + (temp[f][c].pixel[0] * 0.25);
                pixel[f][c].pixel[1] = temp[f][c].pixel[1] + (temp[f][c].pixel[1] * 0.25);
                pixel[f][c].pixel[2] = temp[f][c].pixel[2] + (temp[f][c].pixel[2] * 0.25);
            }
            fwrite(&pixel[f][c], sizeof(t_pixel), 1, archivo);
        }
    }

    printf("Archivo \"%s\" creado con exito", nArchivo);
    fclose(archivoOriginal);
    fclose(archivo);
}

void reducirContraste(char arg[][TAM], int posicion, char nombre[])
{
    int promedio;
    char nArchivo[] = {0};
    t_pixel pixelOriginal[WIDTH][HEIGHT], temp[WIDTH][HEIGHT], pixel[WIDTH][HEIGHT];

    FILE*archivoOriginal = fopen(nombre, "rb");
    if(archivoOriginal == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }

    strcpy(nArchivo, arg[posicion]);
    strcat(nArchivo,"-");
    strcat(nArchivo, nombre);

    FILE*archivo = fopen(nArchivo, "wb");
    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }

    printf("Creando Archivo \"%s\"\n", arg[posicion]);

    //Lecturas y Escrituras
    copyData(archivoOriginal, archivo);

    for(int f = 0; f < WIDTH; f++)
    {
        for(int c = 0; c<HEIGHT; c++)
        {
            fread(&pixelOriginal[f][c], sizeof(t_pixel), 1, archivoOriginal);
            temp[f][c] = pixelOriginal[f][c];
        }
    }

    for(int f = 0; f < WIDTH; f++)
    {
        for(int c = 0; c<HEIGHT; c++)
        {
            pixel[f][c].profundidad = temp[f][c].profundidad;
            promedio = promedioPixel(temp[f][c].pixel[0], temp[f][c].pixel[1], temp[f][c].pixel[2]);
            if(promedio >= 127)
            {
                pixel[f][c].pixel[0] = temp[f][c].pixel[0] + (temp[f][c].pixel[0] * 0.25);
                pixel[f][c].pixel[1] = temp[f][c].pixel[1] + (temp[f][c].pixel[1] * 0.25);
                pixel[f][c].pixel[2] = temp[f][c].pixel[2] + (temp[f][c].pixel[2] * 0.25);
            }
            else
            {
                pixel[f][c].pixel[0] = temp[f][c].pixel[0] - (temp[f][c].pixel[0] * 0.25);
                pixel[f][c].pixel[1] = temp[f][c].pixel[1] - (temp[f][c].pixel[1] * 0.25);
                pixel[f][c].pixel[2] = temp[f][c].pixel[2] - (temp[f][c].pixel[2] * 0.25);
            }
            fwrite(&pixel[f][c], sizeof(t_pixel), 1, archivo);
        }
    }

    printf("Archivo \"%s\" creado con exito", nArchivo);
    fclose(archivoOriginal);
    fclose(archivo);
}
/*######## Funcionalidades ########*/

void dump(char nombre[])
{
    unsigned char buffer[16];
    int cont = 0;

    FILE *archivo;
    archivo = fopen(nombre, "rb");
    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }

    fread(&buffer, sizeof(unsigned char), 16, archivo);
    while(!feof(archivo))
    {
        printf("%04x ", cont);
        for(int i = 0; i < sizeof(buffer); i++)
            printf("%02x ", buffer[i]);
        printf(" | ");
        for(int i = 0; i < sizeof(buffer); i++)
            printf("%c", buffer[i]);
        cont+=sizeof(buffer);
        printf("\n");

        fread(&buffer, sizeof(unsigned char), 16, archivo);
    }
    fclose(archivo);
}


int buscar(char arg[], char comando)
{
    int i = 0, max = strlen(arg);

    if(arg[i] == comando && arg[i+1] == comando)
    {
        return 1;
    }
    if(arg[max-4] == comando && arg[max-3] == 'b' && arg[max-2] == 'm' && arg[max-1] == 'p')
    {
        return 2;
    }
    return 0;
}

void copyData(FILE*archivoOriginal, FILE*archivoNuevo)
{
    unsigned char data[54];
    fread(data, 54, 1, archivoOriginal);
    if(fread(data, 54, 1, archivoOriginal) != 1)
    {
        printf("Error al leer el archivo\n");
        exit(1);
    }
    fwrite(data, 54, 1, archivoNuevo);
}

int promedioPixel(unsigned char valor1, unsigned char valor2,unsigned char valor3)
{
    return (valor1+valor2+valor3)/3;
}
