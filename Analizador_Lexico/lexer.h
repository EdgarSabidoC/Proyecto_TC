#ifndef __LEXER__
#define __LEXER__

// NOTA: Para evitar errores inesperados
// NO MODIFICAR ninguna de las funciones de este archivo.

#include <ctype.h> 
#include "listas.h" // Funciones de listas.

long long OctADec(char *numero);

//--------------------------------------------------FUNCIONES PRIVADAS----------------------------------------------

int __contarLineasArchivo(FILE *archivo);

void __guardarLineas(FILE *archivo, unsigned int lineas, unsigned int caracteres, char cadena[lineas][caracteres]);

int __esReservada(char *cadena);

int __esAsig(char *cadena);

int __esSimbol(char *token);

int __esOpAr(char *cadena) ;

int __esNum(char *cadena);

int __esOpRel(char *cadena);

int __esComentario(char *cadena);

int __esComilla(char *cadena);

int __esTexto(char *token, unsigned int num_linea);

int __esVarValid(char *cadena);

int __esVariable(char *cadena);

char __identifica(char *token, unsigned int num_linea);


//------------------------------------------------------------------FUNCIONES DEL ANALIZADOR-----------------------------------------------------------------------------------------------


char *tokenCadena(char *cadena);

void impTokLex(FILE *archivo_lex, char ident, char *token, listaVarNum *lista_vars, listaText *lista_cadenas, listaVal *lista_valores);

void imprimeSim(FILE *archivo_sim, listaVarNum *lista_vars, listaText *lista_cadenas, listaVal *lista_valores);

char *genTok(FILE *archivo_lex, char *cadena, unsigned int num_linea, listaVarNum *lista_vars, listaText *lista_cadenas, listaVal *lista_valores);

void analizador(FILE *archivo_lex, unsigned int lineas, unsigned int chars, char cadena[lineas][chars], listaVarNum *lista_vars, listaText *lista_strs, listaVal *lista_vals);

#endif