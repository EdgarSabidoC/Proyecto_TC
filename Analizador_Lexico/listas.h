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

	struct _nodoTxt *sig;
	
} nodo_Txt;

// Estructura de lista de cadena de texto:
typedef
struct
{
	nodo_Txt *raiz;
	unsigned int tam;

} listaText;

typedef
struct __nodoVal
{
	int valor_octal;
	long long valor_decimal;

	struct __nodoVal *sig;
} nodo_Val;


// Estructura de la lista de valores:
typedef
struct
{
	nodo_Val *raiz;
	unsigned int tam;

} listaVal;


//--------------------------FUNCIONES PARA LISTA DE VARIABLES NUMÉRICAS--------------------------


nodo_VarNum *creaNodoVarNum(char *variable, unsigned int id);

int liberaNodoVarNum(nodo_VarNum *nodo);

void iniListaVarNum(listaVarNum *Lista);

void liberaListaVarNum(listaVarNum *Lista);

void pushBackVarNum(listaVarNum *Lista, nodo_VarNum *nodo);

nodo_VarNum *buscaVarNum(listaVarNum *Lista, char *nombre);


//--------------------------FUNCIONES PARA LISTA DE CADENAS DE TEXTO--------------------------


nodo_Txt *creaNodoText(char *cadena, unsigned int id);

int liberaNodoTxt(nodo_Txt *nodo);

void iniListaTxt(listaText *Lista);

void liberaListaTxt(listaText*Lista);

void pushBackTxt(listaText *Lista, nodo_Txt *nodo);


//--------------------------FUNCIONES PARA LISTA DE VALORES--------------------------

nodo_Val *creaNodoVal(int numero_octal, long long numero_decimal);

int liberaNodoVal(nodo_Val *nodo);

void iniListaVal(listaVal *Lista);

void liberaListaVal(listaVal *Lista);

void pushBackVal(listaVal *Lista, nodo_Val *nodo);

#endif