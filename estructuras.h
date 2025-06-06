#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    int ce;
    int cap;
    size_t tamElem;
    void* elem;
}tdaV;

typedef struct
{
    int ce;
    int cap;
    int filas;
    int columnas;
    size_t tamElem;
    void* mat;
}tdaM;

typedef struct
{
    int dia;
    int mes;
    int anio;
}Fecha;

typedef struct
{
    Fecha fecha;
    char NGyA[50];
    double indice;
}icc;

typedef struct
{
    icc indice;
    char clasificador[50];
}iccClasif;

typedef void (*Imp)(const void*);
typedef int (*TxtAMem)(char*,void*,void*,void*);
typedef int (*Cmp)(const void*, const void*);
typedef void (*DspNorm)(char*);
typedef void (*Selec)(iccClasif*);

void mostrarIcc(const void* elem);
void mostrarItm(const void* elem);
void mostrarIccClasif(const void* elem);
int iccTxt(char* linea,void* elem,DspNorm desencriptar,DspNorm normalizar);
void desencriptarIcc(char* token);
void desencriptarItm(char* token);
void normalizarIcc(char* token);
void normalizarItm(char* token);
void selectorIcc(iccClasif* auxClasif);
void selectorItm(iccClasif* auxClasif);
int fechaCmp(const void* e1,const void* e2);
int strCmpM(const void* e1,const void* e2);

#endif // ESTRUCTURAS_H
