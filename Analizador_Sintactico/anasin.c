#include "sintax.c"

int main(int argc, char **argv)
{
    // Falla el programa:
    if (argc <= 1)
        return EXIT_FAILURE;

    // Se declara e inicializa la lista:
    listaTok lista;
    iniListaTok(&lista);

    // Punteros al archivo .lex:    
    FILE *lex_1 = fopen(argv[1], "r");
    FILE *lex_2 = fopen(argv[1], "r");
    
    // Se guardan los tokens del archivo dentro de la lista:
    guardarTokens(lex_1, lex_2, &lista);

    // Puntero auxiliar para recorrer la lista:
    nodo_Tok *nodo = lista.raiz;

    // Se imprime el contenido de la lista:
    while(nodo)
    {
        printf("Cadena: %s -- Num_linea[%u]\n", nodo->token, nodo->num_linea);
        nodo = nodo->sig;
    }  
    
    // Finalización exitosa del programa:
    return EXIT_SUCCESS;
}