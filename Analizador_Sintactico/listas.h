#ifndef __LISTA_SIMPLE__
#define __LISTA_SIMPLE__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Lista de tokens:
typedef 
struct _nodoToken // Nodo de token
{
	char *token;

	struct _nodoToken *sig;
	
} nodo_Tok;

// EStructura para lista de tokens:
typedef
struct
{
	nodo_Tok *raiz;
	unsigned int tam;

} listaTok;


// Lista de listas:
typedef 
struct _nodoLista // Nodo de lista.
{
	listaTok *raiz_lista_tok;
    unsigned int num_linea;

	struct _nodoLista *sig_lista;
	
} nodo_List;

// EStructura para lista de tokens:
typedef
struct
{
	nodo_List *raiz;
	unsigned int tam;

} listaList;


//--------------------------FUNCIONES PARA LISTA DE TOKENS---------------------------


nodo_Tok *creaNodoTok(char *token);

int liberaNodoTok(nodo_Tok *nodo);

void iniListaTok(listaTok *Lista);

void liberaListaTok(listaTok *Lista);

void pushBackTok(listaTok *Lista, nodo_Tok *nodo);

nodo_Tok *buscaTok(listaTok *Lista, char *token);


//--------------------------FUNCIONES PARA LISTA DE LISTAS---------------------------

nodo_List *creaNodoList(listaTok *lista_tok, unsigned int num_linea);

int liberaNodoList(nodo_List *nodo);

void iniListaList(listaList *lista);

void liberaListaList(listaList *lista);

void pushBackLista(listaList *lista, nodo_List *nodo);

#endif