#include "listadl.h"

dllista *crear_elemento(DATO dato) {
    dllista *nuevo = (dllista *)malloc(sizeof(dllista));
    if (nuevo == NULL)
        return NULL;
    nuevo->dato = dato;
    nuevo->previo = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

ListaDL *crear_lista(void) {
    ListaDL *lista = (ListaDL *)malloc(sizeof(ListaDL));
    if (lista == NULL)
        return NULL;
    lista->cabeza = NULL;
    lista->longitud = 0;
    return lista;
}

void insertar_inicio(ListaDL *lista, DATO dato) {
    dllista *nuevo = crear_elemento(dato);
    if (nuevo == NULL)
        return;

    if (lista->cabeza == NULL) {
        lista->cabeza = nuevo;
		nuevo->siguiente=nuevo;
		nuevo->previo=nuevo;
    } else {
		nuevo->siguiente = lista->cabeza;
		nuevo->previo=lista->cabeza->previo;
		lista->cabeza->previo->siguiente= nuevo;
		lista->cabeza->previo=nuevo;
		lista->cabeza = nuevo;
    }
    lista->longitud++;
}

void insertar_final(ListaDL *lista, DATO dato) {
    dllista *nuevo = crear_elemento(dato);
    if (nuevo == NULL)
        return;

    if (lista->cabeza == NULL) {
        lista->cabeza = nuevo;
	nuevo->siguiente= nuevo;
	nuevo->previo=nuevo;
    } else {
        dllista *actual = lista->cabeza->previo;
        actual->siguiente = nuevo;
        nuevo->previo = actual;
		nuevo->siguiente = lista->cabeza;
		lista->cabeza->previo=nuevo;
    }
    lista->longitud++;
}

void insertar_en_posicion(ListaDL *lista, DATO dato, int posicion) {
    if (posicion < 0 || posicion > lista->longitud)
        return;

    if (posicion == 0) {
        insertar_inicio(lista, dato);
        return;
    }
    if (posicion == lista->longitud) {
        insertar_final(lista, dato);
        return;
    }

    dllista *nuevo = crear_elemento(dato);
    if (nuevo == NULL)
        return;

    dllista *actual = lista->cabeza;
    for (int i = 0; i < posicion; i++)
        actual = actual->siguiente;

    nuevo->previo = actual->previo;
    nuevo->siguiente = actual;
    actual->previo->siguiente = nuevo;
    actual->previo = nuevo;
    lista->longitud++;
}

DATO eliminar_inicio(ListaDL *lista) {
    if (lista->cabeza == NULL)
        return -1;

    dllista *eliminado = lista->cabeza;
    DATO dato = eliminado->dato;

    if (lista->cabeza->siguiente == lista->cabeza) {
        lista->cabeza = NULL;
    } else {
	dllista *actual=lista->cabeza->previo;
    lista->cabeza = eliminado->siguiente;
    lista->cabeza->previo = actual;
	actual->siguiente=lista->cabeza;
	}
    free(eliminado);
    lista->longitud--;
    return dato;
}

DATO eliminar_final(ListaDL *lista) {
    if (lista->cabeza == NULL)
        return -1;

    dllista *actual = lista->cabeza->previo;

    DATO dato = actual->dato;

    if (actual == lista->cabeza) {
        lista->cabeza = NULL;
    } else {
        actual->previo->siguiente = lista->cabeza;
        lista->cabeza->previo=actual->previo;
    }

    free(actual);
    lista->longitud--;
    return dato;
}

DATO eliminar_en_posicion(ListaDL *lista, int posicion) {
    if (posicion < 0 || posicion >= lista->longitud)
        return -1;

    if (posicion == 0)
        return eliminar_inicio(lista);
    if (posicion == lista->longitud - 1)
        return eliminar_final(lista);

    dllista *actual = lista->cabeza;
    for (int i = 0; i < posicion; i++)
        actual = actual->siguiente;

    DATO dato = actual->dato;
    actual->previo->siguiente = actual->siguiente;
    actual->siguiente->previo = actual->previo;
    free(actual);
    lista->longitud--;
    return dato;
}

int buscar(ListaDL *lista, DATO dato) {
    if (lista->cabeza == NULL)
        return -1;
        
    dllista *actual = lista->cabeza;
    int posicion = 0;
    do{
        if (actual->dato == dato)
            return posicion;
        actual = actual->siguiente;
        posicion++;
    }while (actual != lista->cabeza) ;
    return -1;
}

DATO obtener(ListaDL *lista, int posicion) {
    if (posicion < 0 || posicion >= lista->longitud)
        return -1;

    dllista *actual = lista->cabeza;
    for (int i = 0; i < posicion; i++)
        actual = actual->siguiente;
    return actual->dato;
}

int esta_vacia(ListaDL *lista) {
    return lista->cabeza == NULL;
}

int longitud(ListaDL *lista) {
    return lista->longitud;
}

void imprimir_lista(ListaDL *lista) {
    if (lista->cabeza == NULL)
        return;
    dllista *actual = lista->cabeza;
    do{
        printf("[%d]", actual->dato);
        if (actual->siguiente != lista->cabeza)
            printf(" <-> ");
        actual = actual->siguiente;
    }while (actual != lista->cabeza);
    printf(" -> Retorno\n");
}

void imprimir_lista_reversa(ListaDL *lista) {
    if (lista->cabeza == NULL)
        return;
    dllista *actual = lista->cabeza->previo;
    do {
        printf("[%d]", actual->dato);
        if (actual->previo != lista->cabeza->previo)
            printf(" <-> ");
        actual = actual->previo;
    }while (actual != lista->cabeza->previo);
    printf(" -> Retorno\n");
}

void liberar_lista(ListaDL *lista) {
    if (lista->cabeza == NULL) {
        free(lista);
        return;
    }
    if (lista->cabeza != NULL) {
        dllista *actual = lista->cabeza->siguiente;
        while (actual != lista->cabeza) {
            dllista *temp = actual;
            actual = actual->siguiente;
            free(temp);
        }
        free(lista->cabeza);
    }
    free(lista);
}
