#include "../include/persona.h"
#include "../include/generador_datos.h"
#include "../include/persistencia.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Sistema de registro" << endl;
    
    GeneradorDatos generador;
    vector<Persona> personas = generador.generarPersonas(100); // cambiar a 33000000
    
    Persistencia::guardarEnCSV(personas, "data/datos.csv");
   
    vector<Persona> personasCargadas = Persistencia::cargarDesdeCSV("data/datos.csv");
    cout << "Total de registros: " << personasCargadas.size() << endl;
    
    return 0;
}