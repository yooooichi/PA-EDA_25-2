#include "../include/persistencia.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// ==================== GUARDADO Y CARGA EN CSV ====================

bool Persistencia::guardarEnCSV(const vector<Persona*>& personas, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        cout << "Error al crear el archivo CSV" << endl;
        return false;
    }
    
    // Escribir encabezado
    archivo << "DNI,Nombres,Apellidos,Nacionalidad,Lugar_Nacimiento,Direccion,Telefono,Correo,Estado_Civil" << endl;
    
    // Escribir cada registro
    for (const auto& persona : personas) {
        archivo << persona->toCSV() << endl;
    }
    
    archivo.close();
    cout << "Guardados " << personas.size() << " registros en CSV" << endl;
    return true;
}

vector<Persona*> Persistencia::cargarDesdeCSV(const string& nombreArchivo) {
    vector<Persona*> personas;
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
        getline(ss, estado);
        
        Persona* p = new Persona(dni, nombres, apellidos, nacionalidad, 
                                 lugar, direccion, telefono, correo, estado);
        personas.push_back(p);
        
        contador++;
        if (contador % 100000 == 0) {
            cout << "Cargadas " << contador << " personas..." << endl;
        }
    }
    
    archivo.close();
    cout << "Carga completada: " << personas.size() << " registros" << endl;
    return personas;
}

// ==================== GUARDADO Y CARGA EN BINARIO ====================

bool Persistencia::guardarEnBinario(const vector<Persona*>& personas, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::binary);
    
    if (!archivo.is_open()) {
        cout << "Error al crear el archivo binario" << endl;
        return false;
    }
    
    // Escribir número total de registros
    size_t numRegistros = personas.size();
    archivo.write(reinterpret_cast<const char*>(&numRegistros), sizeof(numRegistros));
    
    // Escribir cada persona
    for (const auto& persona : personas) {
        // Función auxiliar para escribir strings
        auto escribirString = [&archivo](const string& str) {
            size_t longitud = str.length();
            archivo.write(reinterpret_cast<const char*>(&longitud), sizeof(longitud));
            archivo.write(str.c_str(), longitud);
        };
        
        escribirString(persona->getDNI());
        escribirString(persona->getNombres());
        escribirString(persona->getApellidos());
        escribirString(persona->getNacionalidad());
        escribirString(persona->getLugar_Nacimiento());
        escribirString(persona->getDireccion());
        escribirString(persona->getTelefono());
        escribirString(persona->getCorreo());
        escribirString(persona->getEstado());
    }
    
    archivo.close();
    cout << "Guardados " << personas.size() << " registros en formato binario" << endl;
    return true;
}

vector<Persona*> Persistencia::cargarDesdeBinario(const string& nombreArchivo) {
    vector<Persona*> personas;
    ifstream archivo(nombreArchivo, ios::binary);
    
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir " << nombreArchivo << endl;
        return personas;
    }
    
    // Leer número total de registros
    size_t numRegistros;
    archivo.read(reinterpret_cast<char*>(&numRegistros), sizeof(numRegistros));
    
    cout << "Cargando " << numRegistros << " registros desde archivo binario..." << endl;
    
    // Función auxiliar para leer strings
    auto leerString = [&archivo]() -> string {
        size_t longitud;
        archivo.read(reinterpret_cast<char*>(&longitud), sizeof(longitud));
        char* buffer = new char[longitud + 1];
        archivo.read(buffer, longitud);
        buffer[longitud] = '\0';
        string resultado(buffer);
        delete[] buffer;
        return resultado;
    };
    
    // Leer cada persona
    for (size_t i = 0; i < numRegistros; i++) {
        string dni = leerString();
        string nombres = leerString();
        string apellidos = leerString();
        string nacionalidad = leerString();
        string lugar = leerString();
        string direccion = leerString();
        string telefono = leerString();
        string correo = leerString();
        string estado = leerString();
        
        Persona* p = new Persona(dni, nombres, apellidos, nacionalidad,
                                 lugar, direccion, telefono, correo, estado);
        personas.push_back(p);
        
        if ((i + 1) % 1000000 == 0) {
            cout << "Cargadas " << (i + 1) << " personas..." << endl;
        }
    }
    
    archivo.close();
    cout << "Carga completada: " << personas.size() << " registros" << endl;
    return personas;
}

// ==================== GUARDADO Y CARGA DEL ÁRBOL B ====================

bool Persistencia::guardarArbolB(ArbolB* arbol, const string& nombreArchivo) {
    if (arbol == nullptr) {
        cout << "Error: Arbol nulo" << endl;
        return false;
    }
    
    // Obtener todas las personas del árbol
    vector<Persona*> personas = arbol->obtenerTodasPersonas();
    
    // Guardar en formato binario
    return guardarEnBinario(personas, nombreArchivo);
}

ArbolB* Persistencia::cargarArbolB(const string& nombreArchivo) {
    // Cargar personas desde archivo binario
    vector<Persona*> personas = cargarDesdeBinario(nombreArchivo);
    
    if (personas.empty()) {
        return nullptr;
    }
    
    // Crear nuevo árbol B
    ArbolB* arbol = new ArbolB();
    
    cout << "Insertando registros en el Arbol B..." << endl;
    
    // Insertar cada persona en el árbol
    for (size_t i = 0; i < personas.size(); i++) {
        arbol->insertar(personas[i]);
        
        if ((i + 1) % 1000000 == 0) {
            cout << "Insertadas " << (i + 1) << " personas en el arbol..." << endl;
        }
    }
    
    cout << "Arbol B reconstruido con " << arbol->obtenerNumRegistros() << " registros" << endl;
    
    return arbol;
}

// ==================== LIBERAR MEMORIA ====================

void Persistencia::liberarPersonas(vector<Persona*>& personas) {
    for (auto persona : personas) {
        delete persona;
    }
    personas.clear();
}