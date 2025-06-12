#ifndef MATRICES_H
#define MATRICES_H

void matDestruir(void** mat, int filas);
bool matCrear(tdaM* mat,size_t tamElem);
void matLLenar(tdaM* mat);
void matMostrar(tdaM* mat);

#endif // MATRICES_H
