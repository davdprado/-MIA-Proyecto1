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
    Disco(int num, string ruta)
    {
        numero = num;
        path = ruta;
        letra = 'a';
    }
};