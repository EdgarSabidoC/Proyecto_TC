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

    // Se verifica que la extensión sea .mio
    if(strncmp(punto, mio, sizeof(".mio")))
    {
        printf("ERROR, no se encontró archivo .mio\n\n");
        return EXIT_FAILURE;
    }

    // Puntero al nombre del programa:
    char *nombre_programa = argv[1];
        
    printf("%s\n", nombre_programa);



    // Archivo .lex:
        
    // Nombre del archivo .lex:
    int tam = strlen(argv[1]);
    char nombre_lex[tam];
    memcpy(nombre_lex, argv[1], tam-4); // Se copia el nombre sin la extensión.
    strncat(nombre_lex, ".lex", tam-4); // Se concatena la nueva extensión.

    // Se crea el archivo .lex:
    FILE *lexer = fopen(nombre_lex, "w+");
        


    // Archivo .sim:
        
    // Nombre del archivo .sim:
    char nombre_sim[tam];
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

    // Programa exitoso:
    return EXIT_SUCCESS;
}