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

void crearCarpeta(string rutadisco, string id, string name, bool isP, string carpetname)
{
    // deberia verificar primero si la carpeta ya existe

    //
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
    bool existecarpeta = false;
    string s = rutadisco;
    char sc[s.size() + 1];
    strcpy(sc, s.c_str());
    FILE *file = fopen(sc, "rb+");
    fseek(file, startpart, SEEK_SET);
    fread(&superb, sizeof(Super_Block), 1, file);
    // obtengo los datos del super bloque

    // busco si ya existe
    // buscar el inodo raiz
    Inodo_Table inoraiz;
    fseek(file, superb.s_inode_start, SEEK_SET);
    fread(&inoraiz, sizeof(Inodo_Table), 1, file);
    // buscar los apuntadores a los bloques
    int numblock = -2;
    for (int i = 0; i < 15; i++)
    {
        if (inoraiz.i_block[i] != -1)
        {
            // me ubico en el bloque de carpeta
            Carpet_Block bloqueaux;
            fseek(file, superb.s_block_start + (sizeof(Carpet_Block) * inoraiz.i_block[i]), SEEK_SET);
            fread(&bloqueaux, sizeof(Carpet_Block), 1, file);
            // ver contenido del bloque
            for (int j = 0; j < 4; j++)
            {
                if (bloqueaux.b_content[j].b_inodo != -1)
                {
                    if (strcmp(bloqueaux.b_content[j].b_name, deleteCaracter(carpetname, '/').c_str()) == 0)
                    {
                        cout << "ya existe la carpeta " + carpetname << endl;
                        return;
                    }
                }
            }
        }
    }
    // si no salio es porque no existe ninguna carpeta con ese nombre
    // encontrar el primer bloque carpeta disponible si no hay que crear uno
    for (int i = 0; i < 15; i++)
    {
        if (inoraiz.i_block[i] != -1)
        {
            // me ubico en el bloque de carpeta
            Carpet_Block bloqueaux;
            fseek(file, superb.s_block_start + (sizeof(Carpet_Block) * inoraiz.i_block[i]), SEEK_SET);
            fread(&bloqueaux, sizeof(Carpet_Block), 1, file);
            // ver contenido del bloque
            for (int j = 0; j < 4; j++)
            {
                if (bloqueaux.b_content[j].b_inodo == -1)
                {
                    numblock = inoraiz.i_block[i];
                }
            }
        }
    }
    // verificar si hay que crear un nuevo bloque de carpeta
    if (numblock != -2)
    {
        // solo crear un inodo
        Inodo_Table newinodo;
        newinodo.i_uid = 1;
        newinodo.i_gid = 1;
        newinodo.i_size = 0;
        newinodo.i_atime = time(nullptr);
        newinodo.i_ctime = time(nullptr);
        newinodo.i_mtime = time(nullptr);
        newinodo.i_type = '0';
        memset(newinodo.i_block, -1, sizeof(newinodo.i_block));
        // escribimos nuestro nuebo inodo
        fseek(file, superb.s_inode_start + (sizeof(Inodo_Table) * superb.s_first_ino), SEEK_SET);
        fwrite(&newinodo, sizeof(Inodo_Table), 1, file);
        // para saber que inodo poner de enlaze en el bloque de carpeta
        int numinodo = superb.s_first_ino;

        // modificaremos nuestro bloque
        Carpet_Block c_block;
        fseek(file, superb.s_block_start + (sizeof(Carpet_Block) * numblock), SEEK_SET);
        fread(&c_block, sizeof(Carpet_Block), 1, file);

        bool banderacreado = false;
        for (int i = 0; i < 4; i++)
        {
            if (c_block.b_content[i].b_inodo == -1)
            {
                strcpy(c_block.b_content[i].b_name, deleteCaracter(carpetname, '/').c_str());
                c_block.b_content[i].b_inodo = numinodo;
                banderacreado = true;
                break;
            }
        }
        // escribimos nuestro modificado bloquede carpeta
        fseek(file, superb.s_block_start + (sizeof(Carpet_Block) * numblock), SEEK_SET);
        fwrite(&c_block, sizeof(Carpet_Block), 1, file);
        // modificar el bitmap de inodos
        // y todo lo referente con el inodo
        int n = floor((sizepart - sizeof(Super_Block)) / (4 + sizeof(Journal) + sizeof(Inodo_Table) + 3 * sizeof(Carpet_Block)));
        fseek(file, superb.s_bm_inode_start, SEEK_SET);
        char bm_inodo[n];
        fread(bm_inodo, sizeof(char), n, file);
        bm_inodo[superb.s_first_ino] = '1';
        fseek(file, superb.s_bm_inode_start, SEEK_SET);
        fwrite(bm_inodo, sizeof(bm_inodo), 1, file);

        // actualizar el superbloque
        superb.s_first_ino = superb.s_first_ino + 1;
        superb.s_free_inodes_count = superb.s_free_inodes_count - 1;
        fseek(file, startpart, SEEK_SET);
        fwrite(&superb, sizeof(Super_Block), 1, file);
    }
    else
    {
        int n = floor((sizepart - sizeof(Super_Block)) / (4 + sizeof(Journal) + sizeof(Inodo_Table) + 3 * sizeof(Carpet_Block)));

        // crear nuevo bloque de carpeta con su respectivo inodo
        // buscar el primer puntero disponible
        int apuntador_raiz = -1;
        for (int i = 0; i < 15; i++)
        {
            if (inoraiz.i_block[i] == -1)
            {
                // me ubico en el bloque de carpeta
                apuntador_raiz = i;
                break;
            }
        }

        Inodo_Table newinodo;
        newinodo.i_uid = 1;
        newinodo.i_gid = 1;
        newinodo.i_size = 0;
        newinodo.i_atime = time(nullptr);
        newinodo.i_ctime = time(nullptr);
        newinodo.i_mtime = time(nullptr);
        newinodo.i_type = '0';
        memset(newinodo.i_block, -1, sizeof(newinodo.i_block));
        // escribimos nuestro nuebo inodo
        fseek(file, superb.s_inode_start + (sizeof(Inodo_Table) * superb.s_first_ino), SEEK_SET);
        fwrite(&newinodo, sizeof(Inodo_Table), 1, file);
        // para saber que inodo poner de enlaze en el bloque de carpeta
        int numinodo = superb.s_first_ino;

        Carpet_Block newCarpetab;
        for (int i = 0; i < 4; i++)
        {
            newCarpetab.b_content[i].b_inodo = -1;
        }
        memset(newCarpetab.b_content[0].b_name, '\0', sizeof(newCarpetab.b_content[1].b_name));
        strcpy(newCarpetab.b_content[0].b_name, deleteCaracter(carpetname, '/').c_str());
        newCarpetab.b_content[0].b_inodo = numinodo;
        fseek(file, superb.s_block_start + (sizeof(Carpet_Block) * numblock), SEEK_SET);
        fwrite(&newCarpetab, sizeof(Carpet_Block), 1, file);

        // inodo -> bloque carpeta
        inoraiz.i_mtime = time(nullptr);
        inoraiz.i_block[apuntador_raiz] = superb.s_first_blo;
        fseek(file, superb.s_inode_start, SEEK_SET);
        fwrite(&inoraiz, sizeof(Inodo_Table), 1, file);

        // actualizar inodo raiz
        fseek(file, superb.s_bm_inode_start, SEEK_SET);
        char bm_inodo[n];
        fread(bm_inodo, sizeof(char), n, file);
        bm_inodo[superb.s_first_ino] = '1';
        fseek(file, superb.s_bm_inode_start, SEEK_SET);
        fwrite(bm_inodo, sizeof(bm_inodo), 1, file);

        fseek(file, superb.s_bm_block_start, SEEK_SET);
        char bm_block[3 * n];
        fread(bm_block, sizeof(char), 3 * n, file);
        bm_block[superb.s_first_blo] = '1';
        fseek(file, superb.s_bm_block_start, SEEK_SET);
        fwrite(bm_block, sizeof(bm_block), 1, file);

        // actualizar conteos del superbloque
        // conteo de inodos
        superb.s_first_ino = superb.s_first_ino + 1;
        superb.s_free_inodes_count = superb.s_free_inodes_count - 1;
        fseek(file, startpart, SEEK_SET);
        fwrite(&superb, sizeof(Super_Block), 1, file);
        // conteo de bloques
        superb.s_first_blo = superb.s_first_blo + 1;
        superb.s_free_blocks_count = superb.s_free_blocks_count - 1;
        fseek(file, startpart, SEEK_SET);
        fwrite(&superb, sizeof(Super_Block), 1, file);
    }
    cout << "se creo el directorio" << carpetname << endl;
    fclose(file);
}
void mkdirr(char *tokens)
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
        else
        {
            cout << "El parametro [" << newtoken << "] no es reconocido por Mkdir" << endl;
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

    crearCarpeta(deleteCaracter(rutadisco, '\"'), id, namePartition, p, deleteCaracter(path, '\"'));
    // aqui solo ira el cp del archivo binario
}