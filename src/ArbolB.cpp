#include "../include/ArbolB.h"
#include <iostream>
#include <chrono>
using namespace std;

// ==================== CONSTRUCTOR Y DESTRUCTOR DEL ÁRBOL ====================

ArbolB::ArbolB() {
    raiz = nullptr;
    grado = T;
    numRegistros = 0;
}

ArbolB::~ArbolB() {
    if (raiz != nullptr) {
        delete raiz;
    }
}

// Convierte un DNI string a número long long para comparaciones más eficientes
long long ArbolB::dniANumero(const string& dni) const {
    try {
        return stoll(dni);
    } catch (...) {
        return 0;
    }
}

// ==================== CONSTRUCTOR Y DESTRUCTOR DEL NODO ====================

ArbolB::NodoB::NodoB(bool hoja) {
    esHoja = hoja;
    claves = new long long[2 * T - 1];
    personas = new Persona*[2 * T - 1];
    hijos = new NodoB*[2 * T];
    numClaves = 0;
    
    // Inicializar punteros a nullptr
    for (int i = 0; i < 2 * T - 1; i++) {
        personas[i] = nullptr;
    }
    for (int i = 0; i < 2 * T; i++) {
        hijos[i] = nullptr;
    }
}

ArbolB::NodoB::~NodoB() {
    // Eliminar recursivamente los nodos hijos
    if (!esHoja) {
        for (int i = 0; i <= numClaves; i++) {
            if (hijos[i] != nullptr) {
                delete hijos[i];
            }
        }
    }
    
    // Liberar memoria de los arrays
    delete[] claves;
    delete[] personas;
    delete[] hijos;
}

// ==================== INSERCIÓN ====================

void ArbolB::insertar(Persona* persona) {
    long long dni = dniANumero(persona->getDNI());
    
    // Si el árbol está vacío, crear la raíz
    if (raiz == nullptr) {
        raiz = new NodoB(true);
        raiz->claves[0] = dni;
        raiz->personas[0] = persona;
        raiz->numClaves = 1;
        numRegistros++;
        return;
    }
    
    // Si la raíz está llena, dividirla
    if (raiz->numClaves == 2 * grado - 1) {
        NodoB *nuevaRaiz = new NodoB(false);
        nuevaRaiz->hijos[0] = raiz;
        nuevaRaiz->dividirHijo(0, raiz);
        
        int i = 0;
        if (nuevaRaiz->claves[0] < dni) {
            i++;
        }
        nuevaRaiz->hijos[i]->insertarNoLleno(dni, persona);
        
        raiz = nuevaRaiz;
    } else {
        raiz->insertarNoLleno(dni, persona);
    }
    
    numRegistros++;
}

void ArbolB::NodoB::insertarNoLleno(long long dni, Persona* persona) {
    int i = numClaves - 1;
    
    if (esHoja) {
        // Insertar en nodo hoja
        while (i >= 0 && claves[i] > dni) {
            claves[i + 1] = claves[i];
            personas[i + 1] = personas[i];
            i--;
        }
        claves[i + 1] = dni;
        personas[i + 1] = persona;
        numClaves++;
    } else {
        // Insertar en nodo interno
        while (i >= 0 && claves[i] > dni) {
            i--;
        }
        
        if (hijos[i + 1]->numClaves == 2 * T - 1) {
            dividirHijo(i + 1, hijos[i + 1]);
            if (claves[i + 1] < dni) {
                i++;
            }
        }
        hijos[i + 1]->insertarNoLleno(dni, persona);
    }
}

void ArbolB::NodoB::dividirHijo(int indice, NodoB *hijo) {
    NodoB *nuevoNodo = new NodoB(hijo->esHoja);
    nuevoNodo->numClaves = T - 1;
    
    // Copiar las últimas T-1 claves del hijo al nuevo nodo
    for (int j = 0; j < T - 1; j++) {
        nuevoNodo->claves[j] = hijo->claves[j + T];
        nuevoNodo->personas[j] = hijo->personas[j + T];
    }
    
    // Copiar los últimos T hijos si no es hoja
    if (!hijo->esHoja) {
        for (int j = 0; j < T; j++) {
            nuevoNodo->hijos[j] = hijo->hijos[j + T];
        }
    }
    
    hijo->numClaves = T - 1;
    
    // Hacer espacio para el nuevo hijo
    for (int j = numClaves; j >= indice + 1; j--) {
        hijos[j + 1] = hijos[j];
    }
    hijos[indice + 1] = nuevoNodo;
    
    // Mover la clave del medio hacia arriba
    for (int j = numClaves - 1; j >= indice; j--) {
        claves[j + 1] = claves[j];
        personas[j + 1] = personas[j];
    }
    claves[indice] = hijo->claves[T - 1];
    personas[indice] = hijo->personas[T - 1];
    numClaves++;
}

// ==================== BÚSQUEDA ====================

Persona* ArbolB::buscar(const string& dni) {
    if (raiz == nullptr) {
        return nullptr;
    }
    long long dniNum = dniANumero(dni);
    return raiz->buscar(dniNum);
}

Persona* ArbolB::NodoB::buscar(long long dni) {
    int i = 0;
    
    // Encontrar la primera clave mayor o igual al DNI buscado
    while (i < numClaves && dni > claves[i]) {
        i++;
    }
    
    // Si encontramos el DNI, retornar la persona
    if (i < numClaves && claves[i] == dni) {
        return personas[i];
    }
    
    // Si es hoja, el DNI no existe
    if (esHoja) {
        return nullptr;
    }
    
    // Buscar en el hijo apropiado
    return hijos[i]->buscar(dni);
}

// ==================== ELIMINACIÓN ====================

void ArbolB::eliminar(const string& dni) {
    if (raiz == nullptr) {
        cout << "Arbol vacio\n";
        return;
    }
    
    long long dniNum = dniANumero(dni);
    raiz->eliminar(dniNum);
    
    // Si la raíz quedó vacía, ajustar
    if (raiz->numClaves == 0) {
        NodoB *tmp = raiz;
        if (raiz->esHoja) {
            raiz = nullptr;
        } else {
            raiz = raiz->hijos[0];
        }
        
        if (!tmp->esHoja) {
            tmp->hijos[0] = nullptr;
        }
        delete tmp;
    }
    
    numRegistros--;
}

void ArbolB::NodoB::eliminar(long long dni) {
    int idx = encontrarClave(dni);
    
    if (idx < numClaves && claves[idx] == dni) {
        if (esHoja) {
            eliminarDeHoja(idx);
        } else {
            eliminarDeNoHoja(idx);
        }
    } else {
        if (esHoja) {
            cout << "DNI " << dni << " no existe\n";
            return;
        }
        
        bool flag = (idx == numClaves);
        
        if (hijos[idx]->numClaves < T) {
            rellenar(idx);
        }
        
        if (flag && idx > numClaves) {
            hijos[idx - 1]->eliminar(dni);
        } else {
            hijos[idx]->eliminar(dni);
        }
    }
}

int ArbolB::NodoB::encontrarClave(long long dni) {
    int idx = 0;
    while (idx < numClaves && claves[idx] < dni) {
        ++idx;
    }
    return idx;
}

void ArbolB::NodoB::eliminarDeHoja(int idx) {
    for (int i = idx + 1; i < numClaves; ++i) {
        claves[i - 1] = claves[i];
        personas[i - 1] = personas[i];
    }
    numClaves--;
}

void ArbolB::NodoB::eliminarDeNoHoja(int idx) {
    long long dni = claves[idx];
    
    if (hijos[idx]->numClaves >= T) {
        long long pred = obtenerPredecesor(idx);
        claves[idx] = pred;
        hijos[idx]->eliminar(pred);
    } else if (hijos[idx + 1]->numClaves >= T) {
        long long succ = obtenerSucesor(idx);
        claves[idx] = succ;
        hijos[idx + 1]->eliminar(succ);
    } else {
        fusionar(idx);
        hijos[idx]->eliminar(dni);
    }
}

long long ArbolB::NodoB::obtenerPredecesor(int idx) {
    NodoB *cur = hijos[idx];
    while (!cur->esHoja) {
        cur = cur->hijos[cur->numClaves];
    }
    return cur->claves[cur->numClaves - 1];
}

long long ArbolB::NodoB::obtenerSucesor(int idx) {
    NodoB *cur = hijos[idx + 1];
    while (!cur->esHoja) {
        cur = cur->hijos[0];
    }
    return cur->claves[0];
}

void ArbolB::NodoB::rellenar(int idx) {
    if (idx != 0 && hijos[idx - 1]->numClaves >= T) {
        tomarDePrevio(idx);
    } else if (idx != numClaves && hijos[idx + 1]->numClaves >= T) {
        tomarDeSiguiente(idx);
    } else {
        if (idx != numClaves) {
            fusionar(idx);
        } else {
            fusionar(idx - 1);
        }
    }
}

void ArbolB::NodoB::tomarDePrevio(int idx) {
    NodoB *hijo = hijos[idx];
    NodoB *hermano = hijos[idx - 1];
    
    for (int i = hijo->numClaves - 1; i >= 0; --i) {
        hijo->claves[i + 1] = hijo->claves[i];
        hijo->personas[i + 1] = hijo->personas[i];
    }
    
    if (!hijo->esHoja) {
        for (int i = hijo->numClaves; i >= 0; --i) {
            hijo->hijos[i + 1] = hijo->hijos[i];
        }
    }
    
    hijo->claves[0] = claves[idx - 1];
    hijo->personas[0] = personas[idx - 1];
    
    if (!hijo->esHoja) {
        hijo->hijos[0] = hermano->hijos[hermano->numClaves];
    }
    
    claves[idx - 1] = hermano->claves[hermano->numClaves - 1];
    personas[idx - 1] = hermano->personas[hermano->numClaves - 1];
    
    hijo->numClaves++;
    hermano->numClaves--;
}

void ArbolB::NodoB::tomarDeSiguiente(int idx) {
    NodoB *hijo = hijos[idx];
    NodoB *hermano = hijos[idx + 1];
    
    hijo->claves[hijo->numClaves] = claves[idx];
    hijo->personas[hijo->numClaves] = personas[idx];
    
    if (!hijo->esHoja) {
        hijo->hijos[hijo->numClaves + 1] = hermano->hijos[0];
    }
    
    claves[idx] = hermano->claves[0];
    personas[idx] = hermano->personas[0];
    
    for (int i = 1; i < hermano->numClaves; ++i) {
        hermano->claves[i - 1] = hermano->claves[i];
        hermano->personas[i - 1] = hermano->personas[i];
    }
    
    if (!hermano->esHoja) {
        for (int i = 1; i <= hermano->numClaves; ++i) {
            hermano->hijos[i - 1] = hermano->hijos[i];
        }
    }
    
    hijo->numClaves++;
    hermano->numClaves--;
}

void ArbolB::NodoB::fusionar(int idx) {
    NodoB *hijo = hijos[idx];
    NodoB *hermano = hijos[idx + 1];
    
    hijo->claves[T - 1] = claves[idx];
    hijo->personas[T - 1] = personas[idx];
    
    for (int i = 0; i < hermano->numClaves; ++i) {
        hijo->claves[i + T] = hermano->claves[i];
        hijo->personas[i + T] = hermano->personas[i];
    }
    
    if (!hijo->esHoja) {
        for (int i = 0; i <= hermano->numClaves; ++i) {
            hijo->hijos[i + T] = hermano->hijos[i];
            hermano->hijos[i] = nullptr;
        }
    }
    
    for (int i = idx + 1; i < numClaves; ++i) {
        claves[i - 1] = claves[i];
        personas[i - 1] = personas[i];
    }
    
    for (int i = idx + 2; i <= numClaves; ++i) {
        hijos[i - 1] = hijos[i];
    }
    
    hijo->numClaves += hermano->numClaves + 1;
    numClaves--;
    
    delete hermano;
}

// ==================== RECORRIDO ====================

void ArbolB::recorrer() {
    if (raiz != nullptr) {
        raiz->recorrer();
    }
    cout << endl;
}

void ArbolB::NodoB::recorrer() {
    int i;
    for (i = 0; i < numClaves; i++) {
        if (!esHoja) {
            hijos[i]->recorrer();
        }
        cout << claves[i] << " ";
    }
    
    if (!esHoja) {
        hijos[i]->recorrer();
    }
}

// ==================== MÉTODOS AUXILIARES ====================

void ArbolB::NodoB::recolectarPersonas(vector<Persona*>& lista) {
    int i;
    for (i = 0; i < numClaves; i++) {
        if (!esHoja) {
            hijos[i]->recolectarPersonas(lista);
        }
        lista.push_back(personas[i]);
    }
    
    if (!esHoja) {
        hijos[i]->recolectarPersonas(lista);
    }
}

vector<Persona*> ArbolB::obtenerTodasPersonas() {
    vector<Persona*> lista;
    if (raiz != nullptr) {
        raiz->recolectarPersonas(lista);
    }
    return lista;
}

// ==================== MEDICIÓN DE TIEMPOS ====================

void ArbolB::medirTiempoBusqueda(const string& dni) {
    auto inicio = chrono::high_resolution_clock::now();
    Persona* resultado = buscar(dni);
    auto fin = chrono::high_resolution_clock::now();
    
    auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
    
    cout << "Tiempo de busqueda: " << duracion.count() << " microsegundos" << endl;
    if (resultado != nullptr) {
        cout << "Registro encontrado: " << resultado->getDNI() << endl;
    } else {
        cout << "Registro no encontrado" << endl;
    }
}

void ArbolB::medirTiempoInsercion(Persona* persona) {
    auto inicio = chrono::high_resolution_clock::now();
    insertar(persona);
    auto fin = chrono::high_resolution_clock::now();
    
    auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
    cout << "Tiempo de insercion: " << duracion.count() << " microsegundos" << endl;
}

void ArbolB::medirTiempoEliminacion(const string& dni) {
    auto inicio = chrono::high_resolution_clock::now();
    eliminar(dni);
    auto fin = chrono::high_resolution_clock::now();
    
    auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
    cout << "Tiempo de eliminacion: " << duracion.count() << " microsegundos" << endl;
}