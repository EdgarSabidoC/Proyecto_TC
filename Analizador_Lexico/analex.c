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

    // Se verifica que el archivo sea extensión .mio:
    char *punto = strchr(argv[1], '.');
    char *mio = ".mio";

    // Se verifica si la extensión es .mio
    if(strncmp(punto, mio, sizeof(".mio") != 0))
    {
        printf("ERROR, no se encontró archivo .mio\n\n");
        return EXIT_FAILURE;
    }

    // Puntero al nombre del programa:
    char *nombre_programa = argv[1];
        
    printf("%s\n", nombre_programa);


    // Se verifica que exista el archivo:
    FILE *prueba_archivo = fopen(argv[1], "r");
    
    if(!prueba_archivo)
    {
        printf("ERROR! El archivo %s no existe.\n", argv[1]);

        free(prueba_archivo); // Se libera la memoria.
        prueba_archivo = NULL;
        
        return EXIT_FAILURE;
    }

    free(prueba_archivo); // Se libera la memoria.
    prueba_archivo = NULL;


    // Archivo .lex:
        
    // Nombre del archivo .lex:
    int tam = strlen(argv[1]);
    char *nombre_lex = malloc(strlen(argv[1])+1 * sizeof(char));
    memcpy(nombre_lex, argv[1], tam-4); // Se copia el nombre sin la extensión.
    strncat(nombre_lex, ".lex", tam-4); // Se concatena la nueva extensión.

    // Se crea el archivo .lex:
    FILE *lexer = fopen(nombre_lex, "w+");
        


    // Archivo .sim:
        
    // Nombre del archivo .sim:
    char *nombre_sim = malloc(strlen(argv[1])+1 * sizeof(char));
    memcpy(nombre_sim, argv[1], tam-4); // Se copia el nombre sin la extensión.
    strncat(nombre_sim, ".sim", tam-4); // Se concatena la nueva extensión.

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

    // Se valida que el archivo exista:
    if(!archivo)
    {
        printf("ERROR! El archivo %s no existe.\n", argv[1]);

        free(archivo); // Se libera la memoria.
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
        printf("ERROR! El archivo %s no existe.\n", argv[1]);

        free(parchivo); // Se libera la memoria.
        parchivo = NULL;
        
        return EXIT_FAILURE;
    }

    // Se guarda cada línea del archivo:
    __guardarLineas(parchivo, lineas, caracteres, array);
    fclose(parchivo); // Se cierra el archivo
    parchivo = NULL;

    printf("Se guardarons los tokens.\n");

    // Se generan los tokens:
    analizador(lexer, lineas, caracteres, array, &lista_var, &lista_txt, &lista_val);

    printf("Finalizó el analizador.\n");

    // Se imprimen las listas en el archivo .sim:
    imprimeSim(sim, &lista_var, &lista_txt, &lista_val);


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

    // Programa exitoso:
    return EXIT_SUCCESS;
}