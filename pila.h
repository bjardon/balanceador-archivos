#include <stdlib.h>
#include <stdio.h>

typedef struct _nodo {
	char operador;
	int linea;
	struct _nodo * siguiente;
} _Nodo;

typedef struct _pila {
	struct _nodo * tope;
} _Pila;

typedef _Nodo * Nodo;
typedef _Pila * Pila;


// Prototipos
void inicializar(Pila*);
void push(Pila, char, int);
Nodo pop(Pila);
Nodo top(Pila);
int vacia(Pila);

// Metodos

void inicializar(Pila *p) {
	*p = (Pila)malloc(sizeof(_Pila));
}

void push(Pila p, char operador, int linea) {
	Nodo nodo = (Nodo)malloc(sizeof(_Nodo));
	nodo->operador = operador;
	nodo->linea = linea;
	nodo->siguiente = p->tope;
	p->tope = nodo;
}

Nodo pop(Pila p) {
	Nodo nodo = p->tope;
	if (nodo == NULL)
		return NULL;
		
	p->tope = nodo->siguiente;
	return nodo;
}

Nodo top(Pila p) {
	return p->tope;
}

int vacia(Pila p){
	if(p->tope == NULL)
		return 1;
	return 0;
}

void imprimirTodo(Pila p) {
	printf("\nImprimiendo pila --------------------------------------------------");
	Nodo aux = p->tope;
	while(aux) {
		printf("\n\tNodo: %p", aux);
		aux = aux->siguiente;
	}
	printf("\nTerminado ---------------------------------------------");
}
