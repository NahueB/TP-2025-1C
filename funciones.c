#include "funciones.h"
#include "vectores.h"

int btm(char* nArch,tdaV* vec)
{
    FILE* fp = fopen(nArch,"rb");
    if(!fp)
    {
        printf("ERROR LEYENDO ARCHIVO %s\n",nArch);
        fclose(fp);
        exit(1);
        return ERROR_ARCH;
    }

    void* elem = malloc(vec->tamElem);
    if(!elem)
    {
        printf("ERROR SIN MEMORIA\n");
        free(elem);
        fclose(fp);
        exit(1);
        return SIN_MEM;
    }

    fread(elem,vec->tamElem,1,fp);

    while(!feof(fp))
    {
        //vecInsOrd(elem,vec,cmp);
        if(vecInsFin(vec,elem)!=TODO_OK)
        {
            printf("ERROR GUARDANDO ELEMENTO\n");
            fclose(fp);
            exit(1);
            return SIN_MEM;
        }
        fread(elem,vec->tamElem,1,fp);
    }

    free(elem);
    fclose(fp);
    return TODO_OK;
}

int ttm(char* nArch,tdaV* vec,TxtAMem tipoTxt,DspNorm desencriptar,DspNorm normalizar)
{
    FILE* fp = fopen(nArch,"rt");
    if(!fp)
    {
        printf("ERROR LEYENDO ARCHIVO %s\n",nArch);
        fclose(fp);
        exit(1);
        return ERROR_ARCH;
    }

    void* elem = malloc(vec->tamElem);
    char linea[TAM_LINEA];
    int ret = TODO_OK;
    if(!elem)
    {
        printf("ERROR SIN MEMORIA\n");
        free(elem);
        fclose(fp);
        exit(1);
        return SIN_MEM;
    }

    fgets(linea,TAM_LINEA,fp);

    while(fgets(linea,TAM_LINEA,fp)!=NULL)
    {
        ret = tipoTxt(linea,elem,desencriptar,normalizar);
        if(vecInsFin(vec,elem)!=TODO_OK || ret!=TODO_OK)
        {
            printf("ERROR GUARDANDO ELEMENTO\n");
            fclose(fp);
            exit(1);
            return SIN_MEM;
        }
    }

    free(elem);
    fclose(fp);
    return TODO_OK;
}

int iccTxt(char* linea,void* elem,DspNorm desencriptar,DspNorm normalizar)
{
    cambiarCxP(linea);
    icc* e = (icc*)elem;
    char* token = strchr(linea,'\n');
    *token='\0';
    token = strrchr(linea,';');
    sscanf(token+1,"%lf",&e->indice);
    token--;
    *token='\0';
    token = strrchr(linea,';');
    strncpy(e->NGyA,token+2,sizeof(e->NGyA)/sizeof(*e->NGyA));
    token--;
    *token='\0';
    sscanf(linea+1,"%d/%d/%d",&e->fecha.dia,&e->fecha.mes,&e->fecha.anio);
    desencriptar(e->NGyA);
    normalizar(e->NGyA);
    return TODO_OK;
}

void cambiarCxP(char* linea)
{
    char* aux = strchr(linea,',');
    if(aux!=NULL)
        *aux='.';
}

void desencriptarIcc(char* token)
{
    int cant = 0;
    int dif;
    while(*token!='\0')
    {
        if((cant%2)==0 && (*token>='a' && *token<='z'))
        {
            *token+=4;
            dif = *token-122;
            if(*token>'z')
            {
                *token=96+dif;
            }
        }
        if((cant%2)!=0 && (*token>='a' && *token<='z'))
        {
            *token+=2;
            dif = *token-122;
            if(*token>'z')
            {
                *token=96+dif;
            }
        }
        token++;
        cant++;
    }
}

void desencriptarItm(char* token)
{
    while(*token!='\0')
    {
        switch(*token)
        {
        case '@':
            *token='a';
            break;
        case '8':
            *token='b';
            break;
        case '3':
            *token='e';
            break;
        case '1':
            *token='i';
            break;
        case '0':
            *token='o';
            break;
        case '$':
            *token='s';
            break;
        case '7':
            *token='t';
            break;
        case '|':
            *token='l';
            break;
        case '5':
            *token='m';
            break;
        case '9':
            *token='n';
            break;
        }
        token++;
    }
}

void normalizarIcc(char* token)
{
    bool flag = true;
    while(*token!='\0')
    {
        if(flag)
        {
            *token=(*token)-32;
            flag=false;
        }
        if(*token=='_')
            *token=' ';
        token++;
    }
}

void normalizarItm(char* token)
{
    char* guion = strchr(token, '_');
    char* auxToken = token;
    if(guion != NULL)
    {
        // Quitar todo lo anterior al primer guión bajo
        memmove(token, guion + 1, strlen(guion));
        // Quitar todos los guiones bajos posteriores
        char* pos = token;
        while(*pos != '\0')
        {
            if(*pos == '_')
            {
                *pos = ' '; // Reemplazar guión bajo por espacio
            }
            pos++;
        }
    }
    // Colocar la primera letra en mayúscula
    if(auxToken != '\0')
    {
        *auxToken = *auxToken-32;
    }
}

void crearClasificador(tdaV *vecInd,tdaV *vecClasif,Selec selector)
{
    icc *auxInd = vecInd->elem;
    icc *auxult = vecInd->elem + vecInd->ce * vecInd->tamElem;

    void* elem = malloc(vecClasif->tamElem);
    iccClasif* auxClasif = elem;

    while (auxInd < auxult)
    {
        auxClasif->indice.fecha.anio = auxInd->fecha.anio;
        auxClasif->indice.fecha.mes = auxInd->fecha.mes;
        auxClasif->indice.fecha.dia = auxInd->fecha.dia;
        strcpy (auxClasif->indice.NGyA,auxInd->NGyA);
        auxClasif->indice.indice= auxInd->indice;

        selector(auxClasif);

        vecInsFin(vecClasif,elem);
        auxInd++;
    }
}

void selectorIcc(iccClasif* auxClasif)
{
    if (strcmpi(auxClasif->indice.NGyA,"Nivel general") == 0)
        strcpy (auxClasif->clasificador,"Nivel general");
    else
        strcpy (auxClasif->clasificador,"Capitulos");
}

void selectorItm(iccClasif* auxClasif)
{
    strcpy(auxClasif->clasificador,"Items");
}

void merge(tdaV* vecMerge,tdaV* vecClasifIcc,tdaV* vecClasifItm)
{
    void* posIcc = vecClasifIcc->elem;
    void* posItm = vecClasifItm->elem;
    void* ultIcc = vecClasifIcc->elem + (vecClasifIcc->tamElem*(vecClasifIcc->ce - 1));
    void* ultItm = vecClasifItm->elem + (vecClasifItm->tamElem*(vecClasifItm->ce - 1));
    iccClasif* elemIcc = (iccClasif*)posIcc;
    iccClasif* elemItm = (iccClasif*)posItm;

    while(posIcc!=ultIcc || posItm!=ultItm)
    {
        if()
    }
}
