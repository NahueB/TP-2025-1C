#include "funciones.h"
#include "vectores.h"
#include "estructuras.h"
#include "constantes.h"

bool vecCrear(tdaV* vec,size_t tamElem)
{
    vec->cap=10;
    vec->elem=malloc(tamElem*10);

    if(!vec->elem)
        return false;

    vec->ce=0;
    vec->tamElem=tamElem;

    return true;
}

void vecEliminar(tdaV* vec)
{
    vec->cap=0;
    vec->ce=0;
    vec->tamElem=0;
    free(vec->elem);
    vec->elem=NULL;
}

int vecAumentar(tdaV* vec)
{
    int nCap = vec->cap*1.5;
    void* nVec = realloc(vec->elem,nCap*vec->tamElem);
    if(!nVec)
        return SIN_MEM;

    vec->cap = nCap;
    vec->elem = nVec;

    return TODO_OK;
}

int vecInsOrd(tdaV* vec,void* elem,Cmp cmp)
{
    if(vec->cap==vec->ce)
        if(vecAumentar(vec)!=TODO_OK)
            return SIN_MEM;
    void* posIns = vec->elem;
    void* ult = vec->elem + (vec->ce-1) * vec->tamElem;

    while(posIns <= ult && cmp(posIns,elem) > 0)
        posIns += vec->tamElem;

    if(posIns <= ult && cmp(posIns,elem)==0)
        return SIN_MEM;

    for(void* i = ult; i >= posIns; i -= vec->tamElem)
        memcpy(i + vec->tamElem, i, vec->tamElem);

    memcpy(posIns,elem,vec->tamElem);
    vec->ce++;
    return TODO_OK;
}

int vecInsFin(tdaV* vec,void* elem)
{
    if(vec->ce == vec->cap)
        if(vecAumentar(vec)!= TODO_OK)
            return SIN_MEM;

    void* posIns = vec->elem + vec->ce * vec->tamElem;
    memcpy(posIns, elem, vec->tamElem);
    vec->ce++;

    return TODO_OK;
}

void vecMostrar(tdaV* vec,Imp imp)
{
    void* ult = vec->elem + (vec->ce-1)*vec->tamElem;

    for(void* i = vec->elem; i <= ult; i += vec->tamElem)
    {
        imp(i);
        putchar('\n');
    }

    puts("\n=================================================================================================================\n");
}

void mostrarIcc(const void* elem)
{
    const icc* Icc = elem;
    printf("%04d-%02d-%02d | %40s | %4.8f",Icc->fecha.anio,Icc->fecha.mes,Icc->fecha.dia,Icc->NGyA,Icc->indice);
}

void mostrarItm(const void* elem)
{
    const icc* Icc = elem;
    printf("%04d-%02d-%02d | %40s | %4.8f",Icc->fecha.anio,Icc->fecha.mes,Icc->fecha.dia,Icc->NGyA,Icc->indice);
}

void mostrarIccClasif(const void* elem)
{
    const iccClasif* e = elem;
    printf("%04d-%02d-%02d | %40s | %4.8f | %20s",e->indice.fecha.anio,e->indice.fecha.mes,e->indice.fecha.dia,e->indice.NGyA,e->indice.indice,e->clasificador);
}

void mostrarVariacion(const void* elem)
{
    const variacion* e = elem;
    printf("%04d-%02d-%02d | %40s | %4.8f | %20s",e->indice.indice.fecha.anio,e->indice.indice.fecha.mes,e->indice.indice.fecha.dia,e->indice.indice.NGyA,e->indice.indice.indice,e->indice.clasificador);
    if(e->mensual != 0)
        printf("| %4.2f ",e->mensual);
    else
        printf("| N/A ");
    if(e->anual != 0)
        printf("| %4.2f",e->anual);
    else
        printf("| N/A");
}

