// Programa principal del analizador léxico.

// Biblioteca con las funciones del analizador léxico:
#include "lexer.h" 

/*
 * DESCRIPCIÓN: 
 * Función principal que controla al analizador.
 * Aquí se realizan los llamados a las funciones
 * del analizador léxico y se inicializan
 * las listas donde se guardarán los tokens.
 * 
 * ENTRADA: Cadena (string) con el nombre del archivo .lex
 * 
 * SALIDA: Resultado de la compilación:
 *          EXIT_SUCCESS - Compilación exitosa.
 *          EXIT_FAILURE - Fallo en la compilación.
 * 
 */
int main(int argc, char **argv)
{   
    // Si el programa no tiene la cantidad de argumentos correctos:
    if (argc <= 1 || argc > 2)
    // Falló al correr el programa:
        return EXIT_FAILURE;

    // Puntero al nombre del programa:
    char *nombre_programa = argv[1];

    // Se verifica que el archivo sea extensión .mio:
    char *punto = strchr(argv[1], '.');
    //char *mio = ".mio";

    // Se verifica si la extensión es .mio
    if(strncmp(punto, ".mio", strlen("mio")) != 0)
    {
        printf("\n\nERROR, no se encontró archivo con extensión .mio\n\n");
        printf("\n\nEl analizador léxico ha finalizado inesperadamente.\n\n\n");
        return EXIT_FAILURE;
    }
        
    printf("\n\nNombre del programa: %s\n\n", nombre_programa);


    // Se verifica que exista el archivo:
    FILE *prueba_archivo = fopen(argv[1], "r");
    
    if(!prueba_archivo)
    {
        printf("ERROR! El archivo [%s] no existe.\n", argv[1]);
        printf("\n\nEl analizador léxico ha finalizado inesperadamente.\n\n\n");
        prueba_archivo = NULL;
        
        return EXIT_FAILURE;
    }

    fclose(prueba_archivo); // Se libera la memoria.
    prueba_archivo = NULL;


    // Archivo .lex:
        
    // Nombre del archivo .lex:
    int tam = strlen(argv[1]);
    char *nombre_lex = malloc(strlen(argv[1])+1 * sizeof(char));
    memcpy(nombre_lex, argv[1], tam-4); // Se copia el nombre sin la extensión.
    strncat(nombre_lex, ".lex", tam-4); // Se concatena la nueva extensión.

    // Se crea el archivo .lex:
    FILE *lexer = fopen(nombre_lex, "w+");
        
    printf("Se generó el archivo [%s] correctamente.\n", nombre_lex);

    // Archivo .sim:
        
    // Nombre del archivo .sim:
    char *nombre_sim = malloc(strlen(argv[1])+1 * sizeof(char));
    memcpy(nombre_sim, argv[1], tam-4); // Se copia el nombre sin la extensión.
    strncat(nombre_sim, ".sim", tam-4); // Se concatena la nueva extensión.

    // Se crea el archivo .sim:
    FILE *sim = fopen(nombre_sim, "w+");
    

    printf("Se generó el archivo [%s] correctamente.\n\n", nombre_sim);


    // Se inicializan las listas para almacenar la tabla de símbolos.
    listaVarNum lista_var;
    listaText lista_txt;
    listaVal lista_val;

    iniListaVarNum(&lista_var);
    iniListaTxt(&lista_txt);
    iniListaVal(&lista_val);



    // Se cuenta la cantidad de líneas del archivo .mio:
    FILE *archivo = fopen(argv[1], "r");

    // Se valida que el archivo exista:
    if(!archivo)
    {
        printf("ERROR! El archivo [%s] no existe.\n", argv[1]);
        printf("\n\nEl analizador léxico ha finalizado inesperadamente.\n\n\n");
        archivo = NULL;
        
        return EXIT_FAILURE;
    }

    unsigned int lineas;
    lineas = __contarLineasArchivo(archivo);
    fclose(archivo); // Se cierra el archivo
    archivo = NULL;


    // Cantidad de caracteres máximos de cada archivo:
    unsigned int caracteres = 10000;

    // Arreglo que almacenará cada línea del archivo:
    char array[lineas][caracteres];

    // Puntero al archivo:
    FILE *parchivo = fopen(argv[1], "r");

    // Se valida que el archivo exista:
    if(!parchivo)
    {
        printf("ERROR! El archivo [%s] no existe.\n", argv[1]);
        printf("\n\nEl analizador léxico ha finalizado inesperadamente.\n\n\n");
        parchivo = NULL;
        
        return EXIT_FAILURE;
    }

    // Se guarda cada línea del archivo:
    __guardarLineas(parchivo, lineas, caracteres, array);
    fclose(parchivo); // Se cierra el archivo
    parchivo = NULL;

    printf("Se guardarons las líneas correctamente.\n\n\n");

    printf("Proceso de análisis iniciado.\n\n\n");

    // Se generan los tokens:
    analizador(lexer, lineas, caracteres, array, &lista_var, &lista_txt, &lista_val);

    printf("\n\nProceso de análisis finalizado.\n");

    printf("\n\nLa impresión de archivos ha iniciado.\n");

    // Se imprimen las listas en el archivo .sim:
    imprimeSim(sim, &lista_var, &lista_txt, &lista_val);

    printf("La impresión de archivos ha finalizado.\n");

    // Se libera la memoria ocupada por las listas:
    liberaListaVarNum(&lista_var);
    liberaListaTxt(&lista_txt);
    liberaListaVal(&lista_val);


    // Se cierra el archivo .lex y el archivo .sim:
    fclose(lexer);
    lexer = NULL;

    fclose(sim);
    sim = NULL;

    // Se libera la memoria de los punteros de los nombres:
    free(nombre_lex);
    free(nombre_sim);
    nombre_lex = NULL;
    nombre_sim = NULL;

    printf("\n\nEl analizador léxico ha finalizado correctamente.\n\n\n");

    // Programa exitoso:
    return EXIT_SUCCESS;
}