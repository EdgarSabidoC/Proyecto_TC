#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "lexer.h"

// VARIABLES

typedef struct _variable_numerica 
{
    char nombre[17]; // Nombre del identificador
    char *id; // Clave del identificador
    int valor; // Número
    unsigned int num_linea;
} num_var;

/* TOKENS ACEPTADOS QUE SON PARTE DEL LENGUAJE MIO */

//char operadores_relacionales[] = {">", "<", "=="};

//char operadores_aritmeticos[] = {'+', '-', '*', '/'};

char asignacion = '=';



//-----------------------------------------------------------------FUNCIONES------------------------------------------------------------

/* La función halla la cantidad de líneas de un texto */
int __contarLineasArchivo(FILE *archivo)
{
    int numero_lineas = 0;
    char c; // Almacena el caracter leído del archivo.

    // Si el archivo no existe:
    if (!archivo)
    {
        printf("ERROR: No se pudo abrir el archivo");
        return -1;
    }

    // Se extra el primer caracter de cada línea y se guarda en c:
    for(c = getc(archivo); c != EOF; c = getc(archivo))
        if(c == '\n') // Si hay un salto de línea se incrementa el contador.
            numero_lineas++;

    printf("La cantidad de lineas es: %d\n", numero_lineas+1);
    return numero_lineas+1; // Se retorna la cantidad de líneas del archivo.
}

/* La función almacena las líneas del archivo dentro de un vector */
void __guardarLineas(FILE *archivo, unsigned int lineas, unsigned caracteres, char cadena[lineas][caracteres])
{
    unsigned int i = 0;

    while(1)
    {
        // Se guarda la línea del archivo en el arreglo:
        //if(fgets(cadena[i], chars, archivo) != NULL) 
        if(fgets(cadena[i], sizeof(cadena[i]), archivo) != NULL)
        {
            printf("%s", cadena[i]);
            i++;
        }
        else
        {
            break;
        }
    }
}


// Retorna 'true' si el char es un OPERADOR. 
bool __esOperadorAr(char ch) 
{ 
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return (true); 
	else
        return (false); 
}

bool __esTexto(char ch)
{
    // 34 == " en ASCII
    char comilla = '\"';

	if (ch == comilla)
		return (true); 
	else
        return (false); 
}

bool __esReservada(char *str)
{
    unsigned int i = 0;
    char *palabras_reservadas[12] = {"PROGRAMA", "FINPROG", "SI", "ENTONCES", "SINO", "FINSI", "REPITE", "VECES", "FINREP", "IMPRIME", "LEE", 0};

    while(palabras_reservadas[i])
    {
        if(strncmp(str, palabras_reservadas[i], sizeof(palabras_reservadas[i])) == 0)
        {   
            return (true);
        }
        i++;
    }
    return (false);
    
}

bool __esComentario(char ch)
{
    char comentario = '#';

    if(ch == comentario)
        return (true);
    return (false);
}

bool __estaEnTabSim(char *str, char **tabla_sim)
{
    unsigned int i = 0;

    while(tabla_sim[i])
    {
        if(strncmp(str, tabla_sim[i], sizeof(tabla_sim[i])) == 0)
        {   
            return (true);
        }
        i++;
    }
    return (false);
}

/* Valida los tokens y los imprime */
bool __esVarValid(char *token, unsigned int num_linea)
{
    // Se verifica si el primer elemento es una letra:
    if (isalpha(*token))
    {    
        // Se verifica que no sea una palabra reservada:
        if(__esReservada(token) == false)
        {    
            return (true);
        }

        // Si es una palabra reservada:
        else
        {
            printf("Es palabra reservada: ");
            return (false);
        }        
    } 

    // Es un número:
    else if (isdigit(*token))
    {
        printf("ERROR en línea %d: Las variables no pueden iniciar con un número: ", num_linea);
        return (false);
    }
}

char *generarTokens(unsigned int lineas, unsigned int chars, char cadena[lineas][chars])
{
    unsigned int i, j; 
    char *token, *ptr;
    unsigned int cont_txt = 0;

    // Se recorre cada línea:
    for(i = 0; i < lineas; i++)
    {
        // Se ignoran los comentarios:
        if(cadena[i][0] == '#')
        {
            continue;
        }

        // Se genera una copia de la cadena:
        //char *copia = (char *)malloc(strlen(cadena[i]) + 1);
        //strcpy(copia, cadena[i]);

        /* Si hay un string en la linea */
        if(strchr(cadena[i], '\"') != 0)
        {   
            // Se genera el primer token:
            token = strtok(cadena[i], "\"\n");
        
            while(token != NULL) 
            {  
                // Se ignoran los comentarios:
                if(*token == '#')
                {
                    break;
                }
                
                if(__esVarValid(token, i+1) == true)
                {
                    printf("Es reservada: ");
                    printf("%s\n", token);
                }

                else printf("%s\n", token);

                // Se generan los tokens siguientes:
                token = strtok(NULL, "\"\n");

            }// Fin While
        }// Fin if  

        /*else if(strchr(cadena[i], '='))
        {
        
            // Si hay un asinación de variable númerica en la linea 
            if(strchr(cadena[i], '\"') != 0)
            {   
                // Se genera el primer token:
                token = strtok(cadena[i], "\"");
        
                while(token != NULL) 
                {  
                    // Se ignoran los comentarios:
                    if(*token == '#')
                    {
                        break;
                    }

                    printf("%s\n", token);

                    // Se generan los tokens siguientes:
                    token = strtok(NULL, "\"");

                }// Fin While
            }
        }*/

        // Si sólo son palabras dentro de la línea:
        else
        {
            // Se genera el primer token:
            token = strtok(cadena[i], " \n\t");
        
            while(token != NULL) 
            {  
                // Se ignoran los comentarios:
                if(*token == '#')
                {
                    break;
                }

                if(__esVarValid(token, i+1) == true)
                {
                    printf("%s\n", token);
                }

                else printf("%s\n", token);

                // Se generan los tokens siguientes:
                token = strtok(NULL, " \n\t");

            }// Fin While
        } // Fin else
        
    } // Fin for
}

void generarLexer(char *cadena)
{
    FILE *lexer = fopen("Programa.lex", "a+");

    fprintf(lexer, "%s\n", cadena);

    fclose(lexer);
}

/* La función imprime un arreglo con las líneas del archivo */
void __imprimeLineas(unsigned int lineas, unsigned int chars, char arreglo[lineas][chars])
{
    unsigned int i;

    for(i = 0; i < lineas; i++)
        printf("\n%s", arreglo[i]);
}

int main(int argc, char **argv)
{   
    if (argc>1)
    {
        // Puntero al archivo:
        FILE *archivo = fopen(argv[1], "r");
    
        // Se cuenta la cantidad de líneas del archivo:
        unsigned int lineas;
        lineas = __contarLineasArchivo(archivo);
        fclose(archivo); // Se cierra el archivo

        // Cantidad de caracteres máximos de cada archivo:
        unsigned int caracteres = 256;

        // Arreglo que almacenará cada línea del archivo:
        char array[lineas][caracteres];

        // Puntero al archivo:
        FILE *parchivo = fopen(argv[1], "r");
        
        // Se guarda cada línea del archivo:
        __guardarLineas(parchivo, lineas, caracteres, array);
        fclose(parchivo); // Se cierra el archivo

        // Se imprime cada línea del archivo:
        printf("\n\n\nSe imprime lo del documento.\n");
        __imprimeLineas(lineas, caracteres, array);
        printf("\n\n\n");

        // Se generan los tokens:
        printf("\n\n\nSe verifican los tokens:\n");
        generarTokens(lineas, caracteres, array);

        // Se genera el archivo .lex:
        //generarLexer(lineas, array);

        // Se imprime la última línea del archivo:
        //printf("\nEl numero de caracteres de la ultima linea es: %d", strlen(array[lineas-1]));
        
    }

    return 0;
}
