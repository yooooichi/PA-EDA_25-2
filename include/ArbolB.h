#ifndef ARBOL_B_H
#define ARBOL_B_H

#include "persona.h"
#include <string>
#include <vector>
using namespace std;

// Grado mínimo del árbol B (cada nodo puede tener entre T-1 y 2T-1 claves)
const int T = 128; // Optimizado para grandes volúmenes de datos

/**
 * Árbol B para almacenar y buscar registros de personas por DNI
 * Permite búsquedas, inserciones y eliminaciones eficientes en O(log n)
 */
class ArbolB {
private:
    /**
     * Nodo interno del Árbol B
     * Cada nodo contiene:
     * - Un array de claves (DNIs convertidos a enteros)
     * - Un array de punteros a objetos Persona
     * - Un array de punteros a nodos hijos
     */
    class NodoB {
    public:
        long long *claves;          // Array de DNIs (convertidos a long long)
        Persona **personas;         // Array de punteros a objetos Persona
        NodoB **hijos;              // Array de punteros a nodos hijos
        int numClaves;              // Número actual de claves en el nodo
        bool esHoja;                // Indica si es un nodo hoja

        NodoB(bool hoja);
        ~NodoB();

        // Métodos de recorrido y búsqueda
        void recorrer();
        Persona* buscar(long long dni);
        
        // Métodos de inserción
        void insertarNoLleno(long long dni, Persona* persona);
        void dividirHijo(int indice, NodoB *hijo);
        
        // Métodos de eliminación
        void eliminar(long long dni);
        int encontrarClave(long long dni);
        void eliminarDeHoja(int idx);
        void eliminarDeNoHoja(int idx);
        long long obtenerPredecesor(int idx);
        long long obtenerSucesor(int idx);
        void rellenar(int idx);
        void tomarDePrevio(int idx);
        void tomarDeSiguiente(int idx);
        void fusionar(int idx);
        
        // Métodos para recolectar todas las personas
        void recolectarPersonas(vector<Persona*>& personas);
    };

    NodoB *raiz;                    // Puntero a la raíz del árbol
    int grado;                      // Grado mínimo del árbol
    long long numRegistros;         // Contador de registros en el árbol

    // Convierte string DNI a long long para comparaciones más rápidas
    long long dniANumero(const string& dni) const;

public:
    ArbolB();
    ~ArbolB();

    // Operaciones principales
    void insertar(Persona* persona);
    Persona* buscar(const string& dni);
    void eliminar(const string& dni);
    void recorrer();
    
    // Métodos para persistencia
    vector<Persona*> obtenerTodasPersonas();
    long long obtenerNumRegistros() const { return numRegistros; }
    
    // Métodos para análisis de complejidad
    void medirTiempoBusqueda(const string& dni);
    void medirTiempoInsercion(Persona* persona);
    void medirTiempoEliminacion(const string& dni);
};

#endif