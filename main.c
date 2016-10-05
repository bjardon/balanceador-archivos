#include "pila.h"
#include <string.h>
#include <stdio.h>

int menu(char * nombre) {
	printf("\nNo especificó segundo argumento.\nIngrese el nombre del archivo ahora: >  ");
	scanf("%[^\n]s", nombre);
}

int main(int argc, const char * argv[]) {
	char nombre[255], a;
	int linea = 1, error = 0;
	FILE * archivo;
	Pila pila;
	Nodo nodo;
	
	if(argc > 1)
		strcpy(nombre, argv[1]);
	else
		menu(nombre);

	inicializar(&pila);
	archivo = fopen(nombre, "r+");
	a = fgetc(archivo);
	
	if(archivo != NULL)
		printf("El archivo especificado es: %s: [%p]\n", nombre, archivo);
	else {
		printf("No se tiene acceso al archivo %s", nombre);
		exit(0);
	}

	while(a!= EOF) {
		switch(a) {
			
			case '(': {
				push(pila, (a + 1), linea);
				break;
			}
			case '[': case '{':{ 
				push(pila, (a + 2), linea);
				break;
			}
			case ')': case ']': case '}': {
				nodo = pop(pila);
				if(nodo == NULL) {
					printf("\nExpresion incorrecta, falta un %c de apertura al final", a);
					error = 1;
				}
				if(nodo->operador != a) {
					printf("\nExpresion incorrecta, falta un %c de apertura en la linea %d", a, nodo->linea);
					error = 1;
				}
				break;
			}
			
			case '\n': 
				linea++;
				break;	
			
		}
	a = fgetc(archivo);	
	}
	
	if(vacia(pila) && !error){
		printf("\nÉxito. El archivo está balanceado.");
	} else {
		nodo = pop(pila);
		while(nodo != NULL) {
			printf("\nError. Falta un %c de cierre que se abrio en la linea %d", nodo->operador, nodo->linea);
			nodo = pop(pila);
		}
	}

	printf("\n");
	fclose(archivo);

	return 0;		
}
