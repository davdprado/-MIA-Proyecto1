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
#include <list>
#include <math.h>

#include <filesystem>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../Estructuras/Estructuras.h"
#include "../Estructuras/Disco.h"
#include "./Mkdisk.h"
#include "./Fdisk.h"
#include "./Rep.h"
#include "./Mount.h"
#include "./Mkfs.h"

using namespace std;

void datamkfile(string rutadisco, string id, string name, string filecont, bool isP)
{
    MBR mbrdisk;
    int startpart, sizepart;
    mbrdisk = ObtenerDatosDisco(deleteCaracter(rutadisco, '\"'));
    for (auto &&parti : mbrdisk.mbr_partition)
    {
        string namepart = parti.part_name;
        if (parti.part_type == 'E')
        {
            EBR listaebr[14];
            string s = deleteCaracter(rutadisco, '\"');
            char sc[s.size() + 1];
            strcpy(sc, s.c_str());
            FILE *file = fopen(sc, "rb+");
            fseek(file, parti.part_start, SEEK_SET);
            fread(&listaebr, sizeof(EBR), 14, file);
            fclose(file);
            for (auto &&logica : listaebr)
            {
                string nlog = logica.part_name;
                if (name == nlog)
                {
                    startpart = logica.part_start;
                    sizepart = logica.part_size;
                }
            }
        }
        if (name == namepart)
        {
            // cout << "Logro entrar aqui" << endl;
            startpart = parti.part_start;
            sizepart = parti.part_size;
        }
    }
    Super_Block superb;

    string s = rutadisco;
    char sc[s.size() + 1];
    strcpy(sc, s.c_str());
    FILE *file = fopen(sc, "rb+");
    fseek(file, startpart, SEEK_SET);
    fread(&superb, sizeof(Super_Block), 1, file);

    if (isP)
    {
        // crear las carpetas
    }
    // verificar si hay parametro cont
    if (!isP)
    {
        /* code */
    }

    // verificar si existe el archivo cont
}

void makefile(char *tokens)
{
    string id = "";
    int agregar = 0;
    string path = "";
    bool p = false;
    string cont = "";
    vector<string> params = split(tokens, "$");
    vector<string> newparams;
    // separar los obligatorios de los opcionales y unirlos
    // como quien dice juntos pero no revueltos
    for (auto &&parametro : params)
    {
        if (strstr(parametro.c_str(), "@") != NULL)
        {
            vector<string> newparam = split(parametro, "@");
            if (newparam.size() > 0)
            {
                for (auto &&opcionales : newparam)
                {

                    newparams.push_back(opcionales);
                }
            }
        }
        else
        {
            newparams.push_back(parametro);
        }
    }
    for (auto &&i : newparams)
    {
        cout << i << endl;
    }

    for (auto &&parametro : newparams)
    {
        char *str_aux = strdup(parametro.c_str());
        char *newtoken = strtok(str_aux, "=>");
        // cout << "Parametro: " << newtoken;
        // cout << " Valor: " << newtoken << endl;
        if (strcasecmp(newtoken, "id") == 0)
        {
            // tomar el dato de path
            newtoken = strtok(NULL, ">");
            // obtener el path
            id = newtoken;
            // quitar las comillas al inicio y final
            // path.erase(path.begin());
            // path.erase(path.size() - 1);
        }
        else if (strcasecmp(newtoken, "path") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            path = newtoken;
        }
        else if (strcasecmp(newtoken, "p") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            if (newtoken == "1")
            {
                p = true;
            }
        }
        else if (strcasecmp(newtoken, "cont") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            cont = newtoken;
        }
        else
        {
            cout << "El parametro [" << newtoken << "] no es reconocido por MKFILE" << endl;
            return;
        }
    }
    // necesitamos darle un formato a nuestro disco
    string rutadisco = obtenerRutaDiscol(id);
    if (rutadisco == " ")
    {
        cout << "No se encuentra la particion en ningun disco con el id=> " << id << endl;
        return;
    }
    // obtener el name de la particion
    string namePartition = "";
    for (auto &&disco : listaDisco)
    {
        for (auto &&parti : disco.listaparticiones)
        {
            if (parti.id == id)
            {
                namePartition = parti.nombre;
            }
        }
    }
    bool israid = false;
    // hora de ver si tengo que trabajar en el raid
    if (!fileExists(deleteCaracter(rutadisco, '\"')))
    {
        string path_raid = deleteCaracter(rutadisco, '\"');
        vector<string> aux = split(path_raid, ".");
        path_raid = "\"" + aux[0] + "_raid.dsk\"";
        rutadisco = path_raid;
        israid = true;
        // crearParticion(path_raid, u, tam, name, type, fit, true);
        if (!fileExists(deleteCaracter(path_raid, '\"')))
        {
            cout << "No existe disco con ruta: " + path_raid << endl;
            return;
        }
    }
    datamkfile(rutadisco, id, namePartition, cont, p);
    // aqui solo ira el cp del archivo binario
}