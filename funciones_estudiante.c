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
#include<stdlib.h>
#include "funciones_estudiante.h"
#include "constantes.h"

int solucion(int argc, char* argv[])
{
    int contador = 1, cantidadArgumentos[12], status = 0 /*bk*/;
    char nombreImagen[LEGHT];

    while(contador<argc){
        puts(argv[contador]);

        if(!buscar(argv[contador]) && !buscar(argv[contador]))
            puts("\tArgumento/Imagen incorrecto");

        if(buscar(argv[contador]) == 1){
            cantidadArgumentos[status] = identificar(argv[contador]);
            if(cantidadArgumentos[status] != -1){
                status++;
                puts("\tARG");
            }else{
                puts("Arg incorrecto\n");
            }
        }

        if(buscar(argv[contador]) == 11){
            if(status != 0){
                puts("\tIMG");
                strcpy(nombreImagen, argv[contador]);
                menu( nombreImagen, cantidadArgumentos, status );
                //printf("Status: %d\n", status);
                //mostrar(cantidadArgumentos, status);
                reset(cantidadArgumentos, status);
                //bk = status;
                status = 0;
                //printf("Status: %d\n", status);
                //mostrar(cantidadArgumentos, bk);
            }
        }

        contador++;
    }
    return TODO_OK;
}

/*+++++++++++++++++Argumentos+++++++++++++++++*/

void menu(const char *nombre, const int *argumento, const int status){
    FILE *imgOriginal, *imgNueva;
    const char *funciones[] = { "help",                 //0
                                "dump",                 //1
                                "negativo",             //2
                                "escala-de-grises",     //3
                                "aumentar-contraste",   //4
                                "reducir-contraste",    //5
                                "tonalidad-azul",       //6
                                "tonalidad-verde",      //7
                                "tonalidad-roja",       //8
                                "recortar",             //9
                                "rotar-izquierda",      //10
                                "rotar-derecha",        //11
                                "concatenar",           //12
                                "achicar",              //13
                                "monocromo",            //14
                                "comodin"               //15
                              };

    for(int pos = 0; pos<status; pos++){
            printf("\nArg %d :: ", argumento[pos]);
        switch(argumento[pos]){
            case 0:
                help();
                break;
            case 1:
                dump(nombre);
                break;
            case 2:
                negativo(nombre, funciones[2], &imgOriginal, &imgNueva);
                break;
            case 3:
                escalaDeGrises(nombre, funciones[3], &imgOriginal, &imgNueva);
                break;
            case 4:
                aumentarContraste(nombre, funciones[4], &imgOriginal, &imgNueva);
                break;
            case 5:
                reducirContraste(nombre, funciones[5], &imgOriginal, &imgNueva);
                break;
            case 6:
                azul(nombre, funciones[6], &imgOriginal, &imgNueva);
                break;
            case 7:
                verde(nombre, funciones[7], &imgOriginal, &imgNueva);
                break;
            case 8:
                rojo(nombre, funciones[8], &imgOriginal, &imgNueva);
                break;
            case 9:
                recortar(nombre, funciones[9], &imgOriginal, &imgNueva);
                break;
            case 10:
                rotarIzquierda(nombre, funciones[10], &imgOriginal, &imgNueva);
                break;
            case 11:
                rotarDerecha(nombre, funciones[11], &imgOriginal, &imgNueva);
                break;
            /*case 12:
                concatenar();
                break;
            case 13:
                achicar();
                break;
            case 14:
                monocromo();
                break;
            case 15:
                comodin();
                break;
*/
        }
    }
}
/*+++++++++++++++++*/     /*+++++++++++++++++*/

void help() {puts("help :: troliado");}

void dump(const char *nombre){
    unsigned char buffer[16];
    int cont = 0;

    FILE *archivo = fopen(nombre, "rb");
    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }

    fread(&buffer, sizeof(unsigned char), 16, archivo);
    while(!feof(archivo))
    {
        printf("%04x ", cont);
        for(int pos = 0; pos < sizeof(buffer); pos++)
            printf("%02x ", buffer[pos]);
        printf(" | ");
        for(int pos = 0; pos < sizeof(buffer); pos++)
            printf("%c", buffer[pos]);
        cont+=sizeof(buffer);
        printf("\n");

        fread(&buffer, sizeof(unsigned char), 16, archivo);
    }
    fclose(archivo);

}

void negativo(const char *nombre, const char *arg, FILE**imgO, FILE**imgN){
    char nombreArchivo[LEGHT] = {"Estudiantes_"};
    unsigned int data = 0;
    t_pixel vPixel;

    *imgO = fopen(nombre, "rb");
    strcat(nombreArchivo, arg);
    strcat(nombreArchivo, ".bmp");
    *imgN = fopen(nombreArchivo, "wb");

    printf("Negativo\n");
    if(*imgO == NULL || *imgN == NULL)
        exit(1);
    puts("Creando Imagen");

    posicionData(imgO, &data);
    copiarData(imgO,imgN, &data);
    fseek(*imgO, data, SEEK_SET);

    fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    while(!feof(*imgO)){
        calcularNegativo(&vPixel);
        fwrite(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgN);
        fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    }

    fclose(*imgO);
    fclose(*imgN);
    printf("Archivo %s creado exitosamente", nombreArchivo);
}
/*+++++++++++++++++++++++++++++++++++++++++++*/

void calcularNegativo(t_pixel *p){
    p->pixel[0] = MAXIMO(~p->pixel[0], 255);
    p->pixel[1] = MAXIMO(~p->pixel[1], 255);
    p->pixel[2] = MAXIMO(~p->pixel[2], 255);
}
/*+++++++++++++++++++++++++++++++++++++++++++*/
void escalaDeGrises(const char *nombre, const char *arg, FILE**imgO, FILE**imgN){
    char nombreArchivo[LEGHT] = {"Estudiantes_"};
    unsigned int data = 0;
    t_pixel vPixel;

    *imgO = fopen(nombre, "rb");
    strcat(nombreArchivo, arg);
    strcat(nombreArchivo, ".bmp");
    *imgN = fopen(nombreArchivo, "wb");

    printf("Escala de grises\n");
    if(*imgO == NULL || *imgN == NULL)
        exit(1);
    puts("Creando Imagen");

    posicionData(imgO, &data);
    copiarData(imgO,imgN, &data);
    fseek(*imgO, data, SEEK_SET);

    fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    while(!feof(*imgO)){
        calcularEscalaDeGrises(&vPixel);
        fwrite(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgN);
        fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    }

    fclose(*imgO);
    fclose(*imgN);
    printf("Archivo %s creado exitosamente", nombreArchivo);
}
/*+++++++++++++++++++++++++++++++++++++++++++*/

void calcularEscalaDeGrises(t_pixel *p){
    int promedio = (p->pixel[0] + p->pixel[1] + p->pixel[2])/3;
    if(promedio <= 0){
        p->pixel[0] = 0;
        p->pixel[1] = 0;
        p->pixel[2] = 0;
    }else if(promedio >= 255){
        p->pixel[0] = 255;
        p->pixel[1] = 255;
        p->pixel[2] = 255;
    }else{
        p->pixel[0] = promedio;
        p->pixel[1] = promedio;
        p->pixel[2] = promedio;
    }
}
/*+++++++++++++++++++++++++++++++++++++++++++*/
void aumentarContraste(const char *nombre, const char *arg, FILE**imgO, FILE**imgN){
    char nombreArchivo[LEGHT] = {"Estudiantes_"};
    unsigned int data = 0;
    t_pixel vPixel;

    *imgO = fopen(nombre, "rb");
    strcat(nombreArchivo, arg);
    strcat(nombreArchivo, ".bmp");
    *imgN = fopen(nombreArchivo, "wb");

    printf("Aumentar contraste\n");
    if(*imgO == NULL || *imgN == NULL)
        exit(1);
    puts("Creando Imagen");

    posicionData(imgO, &data);
    copiarData(imgO,imgN, &data);
    fseek(*imgO, data, SEEK_SET);

    fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    while(!feof(*imgO)){
        calcularContraste(&vPixel, 'a');
        fwrite(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgN);
        fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    }

    fclose(*imgO);
    fclose(*imgN);
    printf("Archivo %s creado exitosamente", nombreArchivo);
}
void reducirContraste(const char *nombre, const char *arg, FILE **imgO, FILE **imgN){
    char nombreArchivo[LEGHT] = {"Estudiantes_"};
    unsigned int data = 0;
    t_pixel vPixel;

    *imgO = fopen(nombre, "rb");
    strcat(nombreArchivo, arg);
    strcat(nombreArchivo, ".bmp");
    *imgN = fopen(nombreArchivo, "wb");

    printf("Reducir Contraste\n");
    if(*imgO == NULL || *imgN == NULL)
        exit(1);
    puts("Creando Imagen");

    posicionData(imgO, &data);
    copiarData(imgO,imgN, &data);
    fseek(*imgO, data, SEEK_SET);

    fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    while(!feof(*imgO)){
        calcularContraste(&vPixel, 'r');
        fwrite(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgN);
        fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    }

    fclose(*imgO);
    fclose(*imgN);
    printf("Archivo %s creado exitosamente", nombreArchivo);
}
/*+++++++++++++++++++++++++++++++++++++++++++*/

void calcularContraste(t_pixel *p, const char type){
    int promedio = (p->pixel[0] + p->pixel[1] + p->pixel[2])/3;
    if(type == 'a'){
        if(promedio >= 127){
            p->pixel[0] = MAXIMO((p->pixel[0] * 1.25), 255);
            p->pixel[1] = MAXIMO((p->pixel[1] * 1.25), 255);
            p->pixel[2] = MAXIMO((p->pixel[2] * 1.25), 255);
        }else{
            p->pixel[0] = MINIMO((p->pixel[0]*0.75), 0);
            p->pixel[1] = MINIMO((p->pixel[1]*0.75), 0);
            p->pixel[2] = MINIMO((p->pixel[2]*0.75), 0);
        }
    }else if (type == 'r'){
        if(promedio >= 127){
                p->pixel[0] = MINIMO((p->pixel[0] * 0.75), 0);
                p->pixel[1] = MINIMO((p->pixel[1] * 0.75), 0);
                p->pixel[2] = MINIMO((p->pixel[2] * 0.75), 0);
            }else{
                p->pixel[0] = MAXIMO((p->pixel[0]*1.25), 255);
                p->pixel[1] = MAXIMO((p->pixel[1]*1.25), 255);
                p->pixel[2] = MAXIMO((p->pixel[2]*1.25), 255);
            }
    }
}
/*+++++++++++++++++++++++++++++++++++++++++++*/

void azul(const char *nombre, const char *arg, FILE **imgO, FILE **imgN){
    char nombreArchivo[LEGHT] = {"Estudiantes_"};
    unsigned int data = 0;
    t_pixel vPixel;

    *imgO = fopen(nombre, "rb");
    strcat(nombreArchivo, arg);
    strcat(nombreArchivo, ".bmp");
    *imgN = fopen(nombreArchivo, "wb");

    printf("Tonalidad Azul\n");
    if(*imgO == NULL || *imgN == NULL)
        exit(1);
    puts("Creando Imagen");

    posicionData(imgO, &data);
    copiarData(imgO,imgN, &data);
    fseek(*imgO, data, SEEK_SET);

    fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    while(!feof(*imgO)){
        calcularColores(&vPixel, 'a');
        fwrite(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgN);
        fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    }

    fclose(*imgO);
    fclose(*imgN);
    printf("Archivo %s creado exitosamente", nombreArchivo);
}
void verde(const char *nombre, const char *arg, FILE **imgO, FILE **imgN){
    char nombreArchivo[LEGHT] = {"Estudiantes_"};
    unsigned int data = 0;
    t_pixel vPixel;

    *imgO = fopen(nombre, "rb");
    strcat(nombreArchivo, arg);
    strcat(nombreArchivo, ".bmp");
    *imgN = fopen(nombreArchivo, "wb");

    printf("Tonalidad Verde\n");
    if(*imgO == NULL || *imgN == NULL)
        exit(1);
    puts("Creando Imagen");

    posicionData(imgO, &data);
    copiarData(imgO,imgN, &data);
    fseek(*imgO, data, SEEK_SET);

    fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    while(!feof(*imgO)){
        calcularColores(&vPixel, 'v');
        fwrite(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgN);
        fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    }

    fclose(*imgO);
    fclose(*imgN);
    printf("Archivo %s creado exitosamente", nombreArchivo);
}
void rojo(const char *nombre, const char *arg, FILE **imgO, FILE **imgN){
char nombreArchivo[LEGHT] = {"Estudiantes_"};
    unsigned int data = 0;
    t_pixel vPixel;

    *imgO = fopen(nombre, "rb");
    strcat(nombreArchivo, arg);
    strcat(nombreArchivo, ".bmp");
    *imgN = fopen(nombreArchivo, "wb");

    printf("Tonalidad Rojo\n");
    if(*imgO == NULL || *imgN == NULL)
        exit(1);
    puts("Creando Imagen");

    posicionData(imgO, &data);
    copiarData(imgO,imgN, &data);
    fseek(*imgO, data, SEEK_SET);

    fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    while(!feof(*imgO)){
        calcularColores(&vPixel, 'r');
        fwrite(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgN);
        fread(&vPixel.pixel, sizeof(vPixel.pixel), 1, *imgO);
    }

    fclose(*imgO);
    fclose(*imgN);
    printf("Archivo %s creado exitosamente", nombreArchivo);
}

/*+++++++++++++++++++++++++++++++++++++++++++*/

void calcularColores(t_pixel *p, const char type){
    if(type == 'a') p->pixel[0] = MAXIMO(p->pixel[0]*1.5, 255);
    if(type == 'v') p->pixel[1] = MAXIMO(p->pixel[0]*1.5, 255);
    if(type == 'r') p->pixel[2] = MAXIMO(p->pixel[0]*1.5, 255);
}

/*+++++++++++++++++++++++++++++++++++++++++++*/

void recortar(const char *nombre, const char *arg, FILE **imgO, FILE **imgN){
    char nombreArchivo[LEGHT] = {"Estudiantes_"};
    t_pixel pixel;
    t_metadata data;


    *imgO = fopen(nombre, "rb");
    strcat(nombreArchivo, arg);
    strcat(nombreArchivo, ".bmp");
    *imgN = fopen(nombreArchivo, "wb");

    printf("recortar\n");
    if(*imgO == NULL || *imgN == NULL) exit(1);
    puts("Creando Imagen");

    posicionData(imgO, &data.comienzoImagen);
    copiarData(imgO, imgN, &data.comienzoImagen);
    dimesiones(imgO,&data);
    actualizarDimensiones(imgN, &data);

    fseek(*imgO, data.comienzoImagen, SEEK_SET);
    imagenRecortada(imgO, imgN, &data, &pixel);

    fclose(*imgO);
    fclose(*imgN);
    printf("Archivo %s creado exitosamente", nombreArchivo);
}

/*+++++++++++++++++++++++++++++++++++++++++++*/

void rotarDerecha(const char *nombre, const char *arg, FILE **imgO, FILE **imgN){
    char nombreArchivo[LEGHT] = {"Estudiantes_"};
    t_pixel pixel;
    t_metadata data;

    *imgO = fopen(nombre, "rb");
    strcat(nombreArchivo, arg);
    strcat(nombreArchivo, ".bmp");
    *imgN = fopen(nombreArchivo, "wb");

    printf("Rotar a derecha\n");
    if(*imgO == NULL || *imgN == NULL) exit(1);
    puts("Creando Imagen");

    posicionData(imgO, &data.comienzoImagen);
    copiarData(imgO, imgN, &data.comienzoImagen);
    dimesiones(imgO,&data);
    rotarDimensiones(imgN, &data);

    calcularGiro(imgO, imgN, &data, &pixel, DERECHA);

    fclose(*imgO);
    fclose(*imgN);
    printf("Archivo %s creado exitosamente", nombreArchivo);
}
void rotarIzquierda(const char *nombre, const char *arg, FILE **imgO, FILE **imgN){
    char nombreArchivo[LEGHT] = {"Estudiantes_"};
    t_pixel pixel;
    t_metadata data;

    *imgO = fopen(nombre, "rb");
    strcat(nombreArchivo, arg);
    strcat(nombreArchivo, ".bmp");
    *imgN = fopen(nombreArchivo, "wb");

    printf("Rotar a izquierda\n");
    if(*imgO == NULL || *imgN == NULL) exit(1);
    puts("Creando Imagen");

    posicionData(imgO, &data.comienzoImagen);
    copiarData(imgO, imgN, &data.comienzoImagen);
    dimesiones(imgO,&data);
    rotarDimensiones(imgN, &data);


    calcularGiro(imgO, imgN, &data, &pixel, IZQUIERDA);

    fclose(*imgO);
    fclose(*imgN);
    printf("Archivo %s creado exitosamente", nombreArchivo);
}

/*+++++++++++++++++++++++++++++++++++++++++++*/

void dimesiones(FILE**img, t_metadata*data){

    fseek(*img, B_TAM, SEEK_SET);
    fread(&data->tamArchivo, sizeof(data->tamArchivo), 1, *img);
    fseek(*img, B_ANCHO, SEEK_SET);
    fread(&data->ancho, sizeof(data->ancho), 1, *img);
    fread(&data->alto, sizeof(data->alto), 1, *img);

}
void rotarDimensiones(FILE**img, t_metadata*data){
    unsigned int *nAlto = NULL, *nAncho=NULL;
    int bk = ftell(*img);

    nAlto = (unsigned int *)malloc(sizeof(unsigned int));
    nAncho = (unsigned int *)malloc(sizeof(unsigned int));

    printf("%d | %d\n", data->ancho, data->alto);
    *nAncho = data->alto;
    *nAlto = data->ancho;
    data->ancho = *nAncho;
    data->alto = *nAlto;

    printf("%d | %d\n", data->ancho, data->alto);
    //exit(1);
    fseek(*img, B_ANCHO, SEEK_SET);
    fwrite(&data->ancho, sizeof(data->ancho), 1, *img);
    fwrite(&data->alto, sizeof(data->alto), 1, *img);
    fseek(*img, bk, SEEK_SET);

    free(nAncho);
    free(nAlto);
}
void actualizarDimensiones(FILE**img, t_metadata*data){
    int bk = ftell(*img);

    data->tamArchivo /= 2;
    data->alto /= 2;
    data->ancho /= 2;

    fseek(*img, B_ANCHO, SEEK_SET);
    fwrite(&data->ancho, sizeof(data->ancho), 1, *img);
    fwrite(&data->alto, sizeof(data->alto), 1, *img);
    fseek(*img, B_TAM, SEEK_SET);
    fwrite(&data->tamArchivo, sizeof(data->tamArchivo), 1, *img);
    fseek(*img, bk, SEEK_SET);

}
void imagenRecortada(FILE **imgO, FILE **imgN, t_metadata *data, t_pixel *pixel){

    for(int c = 0; c < data->ancho; c++){
        for(int f = 0; f < data->alto; f++){
            fread(&pixel->pixel, sizeof(pixel->pixel), 1, *imgO);
            fwrite(&pixel->pixel, sizeof(pixel->pixel), 1, *imgN);
        }
        fseek(*imgO, (data->ancho)+T_PIXEL, SEEK_CUR);
    }
}
void calcularGiro(FILE **imgO, FILE **imgN, t_metadata *data, t_pixel *pixel, char type){
    unsigned char **matriz;
    matriz = CrearMatriz(&data->alto, &data->ancho);

    // vvv PROBLEMA A RESOLVER vvv //

    fseek(*imgO, data->comienzoImagen, SEEK_SET);
    if(type == DERECHA){
        puts("paso por algoritmo");

        fread(&pixel->pixel, sizeof(pixel->pixel), 1, *imgO);
        for(int c =  0; c <= data->ancho; c++){
            for(int f  = data->alto; f >= 0; f-=T_PIXEL){
                matriz[f][c] = pixel->pixel[2];
                matriz[f-1][c] = pixel->pixel[1];
                matriz[f-2][c] = pixel->pixel[0];

                fread(&pixel->pixel, sizeof(pixel->pixel), 1, *imgO);
            }
        }
    }
    if(type == IZQUIERDA){
        puts("paso por algoritmo");
        for(int c = 0; c <= data->ancho; c++){
            for(int f = data->alto; f > 0; f -=T_PIXEL){
                fread(&pixel->pixel, sizeof(pixel->pixel), 1, *imgO);

                matriz[f-2][c] = pixel->pixel[2];
                matriz[f-1][c] = pixel->pixel[1];
                matriz[f][c] = pixel->pixel[0];
            }
        }
    }
    puts("paso por aca");
    for(int c = 0; c < data->ancho; c++){
        for(int f = data->alto; f > 0; f-=T_PIXEL){
            pixel->pixel[0] = matriz[f][c];
            pixel->pixel[1] = matriz[f][c+1];
            pixel->pixel[2] = matriz[f][c+2];

            fwrite(&pixel->pixel, sizeof(pixel->pixel), 1, *imgN);
        }
    }

    for(int i = 0; i < data->ancho; i++)
        free(matriz[i]);
    free(matriz);

}
unsigned char ** CrearMatriz(unsigned int *fila, unsigned int *columna){
    puts("paso por creando matriz dinamica");
    unsigned char **m = NULL;
    m = (unsigned char **)malloc(*fila * sizeof(unsigned char *));

    if(m == NULL) free(m);
    for(int i = 0; i < *fila; i++){
        m[i] = (unsigned char *)malloc(*columna * sizeof(unsigned char));
        if(m[i] == NULL) free(m[i]);
    }
    return m;
}
/*+++++++++++++++++++++++++++++++++++++++++++*/

//comodin

/*+++++++++++++++++Funciones+++++++++++++++++*/

int buscar(const char *arg)
{
    char *tipo = {".bmp"};
    int ultimo = ((int)strlen(arg))-1;


    if(*arg == ARGS && *(arg+1) == ARGS)
        return 1;
    if(*((arg+ultimo)-3) == *tipo && *((arg+ultimo)-2) == *(tipo+1) && *((arg+ultimo)-1) == *(tipo+2) && *(arg+ultimo) == *(tipo+3))
        return 11;

    return 0;
}

int buscarFuncion(const char **f, const char *a){
    int contador = 0;

    while(contador < 12){
        if(strcmp(f[contador], a) == 0)
            return contador;
        contador++;
    }
    return -1;
}

int identificar(const char *arg)
{
    int funcion;
    const char *funciones[] = { "--help",                 //0
                                "--dump",                 //1
                                "--negativo",             //2
                                "--escala-de-grises",     //3
                                "--aumentar-contraste",   //4
                                "--reducir-contraste",    //5
                                "--tonalidad-azul",       //6
                                "--tonalidad-verde",      //7
                                "--tonalidad-roja",       //8
                                "--recortar",             //9
                                "--rotar-izquierda",      //10
                                "--rotar-derecha",        //11
                                "--concatenar",           //12
                                "--achicar",              //13
                                "--monocromo",            //14
                                "--comodin"               //15
                              };

    funcion = buscarFuncion(funciones, arg);

    return funcion > -1 ? funcion : -1;
}
/**/

void posicionData(FILE**img, unsigned int *dataPosicion){
    fseek(*img, B_IMG, SEEK_SET);
    if(fread(dataPosicion, sizeof(*dataPosicion), 1, *img) != 1)
        *dataPosicion = -1;

}
void copiarData(FILE **imgO, FILE **imgN, unsigned int *byte){
    unsigned char *buffer = (unsigned char*)malloc(sizeof(*buffer)*(*byte));

    if(buffer == NULL){
        free(buffer);
        exit(1);
    }

    fseek(*imgO, 0, SEEK_SET);
    fseek(*imgN, 0, SEEK_SET);

    fread(buffer, sizeof(*buffer), *byte, *imgO);
    fwrite(buffer, sizeof(*buffer), *byte, *imgN);

    free(buffer);
}

/**/
void reset(int *arg, int cantidad)
{
    int i = 0;
    while(i<cantidad){
        *arg = 0;
        arg++;
        i++;
    }
}

void mostrar(const int *arg, int cantidad)
{
    int i = 0;
    while(i < cantidad){
        printf("%d\n", *arg);

        arg++;
        i++;
    }
}
