#ifndef __LISTA_SIMPLE__
#define __LISTA_SIMPLE__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Lista para variables numéricas:
typedef 
struct _nodoNum // Nodo de variable numérica
{
	char nombre[17];
    unsigned int ID;

	struct _nodoNum *sig;
	
} nodo_VarNum;

// EStructura para lista de variables numéricas
typedef
struct
{
	nodo_VarNum *raiz;
	unsigned int tam;

} listaVarNum;

// Lista para cadenas de texto:
typedef 
struct _nodoTxt // Nodo de cadena de texto
{
	char *cadena;
    unsigned int ID;
    unsigned int num_linea;

	struct _nodoTxt *sig;
	
} nodo_Txt;

// Estructura de lista de cadena de texto:
typedef
struct
{
	nodo_Txt *raiz;
	unsigned int tam;

} listaText;

//--------------------------FUNCIONES PARA LISTA DE VARIABLES NUMÉRICAS--------------------------

extern nodo_VarNum *basura_num;

nodo_VarNum *creaNodoVarNum(char *variable, unsigned int id);

int liberaNodoVarNum(nodo_VarNum *nodo);

void iniListaVarNum(listaVarNum *Lista);

void liberaListaVarNum(listaVarNum *Lista);

void pushBackVarNum(listaVarNum *Lista, nodo_VarNum *nodo);

nodo_VarNum *buscaVarNum(listaVarNum *Lista, char *nombre);

//int borraNodoVarNum(listaVarNum *Lista, nodo_VarNum *nodo);

void imprimeListaVarNum(FILE *archivo, listaVarNum *Lista);


//--------------------------FUNCIONES PARA LISTA DE CADENAS DE TEXTO--------------------------

extern nodo_Txt *basura_txt;

nodo_Txt *creaNodoText(char *cadena, unsigned int id, unsigned int num_linea);

int liberaNodoTxt(nodo_Txt *nodo);

void iniListaTxt(listaText *Lista);

void liberaListaTxt(listaText*Lista);

void pushBackTxt(listaText *Lista, nodo_Txt *nodo);

nodo_Txt *buscaTxt(listaText *Lista, char *cadena);

//int borraNodoTxt(listaText *Lista, nodo_Txt *nodo);

void imprimeListaTxt(FILE *archivo, listaText *Lista);

#endif