#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "persona.h"
#include <vector>
#include <string>
using namespace std;

class Persistencia {
public:
    static bool guardarEnCSV(const vector<Persona>& personas, const string& nombreArchivo);
    static vector<Persona> cargarDesdeCSV(const string& nombreArchivo);
};

#endif