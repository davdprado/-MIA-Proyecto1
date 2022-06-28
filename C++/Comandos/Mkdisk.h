#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "../Estructuras/Estructuras.h"

using namespace std;
string deleteCaracter(string str, char caracter)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == caracter)
        {
            str.erase(str.begin() + i);
        }
    }
    return str;
}
vector<string> split(string str, string token)
{
    vector<string> result;
    while (str.size())
    {
        int index = str.find(token);
        if (index != string::npos)
        {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if (str.size() == 0)
                result.push_back(str);
        }
        else
        {
            result.push_back(str);
            str = "";
        }
    }
    for (int i = 0; i < result.size(); i++)
    {
        if (result[i] == "")
        {
            result.erase(result.begin() + i);
        }
        if (result[i].back() == ' ')
        {
            result[i].pop_back();
        }
    }
    return result;
}

void CrearDisk(char *tokens)
{
    string path, name;
    int tam = 0;
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
        else if (strcasecmp(newtoken, "size") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            int tam_aux = atoi(newtoken);
            if (tam_aux % 8 != 0)
            {
                cout << "El size del disco no es multiplo de 8" << endl;
                return;
            }
            tam = tam_aux * 1024 * 1024;
        }
        else if (strcasecmp(newtoken, "name") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            name = newtoken;
            // quitar las comillas al name
            if (name[0] == '\"')
            {
                name.erase(name.begin());
                name.erase(name.size() - 1);
            }
        }
        else
        {
            cout << "El parametro [" << newtoken << "] no es reconocido por MKDISK" << endl;
            return;
        }
    }
    // cout << "mis datos son un disco de " << tam << "MB con ruta: " << path << name << endl;
    // crear el struct
    MBR mbr;
    mbr.mbr_disk_asignature = rand() % 1000;
    mbr.mbr_fecha = time(nullptr);
    mbr.mbr_tam = tam;
    for (int i = 0; i < 4; i++)
    {
        mbr.mbr_partition[i].part_size = 0;
        mbr.mbr_partition[i].part_fit = 'w';
        mbr.mbr_partition[i].part_start = tam;
        mbr.mbr_partition[i].part_status = '0';
        strcpy(mbr.mbr_partition[i].part_name, "");
    }

    string comandodir = "mkdir -p " + path;
    int status = system(comandodir.c_str());
    if (status == 0)
        cout << "directorio: " + path + name + " Creado" << endl;
    else
        cout << "ocurrio un error" << endl;

    // ahora solo s necesita el directorio para crear el archivo
    path.erase(path.begin());
    path.erase(path.size() - 1);
    string s = path + name;
    char sc[s.size() + 1];
    strcpy(sc, s.c_str());
    FILE *file = NULL;
    // r= read = si el disco ya existia
    file = fopen(sc, "r");
    if (file != NULL)
    {
        cout << "ERROR: Ya existe el disco" << endl;
        return; // error
    }
    file = fopen(sc, "wb");
    fwrite("\0", 1, 1, file);   //   escribe en el byte 1 un \0
    fseek(file, tam, SEEK_SET); //   se posiciona hasta el final del archivo es decir el tamanio del disco y
    fwrite("\0", 1, 1, file);   //   vuelve a escribir un 0 y asi se llena el archivo
    cout << "-------------DISCO CREADO--------------------" << endl;
    cout << "Disco\nFecha de creacion: " << mbr.mbr_disk_asignature << endl;
    cout << "Signature: " << mbr.mbr_disk_asignature << endl;
    cout << "Tamaño: " << mbr.mbr_tam << " Bytes" << endl;
    fseek(file, 0, SEEK_SET);
    fwrite(&mbr, sizeof(MBR), 1, file);
    fclose(file);
    // faltaria la simulacion del raid
    // crear el raid
    string pathraid;
    vector<string> auxraid = split(s, ".");
    pathraid = auxraid[0] + "_raid.dsk";
    string comandoraid = "cp -a \"" + s + "\" \"" + pathraid + "\"";
    int status2 = system(comandoraid.c_str());
    if (status2 == 0)
        cout << "Raid Creado" << endl;
    else
        cout << "ocurrio un error" << endl;
}