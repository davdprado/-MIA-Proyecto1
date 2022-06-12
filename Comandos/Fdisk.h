#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <ctime>
#include <sstream>
#include <cstdio>
#include <iomanip>
#include <list>

#include <filesystem>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Mkdisk.h"
#include "../Estructuras/Estructuras.h"
using namespace std;

void efeDisk(char *tokens)
{
    string path = "";
    int tam = 0;
    string u = "k";
    string type = "p";
    string fit = "wf";
    string name = "";
    string delette = "";
    int agregar = 0;
    bool banderaCreate = true;
    bool banderaDelete = false;
    bool banderaCustom = false;
    vector<string> params = split(tokens, "$");
    // separar los obligatorios de los opcionales y unirlos
    // como quien dice juntos pero no revueltos
    for (auto &&ite : params)
    {
        vector<string> newparam = split(ite, "@");
        for (auto &&opcionales : newparam)
        {
            params.push_back(opcionales);
        }
    }

    for (auto &&parametro : params)
    {
        char *str_aux = strdup(parametro.c_str());
        char *newtoken = strtok(str_aux, "=>");
        // cout << "Parametro: " << newtoken;
        // cout << " Valor: " << newtoken << endl;
        if (strcasecmp(newtoken, "path") == 0)
        {
            // tomar el dato de path
            newtoken = strtok(NULL, ">");
            // obtener el path
            path = newtoken;
            // quitar las comillas al inicio y final
            // path.erase(path.begin());
            // path.erase(path.size() - 1);
        }
        else if (strcasecmp(newtoken, "size") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            tam = atoi(newtoken);
            if (tam <= 0)
            {
                cout << "El size debe de ser <= 0" << endl;
                return;
            }
        }
        else if (strcasecmp(newtoken, "name") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            name = newtoken;
        }
        else if (strcasecmp(newtoken, "unit") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            u = newtoken;
        }
        else if (strcasecmp(newtoken, "type") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            type = newtoken;
        }
        else if (strcasecmp(newtoken, "fit") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            fit = newtoken;
        }
        else if (strcasecmp(newtoken, "delete") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            delette = newtoken;
            banderaDelete = true;
            banderaCreate = false;
        }
        else if (strcasecmp(newtoken, "add") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            agregar = atoi(newtoken);
            banderaCustom = true;
            banderaCreate = false;
        }
        else
        {
            cout << "El parametro [" << newtoken << "] no es reconocido por FDISK" << endl;
            return;
        }
    }
    if (path == "" || name == "")
    {
        cout << "ERROR: Parametro [path/name] obligatorio no encontrado" << endl;
        return;
    }
    // validaremos la accion que queremos realizar mediante los parametros
    if ((banderaDelete && banderaCustom) || (banderaCustom && banderaCreate) || (banderaDelete && banderaCreate))
    {
        // no pueden existir las dos acciones juntas en el mismo comando asi que es un error
        cout << "ERROR: no puede existir parametro delete y add en el mismo comando" << endl;
        return;
    }
    if (banderaCreate)
    {
        // aqui va el crear una particion
        // CrearParticion(path, u, tam, name, type, fit);
    }
    else if (banderaCustom)
    {
        // aqui va el add
    }
    else if (banderaDelete)
    {
        // aqui va el delete
        // EliminarParticion(path, name, delette);
    }
}