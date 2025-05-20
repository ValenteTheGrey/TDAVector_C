#ifndef TDAVECTOR_VECTOR_H
#define TDAVECTOR_VECTOR_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>

#define CAP_INI 10
#define FACTOR_INCR 1.5
#define FACTOR_OCUP 0.25
#define FACTOR DECR 0.5 // < 1

#define TODO_OK 0
#define SIN_MEM 1
#define DUPLICADO 2

typedef struct
{
    void* vec;
    size_t ce;
    size_t cap;
    size_t tamElem;
}Vector;

typedef struct
{
    void* primero;
    void* actual;
    void* ultimo;
    size_t tamElem;
}VectorIterador;

typedef int (*Cmp)(const void* a, const void* b);
typedef void (*Action)(void*, void*);
typedef void (*Imprimir)(const void* a);

bool vectorCrear(Vector* vector, size_t tamElem);
void vectorInsertarRandom(Vector* vector, int ce, int digitos);
int vectorOrdBuscar(const Vector* vector, void* elem, Cmp cmp);
int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp);
int vectorOrdInsertar2(Vector* vector, const void* elem, Cmp cmp);
int vectorInsertarAlFinal(Vector* vector, const void* elem);
void vectorDestruir(Vector* vector);
bool vectorOrdEliminarElem(Vector* vector, void* elem,Cmp cmp);
void vectorVaciar(Vector* vector);
void vectorOrdenarSeleccion(Vector* vector, Cmp cmp);
void intercambiar(void* a, void* b, size_t tamElem);
void vectorItCrear(VectorIterador* vectorIt, Vector* vector);
void* vectorItPrimero(VectorIterador* vectorIt);
void* vectorItSiguiente(VectorIterador* vectorIt);
bool vectorItFin(VectorIterador* vectorIt);
int cmpInt(const void* a, const void* b);
void vectorMostrarInt(Vector* vector);
void vectorItRecorrer(VectorIterador* vectorIt, Action accion, void* datos);
void imprimirInt(void* e, void* ptFILE);
void vectorMostrar(const Vector* vector, Imprimir imprimir);


#endif //TDAVECTOR_VECTOR_H
