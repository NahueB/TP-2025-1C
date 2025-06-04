#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "estructuras.h"
#include "constantes.h"
#include "vectores.h"

int btm(char* nArch,tdaV* vec);
int ttm(char* nArch,tdaV* vec,TxtAMem tipoTxt,DspNorm desencriptar,DspNorm normalizar);
void cambiarCxP(char* linea);
void crearClasificador(tdaV *vecInd,tdaV *vecClasif,Selec selector);
void merge(tdaV* vecMerge,tdaV* vecClasifIcc,tdaV* vecClasifItm,Cmp cmpF,Cmp cmpS);

#endif // FUNCIONES_H
