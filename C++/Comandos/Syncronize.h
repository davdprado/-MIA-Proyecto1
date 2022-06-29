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

std::wstring wtime(const time_t &t)
{
    std::tm tm = *std::localtime(&t);
    std::wstringstream wss;
    wss << std::put_time(&tm, L"%F %T");
    return wss.str();
}

void crearJSON(MBR mbrdisk, string rutadisco, string rutadestino, string name)
{
    int startpart, sizepart;
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
    bool existecarpeta = false;
    string s = rutadisco;
    char sc[s.size() + 1];
    strcpy(sc, s.c_str());
    FILE *file = fopen(sc, "rb+");
    fseek(file, startpart, SEEK_SET);
    fread(&superb, sizeof(Super_Block), 1, file);

    Inodo_Table lisinodes[superb.s_first_ino];
    fseek(file, superb.s_inode_start, SEEK_SET);
    fread(&lisinodes, sizeof(Inodo_Table), superb.s_first_ino, file);
    Carpet_Block listblocks[superb.s_first_blo];
    fseek(file, superb.s_block_start, SEEK_SET);
    fread(&listblocks, sizeof(Carpet_Block), superb.s_first_blo, file);
    fclose(file);

    if (superb.s_first_ino < 1)
    {
        cout << "El id que menciono no tiene ninguna carpeta creada" << endl;
        return;
    }

    string contenido = "";
    contenido += "[\n";
    contenido += "{\n";
    // ahora el contenido del directorio raiz
    contenido += "\"Nombre\":\"root\",\n";
    wstring wide = wtime(lisinodes[0].i_atime);
    string fecha(wide.begin(), wide.end());
    contenido += "\"FechaC\":\"" + fecha + "\",\n";
    contenido += "\"Contenido\":[\n";
    for (auto &&bloque : listblocks)
    {
        for (auto &&nombrei : bloque.b_content)
        {
            string nombrecarpeta = nombrei.b_name;
            if ((nombrecarpeta != "." || nombrecarpeta != "..") && nombrei.b_inodo != -1)
            {
                contenido += "{\n";
                contenido += "\"Nombre\":\"" + nombrecarpeta + "\",\n";
                wstring wide2 = wtime(lisinodes[nombrei.b_inodo].i_atime);
                string fecha2(wide2.begin(), wide2.end());
                contenido += "\"FechaC\":\"" + fecha2 + "\",\n";
                contenido += "\"Contenido\":[]},";
            }
        }
    }
    contenido.erase(contenido.size() - 1);
    contenido += "]";
    contenido += "}";
    contenido += "]";
    // ahora tocara hacer crear el archivo;
    ofstream archivo;
    archivo.open(deleteCaracter(rutadestino, '\"'));
    archivo << contenido;
    archivo.close();
    cout << "JSON creado en la ruta " + rutadestino << endl;
}

void sincronizar(char *tokens)
{
    string path = "";
    string name = "";
    bool existepart = false;
    bool eslogica = false;
    bool israid = false;
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
        else if (strcasecmp(newtoken, "id") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            name = newtoken;
            // quitar las comillas al name
        }
        else
        {
            cout << "El parametro [" << newtoken << "] no es reconocido por SYNCRONIZE" << endl;
            return;
        }
    }

    string rutadisco = obtenerRutaDiscol(name);
    if (rutadisco == " ")
    {
        cout << "El id: " + name + " no existe " << endl;
        return;
    }
    // mbr para obtener los datos
    MBR newmbr;
    newmbr = ObtenerDatosDisco(deleteCaracter(rutadisco, '\"'));
    // nombre de la particion
    string namePartition = "";
    for (auto &&disco : listaDisco)
    {
        for (auto &&parti : disco.listaparticiones)
        {
            if (parti.id == name)
            {
                namePartition = parti.nombre;
            }
        }
    }

    crearJSON(newmbr, rutadisco, path, namePartition);
}