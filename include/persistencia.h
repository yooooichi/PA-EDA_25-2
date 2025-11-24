#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "persona.h"
#include "ArbolB.h"
#include <vector>
#include <string>
using namespace std;

class Persistencia {
public:
    // Métodos para CSV (útil para debugging y exportación)
    static bool guardarEnCSV(const vector<Persona*>& personas, const string& nombreArchivo);
    static vector<Persona*> cargarDesdeCSV(const string& nombreArchivo);
    
    // Métodos para formato binario (más eficiente para grandes volúmenes)
    static bool guardarEnBinario(const vector<Persona*>& personas, const string& nombreArchivo);
    static vector<Persona*> cargarDesdeBinario(const string& nombreArchivo);
    
    // Métodos para trabajar directamente con el Árbol B
    static bool guardarArbolB(ArbolB* arbol, const string& nombreArchivo);
    static ArbolB* cargarArbolB(const string& nombreArchivo);
    
    // Método auxiliar para liberar memoria
    static void liberarPersonas(vector<Persona*>& personas);
};

#endif