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

#include <filesystem>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../Estructuras/Estructuras.h"
#include "../Estructuras/Disco.h"
#include "./Mkdisk.h"
#include "./Fdisk.h"

using namespace std;

// funciones que pueden servir de este lado del mundo
vector<Disco> listaDisco;
char contador = 'a';

bool existeDisco(string path)
{
    for (auto &&disco : listaDisco)
    {
        if (path == disco.path)
        {
            return true;
        }
    }
    return false;
}

void desmontar(char *tokens)
{
    // faltaria la lista de ids
    string ident = "";
    bool existeid = false;
    vector<string> params = split(tokens, "$");
    // limpiando parametros
    // recorreremos los parametros
    for (auto &&parametro : params)
    {
        char *str_aux = strdup(parametro.c_str());
        char *newtoken = strtok(str_aux, "=>");
        // cout << "Parametro: " << newtoken;
        // cout << " Valor: " << newtoken << endl;
        if (strcasecmp(newtoken, "id") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            ident = newtoken;
            // quitar las comillas al name
            if (ident[0] == '\"')
            {
                ident.erase(ident.begin());
                ident.erase(ident.size() - 1);
            }
        }
        else
        {
            cout << "El parametro [" << newtoken << "] no es reconocido por UNMOUNT" << endl;
            return;
        }
    }
    // buscar el id en la lista de particiones montadas
    for (auto &&disk : listaDisco)
    {
        int ite = 0;
        for (auto &&partm : disk.listaparticiones)
        {
            string idpart = partm.id;
            if (idpart == ident)
            {
                // se eliminara de la lista
                disk.listaparticiones.erase(disk.listaparticiones.begin() + ite);
                // se desmonto
                cout << "se desmonto la particion" << endl;
                existeid = true;
            }

            ite++;
        }
    }
    if (!existeid)
    {
        cout << "No existe particion montada con el id " + ident << endl;
        return;
    }
} //*/

void montar(char *tokens)
{
    cout << "---------------------------------ENTRA MOUNT" << endl;
    string carnet = "20";
    string path = "";
    string name = "";
    bool existepart = false;
    bool eslogica = false;
    vector<string> params = split(tokens, "$");
    // limpiando parametros
    // recorreremos los parametros
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
            cout << "El parametro [" << newtoken << "] no es reconocido por MOUNT" << endl;
            return;
        }
    }
    if (path == "" || name == "")
    {
        cout << "ERROR: Parametro [path/name] obligatorio no encontrado" << endl;
        return;
    }
    // hora de montar el disco
    // ver si el disco existe por medio del path
    if (!fileExists(deleteCaracter(path, '\"')))
    {
        string path_raid = deleteCaracter(path, '\"');
        vector<string> aux = split(path_raid, ".");
        path_raid = "\"" + aux[0] + "_raid.dsk\"";
        path = path_raid;
        // crearParticion(path_raid, u, tam, name, type, fit, true);
        if (!fileExists(deleteCaracter(path_raid, '\"')))
        {
            cout << "No existe disco con ruta: " + path_raid << endl;
            return;
        }
    }

    if (!existeDisco(deleteCaracter(path, '\"')))
    {
        // crear disco
        Disco nuevodisco(contador, deleteCaracter(path, '\"'));
        listaDisco.push_back(nuevodisco);
        contador++;
        cout << "se creo el disco" << endl;
    }

    MBR mbrviejo;
    mbrviejo = ObtenerDatosDisco(deleteCaracter(path, '\"'));
    partmount nuevamont;
    for (auto &&parti : mbrviejo.mbr_partition)
    {
        string namepart = parti.part_name;
        if (parti.part_type == 'E')
        {
            EBR listaebr[14];
            string s = deleteCaracter(path, '\"');
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
                    logica.part_status = '1';
                    logica.part_next = -1;
                    existepart = true;
                    eslogica = true;
                    OrdenarArreglo(listaebr);
                    setPunteros(listaebr);
                    FILE *file = fopen(sc, "rb+");
                    fseek(file, parti.part_start, SEEK_SET);
                    fwrite(&listaebr, sizeof(EBR), 14, file);
                    fclose(file);
                    strcpy(nuevamont.nombre, name.c_str());
                }
            }
        }
        if (name == namepart)
        {
            // cout << "Logro entrar aqui" << endl;
            parti.part_status = '1';
            OrdenarParticiones(mbrviejo.mbr_partition);
            ModificarDiscof(mbrviejo, deleteCaracter(path, '\"'));
            // se crea la particion
            strcpy(nuevamont.nombre, name.c_str());
            // cout << "jijis: " << name << " - " << newid << endl;
            existepart = true;
        }
    }
    // busca en la lista el disco

    if (!existepart)
    {
        cout << "no se encontro la particion con el nombre: " + name << " Mount" << endl;
        return;
    }
    // falta el raid
    //  cout << "Paso el primerfiltro" << endl;
    for (auto &&disk : listaDisco)
    {
        if (disk.path == deleteCaracter(path, '\"'))
        {
            string newid;
            newid = newid + "vd";
            newid += disk.letra;
            newid += to_string(disk.numero);
            strcpy(nuevamont.id, newid.c_str());
            disk.listaparticiones.push_back(nuevamont);
            disk.numero = disk.numero + 1;
            break;
        }
    }
    cout << "Se Monto la particion la particion" << endl;
    cout << "-----------------------------------------" << endl;
    for (auto &&disco : listaDisco)
    {
        for (auto &&parti : disco.listaparticiones)
        {
            cout << disco.path << " | ";
            cout << parti.nombre << " | ";
            cout << parti.id << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
}
//*/