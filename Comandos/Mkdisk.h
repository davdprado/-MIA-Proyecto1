#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

void CrearDisk(char *tokens)
{
    vector<string> params;
    while (tokens)
    {
        cout << "parametro " << tokens << endl;
        tokens = strtok(NULL, " $");
    }
}