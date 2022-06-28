#pragma once
#include <vector>
#include <string>
#include "Estructuras.h"
using namespace std;

class Disco
{
public:
    int numero;
    string path;
    char letra;
    vector<partmount> listaparticiones;
    Disco(char let, string ruta)
    {
        numero = 1;
        path = ruta;
        letra = let;
    }
};