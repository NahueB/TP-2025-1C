#include "funciones.h"
#include "vectores.h"

int main()
{
    tdaV vecIcc;
    tdaV vecItm;
    tdaV vecClasifIcc;
    tdaV vecClasifItm;
    tdaV vecMerge;
    tdaV vecVariacion;

    if(!vecCrear(&vecIcc,sizeof(icc)))
        return SIN_MEM;
    if(!vecCrear(&vecItm,sizeof(icc)))
        return SIN_MEM;
    if(!vecCrear(&vecMerge,sizeof(iccClasif)))
        return SIN_MEM;
    if(!vecCrear(&vecClasifIcc,sizeof(iccClasif)))
        return SIN_MEM;
    if(!vecCrear(&vecClasifItm,sizeof(iccClasif)))
        return SIN_MEM;
    if(!vecCrear(&vecVariacion,sizeof(variacion)))
        return SIN_MEM;

    if(ttm("indices_icc_general_capitulos.csv",&vecIcc,(TxtAMem)iccTxt,(DspNorm)desencriptarIcc,(DspNorm)normalizarIcc)!=TODO_OK)
    {
        printf("ERROR DESCARGANDO LOS DATOS");
        return SIN_MEM;
    }
    if(ttm("Indices_items_obra.csv",&vecItm,(TxtAMem)iccTxt,(DspNorm)desencriptarItm,(DspNorm)normalizarItm)!=TODO_OK)
    {
        printf("ERROR DESCARGANDO LOS DATOS");
        return SIN_MEM;
    }

//    vecMostrar(&vecIcc,(Imp)mostrarIcc);
//    vecMostrar(&vecItm,(Imp)mostrarItm);

    crearClasificador(&vecIcc,&vecClasifIcc,selectorIcc);// WARNING: ESTA FUNCION ELIMINA LOS VECTORES EN ARG[0]
    crearClasificador(&vecItm,&vecClasifItm,selectorItm);// WARNING: ESTA FUNCION ELIMINA LOS VECTORES EN ARG[0]

    merge(&vecMerge,&vecClasifIcc,&vecClasifItm,fechaCmp,strCmpM);


//    vecMostrar(&vecClasifIcc,(Imp)mostrarIccClasif);
//    vecMostrar(&vecClasifItm,(Imp)mostrarIccClasif);
//    vecMostrar(&vecMerge,(Imp)mostrarIccClasif);

    variacionMensual(&vecMerge,&vecVariacion);
    vecMostrar(&vecVariacion,(Imp)mostrarVariacion);

    vecEliminar(&vecClasifIcc);
    vecEliminar(&vecClasifItm);
//    vecEliminar(&vecMerge);
    vecEliminar(&vecVariacion);

    return TODO_OK;
}

//int main()
//{
//    tdaM mat;
//
//    if(!matCrear(&mat,sizeof(int)))
//        return SIN_MEM;
//    matLLenar(&mat);
//    matMostrar(&mat);
//    matDestruir(&mat);
//}
