#include "Vector.h"



bool _vectorOrdBuscar(const Vector* vector, const void* elem, void** pos, Cmp cmp);
bool _vectorOrdBuscarBinario(const Vector* vector, const void* elem, void** pos, Cmp cmp);
int _ampliarCapVector(Vector* vector);
void* _buscarMenor(void* ini, void* fin, size_t tamElem, Cmp cmp);


bool vectorCrear(Vector* vector, size_t tamElem)
{
    vector->vec = malloc(CAP_INI * tamElem);

    if(!vector->vec)
        return false;

    vector->ce = 0;
    vector->cap = CAP_INI;
    vector->tamElem = tamElem;

    return true;
}


void vectorInsertarRandom(Vector* vector, int ce, int numMayor)
{
    srand(time(NULL));

    int e;

    for(int i = 1; i <= ce; i++) {
        e = rand() % (numMayor + 1);
        vectorInsertarAlFinal(vector, &e);
    }
}


int vectorOrdBuscar(const Vector* vector, void* elem, Cmp cmp)
{
    void* pos;
    bool existe = _vectorOrdBuscar(vector, elem, &pos, cmp);

    if(existe)
        memcpy(elem, pos, vector->tamElem); //copia el elemento entero (ej Empleado) al elem usado (ej Legajo)

    return existe ? (pos - vector->vec) / vector->tamElem : -1;         //devuelve la posicion del elemento
}


bool _vectorOrdBuscar(const Vector* vector, const void* elem, void** pos, Cmp cmp)
{
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;
    void* i = vector->vec;

    while( i <= ult && cmp(elem, i) > 0)
        i += vector->tamElem;

    *pos = i;

    return i <= ult && cmp(elem, i) == 0;
}

bool _vectorOrdBuscarBinario(const Vector* vector, const void* elem, void** pos, Cmp cmp)
{
    char* li = (char*)vector->vec;
    char* ls = (char*)vector->vec + (vector->ce - 1) * vector->tamElem;
    char* m;

    while(li <= ls)
    {
        m = li + ((ls - li) / vector->tamElem / 2) * vector->tamElem;

        int cmpRes = cmp(m, elem);

        if(cmpRes == 0) {
            *pos = m;
            return true;
        }
        else if(cmpRes < 0){
            li = m + vector->tamElem;
        }
        else{
            ls = m - vector->tamElem;
        }
    }

    *pos = li;  // posición donde debería insertarse si no se encuentra

    return false;

}


int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp)
{
    if(vector->ce == 0)
    {
        memcpy(vector->vec, elem, vector->tamElem);
        return TODO_OK;
    }
    
    if(vector->ce == vector->cap)
    {
        if(!_ampliarCapVector(vector))
            return SIN_MEM;
    }

    void* posIns;
    bool existe = _vectorOrdBuscar(vector, elem, &posIns, cmp);

    if(existe)
        return DUPLICADO;

    for(void* i = vector->vec + (vector->ce - 1) * vector->tamElem; i >= posIns; i -= vector->tamElem)
        memcpy(i + vector->tamElem, i, vector->tamElem);

    memcpy(posIns, elem, vector->tamElem);
    vector->ce++;

    return TODO_OK;
}

int vectorOrdInsertar2(Vector* vector, const void* elem, Cmp cmp)
{
    if(vector->ce == 0)
    {
        memcpy(vector->vec, elem, vector->tamElem);
        return TODO_OK;
    }
    
    if(vector->ce == vector->cap)
    {
        if(!_ampliarCapVector(vector))
            return SIN_MEM;
    }

    void* posIns;
    bool existe = _vectorOrdBuscarBinario(vector, elem, &posIns, cmp);

    if(existe)
        return DUPLICADO;

    for(void* i = vector->vec + (vector->ce - 1) * vector->tamElem; i >= posIns; i -= vector->tamElem)
        memcpy(i + vector->tamElem, i, vector->tamElem);

    memcpy(posIns, elem, vector->tamElem);
    vector->ce++;

    return TODO_OK;
}

int _ampliarCapVector(Vector* vector)
{
    size_t nCap = vector->cap * FACTOR_INCR;
    void* nVec = realloc(vector->vec, nCap * vector->tamElem);

    if(!nVec)
        return SIN_MEM;

    vector->vec = nVec;
    vector->cap = nCap;

    return TODO_OK;
}


int vectorInsertarAlFinal(Vector* vector, const void* elem)
{
    if(vector->ce == vector->cap)
    {
        if(_ampliarCapVector(vector) == SIN_MEM)
            return SIN_MEM;
    }

    void* posIns = vector->vec + vector->ce * vector->tamElem;
    memcpy(posIns, elem, vector->tamElem);
    vector->ce++;

    return TODO_OK;
}


void vectorDestruir(Vector* vector)
{
    free(vector->vec);
    vector->vec = NULL;
}


bool vectorOrdEliminarElem(Vector* vector, void* elem,Cmp cmp)
{
    void* posElim;
    bool existe = _vectorOrdBuscar(vector, elem, &posElim, cmp);

    if(!existe)
        return false;

    //TERMINAR LA FUNCION
    void* ult = vector->vec + (vector->ce -1) * vector->tamElem;
    for(void* i = posElim; i <= ult; i += vector->tamElem)
        memcpy(i, i + vector->tamElem, vector->tamElem);

    vector->ce--;
    return true;
}


void vectorVaciar(Vector* vector)
{
    vector->cap = CAP_INI;
    vector->ce = 0;
    vector->vec = realloc(vector->vec, CAP_INI * vector->tamElem);
}


void vectorOrdenarSeleccion(Vector* vector, Cmp cmp)
{
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;
    void* m;
    for(void* i = vector->vec; i < ult; i += vector->tamElem)
    {
        m = _buscarMenor(i, ult, vector->tamElem, cmp);
        intercambiar(m, i, vector->tamElem);
    }
}


void* _buscarMenor(void* ini, void* fin, size_t tamElem, Cmp cmp)
{
    void* m = ini;

    for(void* j = ini + tamElem; j <= fin; j += tamElem)
    {
        if(cmp(j, m) < 0)
            m = j;
    }
    return m;
}


void _buscarMenoryMayor(void* ini, void* fin, void** pDMenor, void** pDMayor, size_t tamElem, Cmp cmp)
{
    //ver video Archivos 3:24
}


void intercambiar(void* a, void* b, size_t tamElem)
{
    void* aTemp = malloc(tamElem);

    memcpy(aTemp, a, tamElem);
    memcpy(a, b, tamElem);
    memcpy(b, aTemp, tamElem);

    free(aTemp);
}


void vectorItCrear(VectorIterador* vectorIt, Vector* vector)
{
    vectorIt->primero = vector->vec;
    vectorIt->actual = NULL;
    vectorIt->ultimo = vector->vec + (vector->ce - 1) * vector->tamElem;
    vectorIt->tamElem = vector->tamElem;
}


void* vectorItPrimero(VectorIterador* vectorIt)
{
    vectorIt->actual = vectorIt->primero;

    if(vectorIt->actual > vectorIt->ultimo)
        return NULL;

    return vectorIt->actual;
}


void* vectorItSiguiente(VectorIterador* vectorIt)
{
    if(!vectorIt->actual)
        return NULL;

    vectorIt->actual += vectorIt->tamElem;

    if(vectorIt->actual > vectorIt->ultimo)
        return NULL;

    return vectorIt->actual;
}


bool vectorItFin(VectorIterador* vectorIt)
{
    return vectorIt->actual > vectorIt->ultimo;
}


int cmpInt(const void* a, const void* b)
{
    int x = *(const int*)a;
    int y = *(const int*)b;

    return x-y;
}


void vectorMostrarInt(Vector* vector)
{
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;

    for(void* i = vector->vec; i <= ult; i += vector->tamElem)
    {
        printf("%d ", *(int*)i);
    }
}

void vectorItRecorrer(VectorIterador* vectorIt, Action accion, void* datos)
{
    for(void* i = vectorIt->primero; i <= vectorIt->ultimo; i += vectorIt->tamElem)
    {
        accion(i, datos);
    }
}


void imprimirInt(void* e, void* ptFILE) //datosA puntero a file donde imprimir
{
    int* i = e;
    FILE* arch = ptFILE;

    fprintf(arch, "%d\n", *i);
}

void vectorMostrar(const Vector* vector, Imprimir imprimir)
{
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;

    for(void* i = vector->vec; i <= ult; i += vector->tamElem)
    {
        imprimir(i);
    }

    putchar('\n');
}
