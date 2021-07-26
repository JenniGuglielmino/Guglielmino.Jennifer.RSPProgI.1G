#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char marca[20];
    int tipo;
    float peso;
} eVehiculo;
eVehiculo* vehiculo_new();
eVehiculo* vehiculo_newParametros(char* idStr,char* marca,char* tipo, char* pesoStr);
int vehiculo_setId(eVehiculo* this, int id);
int vehiculo_setMarca(eVehiculo* this,char* marca);
int vehiculo_setTipo(eVehiculo* this,int tipo);
int vehiculo_setPeso(eVehiculo* this, float peso);
int vehiculo_delete(eVehiculo* this);
int controller_saveAsText(eVehiculo* vehiculo);
int controller_saveAsBinary(eVehiculo* vehiculo);
eVehiculo* vehiculoTest = NULL;

int main()
{
    vehiculoTest = vehiculo_newParametros("1","Nissan","Tiida","1300");
    controller_saveAsBinary(vehiculoTest);
    controller_saveAsText(vehiculoTest);
    system("pause");
    return 0;
}

eVehiculo* vehiculo_new()
{
    eVehiculo* nuevoVehiculo = (eVehiculo*)malloc(sizeof(eVehiculo));
    if(nuevoVehiculo != NULL)
    {
        nuevoVehiculo->id = 0;
        strcpy(nuevoVehiculo->marca, " ");
        nuevoVehiculo->tipo = 0;
        nuevoVehiculo->peso = 0;
    }
    return nuevoVehiculo;
}

eVehiculo* vehiculo_newParametros(char* idStr,char* marca,char* tipo, char* pesoStr)
{
    eVehiculo* nuevoVehiculo = vehiculo_new();
    if(nuevoVehiculo != NULL)
    {
        if(!(vehiculo_setId(nuevoVehiculo, atoi(idStr))
                && vehiculo_setMarca(nuevoVehiculo, marca)
                && vehiculo_setTipo(nuevoVehiculo, atoi(tipo))
                && vehiculo_setPeso(nuevoVehiculo, strtof(pesoStr, NULL))))
        {
            vehiculo_delete(nuevoVehiculo);
            nuevoVehiculo = NULL;
        }
    }
    return nuevoVehiculo;
}

int vehiculo_setId(eVehiculo* this, int id)
{
    int todoOk=0;
    if(this != NULL && id > 0)
    {
        this->id = id;
        todoOk = 1;
    }
    return todoOk;
}

int vehiculo_setMarca(eVehiculo* this,char* marca)
{
    int todoOk=0;
    if(this != NULL && marca != NULL && strlen(marca) > 2 && strlen(marca) < 129)
    {
        strcpy(this->marca, marca);
        todoOk = 1;
    }
    return todoOk;
}

int vehiculo_setTipo(eVehiculo* this,int tipo)
{
    int todoOk=0;
    if(this != NULL && tipo >= 0)
    {
        this->tipo = tipo;
        todoOk = 1;
    }
    return todoOk;
}

int vehiculo_setPeso(eVehiculo* this, float peso)
{
    int todoOk=0;
    if(this != NULL && peso >= 0)
    {
        this->peso = peso;
        todoOk = 1;
    }
    return todoOk;
}

int vehiculo_delete(eVehiculo* this)
{
    int todoOk=0;
    if(this != NULL)
    {
        free(this);
        todoOk = 1;
    }
    return todoOk;
}


int controller_saveAsText(eVehiculo* vehiculo)
{
    int todoOk = 0;
    char confirma = 's';
    char path[128] = "archivoDeTexto.txt";
    int flagError = 0;
    eVehiculo* auxEmp = vehiculo_new();
    FILE* f = NULL;
    f = fopen(path, "r");
    fclose(f);
    if(confirma == 's')
    {
        f = fopen(path, "w");
        if(f == NULL)
        {
            printf("Error!!! --> No se pudo abrir el archivo\n");
        }
        else
        {
            fprintf(f, "id,marca,tipo,peso\n");

            auxEmp = vehiculo;
            fprintf(f, "%d,%s,%d,%.2f\n", auxEmp->id,auxEmp->marca,auxEmp->tipo,auxEmp->peso);//ree
        }
        fclose(f);
    }
    if(flagError)
    {
        printf("Error!!! --> Ocurrio un problema al guardar los empleados en el archivo\n");
    }
    else
    {
        todoOk = 1;
    }
    return todoOk;
}

int controller_saveAsBinary(eVehiculo* vehiculo)
{
    int todoOk= 0;
    int cant;
    char path[128] = "archivoBinario.bin";
    eVehiculo * auxEmp = NULL;
    int flag = 0;
    FILE* f = NULL;
    char confirma = 's';
    f = fopen(path, "rb");
    fclose(f);
    if(confirma == 's')
    {
        f = fopen(path,"wb");
        if(f == NULL)
        {
            printf("Error!!! --> No se pudo abrir el archivo\n");
        }
        else
        {
                    auxEmp = vehiculo;
                    cant = fwrite(auxEmp, sizeof(eVehiculo), 1, f);
                    if(cant < 1)
                    {
                        flag = 1;
                    }


        }
        fclose(f);
    }

    if(flag)
    {
        printf("Error!!! --> Ocurrio un problema al guardar los empleados en el archivo\n");
    }
    else
    {
        todoOk= 1;
    }

    return todoOk;
}

