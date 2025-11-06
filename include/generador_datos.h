#ifndef GENERADOR_DATOS_H
#define GENERADOR_DATOS_H

#include "persona.h"
#include <vector>
#include <string>
using namespace std;

class GeneradorDatos {
private:
    vector<string> nombres = {"Thomas", "Lucas", "Carlos", "Ana", "Pedro", "Julio", 
                             "Walter", "Rosa", "Jorge", "Sofia", "Simon", "Carmen"};
    vector<string> apellidos = {"Garcia", "Rodriguez", "Lopez", "Martinez", "Gonzalez", 
                               "Perez", "Sanchez", "Ramirez", "Torres", "Flores"};
    vector<string> nacionalidades = {"Peruana", "Extranjera"};
    vector<string> departamentos = {"Lima", "Arequipa", "Cusco", "Piura", "La Libertad"};
    vector<string> estados_civiles = {"Soltero", "Casado", "Divorciado", "Viudo"};

public:
    string generarDNI();
    Persona generarPersona();
    vector<Persona> generarPersonas(int cantidad);
};

#endif