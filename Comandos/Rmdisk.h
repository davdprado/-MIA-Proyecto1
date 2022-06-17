#pragma once
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

#include <filesystem>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Mkdisk.h"
#include "../Estructuras/Estructuras.h"

using namespace std;

void EliminarDisk(char *tokens)
{
    string path = "";
    vector<string> params = split(tokens, "$");
    // limpiando parametros
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
        else
        {
            cout << "El parametro [" << newtoken << "] no es reconocido por RMDISK" << endl;
            return;
        }
    }

    string confirmacion = "";
    cout << "Desea eliminar el disco " << path << "? Y/N" << endl;
    cin >> confirmacion;
    if (confirmacion == "n" || confirmacion == "N")
    {
        cout << "Abortando mision de eliminacion" << endl;
        return;
    }

    try
    {
        path.erase(path.begin());
        path.erase(path.size() - 1);
        remove(path.c_str());
        cout << "Se elimino el disco en: " + path << endl;
    }
    catch (const std::exception &e)
    {
        cout << "Error al eliminar archivo" << endl;
        std::cerr << e.what() << '\n';
    }
}