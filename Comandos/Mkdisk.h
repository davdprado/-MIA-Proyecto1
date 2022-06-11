#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "../Estructuras/Estructuras.h"

using namespace std;

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

vector<string> Getparams(string str, string pattern)
{
    int posInit = 0;
    int posFound = 0;
    string splitted;
    vector<string> results;

    while (posFound >= 0)
    {
        posFound = str.find(pattern, posInit);
        splitted = str.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        results.push_back(splitted);
    }

    return results;
}

void limpiarV(vector<string> params)
{
    for (int i = 0; i < params.size(); i++)
    {
        if (params[i] == "")
        {
            params.erase(params.begin() + i);
        }
        if (params[i].back() == ' ')
        {
            params[i].pop_back();
        }
    }
}

void CrearDisk(char *tokens)
{
    vector<string> params = split(tokens, "$");
    // limpiando parametros
    for (auto &&parametro : params)
    {
        char *str_aux = strdup(parametro.c_str());
        char *newtoken = strtok(str_aux, "=>");
        cout << "Parametro: " << newtoken;
        newtoken = strtok(NULL, ">");
        cout << " Valor: " << newtoken << endl;
    }
}