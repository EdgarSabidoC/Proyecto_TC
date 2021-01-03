#include "listas.h"

//--------------------------FUNCIONES PARA LISTA DE VARIABLES NUMÉRICAS--------------------------


/* Crea un nodo_VarNum */
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


/* LIbera la memoria ocupada por un nodo_VarNum */
int liberaNodoVarNum(nodo_VarNum *nodo)
{
	if(nodo) //Equivalente a nodo != NULL
	{
		free(nodo); // Se libera la memoria del nodo_VarNum.
	
		// Si la operación es exitosa:	
		return 0;
	}

	// Si no se pudo libera la memoria del nodo:
	return -1;
}


/* Inicializa una lista de variables numéricas */
void iniListaVarNum(listaVarNum *Lista)
{
	Lista->raiz = NULL; // El nodo raíz de la lista apunta a NULL
	Lista->tam = 0; // La lista está vacía, entonces el tamaño es 0.
}


/* Libera el espacio de memoria ocupada por la lista de variables numéricas */
void liberaListaVarNum(listaVarNum *Lista)
{
	nodo_VarNum *aux; // Apuntador auxiliar
	
	while (Lista->raiz) // Mientras la raíz sea diferente de NULL
	{
		aux = Lista->raiz; // El nodo "aux" adquiere lo que está en el nodo "raíz" de la lista.
		Lista->raiz = Lista->raiz->sig; // La raíz de la lista apunta al valor del nodo siguiente del que era el nodo raíz.
		liberaNodoVarNum(aux); // Se libera el nodo "aux"
	}

	Lista->tam = 0; // Se deja el tamaño en 0, pues la lista está vacía
}


/* Ingresa un nodo_VarNum al final de la lista */
void pushBackVarNum(listaVarNum *Lista, nodo_VarNum *nodo)
{
	if (nodo) //Equivalente a nd != NULL
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
				
			// Se inserta nodo despues de apu;	
			apu->sig = nodo;
			nodo = NULL;
		}	
		Lista->tam++;
	}
}


/* Busca el nodo de una variable numérica dentro de la lista */
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


/* Crea un nodo_Txt */
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


/* Libera la memoria ocupada por un nodo_Txt */
int liberaNodoTxt(nodo_Txt *nodo)
{
	if(nodo) //Equivalente a nodo != NULL
	{
		// Se libera la memoria ocupada por el nodo:
		free(nodo->cadena); // Se libera la memoria del string del nodo.
		free(nodo); // Se libera la memoria del nodo.

		// Si la operación fue exitosa:
		return 0;
	}

	// Si no se pudo liberar la memoria del nodo:
	return -1;
}


/* Inicializa una lista de cadenas de texto */
void iniListaTxt(listaText *Lista)
{
	Lista->raiz = NULL; // El nodo raíz de la lista apunta a NULL
	Lista->tam = 0; // La lista está vacía, entonces el tamaño es 0.
}


/* Libera el espacio de memoria ocpada por la lista de cadenas de texto */
void liberaListaTxt(listaText*Lista)
{
	nodo_Txt *aux; // Apuntador auxiliar
	
	while (Lista->raiz) // Mientras la raíz sea diferente de NULL
	{
		aux = Lista->raiz; // El nodo "aux" adquiere lo que está en el nodo "raíz" de la lista.
		Lista->raiz = Lista->raiz->sig; // La raíz de la lista apunta al valor del nodo siguiente del que era el nodo raíz.
		
		liberaNodoTxt(aux); // Se libera el nodo "aux"
	}

	Lista->tam = 0; // Se deja el tamaño en 0, pues la lista está vacía
}


/* Ingresa un nodo_Txt al final de la lista */
void pushBackTxt(listaText *Lista, nodo_Txt *nodo)
{
	if (nodo) //Equivalente a nd != NULL
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
				
			// Se inserta nodo despues de apu;	
			apu->sig = nodo;
			nodo = NULL;
		}	
		Lista->tam++;
	}
}


//--------------------------FUNCIONES PARA LISTA DE VALORES--------------------------


/* Crea un nodo_Val */
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


/* Libera la memoria ocupada por un nodo_Val */
int liberaNodoVal(nodo_Val *nodo)
{
	if(nodo) //Equivalente a nodo != NULL
	{
		// Se libera el nodo:
		free(nodo);

		// Si resulta existosa la operación:
		return 0;
	}

	// Si no se pudo liberar el nodo:
	return 1;
}


/* Inicializa una lista de valores */
void iniListaVal(listaVal *Lista)
{
	Lista->raiz = NULL; // El nodo raíz de la lista apunta a NULL
	Lista->tam = 0; // La lista está vacía, entonces el tamaño es 0.
}


/* Libera el espacio de memoria ocupado por la lista de valores */
void liberaListaVal(listaVal *Lista)
{
	nodo_Val *aux; // Apuntador auxiliar
	
	while (Lista->raiz) // Mientras la raíz sea diferente de NULL
	{
		aux = Lista->raiz; // El nodo "aux" adquiere lo que está en el nodo "raíz" de la lista.
		Lista->raiz = Lista->raiz->sig; // La raíz de la lista apunta al nodo siguiente del que era el nodo raíz.
		liberaNodoVal(aux); // Se libera el nodo "aux"
	}

	Lista->tam = 0; // Se deja el tamaño en 0, pues la lista está vacía
}


/* Ingresa un nodo_Val al final de la lista */
void pushBackVal(listaVal *Lista, nodo_Val *nodo)
{
	if (nodo) //Equivalente a nd != NULL
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
				
			// Se inserta nodo despues de apu;	
			apu->sig = nodo;
			nodo = NULL;
		}	
		Lista->tam++;
	}
}