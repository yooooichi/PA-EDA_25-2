#include "../include/generador_datos.h"
#include <random>
#include <algorithm>
using namespace std;

string GeneradorDatos::generarDNI() {
    return to_string(10000000 + (rand() % 90000000));
}

Persona GeneradorDatos::generarPersona() {
    string dni = generarDNI();

    string nombre = nombres[rand() % nombres.size()];
    string apellido1 = apellidos[rand() % apellidos.size()];
    string apellido2 = apellidos[rand() % apellidos.size()];
    string departamento = departamentos[rand() % departamentos.size()];
    
    Persona p;
    p.setDNI(dni);
    p.setNombres(nombre);
    p.setApellidos(apellido1 + " " + apellido2);
    p.setNacionalidad("Peruana");
    p.setLugar_Nacimiento(departamento);
    p.setDireccion("Av. " + departamento + " #" + to_string(rand() % 1000));
    p.setTelefono("9" + to_string(10000000 + (rand() % 90000000)));
    p.setCorreo(nombre + "." + apellido1 + "@gmail.com");
    p.setEstado("Soltero");
    
    return p;
}

vector<Persona> GeneradorDatos::generarPersonas(int cantidad) {
    vector<Persona> personas;
    srand(time(0));
    
    cout << "Generando registros" << endl;
    
    for (int i = 0; i < cantidad; i++) {
        personas.push_back(generarPersona());
    }
    return personas;
}