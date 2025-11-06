#include "../include/persistencia.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

bool Persistencia::guardarEnCSV(const vector<Persona>& personas, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        cout << "Error al crear los registros" << endl;
        return false;
    }
    
    archivo << "DNI,Nombres,Apellidos,Nacionalidad,Lugar_Nacimiento,Direccion,Telefono,Correo,Estado_Civil" << endl;
    
    for (const auto& persona : personas) {
        archivo << persona.toCSV() << endl;
    }
    
    archivo.close();
    cout << "Guardado: " << personas.size() << " registros";
    return true;
}

vector<Persona> Persistencia::cargarDesdeCSV(const string& nombreArchivo) {
    vector<Persona> personas;
    ifstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir " << nombreArchivo << endl;
        return personas;
    }
    
    string linea;
    getline(archivo, linea); // Saltar encabezado
    
    int contador = 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dni, nombres, apellidos, nacionalidad, lugar, direccion, telefono, correo, estado;
        
        getline(ss, dni, ',');
        getline(ss, nombres, ',');
        getline(ss, apellidos, ',');
        getline(ss, nacionalidad, ',');
        getline(ss, lugar, ',');
        getline(ss, direccion, ',');
        getline(ss, telefono, ',');
        getline(ss, correo, ',');
        getline(ss, estado, ',');
        
        Persona p(dni, nombres, apellidos, nacionalidad, lugar, direccion, telefono, correo, estado);
        personas.push_back(p);
        
        contador++;
        if (contador % 10000 == 0) {
            cout << "Cargadas " << contador << " personas..." << endl;
        }
    }
    
    archivo.close();
    cout << "Carga completada"<< endl;
    return personas;
}