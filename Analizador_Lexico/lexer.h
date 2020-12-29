#ifndef __LEXER__
#define __LEXER__

// Aquí se ponen los prototipos de las funciones.

int __contarLineasArchivo(FILE *archivo);
void __guardarLineas(FILE *archivo, unsigned int lineas, unsigned int chars, char cadena[lineas][chars]);
char *generarTokens(unsigned int lineas, unsigned int chars, char cadena[lineas][chars]);
void __imprimeLineas(unsigned int lineas, unsigned int chars, char arreglo[lineas][chars]);

#endif