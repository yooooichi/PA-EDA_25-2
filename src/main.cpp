#include "../include/persona.h"
#include "../include/generador_datos.h"
#include "../include/persistencia.h"
#include "../include/ArbolB.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
using namespace std;

/**
 * Sistema de Registro de Ciudadanos usando Árbol B
 * Soporta 33 millones de registros con búsqueda eficiente por DNI
 */

// Variables globales
ArbolB* arbolGlobal = nullptr;
const string ARCHIVO_DATOS = "data/registro_ciudadanos.bin";

// Declaración de funciones
void mostrarMenu();
void cargarDatosExistentes();
void generarNuevosRegistros();
void buscarPorDNI();
void insertarRegistro();
void eliminarRegistro();
void mostrarEstadisticas();
void realizarBenchmark();
void guardarYSalir();

int main() {
    cout << "========================================" << endl;
    cout << "  SISTEMA DE REGISTRO DE CIUDADANOS" << endl;
    cout << "   Estructura de Datos: Arbol B" << endl;
    cout << "========================================" << endl << endl;
    
    // Intentar cargar datos existentes
    cargarDatosExistentes();
    
    // Si no hay datos, crear árbol vacío
    if (arbolGlobal == nullptr) {
        arbolGlobal = new ArbolB();
        cout << "Arbol B inicializado (vacio)" << endl;
    }
    
    // Menú principal
    int opcion;
    do {
        mostrarMenu();
        cout << "Ingrese opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                generarNuevosRegistros();
                break;
            case 2:
                buscarPorDNI();
                break;
            case 3:
                insertarRegistro();
                break;
            case 4:
                eliminarRegistro();
                break;
            case 5:
                mostrarEstadisticas();
                break;
            case 6:
                realizarBenchmark();
                break;
            case 7:
                guardarYSalir();
                break;
            default:
                if (opcion != 7) {
                    cout << "Opcion invalida" << endl;
                }
        }
        
    } while (opcion != 7);
    
    return 0;
}

void mostrarMenu() {
    cout << "\n========================================" << endl;
    cout << "              MENU PRINCIPAL" << endl;
    cout << "========================================" << endl;
    cout << "1. Generar nuevos registros" << endl;
    cout << "2. Buscar ciudadano por DNI" << endl;
    cout << "3. Insertar un registro manualmente" << endl;
    cout << "4. Eliminar un registro" << endl;
    cout << "5. Mostrar estadisticas del sistema" << endl;
    cout << "6. Realizar benchmark (pruebas de rendimiento)" << endl;
    cout << "7. Guardar y salir" << endl;
    cout << "========================================" << endl;
}

void cargarDatosExistentes() {
    cout << "Verificando datos existentes..." << endl;
    
    ifstream verificar(ARCHIVO_DATOS);
    if (verificar.good()) {
        verificar.close();
        cout << "Archivo de datos encontrado. Cargando..." << endl;
        
        auto inicio = chrono::high_resolution_clock::now();
        arbolGlobal = Persistencia::cargarArbolB(ARCHIVO_DATOS);
        auto fin = chrono::high_resolution_clock::now();
        
        auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio);
        
        if (arbolGlobal != nullptr) {
            cout << "Datos cargados exitosamente en " << duracion.count() << " segundos" << endl;
            cout << "Total de registros: " << arbolGlobal->obtenerNumRegistros() << endl;
        }
    } else {
        cout << "No se encontraron datos existentes." << endl;
    }
}

void generarNuevosRegistros() {
    int cantidad;
    cout << "\n--- GENERACION DE REGISTROS ---" << endl;
    cout << "Registros actuales: " << arbolGlobal->obtenerNumRegistros() << endl;
    cout << "¿Cuantos registros desea generar? (recomendado: 100000): ";
    cin >> cantidad;
    
    if (cantidad <= 0) {
        cout << "Cantidad invalida" << endl;
        return;
    }
    
    cout << "\nGenerando " << cantidad << " registros..." << endl;
    
    GeneradorDatos generador;
    
    auto inicio = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < cantidad; i++) {
        Persona* p = new Persona();
        *p = generador.generarPersona();
        arbolGlobal->insertar(p);
        
        if ((i + 1) % 10000 == 0) {
            cout << "Insertados: " << (i + 1) << " / " << cantidad << endl;
        }
    }
    
    auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio);
    
    cout << "\nGeneracion completada!" << endl;
    cout << "Tiempo total: " << duracion.count() << " segundos" << endl;
    cout << "Total de registros en el sistema: " << arbolGlobal->obtenerNumRegistros() << endl;
    
    // Guardar automáticamente
    cout << "\nGuardando datos..." << endl;
    Persistencia::guardarArbolB(arbolGlobal, ARCHIVO_DATOS);
}

void buscarPorDNI() {
    string dni;
    cout << "\n--- BUSQUEDA POR DNI ---" << endl;
    cout << "Ingrese el DNI (8 dígitos): ";
    cin >> dni;
    
    auto inicio = chrono::high_resolution_clock::now();
    Persona* resultado = arbolGlobal->buscar(dni);
    auto fin = chrono::high_resolution_clock::now();
    
    auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
    
    cout << "\nTiempo de búsqueda: " << duracion.count() << " microsegundos" << endl;
    
    if (resultado != nullptr) {
        cout << "\nREGISTRO ENCONTRADO:" << endl;
        cout << "----------------------------------------" << endl;
        resultado->MostrarPersona();
    } else {
        cout << "\nNo se encontro ningun registro con el DNI: " << dni << endl;
    }
}

void insertarRegistro() {
    cout << "\n--- INSERTAR REGISTRO MANUAL ---" << endl;
    
    string dni, nombres, apellidos, nacionalidad, lugar, direccion, telefono, correo, estado;
    
    cout << "DNI: ";
    cin >> dni;
    cin.ignore();
    
    cout << "Nombres: ";
    getline(cin, nombres);
    
    cout << "Apellidos: ";
    getline(cin, apellidos);
    
    cout << "Nacionalidad: ";
    getline(cin, nacionalidad);
    
    cout << "Lugar de nacimiento: ";
    getline(cin, lugar);
    
    cout << "Direccion: ";
    getline(cin, direccion);
    
    cout << "Telefono: ";
    getline(cin, telefono);
    
    cout << "Correo: ";
    getline(cin, correo);
    
    cout << "Estado civil: ";
    getline(cin, estado);
    
    Persona* p = new Persona(dni, nombres, apellidos, nacionalidad, 
                            lugar, direccion, telefono, correo, estado);
    
    arbolGlobal->insertar(p);
    cout << "\nRegistro insertado exitosamente" << endl;
}

void eliminarRegistro() {
    string dni;
    cout << "\n--- ELIMINAR REGISTRO ---" << endl;
    cout << "Ingrese el DNI a eliminar: ";
    cin >> dni;
    
    // Verificar si existe
    Persona* resultado = arbolGlobal->buscar(dni);
    if (resultado == nullptr) {
        cout << "\nNo se encontro el registro con DNI: " << dni << endl;
        return;
    }
    
    cout << "\nRegistro encontrado:" << endl;
    resultado->MostrarPersona();
    
    cout << "¿Esta seguro de eliminar este registro? (S/N): ";
    char confirmacion;
    cin >> confirmacion;
    
    if (confirmacion == 'S' || confirmacion == 's') {
        arbolGlobal->eliminar(dni);
        cout << "\nRegistro eliminado exitosamente" << endl;
    } else {
        cout << "\nOperacion cancelada" << endl;
    }
}

void mostrarEstadisticas() {
    cout << "\n========================================" << endl;
    cout << "        ESTADISTICAS DEL SISTEMA" << endl;
    cout << "========================================" << endl;
    cout << "Total de registros: " << arbolGlobal->obtenerNumRegistros() << endl;
    cout << "Estructura de datos: Arbol B" << endl;
    cout << "Grado minimo (T): " << T << endl;
    cout << "Claves por nodo: " << (T-1) << " a " << (2*T-1) << endl;
    cout << "\nCOMPLEJIDAD ALGORITMICA (Big O):" << endl;
    cout << "- Búsqueda:    O(log n)" << endl;
    cout << "- Inserción:   O(log n)" << endl;
    cout << "- Eliminación: O(log n)" << endl;
    cout << "\nDonde n = numero de registros" << endl;
    cout << "Log base " << T << " (debido al grado del árbol)" << endl;
    cout << "========================================" << endl;
}

void realizarBenchmark() {
    cout << "\n========================================" << endl;
    cout << "       BENCHMARK DE RENDIMIENTO" << endl;
    cout << "========================================" << endl;
    
    if (arbolGlobal->obtenerNumRegistros() == 0) {
        cout << "No hay registros para realizar el benchmark" << endl;
        return;
    }
    
    const int NUM_PRUEBAS = 1000;
    GeneradorDatos generador;
    
    // Benchmark de BÚSQUEDA
    cout << "\n1. BENCHMARK DE BUSQUEDA (" << NUM_PRUEBAS << " busquedas):" << endl;
    
    long long tiempoTotalBusqueda = 0;
    int busquedasExitosas = 0;
    
    // Obtener algunos DNIs existentes
    vector<Persona*> personas = arbolGlobal->obtenerTodasPersonas();
    
    for (size_t i = 0; i < NUM_PRUEBAS && i < personas.size(); i++) {
        string dni = personas[i]->getDNI();
        
        auto inicio = chrono::high_resolution_clock::now();
        Persona* resultado = arbolGlobal->buscar(dni);
        auto fin = chrono::high_resolution_clock::now();
        
        auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
        tiempoTotalBusqueda += duracion.count();
        
        if (resultado != nullptr) {
            busquedasExitosas++;
        }
    }
    
    cout << "   - Tiempo promedio: " << (tiempoTotalBusqueda / NUM_PRUEBAS) << " µs" << endl;
    cout << "   - Búsquedas exitosas: " << busquedasExitosas << " / " << NUM_PRUEBAS << endl;
    
    // Benchmark de INSERCIÓN
    cout << "\n2. BENCHMARK DE INSERCION (100 inserciones):" << endl;
    
    long long tiempoTotalInsercion = 0;
    
    for (int i = 0; i < 100; i++) {
        Persona* p = new Persona();
        *p = generador.generarPersona();
        
        auto inicio = chrono::high_resolution_clock::now();
        arbolGlobal->insertar(p);
        auto fin = chrono::high_resolution_clock::now();
        
        auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
        tiempoTotalInsercion += duracion.count();
    }
    
    cout << "   - Tiempo promedio: " << (tiempoTotalInsercion / 100) << " µs" << endl;
    
    // Benchmark de ELIMINACIÓN
    cout << "\n3. BENCHMARK DE ELIMINACION (100 eliminaciones):" << endl;
    
    long long tiempoTotalEliminacion = 0;
    
    for (size_t i = 0; i < 100 && i < personas.size(); i++) {
        string dni = personas[personas.size() - 1 - i]->getDNI();
        
        auto inicio = chrono::high_resolution_clock::now();
        arbolGlobal->eliminar(dni);
        auto fin = chrono::high_resolution_clock::now();
        
        auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
        tiempoTotalEliminacion += duracion.count();
    }
    
    cout << "   - Tiempo promedio: " << (tiempoTotalEliminacion / 100) << " µs" << endl;
    
    cout << "\n========================================" << endl;
    cout << "ANALISIS DE COMPLEJIDAD ESPACIAL:" << endl;
    cout << "----------------------------------------" << endl;
    long long registros = arbolGlobal->obtenerNumRegistros();
    long long bytesPersona = sizeof(Persona);
    long long bytesNodo = sizeof(long long) * (2*T-1) + sizeof(void*) * (2*T-1 + 2*T);
    
    cout << "Memoria por registro: ~" << bytesPersona << " bytes" << endl;
    cout << "Memoria por nodo interno: ~" << bytesNodo << " bytes" << endl;
    cout << "Total de registros: " << registros << endl;
    cout << "Memoria aproximada: ~" << (registros * bytesPersona / 1024 / 1024) << " MB" << endl;
    cout << "========================================" << endl;
}

void guardarYSalir() {
    cout << "\n--- GUARDANDO DATOS ---" << endl;
    
    auto inicio = chrono::high_resolution_clock::now();
    bool exito = Persistencia::guardarArbolB(arbolGlobal, ARCHIVO_DATOS);
    auto fin = chrono::high_resolution_clock::now();
    
    auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio);
    
    if (exito) {
        cout << "Datos guardados exitosamente en " << duracion.count() << " segundos" << endl;
    } else {
        cout << "Error al guardar los datos" << endl;
    }
    
    // Liberar memoria
    delete arbolGlobal;
    
    cout << "\n¡Hasta pronto!" << endl;
}