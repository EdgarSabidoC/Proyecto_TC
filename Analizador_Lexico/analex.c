// Programa principal del analizador léxico.

#include "lexer.c"

/* Función principal */
int main(int argc, char **argv)
{   
    // Si el programa no tiene la cantidad de argumentos correctos:
    if (argc <= 1 || argc > 2)
    // Falló al correr el programa:
        return 1;

    // Se verifica que el archivo sea extensión .mio:
    char *punto = strchr(argv[1], '.');
    char *mio = ".mio";

    // Se verifica que la extensión sea .mio
    if(strncmp(punto, mio, sizeof(".mio")))
    {
        printf("ERROR, no se encontró archivo .mio\n\n");
        return 1;
    }

    // Puntero al nombre del programa:
    char *nombre_programa = argv[1];
        
    printf("%s\n", nombre_programa);



    // Archivo .lex:
        
    // Nombre del archivo .lex:
    char nombre_lex[strlen(argv[1])+1];
    strncpy(nombre_lex, argv[1], strlen(argv[1])-3);
    strcat(nombre_lex, "lex");

    // Se crea el archivo .lex:
    FILE *lexer = fopen(nombre_lex, "w+");
        


    // Archivo .sim:
        
    // Nombre del archivo .sim:
    char nombre_sim[strlen(argv[1])+1];
    strncpy(nombre_sim, argv[1], strlen(argv[1])-3);
    strcat(nombre_sim, "sim");

    // Se crea el archivo .sim:
    FILE *sim = fopen(nombre_sim, "w+");



    // Se inicializan las listas para almacenar la tabla de símbolos.
    listaVarNum lista_var;
    listaText lista_txt;
    listaVal lista_val;

    iniListaVarNum(&lista_var);
    iniListaTxt(&lista_txt);
    iniListaVal(&lista_val);



    // Se cuenta la cantidad de líneas del archivo .mio:
    FILE *archivo = fopen(argv[1], "r");
    unsigned int lineas;
    lineas = __contarLineasArchivo(archivo);
    fclose(archivo); // Se cierra el archivo



    // Cantidad de caracteres máximos de cada archivo:
    unsigned int caracteres = 10000;

    // Arreglo que almacenará cada línea del archivo:
    char array[lineas][caracteres];



    // Puntero al archivo:
    FILE *parchivo = fopen(argv[1], "r");
    
    // Se guarda cada línea del archivo:
    __guardarLineas(parchivo, lineas, caracteres, array);
    fclose(parchivo); // Se cierra el archivo


    // Se generan los tokens:
    analizador(lexer, lineas, caracteres, array, &lista_var, &lista_txt, &lista_val);



    // Se imprimen las listas en el archivo .sim:
    imprimeSim(sim, &lista_var, &lista_txt, &lista_val);



    // Se libera la memoria ocupada por las listas:
    liberaListaVarNum(&lista_var);
    liberaListaTxt(&lista_txt);
    liberaListaVal(&lista_val);



    // Se cierra el archivo .lex y el archivo .sim:
    fclose(lexer);
    fclose(sim);

    // Programa exitoso:
    return 0;
}