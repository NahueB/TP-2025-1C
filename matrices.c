#include "funciones.h"
#include "matrices.h"
#include "estructuras.h"
#include "constantes.h"

//QUIERO CREAR UNA MATRIZ QUE SE PUEDA REALOCAR LA MEMORIA
//IMPLICA QUE AL CREARLA SEA GENERICA, ES DECIR FILAS Y COLUMNAS
//ME TENGO QUE BASAR EN EL TDAVector
//void** matrizCrear(size_t tamElem)
//{
//    void** mat = (void**)malloc(sizeof(void*) * filas);
//
//    if (!mat)
//        return NULL;
//
//    void** ult = mat + filas - 1;
//
//    for (void** i = mat; i <= ult; i++) {
//        *i = malloc(tamElem * columnas);
//
//        if (!*i) {
//            matrizDestruir(mat, i - mat);
//            return NULL;
//        }
//    }
//
//    return mat;
//}

void matDestruir(void** mat, int filas)
{
    void** ult = mat + filas - 1;

    for(void** i = mat; i <= ult; i++) {
        free(*i);
    }

    free(mat);
}

//void matrizReAsignar(size_t tamElem)
//{
//
//}

bool matCrear(tdaM* mat,size_t tamElem)
{
    mat->ce = 0;
    mat->filas= 10;
    mat->columnas = 10;
    mat->tamElem = tamElem;
    mat->cap = mat->filas*mat->columnas;
    mat->mat = (void**)malloc(sizeof(void*)*mat->filas);

    void** ult = mat->mat + mat->filas;

    for(void** i = mat->mat;i < ult;i++)
    {
        *i = malloc(tamElem*mat->columnas);

        if(!*i)
        {
            matDestruir(mat->mat,i-mat->mat);
            return false;
        }
    }
    return true;
}

void matLLenar(tdaM* mat)
{
    int** matriz = (int**)mat->mat;
    for(int i = 0; i < mat->filas; i++) {
      for(int j = 0; j < mat->columnas; j++)
      {
        matriz[i][j]=j;
      }
    }
}

void matMostrar(tdaM* mat)
{
    int** matriz = (int**)mat->mat;
    for(int i = 0; i < mat->filas; i++) {
      for(int j = 0; j < mat->columnas; j++)
      {
        printf("%d|",matriz[i][j]);
      }
      puts("");
    }
}
