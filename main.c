#include "funciones.h"
#include "vectores.h"

int main()
{
    tdaV vecIcc;
    tdaV vecItm;
    tdaV vecClasifIcc;
    tdaV vecClasifItm;
    tdaV vecMerge;

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

    crearClasificador(&vecIcc,&vecClasifIcc,selectorIcc);
    crearClasificador(&vecItm,&vecClasifItm,selectorItm);
    merge(&vecMerge,&vecClasifIcc,&vecClasifItm,fechaCmp,strCmpM);
    // vecMostrar(&vecIcc,(Imp)mostrarIcc);
    // vecMostrar(&vecClasifIcc,(Imp)mostrarIccClasif);
    // vecMostrar(&vecItm,(Imp)mostrarItm);
    // vecMostrar(&vecClasifItm,(Imp)mostrarIccClasif);
    vecMostrar(&vecMerge,(Imp)mostrarIccClasif);

    vecEliminar(&vecClasifIcc);
    vecEliminar(&vecClasifItm);
    vecEliminar(&vecMerge);

    return TODO_OK;
}
