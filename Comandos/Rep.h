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
#include <fstream>

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

string obtenerRutaDiscol(string id)
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

float porcentaje(int cien, int parte)
{
    float resultado;
    int base;
    base = parte * 100;
    resultado = base / cien;
    return resultado;
}
string tipoP(char tipo)
{
    if (tipo == 'P')
        return "Primaria";
    else if (tipo == 'E')
        return "Extendida";
    else if (tipo == 'L')
        return "logica";
    else
        return " ";
}

string crearReporteTabla(MBR nuevombr, string rutambr, string rutadestino)
{
    string grafica = "";
    bool existeEBR = false;
    int inicioPE = 0;
    string nombrediscor;
    vector<string> auxiliar = split(rutambr, "/");
    nombrediscor = auxiliar[auxiliar.size() - 1];
    grafica += "graph [label = \"Reporte mbr " + nombrediscor + "\"];\n";
    grafica += "node[shape=plain]\n";
    grafica += "randir=TB\n";
    grafica += "mbr[label=<\n";
    grafica += "<table border=\"1\" cellborder=\"1\" cellspacing=\"0\">\n";
    //
    grafica += "<tr><td>Nombre</td><td>Valor</td></tr>\n";
    grafica += "<tr><td>mbr_tam</td><td>" + to_string(nuevombr.mbr_tam) + "</td></tr>\n";
    string fecha = to_string(nuevombr.mbr_fecha);
    grafica += "<tr><td>mbr_fechaCreacion</td><td>" + fecha + "</td></tr>\n";
    grafica += "<tr><td>mbr_disksignature</td><td>" + to_string(nuevombr.mbr_disk_asignature) + "</td></tr>\n";
    string diskfittt;
    grafica += "<tr><td>disk_fit</td><td>" + diskfittt + "</td></tr>\n";
    // recorremos las particiones
    int is = 1;
    for (auto &&parti : nuevombr.mbr_partition)
    {
        if (parti.part_size != 0)
        {
            string status, tipo, fitt;
            status += parti.part_status;
            if (status == "0" || status == "1")
                cout << "";
            else
                status = "0";
            tipo += parti.part_type;
            fitt += parti.part_fit;
            grafica += "<tr><td>part_status_" + to_string(is) + "</td><td>" + status + "</td></tr>\n";
            grafica += "<tr><td>part_type_" + to_string(is) + "</td><td>" + tipo + "</td></tr>\n";
            grafica += "<tr><td>part_fit_" + to_string(is) + "</td><td>" + fitt + "</td></tr>\n";
            grafica += "<tr><td>part_start_" + to_string(is) + "</td><td>" + to_string(parti.part_start) + "</td></tr>\n";
            grafica += "<tr><td>part_size_" + to_string(is) + "</td><td>" + to_string(parti.part_size) + "</td></tr>\n";
            string nombreparti = parti.part_name;
            grafica += "<tr><td>part_name_" + to_string(is) + "</td><td>" + nombreparti + "</td></tr>\n";

            if (parti.part_type == 'E')
            {
                existeEBR = true;
                inicioPE = parti.part_start;
            }
        }

        is++;
    }

    //
    grafica += "\n</table>\n";
    grafica += ">];\n";
    // veremos si hay logicas
    if (existeEBR)
    {
        // deberia pasar algo
        EBR listaebr[10];
        string s = rutambr;
        char sc[s.size() + 1];
        strcpy(sc, s.c_str());
        FILE *file = fopen(sc, "rb+");
        fseek(file, inicioPE, SEEK_SET);
        fread(&listaebr, sizeof(EBR), 10, file);
        fclose(file);
        int otro = 1;
        for (auto &&logica : listaebr)
        {
            if (logica.part_size != 0)
            {
                grafica += "EBR" + to_string(otro) + "[label=<\n";
                grafica += "<table border=\"1\" cellborder=\"1\" cellspacing=\"0\">\n";
                //
                grafica += "<tr><td>Nombre</td><td>Valor</td></tr>\n";
                // datos
                string status, fittt, nombrelogica;
                status += logica.part_status;
                if (status == "0" || status == "1")
                    cout << "";
                else
                    status = "0";
                fittt += logica.part_fit;
                nombrelogica = logica.part_name;
                grafica += "<tr><td>part_status_" + to_string(otro) + "</td><td>" + status + "</td></tr>\n";
                grafica += "<tr><td>part_name_" + to_string(otro) + "</td><td>" + nombrelogica + "</td></tr>\n";
                grafica += "<tr><td>part_fit_" + to_string(otro) + "</td><td>" + fittt + "</td></tr>\n";
                grafica += "<tr><td>part_start_" + to_string(otro) + "</td><td>" + to_string(logica.part_start) + "</td></tr>\n";
                grafica += "<tr><td>part_size_" + to_string(otro) + "</td><td>" + to_string(logica.part_size) + "</td></tr>\n";
                grafica += "<tr><td>part_next_" + to_string(otro) + "</td><td>" + to_string(logica.part_next) + "</td></tr>\n";
                //
                grafica += "\n</table>\n";
                grafica += ">];\n";
                otro++;
            }
        }
    }
    return grafica;
}

string crearReporteDisco(MBR nuevombr, string rutambr, string rutadestino)
{
    string nombrediscor;
    vector<string> auxiliar = split(rutambr, "/");
    nombrediscor = auxiliar[auxiliar.size() - 1];
    string grafica = "";
    grafica += "graph [ label = \"" + nombrediscor + "\"];\n";
    grafica += "node [shape=record];\n";
    grafica += "5[";
    grafica += "label=\"MBR";
    int acarreoP = sizeof(MBR);
    int tamDisco = nuevombr.mbr_tam;
    // recorremos las particiones de la tabla
    for (int i = 0; i < 4; i++)
    {
        // ve que no este vacia
        if (nuevombr.mbr_partition[i].part_size != 0)
        {
            // miramos si hay esspacio entre esta particion y la anterior
            int comienzo = nuevombr.mbr_partition[i].part_start;
            int espacio = comienzo - acarreoP;
            // si es mayor a 1 entonces si hay espacio
            if (espacio > 1)
            {
                grafica += "|Libre \\n" + to_string(porcentaje(tamDisco, espacio)) + "%";
            }
            if (nuevombr.mbr_partition[i].part_type == 'E')
            {
                Particion parti = nuevombr.mbr_partition[i];
                string nombrepart = parti.part_name;
                grafica += "|";
                grafica += "{" + nombrepart + " \\n " + tipoP(parti.part_type) + "\\n " + "|{";
                int acarreoL = parti.part_start;
                // obtendremos el arreglo que esta en el disco
                EBR listaebr[10];
                string s = rutambr;
                char sc[s.size() + 1];
                strcpy(sc, s.c_str());
                FILE *file = fopen(sc, "rb+");
                fseek(file, parti.part_start, SEEK_SET);
                fread(&listaebr, sizeof(EBR), 10, file);
                fclose(file);
                // ya obtubimos el arreglo de particiones logicas
                int itera = 0;
                for (auto &&logica : listaebr)
                {
                    if (logica.part_size != 0)
                    {
                        int comienzo = logica.part_start;
                        int espacio = comienzo - acarreoL;
                        // ver si es la primera que se hara
                        if (itera == 0)
                        {
                            if (espacio > 1)
                            {
                                grafica += "Libre \\n " + to_string(porcentaje(tamDisco, espacio)) + "%";
                            }
                            string nombrelogica = logica.part_name;
                            grafica += "EBR";
                            grafica += "|" + nombrelogica + " \\n Logica \\n " + to_string(porcentaje(tamDisco, logica.part_size)) + "%";
                            acarreoL = logica.part_start + (sizeof(EBR) + logica.part_size);
                            itera++;
                        }
                        else
                        {
                            if (espacio > 1)
                            {
                                grafica += "|Libre \\n " + to_string(porcentaje(tamDisco, espacio)) + "%";
                            }
                            string nombrelogica = logica.part_name;
                            grafica += "|EBR";
                            grafica += "|" + nombrelogica + " \\n Logica \\n " + to_string(porcentaje(tamDisco, logica.part_size)) + "%";
                            acarreoL = logica.part_start + (sizeof(EBR) + logica.part_size);
                        }
                    }
                }
                int espaciofinalE = (parti.part_start + (sizeof(EBR) + parti.part_size)) - acarreoL;
                if (itera == 0)
                {
                    if (espaciofinalE > 1)
                    {
                        grafica += "libre \\n" + to_string(porcentaje(tamDisco, espaciofinalE)) + "%";
                    }
                }
                else
                {
                    if (espaciofinalE > 1)
                    {
                        grafica += "|libre \\n" + to_string(porcentaje(tamDisco, espaciofinalE)) + "%";
                    }
                }

                // acaba
                grafica += "}}";
                acarreoP = parti.part_start + parti.part_size;
            }
            else
            {
                // creo para la paticion acutal
                Particion parti = nuevombr.mbr_partition[i];
                string nombrepart = parti.part_name;
                grafica += "|" + nombrepart + " \\n " + tipoP(parti.part_type) + "\\n " + to_string(porcentaje(tamDisco, parti.part_size)) + "%";
                acarreoP = parti.part_start + parti.part_size;
            }
        }
    }
    int espaciofinal = tamDisco - acarreoP;
    if (espaciofinal > 1)
    {
        grafica += "|libre \\n" + to_string(porcentaje(tamDisco, espaciofinal)) + "%";
    }

    grafica += "\"]\n";
    return grafica;
}

string crearReporteSB(MBR mbrdisk, string rutadisco, string rutadestino, string name)
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
    fclose(file);
    string grafica = "";
    bool existeEBR = false;
    int inicioPE = 0;
    string nombrediscor;
    grafica += "graph [label = \"Reporte SB " + name + "\"];\n";
    grafica += "node[shape=plain]\n";
    grafica += "randir=TB\n";
    grafica += "SB[label=<\n";
    grafica += "<table border=\"1\" cellborder=\"1\" cellspacing=\"0\">\n";
    //
    grafica += "<tr><td>Nombre</td><td>Valor</td></tr>\n";
    grafica += "<tr><td>inodes_count</td><td>" + to_string(superb.s_inodes_count) + "</td></tr>\n";
    grafica += "<tr><td>block_count</td><td>" + to_string(superb.s_blocks_count) + "</td></tr>\n";
    grafica += "<tr><td>first ino</td><td>" + to_string(superb.s_first_ino) + "</td></tr>\n";
    grafica += "<tr><td>first blo</td><td>" + to_string(superb.s_first_blo) + "</td></tr>\n";
    grafica += "<tr><td>magic</td><td>" + to_string(superb.s_magic) + "</td></tr>\n";
    grafica += "<tr><td>bm block start</td><td>" + to_string(superb.s_bm_block_start) + "</td></tr>\n";
    grafica += "<tr><td>bm inode start</td><td>" + to_string(superb.s_bm_inode_start) + "</td></tr>\n";
    grafica += "<tr><td>inode start</td><td>" + to_string(superb.s_inode_start) + "</td></tr>\n";
    grafica += "<tr><td>block start</td><td>" + to_string(superb.s_block_start) + "</td></tr>\n";
    grafica += "<tr><td>free block</td><td>" + to_string(superb.s_free_blocks_count) + "</td></tr>\n";
    grafica += "<tr><td>free inodes</td><td>" + to_string(superb.s_free_inodes_count) + "</td></tr>\n";

    // recorremos las particiones
    grafica += "\n</table>\n";
    grafica += ">];\n";
    return grafica;
}

string crearReporteBlock(MBR mbrdisk, string rutadisco, string rutadestino, string name)
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

    Carpet_Block lisinodes[superb.s_first_blo - 1];
    fseek(file, superb.s_inode_start, SEEK_SET);
    fread(&lisinodes, sizeof(Carpet_Block), superb.s_first_blo - 1, file);
    fclose(file);
    string grafica = "";
    bool existeEBR = false;
    int inicioPE = 0;
    string nombrediscor;
    grafica += "graph [label = \"Reporte Block " + name + "\"];\n";
    grafica += "node[shape=plain]\n";
    grafica += "randir=TB\n";
    for (auto &&ino : lisinodes)
    {
        grafica += to_string(inicioPE) + "[label=<\n";
        grafica += "<table border=\"1\" cellborder=\"1\" cellspacing=\"0\">\n";
        //
        grafica += "<tr><td>Bloque" + to_string(inicioPE) + "</td></tr>\n";
        grafica += "<tr><td>Nombre</td><td>Valor</td></tr>\n";
        for (int i = 0; i < 4; i++)
        {
            string str(ino.b_content[i].b_name);
            grafica += "<tr><td>" + str + "</td><td>" + to_string(ino.b_content[i].b_inodo) + "</td></tr>\n";
        }
        grafica += "\n</table>\n";
        grafica += ">];\n";
        inicioPE++;
    }
    // recorremos las particiones

    return grafica;
}
string crearReporteInode(MBR mbrdisk, string rutadisco, string rutadestino, string name)
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

    Inodo_Table lisinodes[superb.s_first_ino - 1];
    fseek(file, superb.s_inode_start, SEEK_SET);
    fread(&lisinodes, sizeof(Inodo_Table), superb.s_first_ino - 1, file);
    fclose(file);
    string grafica = "";
    bool existeEBR = false;
    int inicioPE = 0;
    string nombrediscor;
    grafica += "graph [label = \"Reporte Inode " + name + "\"];\n";
    grafica += "node[shape=plain]\n";
    grafica += "randir=TB\n";
    for (auto &&ino : lisinodes)
    {
        grafica += to_string(inicioPE) + "[label=<\n";
        grafica += "<table border=\"1\" cellborder=\"1\" cellspacing=\"0\">\n";
        //
        grafica += "<tr><td>Nombre</td><td>Valor</td></tr>\n";
        grafica += "<tr><td>uid</td><td>" + to_string(ino.i_uid) + "</td></tr>\n";
        grafica += "<tr><td>gid</td><td>" + to_string(ino.i_gid) + "</td></tr>\n";
        grafica += "<tr><td>size</td><td>" + to_string(ino.i_size) + "</td></tr>\n";
        grafica += "<tr><td>type</td><td>" + to_string(ino.i_type) + "</td></tr>\n";
        grafica += "<tr><td>block</td><td> ---- </td></tr>\n";
        for (int i = 0; i < 15; i++)
        {
            grafica += "<tr><td>A" + to_string(i) + "</td><td>" + to_string(ino.i_block[i]) + "</td></tr>\n";
        }
        grafica += "\n</table>\n";
        grafica += ">];\n";
        inicioPE++;
    }
    // recorremos las particiones

    return grafica;
}

void reportes(char *tokens)
{
    string rutadestino = "";
    string nombreid = "";
    string reptype = "";
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
            rutadestino = newtoken;
            // quitar las comillas al inicio y final
            // path.erase(path.begin());
            // path.erase(path.size() - 1);
        }
        else if (strcasecmp(newtoken, "id") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            nombreid = newtoken;
            // quitar las comillas al name
            if (nombreid[0] == '\"')
            {
                nombreid.erase(nombreid.begin());
                nombreid.erase(nombreid.size() - 1);
            }
        }
        else if (strcasecmp(newtoken, "name") == 0)
        {
            // tomar el dato de size
            newtoken = strtok(NULL, ">");
            reptype = newtoken;
            // quitar las comillas al name
            if (reptype[0] == '\"')
            {
                reptype.erase(reptype.begin());
                reptype.erase(reptype.size() - 1);
            }
        }
        else
        {
            cout << "El parametro [" << newtoken << "] no es reconocido por REP" << endl;
            return;
        }
    }
    if (strcasecmp(reptype.c_str(), "mbr") == 0)
    {
        reptype = "MBR";
    }
    else if (strcasecmp(reptype.c_str(), "disk") == 0)
    {
        reptype = "Disk";
    }
    else if (strcasecmp(reptype.c_str(), "bm_block") == 0)
    {
        reptype = "Bm_block";
    }
    else if (strcasecmp(reptype.c_str(), "bm_inode") == 0)
    {
        reptype = "Bm_inode";
    }
    else if (strcasecmp(reptype.c_str(), "sb") == 0)
    {
        reptype = "Sb";
    }
    else if (strcasecmp(reptype.c_str(), "block") == 0)
    {
        reptype = "Block";
    }
    else if (strcasecmp(reptype.c_str(), "inode") == 0)
    {
        reptype = "Inode";
    }
    else
    {
        cout << "Atributo erroneo para el reporte" << endl;
        return;
    }

    // crear la ruta
    string directorio = "";
    vector<string> vdirectorio = split(rutadestino, "/");
    vdirectorio.erase(vdirectorio.end());
    vdirectorio.erase(vdirectorio.begin());

    for (auto &&carpeta : vdirectorio)
    {
        directorio += "/" + carpeta;
    }
    // directorio.erase(0, 1);
    //  cout << "Ruta de carpeta: " + directorio << endl;
    //  cout << "Ruta absoluta: " + path << endl;
    string comandodir = "mkdir -p \"" + directorio + "/\"";
    int status = system(comandodir.c_str());
    if (status == 0)
        cout << "directorio: " + directorio + " Creado" << endl;
    else
        cout << "ocurrio un error" << endl;

    string rutadisco = obtenerRutaDiscol(nombreid);
    if (rutadisco == " ")
    {
        cout << "El id: " + nombreid + " no existe " << endl;
        return;
    }

    // obtenemos los datos del disco
    MBR newmbr;
    newmbr = ObtenerDatosDisco(deleteCaracter(rutadisco, '\"'));
    string codegrafica = "";
    codegrafica += "digraph G{\n";
    if (reptype == "MBR")
    {
        // aqui va el reporte del mbr
        codegrafica += crearReporteTabla(newmbr, rutadisco, rutadestino);
    }
    else if (reptype == "Disk")
    {
        codegrafica += crearReporteDisco(newmbr, rutadisco, rutadestino);
        // escribir en el dot
    }
    else if (reptype == "Bm_block")
    {
        // codegrafica += crearReporteDisco(newmbr, rutadisco, rutadestino);
        //  escribir en el dot
    }
    else if (reptype == "Bm_inode")
    {
        // codegrafica += crearReporteDisco(newmbr, rutadisco, rutadestino);
        //  escribir en el dot
    }
    else if (reptype == "Sb")
    {
        string namePartition = "";
        for (auto &&disco : listaDisco)
        {
            for (auto &&parti : disco.listaparticiones)
            {
                if (parti.id == nombreid)
                {
                    namePartition = parti.nombre;
                }
            }
        }
        codegrafica += crearReporteSB(newmbr, rutadisco, rutadestino, namePartition);
        //  escribir en el dot
    }
    else if (reptype == "Block")
    {
        string namePartition = "";
        for (auto &&disco : listaDisco)
        {
            for (auto &&parti : disco.listaparticiones)
            {
                if (parti.id == nombreid)
                {
                    namePartition = parti.nombre;
                }
            }
        }
        codegrafica += crearReporteBlock(newmbr, rutadisco, rutadestino, namePartition);
        //  escribir en el dot
    }
    else if (reptype == "Inode")
    {
        string namePartition = "";
        for (auto &&disco : listaDisco)
        {
            for (auto &&parti : disco.listaparticiones)
            {
                if (parti.id == nombreid)
                {
                    namePartition = parti.nombre;
                }
            }
        }
        codegrafica += crearReporteInode(newmbr, rutadisco, rutadestino, namePartition);
        //  escribir en el dot
    }
    codegrafica += "}";
    string rutadot = "graficaD.dot";
    ofstream archivo;
    archivo.open(rutadot);
    archivo << codegrafica;
    archivo.close();
    string extension = "";
    vector<string> director = split(rutadestino, "/");
    string namearch = director[director.size() - 1];
    vector<string> auxext = split(namearch, ".");
    extension = auxext[auxext.size() - 1];
    string dot = "dot -T " + deleteCaracter(extension, '\"') + " -o " + rutadestino + " graficaD.dot";
    system(dot.c_str());
    cout << "Reporte creado en la ruta " + rutadestino << endl;
}