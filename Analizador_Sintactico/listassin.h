#ifndef __LISTA_SIMPLE__
#define __LISTA_SIMPLE__

// NOTA: Para evitar errores inesperados
// NO MODIFICAR ninguna de las funciones de este archivo.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lista de tokens:
typedef 
struct _nodoToken // Nodo de token
{
	char token[12];
	unsigned int num_linea;

	struct _nodoToken *sig;
	
} nodo_Tok;

// EStructura para lista de tokens:
typedef
struct
{
	nodo_Tok *raiz;
	unsigned int tam;

} listaTok;


//--------------------------FUNCIONES PARA LISTA DE TOKENS---------------------------


nodo_Tok *creaNodoTok(char *token, unsigned int num_linea);

int liberaNodoTok(nodo_Tok *nodo);

void iniListaTok(listaTok *Lista);

void liberaListaTok(listaTok *Lista);

void pushBackTok(listaTok *Lista, nodo_Tok *nodo);

nodo_Tok *buscaTok(listaTok *Lista, char *token);


#endif