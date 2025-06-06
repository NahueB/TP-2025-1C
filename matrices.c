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
//
//void matrizDestruir(void** mat, int filas)
//{
//    void** ult = mat + filas - 1;
//
//    for(void** i = mat; i <= ult; i++) {
//        free(*i);
//    }
//
//    free(mat);
//}

//void matrizReAsignar(size_t tamElem)
