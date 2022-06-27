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

using namespace std;

string obtenerRutaDiscos(string id)
{
    for (auto &&disk : listaDisco)
    {
        for (auto &&partid : disk.listaparticiones)
        {
            string idstring = partid.id;
            if (idstring == id)
            {
                return disk.path;
            }
        }
    }
    return " ";
}
int getN(int tam_particion)
{
    int tam_SuperBlock = sizeof(Super_Block);
    int tam_journling = sizeof(Journal);
    int tam_inodo = sizeof(Inodo_Table);
    int tam_block = sizeof(Carpet_Block);

    int operador = (tam_particion - tam_SuperBlock);
    int denominador = 1 + tam_journling + 3 + tam_inodo + 3 * tam_block;
    int n = floor(operador / denominador);

    return n;
}

void Modificar_Inodo(FILE *disco, Inodo_Table inodo, int pos, int tipo)
{
    if (tipo == 0) // ESTE VA SER PARA MODIFICAR FECHA DE LECTURA
    {
        inodo.i_atime = time(nullptr);
    }
    else if (tipo == 1) // ESTE VA SER PARA MODIFICAR FECHA DE MODIFICACION
    {
        inodo.i_mtime = time(nullptr);
    }

    fseek(disco, pos, SEEK_SET);
    fwrite(&inodo, sizeof(Inodo_Table), 1, disco);
}

int getBlockfree(FILE *disco, int block_start, int size)
{
    fseek(disco, block_start, SEEK_SET);
    int n = getN(size);

    char Bm_bloque[3 * n];
    fread(Bm_bloque, sizeof(char), 3 * n, disco);

    for (unsigned int i = 0; i < sizeof(Bm_bloque); i++)
    {
        if (Bm_bloque[i] == '0')
            return i;
    }
    return -1;
}

int getInodofree(FILE *disco, int inode_start, int size)
{
    fseek(disco, inode_start, SEEK_SET);
    int n = getN(size);
    char Bm_inodo[n];
    fread(Bm_inodo, sizeof(char), n, disco);

    for (unsigned int i = 0; i < sizeof(Bm_inodo); i++)
    {
        if (Bm_inodo[i] == '0')
            return i;
    }
    return -1;
}

void makeExt3(string rutadisco, string id, string name, string type)
{
    // falto el formateo
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
    // hacer el formateo
    if (type == "Full")
    {
        formateofull(deleteCaracter(rutadisco, '\"'), startpart, sizepart);
    }

    // operaciones para todo nuestro EXT3
    // valor de n
    int n = floor((sizepart - sizeof(Super_Block)) / (4 + sizeof(Journal) + sizeof(Inodo_Table) + 3 * sizeof(Carpet_Block)));
    // creacion del superbloque
    Super_Block superb;

    Inodo_Table inodo;
    Carpet_Block cblock;

    // abriremos el archivo
    string s = rutadisco;
    char sc[s.size() + 1];
    strcpy(sc, s.c_str());
    FILE *file = fopen(sc, "rb+");
    fseek(file, startpart, SEEK_SET);
    fread(&superb, sizeof(Super_Block), 1, file);

    // hacemos el bitmap de inodos
    char bitmap_i[n];
    memset(bitmap_i, '0', sizeof(bitmap_i));
    // bitmap de bloques
    char bitmap_b[3 * n];
    memset(bitmap_b, '0', sizeof(bitmap_b));
    // verificamos si ya existe un superbloque en ese lugar
    //  0 es no
    //  1 es si
    if (superb.s_block_size == 0)
    {
        // valores para nuestro superbloques
        superb.s_filesystem_type = 3;
        superb.s_inodes_count = n;
        superb.s_blocks_count = 3 * n;
        superb.s_free_blocks_count = 3 * n;
        superb.s_free_inodes_count = n;
        superb.s_mtime = time(nullptr);
        superb.s_umtime = 0;
        superb.s_mnt_count = 0;
        superb.s_magic = 0xEF53;
        superb.s_inode_size = sizeof(Inodo_Table);
        superb.s_block_size = sizeof(Carpet_Block);
        superb.s_first_ino = 0;
        superb.s_first_blo = 0;
        superb.s_bm_inode_start = startpart + sizeof(Super_Block) + 1 + (n * sizeof(Journal)) + 1;
        superb.s_bm_block_start = superb.s_bm_block_start + n + 1;
        superb.s_inode_start = superb.s_bm_block_start + (3 * n) + 1;
        superb.s_block_start = superb.s_bm_inode_start + n * sizeof(Inodo_Table) + 1;

        // ingresar los datos de del superbloque dentro del archivo
        fseek(file, startpart, SEEK_SET);
        fwrite(&superb, sizeof(Super_Block), 1, file);
        // toca los bitmaps
        fseek(file, superb.s_bm_inode_start, SEEK_SET);
        fwrite(bitmap_i, sizeof(bitmap_i), 1, file);

        fseek(file, superb.s_bm_block_start, SEEK_SET);
        fwrite(bitmap_b, sizeof(bitmap_b), 1, file);
    }
    else
    {
        superb.s_first_blo = 0;
        superb.s_first_ino = 0;
        superb.s_free_blocks_count = 3 * n;
        superb.s_free_inodes_count = n;
        // ingresar los datos de del superbloque dentro del archivo
        fseek(file, startpart, SEEK_SET);
        fwrite(&superb, sizeof(Super_Block), 1, file);
        // toca los bitmaps
        fseek(file, superb.s_bm_inode_start, SEEK_SET);
        fwrite(bitmap_i, sizeof(bitmap_i), 1, file);

        fseek(file, superb.s_bm_block_start, SEEK_SET);
        fwrite(bitmap_b, sizeof(bitmap_b), 1, file);

        char inodo[n * sizeof(Inodo_Table)];
        memset(inodo, '\0', sizeof(inodo));
        fseek(file, superb.s_inode_start, SEEK_SET);
        fwrite(inodo, sizeof(inodo), 1, file);

        char block[3 * n * sizeof(Carpet_Block)];
        memset(block, '\0', sizeof(block));
        fseek(file, superb.s_block_start, SEEK_SET);
        fwrite(block, sizeof(block), 1, file);
    }
    fclose(file);
    // hay que hacer la carpeta raiz
    FILE *file2 = fopen(sc, "rb+");
    if (file2 == NULL)
    {
        cout << "Error al abrir archivo en mkfs" << endl;
        return;
    }
    // crearemos el inodo del archvio raiz
    Inodo_Table inodot;
    inodot.i_uid = 1;
    inodot.i_gid = 1;
    inodot.i_size = 0;
    inodot.i_atime = time(nullptr);
    inodot.i_ctime = time(nullptr);
    inodot.i_mtime = time(nullptr);
    inodot.i_type = '0';
    memset(inodot.i_block, -1, sizeof(inodot.i_block));

    // ponemos el primer bloque como 0
    inodot.i_block[0] = 0;
    // posisionamos y escribimos
    fseek(file2, superb.s_inode_start, SEEK_SET);
    fwrite(&inodot, sizeof(Inodo_Table), 1, file2);

    Carpet_Block bloquec;
    for (int i = 0; i < 15; i++)
    {
        memset(bloquec.b_content[i].b_name, '\0', sizeof(bloquec.b_content[i].b_name));
        bloquec.b_content[i].b_inodo = -1;
    }
    // actual
    memset(bloquec.b_contentf, '\0', sizeof(bloquec.b_contentf));
    bloquec.tipo = 'C';
    strcpy(bloquec.b_content[0].b_name, ".");
    bloquec.b_content[0].b_inodo = 0;
    // anterior<-actual
    strcpy(bloquec.b_content[1].b_name, "..");
    bloquec.b_content[1].b_inodo = 0;
    // se escribe en el archivo binario
    fseek(file2, superb.s_block_start, SEEK_SET);
    fwrite(&bloquec, sizeof(Carpet_Block), 1, file2);

    // actualizar los bitmaps
    // bitmap de inodos
    fseek(file2, superb.s_bm_inode_start, SEEK_SET);
    char bm_inodo[n];
    fread(bm_inodo, sizeof(char), n, file2);
    bm_inodo[0] = '1';
    fseek(file2, superb.s_bm_inode_start, SEEK_SET);
    fwrite(bm_inodo, sizeof(bm_inodo), 1, file2);

    // bitmap de bloques
    fseek(file2, superb.s_bm_block_start, SEEK_SET);
    char bm_block[3 * n];
    fread(bm_block, sizeof(char), 3 * n, file2);
    bm_block[0] = '1';
    fseek(file2, superb.s_bm_block_start, SEEK_SET);
    fwrite(bm_block, sizeof(bm_block), 1, file2);

    // actualizar conteos del superbloque
    // conteo de inodos
    superb.s_first_ino = getInodofree(file2, superb.s_bm_inode_start, sizepart);
    superb.s_free_inodes_count = superb.s_free_inodes_count - 1;
    fseek(file2, startpart, SEEK_SET);
    fwrite(&superb, sizeof(Super_Block), 1, file2);
    // conteo de bloques
    superb.s_first_blo = getBlockfree(file2, superb.s_bm_inode_start, sizepart);
    superb.s_free_blocks_count = superb.s_free_blocks_count - 1;
    fseek(file2, startpart, SEEK_SET);
    fwrite(&superb, sizeof(Super_Block), 1, file2);
    fclose(file2);
    cout << "Se hizo el formateo con EXT3 " << endl;
}

void darformato(char *tokens)
{
    string u = "k";
    string type = "full";
    string id = "";
    string tipodelete = "Fast";
    int agregar = 0;
    bool banderaCreate = true;
    bool banderaDelete = false;
    bool banderaCustom = false;
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
    if (strcasecmp(type.c_str(), "fast") == 0)
    {
        tipodelete = "Fast";
    }
    else if (strcasecmp(type.c_str(), "full") == 0)
    {
        tipodelete = "Full";
    }
    // necesitamos darle un formato a nuestro disco
    string rutadisco = obtenerRutaDiscos(id);
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
    makeExt3(rutadisco, id, namePartition, type);
    // aqui solo ira el cp del archivo binario
}