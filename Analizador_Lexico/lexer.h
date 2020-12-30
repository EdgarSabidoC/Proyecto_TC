#ifndef __LEXER__
#define __LEXER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "listas.c"

// Aquí se ponen los prototipos de las funciones.

int __contarLineasArchivo(FILE *archivo);
void __guardarLineas(FILE *archivo, unsigned int lineas, unsigned int chars, char cadena[lineas][chars]);
void anaLex(unsigned int lineas, unsigned int chars, char cadena[lineas][chars], listaVarNum *lista_vars, listaText *lista_cadenas);
void __imprimeLineas(unsigned int lineas, unsigned int chars, char arreglo[lineas][chars]);

#endif