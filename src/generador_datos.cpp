#include "../include/generador_datos.h"
#include <random>
#include <algorithm>
#include <set>
using namespace std;

// Set estático para rastrear DNIs ya generados y evitar duplicados
static set<string> dnisGenerados;

string GeneradorDatos::generarDNI() {
    // Generar DNI aleatorio único
    string dni;
    int intentos = 0;
    const int MAX_INTENTOS = 1000;
    
    do {
        // Generar número aleatorio de 8 dígitos
        int num = 10000000 + (rand() % 90000000);
        dni = to_string(num);
        intentos++;
        
        // Si después de muchos intentos no encontramos uno único,
        // significa que estamos cerca del límite (99,999,999 DNIs posibles)
        if (intentos > MAX_INTENTOS) {
            // En este caso, generamos uno secuencial
            static long long ultimoDNI = 10000000;
            dni = to_string(ultimoDNI++);
            break;
        }
        
    } while (dnisGenerados.find(dni) != dnisGenerados.end());
    
    // Registrar el DNI como usado
    dnisGenerados.insert(dni);
    
    return dni;
}

Persona GeneradorDatos::generarPersona() {
    string dni = generarDNI();
    
    // Seleccionar datos aleatorios
    string nombre = nombres[rand() % nombres.size()];
    string apellido1 = apellidos[rand() % apellidos.size()];
    string apellido2 = apellidos[rand() % apellidos.size()];
    string nacionalidad = nacionalidades[rand() % nacionalidades.size()];
    string departamento = departamentos[rand() % departamentos.size()];
    string estado_civil = estados_civiles[rand() % estados_civiles.size()];
    
    // Generar datos derivados
    string nombres_completos = nombre;
    string apellidos_completos = apellido1 + " " + apellido2;
    string lugar_nacimiento = departamento;
    
    // Generar dirección
    vector<string> tiposVia = {"Av.", "Jr.", "Ca.", "Psje."};
    string via = tiposVia[rand() % tiposVia.size()];
    string direccion = via + " " + departamento + " #" + to_string(100 + (rand() % 9900));
    
    // Generar teléfono (formato peruano: 9XXXXXXXX)
    string telefono = "9" + to_string(10000000 + (rand() % 90000000));
    
    // Generar correo
    string correo_limpio = nombre;
    transform(correo_limpio.begin(), correo_limpio.end(), correo_limpio.begin(), ::tolower);
    string correo = correo_limpio + "." + to_string(rand() % 10000) + "@gmail.com";
    
    // Crear objeto Persona
    Persona p;
    p.setDNI(dni);
    p.setNombres(nombres_completos);
    p.setApellidos(apellidos_completos);
    p.setNacionalidad(nacionalidad);
    p.setLugar_Nacimiento(lugar_nacimiento);
    p.setDireccion(direccion);
    p.setTelefono(telefono);
    p.setCorreo(correo);
    p.setEstado(estado_civil);
    
    return p;
}

vector<Persona> GeneradorDatos::generarPersonas(int cantidad) {
    vector<Persona> personas;
    
    // Inicializar generador de números aleatorios
    srand(time(0));
    
    cout << "Generando " << cantidad << " registros unicos..." << endl;
    
    for (int i = 0; i < cantidad; i++) {
        personas.push_back(generarPersona());
        
        // Mostrar progreso cada 10,000 registros
        if ((i + 1) % 10000 == 0) {
            cout << "Generados: " << (i + 1) << " / " << cantidad << endl;
        }
    }
    
    cout << "Generacion completada" << endl;
    return personas;
}