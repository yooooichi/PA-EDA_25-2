#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>
using namespace std;

class Persona {
private:
    string DNI;
    string Nombres;
    string Apellidos;
    string Nacionalidad;
    string Lugar_Nacimiento;
    string Direccion;
    string Telefono;
    string Correo;
    string Estado_C;

public:
    Persona();
    Persona(string dni, string nombres, string apellidos, 
            string nacionalidad, string lugar_nacimiento, 
            string direccion, string telefono, 
            string correo, string estado_c);

    string getDNI() const { return DNI; }
    string getNombres() const { return Nombres; }
    string getApellidos() const { return Apellidos; }
    string getNacionalidad() const { return Nacionalidad; }
    string getLugar_Nacimiento() const { return Lugar_Nacimiento; }
    string getDireccion() const { return Direccion; }
    string getTelefono() const { return Telefono; }
    string getCorreo() const { return Correo; }
    string getEstado() const { return Estado_C; }

    void setDNI(string x) { DNI = x; }
    void setNombres(string x) { Nombres = x; }
    void setApellidos(string x) { Apellidos = x; }
    void setNacionalidad(string x) { Nacionalidad = x; }
    void setLugar_Nacimiento(string x) { Lugar_Nacimiento = x; }
    void setDireccion(string x) { Direccion = x; }
    void setTelefono(string x) { Telefono = x; }
    void setCorreo(string x) { Correo = x; }
    void setEstado(string x) { Estado_C = x; }
    
    void MostrarPersona() const;
    string toCSV() const;
};

#endif