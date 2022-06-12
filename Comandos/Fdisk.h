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

void ModificarDiscof(MBR nuevombr, string path)
{
    cout << "Particiones del disco: " << endl;
    cout << "MBR: " << 0 << "-" << sizeof(MBR) << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << nuevombr.mbr_partition[i].part_name << ": " << nuevombr.mbr_partition[i].part_start << "-" << (nuevombr.mbr_partition[i].part_start + nuevombr.mbr_partition[i].part_size) << endl;
    }
    cout << "-----------------------------" << endl;
    string s = path;
    char sc[s.size() + 1];
    strcpy(sc, s.c_str());
    FILE *file = NULL;
    // r= read = si el disco ya existia
    file = fopen(sc, "r");
    if (file == NULL)
    {
        cout << "ERROR: no existe el disco" << endl;
        return; // error
    }
    file = fopen(sc, "rb+");
    fseek(file, 0, SEEK_SET);
    fwrite(&nuevombr, sizeof(MBR), 1, file);
    fclose(file);
    cout << "Se creo la particion" << endl;
}

void OrdenarArreglo(EBR arr[])
{
    EBR temporal;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10 - 1; j++)
        {
            if (arr[j].part_start > arr[j + 1].part_start)
            { // Ordena el array de mayor a menor, cambiar el "<" a ">" para ordenar de menor a mayor
                temporal = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temporal;
            }
        }
    }
}

void OrdenarEspaciosarr(Espacio arr[])
{
    Espacio temporal;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10 - 1; j++)
        {
            if (arr[j].espaciolibre > arr[j + 1].espaciolibre)
            { // Ordena el array de mayor a menor, cambiar el "<" a ">" para ordenar de menor a mayor
                temporal = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temporal;
            }
        }
    }
}
void AgregarExt(MBR nuevombr, string path, int finalpart, int startpart, char partfit)
{
    cout << "Particiones del disco: " << endl;
    cout << "MBR: " << 0 << "-" << sizeof(MBR) << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << nuevombr.mbr_partition[i].part_name << ": " << nuevombr.mbr_partition[i].part_start << "-" << (nuevombr.mbr_partition[i].part_start + nuevombr.mbr_partition[i].part_size) << endl;
    }
    cout << "-----------------------------" << endl;
    string s = path;
    char sc[s.size() + 1];
    strcpy(sc, s.c_str());
    FILE *file = NULL;
    // r= read = si el disco ya existia
    file = fopen(sc, "r");
    if (file == NULL)
    {
        cout << "ERROR: no existe el disco" << endl;
        return; // error
    }
    file = fopen(sc, "rb+");
    fseek(file, 0, SEEK_SET);
    fwrite(&nuevombr, sizeof(MBR), 1, file);

    // se crea el ebr donde va la extendida
    // se crea la lista para meterla en el disco
    EBR listalogicas[14];
    for (int i = 0; i < 14; i++)
    {
        strcpy(listalogicas[i].part_name, "");
        listalogicas[i].part_fit = 'F';
        listalogicas[i].part_size = 0;
        listalogicas[i].part_start = finalpart;
        listalogicas[i].part_next = -1;
    }

    fseek(file, startpart, SEEK_SET);
    fwrite(&listalogicas, sizeof(EBR), 14, file);
    fclose(file);
    cout << "Se creo la particion" << endl;
}

void setPunteros(EBR arr[])
{
    for (int i = 0; i < 10; i++)
    {
        if (arr[i + 1].part_size != 0)
        {
            arr[i].part_next = arr[i + 1].part_start;
        }
    }
}

void OrdenarParticiones(Particion arr[])
{
    Particion particionaux;
    int a, b, c, d, aux;
    if (arr[0].part_start > arr[1].part_start)
    {
        particionaux = arr[0];
        arr[0] = arr[1];
        arr[1] = particionaux;
    }
    if (arr[0].part_start > arr[2].part_start)
    {
        particionaux = arr[0];
        arr[0] = arr[2];
        arr[2] = particionaux;
    }
    if (arr[0].part_start > arr[3].part_start)
    {
        particionaux = arr[0];
        arr[0] = arr[3];
        arr[3] = particionaux;
    }
    if (arr[1].part_start > arr[2].part_start)
    {
        particionaux = arr[1];
        arr[1] = arr[2];
        arr[2] = particionaux;
    }
    if (arr[1].part_start > arr[3].part_start)
    {
        particionaux = arr[1];
        arr[1] = arr[3];
        arr[3] = particionaux;
    }
    if (arr[2].part_start > arr[3].part_start)
    {
        particionaux = arr[2];
        arr[2] = arr[3];
        arr[3] = particionaux;
    }
}

void OrdenarEspacios(Espacio arr[])
{
    Espacio particionaux;
    int a, b, c, d, aux;
    if (arr[0].espaciolibre > arr[1].espaciolibre)
    {
        particionaux = arr[0];
        arr[0] = arr[1];
        arr[1] = particionaux;
    }
    if (arr[0].espaciolibre > arr[2].espaciolibre)
    {
        particionaux = arr[0];
        arr[0] = arr[2];
        arr[2] = particionaux;
    }
    if (arr[0].espaciolibre > arr[3].espaciolibre)
    {
        particionaux = arr[0];
        arr[0] = arr[3];
        arr[3] = particionaux;
    }
    if (arr[1].espaciolibre > arr[2].espaciolibre)
    {
        particionaux = arr[1];
        arr[1] = arr[2];
        arr[2] = particionaux;
    }
    if (arr[1].espaciolibre > arr[3].espaciolibre)
    {
        particionaux = arr[1];
        arr[1] = arr[3];
        arr[3] = particionaux;
    }
    if (arr[2].espaciolibre > arr[3].espaciolibre)
    {
        particionaux = arr[2];
        arr[2] = arr[3];
        arr[3] = particionaux;
    }
}

int ObtenerByteFinal(int empieza, int tamanio)
{
    int bytefinal = 0;
    bytefinal = empieza + tamanio;
    return bytefinal;
}

MBR ObtenerDatosDisco(string path)
{
    string s = path;
    char sc[s.size() + 1];
    strcpy(sc, s.c_str());
    FILE *file = fopen(sc, "rb+");
    fseek(file, 0, SEEK_SET);
    MBR nuevombr;
    fread(&nuevombr, sizeof(nuevombr), 1, file);
    fclose(file);
    cout << "-----Disco Encontrado-----" << endl;
    cout << "Disco\nFecha de creacion: " << nuevombr.mbr_fecha << endl;
    cout << "Signature: " << nuevombr.mbr_disk_asignature << endl;
    cout << "Tamaño: " << nuevombr.mbr_tam << " Bytes" << endl;
    return nuevombr;
}

int CalcularBytes(int tamanio, string dimension)
{
    int tam = 0;
    if (strcasecmp(dimension.c_str(), "b") == 0)
    {
        tam = tamanio;
    }
    else if (strcasecmp(dimension.c_str(), "k") == 0)
    {
        tam = tamanio * 1024;
    }
    else if (strcasecmp(dimension.c_str(), "m") == 0)
    {
        tam = tamanio * 1024 * 1024;
    }
    return tam;
}

void crearParticion(string path, string unit, int size, string name, string type, string ajuste)
{
    char fit, tipo;
    int start = 0, taman = 0;
    char nombre[16];
    strcpy(nombre, name.c_str());

    if (strcasecmp(type.c_str(), "p") == 0)
    {
        tipo = 'P';
    }
    else if (strcasecmp(type.c_str(), "l") == 0)
    {
        tipo = 'L';
    }
    else if (strcasecmp(type.c_str(), "e") == 0)
    {
        tipo = 'E';
    }
    else
    {
        cout << "Error Atributo no valido para Type " + tipo << endl;
        return;
    }

    if (strcasecmp(type.c_str(), "bf") == 0)
    {
        fit = 'B';
    }
    else if (strcasecmp(type.c_str(), "wf") == 0)
    {
        fit = 'W';
    }
    else if (strcasecmp(type.c_str(), "ff") == 0)
    {
        fit = 'F';
    }
    else
    {
        cout << "Error Atributo no valido para fit " + tipo << endl;
        return;
    }
    taman = CalcularBytes(size, unit);

    // aqui va la particion
    // leer el archivo por medio del path
    string rutaresp = path;
    path.erase(path.begin());
    path.erase(path.size() - 1);
    MBR nuevombr = ObtenerDatosDisco(path);
    if (taman > (nuevombr.mbr_tam - sizeof(MBR)))
    {
        cout << "Tamanio de Particion a crear es mayor al del disco" << endl;
        return;
    }
    if (tipo == 'L')
    {
        bool existeExt = false;
        Particion particionExtendida;
        /* code */
        for (auto &&particion : nuevombr.mbr_partition)
        {
            if (particion.part_type == 'E')
            {
                // si existe una extendida
                particionExtendida = particion;
                existeExt = true;
            }
        }
        if (!existeExt)
        {
            cout << "no existe una particion Extendida dentro de este disco " << endl;
            return;
        }
        // aqui va todo lo de las logicas
    }
    else
    {
        // todo lo que sea respecto a Extendidas y primarias va aqui
        if (tipo == 'E')
        {
            // buscar si ya existen extendidas
            for (auto &&particion : nuevombr.mbr_partition)
            {
                if (particion.part_type == 'E')
                {
                    // si existe una extendida
                    cout << "ya existe una particion Extendida en este disco" << endl;
                    return;
                }
            }
        }
        // verificacion de nombre
        for (auto &&particion : nuevombr.mbr_partition)
        {
            string nameapt = particion.part_name;
            string newname = nombre;
            // cout << " " + nameapt + "==" + newname + " \n";
            if (nameapt == newname)
            {
                cout << "ERROR: Ya existe Particion con el nombre: " + name << endl;
                return;
            }
        }
        // verificamos que no hay mas de 4 particiones
        int numpart = 0;
        for (auto &&partici : nuevombr.mbr_partition)
        {
            if (partici.part_size != 0)
            {
                numpart++;
            }
        }
        if (numpart > 3)
        {
            cout << "Ya existen 4 particiones en este disco" << endl;
            return;
        }
        /* Primer Ajuste */
        cout << "este disco tiene primer ajuste" << endl;
        cout << "su espacio empieza del byte: " << sizeof(MBR) + 1 << " y termina en el byte: " << nuevombr.mbr_tam << endl;
        // Ordenar arreglos
        OrdenarParticiones(nuevombr.mbr_partition);
        int byteinicialPart = 0;
        for (int i = 0; i < 4; i++)
        {
            if (i == 0)
            {
                // ve si hay espacio entre la primera particion ordenada y el mbr
                int espaciolibre = (nuevombr.mbr_partition[i].part_start - 1) - sizeof(MBR);
                if (taman <= espaciolibre)
                {
                    // si entra en el espacio se queda
                    byteinicialPart = sizeof(MBR) + 1;
                    break;
                }
                // si no pues pasa a la siguiente particion ordenada
            }
            else if (i == 1)
            {
                // ve si hay espacio entre la segunda y primera particion ordenada
                int endpartition = ObtenerByteFinal(nuevombr.mbr_partition[i - 1].part_start, nuevombr.mbr_partition[i - 1].part_size);
                int espaciolibre = (nuevombr.mbr_partition[i].part_start - 1) - endpartition;
                if (taman <= espaciolibre)
                {
                    // si entra al espacio se queda
                    byteinicialPart = endpartition + 1;
                    break;
                }
            }
            else if (i == 2)
            {
                // ve si hay espacio entre la tercera y segunda particion ordenada
                int endpartition = ObtenerByteFinal(nuevombr.mbr_partition[i - 1].part_start, nuevombr.mbr_partition[i - 1].part_size);
                int espaciolibre = (nuevombr.mbr_partition[i].part_start - 1) - endpartition;
                if (taman <= espaciolibre)
                {
                    // si entra al espacio se queda
                    byteinicialPart = endpartition + 1;
                    break;
                }
            }
            else if (i == 3)
            {
                // ve si hay espacio entre la ultima particion ordenada y el final
                int endpartition = ObtenerByteFinal(nuevombr.mbr_partition[i - 1].part_start, nuevombr.mbr_partition[i - 1].part_size);
                int espaciolibre = (nuevombr.mbr_tam - 1) - endpartition;
                if (taman <= espaciolibre)
                {
                    // si entra en el espacio se queda
                    byteinicialPart = endpartition + 1;
                    break;
                }
                else
                {
                    // como es la ultima opcion disponible y no llena el cupo se da por hecho de que la particion no cabe en ningun lugar
                    cout << "La Particion " + name + " no se pudo asignar por falta de espacio" << endl;
                    return;
                }
                // si no pues pasa a la siguiente particion ordenada
            }
        }
        // buscar una particion que no este libre
        for (int i = 0; i < 4; i++)
        {
            if (nuevombr.mbr_partition[i].part_size == 0)
            {
                nuevombr.mbr_partition[i].part_fit = fit;
                nuevombr.mbr_partition[i].part_size = taman;
                nuevombr.mbr_partition[i].part_start = byteinicialPart;
                nuevombr.mbr_partition[i].part_type = tipo;
                strcpy(nuevombr.mbr_partition[i].part_name, nombre);
                cout << "-------------------------\n";
                cout << "Name: " << name << endl;
                cout << "tamanio: " << taman << endl;
                cout << "inicio: " << byteinicialPart << endl;
                cout << "tipo: " << tipo << endl;
                cout << "Fit: " << fit << endl;
                break;
            }
        }
        // volvemos a ordenar
        OrdenarParticiones(nuevombr.mbr_partition);
        if (tipo == 'E')
        {
            AgregarExt(nuevombr, path, taman + byteinicialPart, byteinicialPart, fit);
        }
        else
        {
            ModificarDiscof(nuevombr, path);
        }
        // xd
    }
}

void EliminarParticion(string path, string name, string delette)
{
    bool existepart = false;
    bool eslogica = false;
    string tipoDelete = "";
    if (strcasecmp(delette.c_str(), "fast") == 0)
    {
        tipoDelete = "Fast";
    }
    else if (strcasecmp(delette.c_str(), "full") == 0)
    {
        tipoDelete = "Full";
    }
    else
    {
        cout << "Dato erroneo de atributo delette " << endl;
        return;
    }
    MBR nuevombr;
    nuevombr = ObtenerDatosDisco(path);
    // ordeno los datos
    OrdenarParticiones(nuevombr.mbr_partition);
    // verificar que la particion existe

    for (auto &&particion : nuevombr.mbr_partition)
    {
        string npath = particion.part_name;
        if (particion.part_type == 'E')
        {
            EBR listaebr[50];
            string s = path;
            char sc[s.size() + 1];
            strcpy(sc, s.c_str());
            FILE *file = fopen(sc, "rb+");
            fseek(file, particion.part_start, SEEK_SET);
            fread(&listaebr, sizeof(EBR), 14, file);
            fclose(file);
            // busca si existe en las particiones logicas dentro de esta extendida
            for (auto &&logica : listaebr)
            {
                string nlog = logica.part_name;
                if (name == nlog)
                {
                    strcpy(logica.part_name, "");
                    logica.part_size = 0;
                    logica.part_fit = 'P';
                    logica.part_start = (particion.part_start + particion.part_size);
                    logica.part_next = -1;
                    existepart = true;
                    eslogica = true;
                    OrdenarArreglo(listaebr);
                    setPunteros(listaebr);
                    FILE *file = fopen(sc, "rb+");
                    fseek(file, particion.part_start, SEEK_SET);
                    fwrite(&listaebr, sizeof(EBR), 50, file);
                    fclose(file);
                    if (tipoDelete == "Full")
                    {
                        formateofull(path, logica.part_start, (sizeof(EBR) + logica.part_size));
                    }
                    for (auto &&logica : listaebr)
                    {
                        if (logica.part_size != 0)
                        {
                            int terminoEBR = 0;
                            terminoEBR = logica.part_start + sizeof(EBR);
                            cout << logica.part_name << ": " << endl;
                            cout << "EBR: " << logica.part_start << " - " << terminoEBR << endl;
                            cout << "Logica: " << terminoEBR + 1 << " - " << terminoEBR + 1 + logica.part_size << " -->" << logica.part_next << endl;
                        }
                    }
                }
            }
        }

        if (npath == name)
        {
            strcpy(particion.part_name, "");
            particion.part_size = 0;
            particion.part_start = nuevombr.mbr_tamanio;
            particion.part_status = 0;
            particion.part_fit = 'W';
            particion.part_type = 'P';
            // activar bandera
            existepart = true;
            OrdenarParticiones(nuevombr.mbr_partition);
            ModificarDiscof(nuevombr, path);
            if (tipoDelete == "Full")
            {
                formateofull(path, particion.part_start, particion.part_size);
            }
        }
    }

    if (!existepart)
    {
        cout << "no se encontro la particion con el nombre: " + name << endl;
        return;
    }
    OrdenarParticiones(nuevombr.mbr_partition);
    cout << "Se Elimino la particion" << endl;
}

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
    int i = 0;
    for (auto &&ite : params)
    {
        bool bandera = false;
        vector<string> newparam = split(ite, "@");
        if (newparam.size() > 0)
        {
            for (auto &&opcionales : newparam)
            {

                if (bandera)
                {
                    params.push_back(opcionales);
                }
                else
                {
                    params.push_back(opcionales);
                    params.erase(params.begin() + i);
                    bandera = true;
                }
            }
        }
        i++;
    }
    for (auto &&i : params)
    {
        cout << i << endl;
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
        crearParticion(path, u, tam, name, type, fit);
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