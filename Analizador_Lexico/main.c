#include "lexer.c"
// Programa principal del analizador léxico.

int main(int argc, char *argv[])
{
    if (argc>1)
    {
        if (guardarLineas(argv[1]) < 0)
            return 1;
    }
    
    return 0;
}