#ifndef __SINTAX__
#define __SINTAX__

// NOTA: Para evitar errores inesperados
// NO MODIFICAR ninguna de las funciones de este archivo.

// Biblioteca que incluye las funciones necesarias para el uso de listas de tipo listaTok:
#include "listas.h" 

//-----------------------------------------------------------------FUNCIONES------------------------------------------------------------

void guardarTokens(FILE *arch_lex, listaTok *lista);

int __esReservada(char *token);

int __esOpAr(char *cadena);

int __esVal(char *token);

int __esOpRel(char *cadena);

int __esTexto(char *token);

int __esVariable(char *token);

int __esElem(char *token);

int __esCompara(nodo_Tok *nodo);
       
int __esLee(char *token);

int __esImprime(char *token);

int __esAsig(char *token);

int __esRepite(char *token);

int __esVeces(char *token);

int __esFinRep(char *token);

int __esSi(char *token);

int __esSiNo(char *token);

int __esEntonces(char *token);

int __esFinSi(char *token);

int __esFinProg(char *token);

nodo_Tok *__esSent(nodo_Tok *nodo);

int iniAnalSin(listaTok *lista);

#endif