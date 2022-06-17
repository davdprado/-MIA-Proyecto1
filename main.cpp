#include <iostream>
#include <string.h>
#include <filesystem>
#include <fstream>
#include "Comandos/Mkdisk.h"
#include "Comandos/Rmdisk.h"
#include "Comandos/Fdisk.h"
#include "Comandos/Mount.h"
#include "Comandos/Rep.h"
using namespace std;

void comandos(string comand_line)
{
    if (comand_line.empty())
    {
        return;
    }

    char *dupli = strdup(comand_line.c_str());
    char *token = strtok(dupli, " ");
    // cout << token << endl;
    if (token[0] == '/' && token[1] == '*')
    {
        return;
    }

    if (strcasecmp(token, "mkdisk") == 0)
    {
        token = strtok(NULL, "");
        CrearDisk(token);
    }
    else if (strcasecmp(token, "rmdisk") == 0)
    {
        token = strtok(NULL, "");
        EliminarDisk(token);
    }
    else if (strcasecmp(token, "fdisk") == 0)
    {
        token = strtok(NULL, "");
        efeDisk(token);
    }
    else if (strcasecmp(token, "mount") == 0)
    {
        token = strtok(NULL, "");
        montar(token);
    }
    else if (strcasecmp(token, "unmount") == 0)
    {
        token = strtok(NULL, "");
        montar(token);
    }
    else if (strcasecmp(token, "rep") == 0)
    {
        token = strtok(NULL, "");
        reportes(token);
    }
    else if (strcasecmp(token, "exec") == 0)
    {
        string path = "";
        token = strtok(NULL, "");
        vector<string> params = split(token, "$");
        for (auto &&parametro : params)
        {
            char *str_aux = strdup(parametro.c_str());
            char *newtoken = strtok(str_aux, "=>");
            if (strcasecmp(newtoken, "path") == 0)
            {
                // tomar el dato de path
                newtoken = strtok(NULL, ">");
                // obtener el path
                path = newtoken;
                if (path[0] == '"')
                {
                    path.erase(path.begin());
                    path.erase(path.size() - 1);
                }
            }
        }
        if (fileExists(path))
        {

            ifstream archivoA(path.c_str());
            string linea;
            while (getline(archivoA, linea))
            {
                if (!linea.empty())
                {
                    cout << "comand:~ " << linea << endl;
                    linea = deleteCaracter(linea, '\r');
                    linea = deleteCaracter(linea, '\t');
                    linea = deleteCaracter(linea, '\n');
                    comandos(linea);
                }
            }
        }
    }
    else if (strcasecmp(token, "pause") == 0)
    {
        token = strtok(NULL, "");
        string statep = "";
        cout << "Estamos en pausa por favor presiona cualquier tecla antes de continuar:";
        getline(cin, statep);
    }
    else
    {
        cout << "Comando No encontrado" << endl;
    }
}

void consola()
{
    string entrada;
    entrada = "";
    cout << "comand:~ ";
    getline(cin, entrada);
    if (entrada == "exit")
    {
        return;
    }
    if (!entrada.empty())
    {
        comandos(entrada);
    }
    consola();
}

int main(int argc, char const *argv[])
{
    consola();
    return 0;
}
