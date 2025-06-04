#ifndef VECTORES_H
#define VECTORES_H

#include "estructuras.h"
#include "constantes.h"

bool vecCrear(tdaV* vec,size_t tamElem);
void vecEliminar(tdaV* vec);
int vecAumentar(tdaV* vec);
int vecInsOrd(tdaV* vec,void* elem,Cmp cmp);
int vecInsFin(tdaV* vec,void* elem);
void vecMostrar(tdaV* vec,Imp imp);

#endif // VECTORES_H
