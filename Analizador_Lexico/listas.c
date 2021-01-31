#include "listas.h"

//--------------------------FUNCIONES PARA LISTA DE VARIABLES NUMÉRICAS--------------------------

/* 
 * DESCRIPCIÓN:
 * Esta función aparta un bloque de memoria
 * en la memoria dinámica y crea un nodo 
 * de tipo nood_VarNum (a partir del token y de su 
 * número de identificador) para una lista de tipo listaVarNum,
 * 
 * ENTRADA: Un puntero a una cadena (token)
 * 			y un unsigned int (número de id del token)
 * 
 * SALIDA: Puntero al nodo.
 * 
 */
nodo_VarNum *creaNodoVarNum(char *variable, unsigned int id)
{
	nodo_VarNum *apu;
	
	apu = (nodo_VarNum *)malloc(sizeof(nodo_VarNum)); // Se crea un espacio de memoria del tamaño de la struct nodo_VarNum

	if (apu) //Equivalente a apu != NULL
	{
		strncpy(apu->nombre, variable, 16); // Se copia el nombre de la variable.
		apu->ID = id; // Se asigna el valor del ID.
		
		apu->sig = NULL; // El apuntador del nodo "apu" apunta a NULL.
	}

	return apu; // Se retorna el nodo "apu".
}


/* 
 * DESCRIPCIÓN:
 * Esta función libera de la memoria dinámica
 * el espacio ocupado por un nodo en una lista
 * de tipo listaVarNum.
 * 
 * ENTRADA: Un puntero de tipo nodo_VarNum (nodo).
 * 
 * SALIDA: 0 si la operación fue exitosa, 
 *         -1 si la operación no fue exitosa.
 * 
 */
int liberaNodoVarNum(nodo_VarNum *nodo)
{
	if(nodo)
	{
		free(nodo); // Se libera la memoria del nodo_VarNum.
		nodo = NULL;

		// Si la operación es exitosa:	
		return 0;
	}

	// Si no se pudo libera la memoria del nodo:
	return -1;
}


/* 
 * DESCRIPCIÓN:
 * Esta función inicializa una lista de tipo
 * listaVarNum apuntando su raíz a NULL y
 * asignando un tamaño de 0.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaVarNum.
 * 
 * SALIDA: N/A.
 * 
 */
void iniListaVarNum(listaVarNum *Lista)
{
	Lista->raiz = NULL; // El nodo raíz de la lista apunta a NULL
	Lista->tam = 0; // La lista está vacía, entonces el tamaño es 0.
}


/* 
 * DESCRIPCIÓN:
 * Esta función libera de la memoria dinámica
 * el espacio ocupado por una lista de tipo
 * listaVarNum.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaVarNum.
 * 
 * SALIDA: N/A.
 * 
 */
void liberaListaVarNum(listaVarNum *Lista)
{
	nodo_VarNum *aux; // Nodo auxiliar
	
	while (Lista->raiz) // Mientras la raíz sea diferente de NULL
	{
		aux = Lista->raiz; // El nodo "aux" adquiere lo que está en el nodo "raíz" de la lista.
		Lista->raiz = Lista->raiz->sig; // La raíz de la lista apunta al valor del nodo siguiente del que era el nodo raíz.
		liberaNodoVarNum(aux); // Se libera el nodo "aux"
	}

	Lista->raiz = NULL;
	Lista->tam = 0; // Se deja el tamaño en 0, pues la lista está vacía
}


/* 
 * DESCRIPCIÓN:
 * Esta función ingresa un nodo de tipo
 * nodo_VarNum al final de una lista de tipo 
 * listaVarNum con una operación pushBack.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaVarNum
 * 			y un puntero a un nodo de tipo 
 * 			nodo_VarNum (nodo).
 * 
 * SALIDA: N/A.
 * 
 */
void pushBackVarNum(listaVarNum *Lista, nodo_VarNum *nodo)
{
	if (nodo)
	{
		if (!Lista->raiz)
		   Lista->raiz = nodo;
		else
		{
			nodo_VarNum *apu;

			// Se recorre toda la lista hasta que
			// apu apunte al último nodo.
			apu = Lista->raiz;
			while (apu->sig)
				apu = apu->sig;
				
			// Se inserta nodo después de apu;	
			apu->sig = nodo;
			nodo = NULL;
		}	
		Lista->tam++;
	}
}


/* 
 * DESCRIPCIÓN:
 * Esta función busca un nodo de tipo nodo_VarNum,
 * a partir del contenido del nodo (token),
 * dentro de una lista de tipo listaVarNum y
 * lo retorna si lo encuentra.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaVarNum
 * 			y un puntero a una cadena (token).
 * 
 * SALIDA: Puntero a un nodo de tipo nodo_VarNum.
 * 
 */
nodo_VarNum *buscaVarNum(listaVarNum *Lista, char *nombre)
{	
	nodo_VarNum *apu;
	
	// Se recorre la lista buscando la cadena:
	apu = Lista->raiz;

	while (apu != NULL)
	{
		// Si se encuentra la cadena:
		if(strncmp(nombre, apu->nombre, 17) == 0) // Compara las cadenas.
		{
			return apu;
		}
		apu = apu->sig;
	}

	// Si la cadena no se encuentra:
	return NULL;	
}


//--------------------------FUNCIONES PARA LISTA DE CADENAS DE TEXTO--------------------------


/* 
 * DESCRIPCIÓN:
 * Esta función aparta un bloque de memoria
 * en la memoria dinámica y crea un nodo 
 * de tipo nood_Txt (a partir del token y de su 
 * número de identificador) para una lista de tipo listaText,
 * 
 * ENTRADA: Un puntero a una cadena (token)
 * 			y un unsigned int (número de id del token)
 * 
 * SALIDA: Puntero al nodo.
 * 
 */
nodo_Txt *creaNodoText(char *cadena, unsigned int id)
{
	nodo_Txt *apu;

	apu = (nodo_Txt *)malloc(sizeof(nodo_Txt)); // Creamos un espacio de memoria del tamaño de la struct nodo_Txt

	if (apu) //Equivalente a apu != NULL
	{
		// Se crea un arreglo dinámico del tamaño de la cadena:
		apu->cadena = (char *)malloc(strlen(cadena)+1 * sizeof(char));

		strncpy(apu->cadena, cadena, strlen(cadena)+1); // Se copia la cadena en el nodo.
		apu->ID = id; // Se asigna el valor del ID.
		
		apu->sig = NULL; // El apuntador del nodo "apu" apunta a NULL.
	}

	return apu; // Se retorna el nodo "apu".
}


/* 
 * DESCRIPCIÓN:
 * Esta función libera de la memoria dinámica
 * el espacio ocupado por un nodo en una lista
 * de tipo listaText.
 * 
 * ENTRADA: Un puntero de tipo nodo_Txt (nodo).
 * 
 * SALIDA: 0 si la operación fue exitosa, 
 *         -1 si la operación no fue exitosa.
 * 
 */
int liberaNodoTxt(nodo_Txt *nodo)
{
	if(nodo)
	{
		// Se libera la memoria ocupada por el nodo:
		free(nodo->cadena); // Se libera la memoria del string del nodo.
		free(nodo); // Se libera la memoria del nodo.
		nodo = NULL;

		// Si la operación fue exitosa:
		return 0;
	}

	// Si no se pudo liberar la memoria del nodo:
	return -1;
}


/* 
 * DESCRIPCIÓN:
 * Esta función inicializa una lista de tipo
 * listaText apuntando su raíz a NULL y
 * asignando un tamaño de 0.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaText.
 * 
 * SALIDA: N/A.
 * 
 */
void iniListaTxt(listaText *Lista)
{
	Lista->raiz = NULL; // El nodo raíz de la lista apunta a NULL
	Lista->tam = 0; // La lista está vacía, entonces el tamaño es 0.
}


/* 
 * DESCRIPCIÓN:
 * Esta función libera de la memoria dinámica
 * el espacio ocupado por una lista de tipo
 * listaText.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaText.
 * 
 * SALIDA: N/A.
 * 
 */
void liberaListaTxt(listaText*Lista)
{
	nodo_Txt *aux; // Nodo auxiliar
	
	while (Lista->raiz) // Mientras la raíz sea diferente de NULL
	{
		aux = Lista->raiz; // El nodo "aux" adquiere lo que está en el nodo "raíz" de la lista.
		Lista->raiz = Lista->raiz->sig; // La raíz de la lista apunta al valor del nodo siguiente del que era el nodo raíz.
		
		liberaNodoTxt(aux); // Se libera el nodo "aux"
	}

	Lista->raiz = NULL;
	Lista->tam = 0; // Se deja el tamaño en 0, pues la lista está vacía
}


/* 
 * DESCRIPCIÓN:
 * Esta función ingresa un nodo de tipo
 * nodo_Txt al final de una lista de tipo 
 * listaText con una operación pushBack.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaText
 * 			y un puntero a un nodo de tipo 
 * 			nodo_Txt (nodo).
 * 
 * SALIDA: N/A.
 * 
 */
void pushBackTxt(listaText *Lista, nodo_Txt *nodo)
{
	if (nodo)
	{
		if (!Lista->raiz)
		   Lista->raiz = nodo;
		else
		{
			nodo_Txt *apu;

			// Se recorre toda la lista hasta que
			// apu apunte al último nodo.
			apu = Lista->raiz;
			while (apu->sig)
				apu = apu->sig;
				
			// Se inserta nodo después de apu;	
			apu->sig = nodo;
			nodo = NULL;
		}	
		Lista->tam++;
	}
}


//--------------------------FUNCIONES PARA LISTA DE VALORES--------------------------


/* 
 * DESCRIPCIÓN:
 * Esta función aparta un bloque de memoria
 * en la memoria dinámica y crea un nodo 
 * de tipo nood_Val (a partir del token y de su 
 * número de identificador) para una lista de tipo listaVal,
 * 
 * ENTRADA: Un int (número octal) y 
 * 			un long long (número decimal).
 * 
 * SALIDA: Puntero al nodo.
 * 
 */
nodo_Val *creaNodoVal(int numero_octal, long long numero_decimal)
{
	nodo_Val *apu;
	
	apu = (nodo_Val *)malloc(sizeof(nodo_Val)); // Creamos un espacio de memoria del tamaño de la struct nodo_Val

	if (apu) //Equivalente a apu != NULL
	{
		apu->valor_octal =  numero_octal; // Se asigna el valor octal.
		apu->valor_decimal = numero_decimal; // Se asigna el valor decimal.
		
		apu->sig = NULL; // El apuntador del nodo "apu" apunta a NULL.
	}

	return apu; // Retornamos el nodo "apu".
}


/* 
 * DESCRIPCIÓN:
 * Esta función libera de la memoria dinámica
 * el espacio ocupado por un nodo en una lista
 * de tipo listaVal.
 * 
 * ENTRADA: Un puntero de tipo nodo_Val (nodo).
 * 
 * SALIDA: 0 si la operación fue exitosa, 
 *         -1 si la operación no fue exitosa.
 * 
 */
int liberaNodoVal(nodo_Val *nodo)
{
	if(nodo)
	{
		// Se libera el nodo:
		free(nodo);
		nodo = NULL;

		// Si resulta exitosa la operación:
		return 0;
	}

	// Si no se pudo liberar el nodo:
	return 1;
}


/* 
 * DESCRIPCIÓN:
 * Esta función inicializa una lista de tipo
 * listaVal apuntando su raíz a NULL y
 * asignando un tamaño de 0.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaVal.
 * 
 * SALIDA: N/A.
 * 
 */
void iniListaVal(listaVal *Lista)
{
	Lista->raiz = NULL; // El nodo raíz de la lista apunta a NULL
	Lista->tam = 0; // La lista está vacía, entonces el tamaño es 0.
}


/* 
 * DESCRIPCIÓN:
 * Esta función libera de la memoria dinámica
 * el espacio ocupado por una lista de tipo
 * listaVal.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaVal.
 * 
 * SALIDA: N/A.
 * 
 */
void liberaListaVal(listaVal *Lista)
{
	nodo_Val *aux; // Nodo auxiliar
	
	while (Lista->raiz) // Mientras la raíz sea diferente de NULL
	{
		aux = Lista->raiz; // El nodo "aux" adquiere lo que está en el nodo "raíz" de la lista.
		Lista->raiz = Lista->raiz->sig; // La raíz de la lista apunta al nodo siguiente del que era el nodo raíz.
		liberaNodoVal(aux); // Se libera el nodo "aux"
	}

	Lista->raiz = NULL;
	Lista->tam = 0; // Se deja el tamaño en 0, pues la lista está vacía
}


/* 
 * DESCRIPCIÓN:
 * Esta función ingresa un nodo de tipo
 * nodo_Val al final de una lista de tipo 
 * listaVal con una operación pushBack.
 * 
 * ENTRADA: Un puntero a una lista de tipo listaVal
 * 			y un puntero a un nodo de tipo 
 * 			nodo_Val (nodo).
 * 
 * SALIDA: N/A.
 * 
 */
void pushBackVal(listaVal *Lista, nodo_Val *nodo)
{
	if (nodo)
	{
		if (!Lista->raiz)
		   Lista->raiz = nodo;
		else
		{
			nodo_Val *apu;

			// Se recorre toda la lista hasta que
			// apu apunte al último nodo.
			apu = Lista->raiz;
			while (apu->sig)
				apu = apu->sig;
				
			// Se inserta nodo después de apu;	
			apu->sig = nodo;
			nodo = NULL;
		}	
		Lista->tam++;
	}
}