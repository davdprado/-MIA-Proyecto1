#include <iostream>
#include <string.h>
#include <filesystem>
#include <fstream>
#include "Comandos/Mkdisk.h"
#include "Comandos/Rmdisk.h"
#include "Comandos/Fdisk.h"
using namespace std;

void comandos(string comand_line)
{
    char *dupli = strdup(comand_line.c_str());
    char *token = strtok(dupli, " ");
    // cout << token << endl;
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
    comandos(entrada);
    consola();
}

int main(int argc, char const *argv[])
{
    consola();
    return 0;
}
