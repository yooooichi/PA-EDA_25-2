#include "../include/persona.h"

Persona::Persona(){
    DNI = "";
    Nombres = "";
    Apellidos = "";
    Nacionalidad = "";
    Lugar_Nacimiento = "";
    Direccion = "";
    Telefono = "";
    Correo = "";
    Estado_C = "";
}
Persona::Persona(string dni, string nombres, string apellidos, 
                 string nacionalidad, string lugar_nacimiento, 
                 string direccion, string telefono, 
                 string correo, string estado_c) {
    DNI = dni;
    Nombres = nombres;
    Apellidos = apellidos;
    Nacionalidad = nacionalidad;
    Lugar_Nacimiento = lugar_nacimiento;
    Direccion = direccion;
    Telefono = telefono;
    Correo = correo;
    Estado_C = estado_c;
}
void Persona::MostrarPersona() const {
    cout << "DNI: " << DNI << endl;
    cout << "Nombres: " << Nombres << endl;
    cout << "Apellidos: " << Apellidos << endl;
    cout << "Nacionalidad: " << Nacionalidad << endl;
    cout << "Lugar de nacimiento: " << Lugar_Nacimiento << endl;
    cout << "Dirección: " << Direccion << endl;
    cout << "Telefono: " << Telefono << endl;
    cout << "Correo: " << Correo << endl;
    cout << "Estado civil: " << Estado_C << endl;
    cout << "----------------------------------------" << endl;
}
string Persona::toCSV() const {
    return DNI + "," + Nombres + "," + Apellidos + "," + 
           Nacionalidad + "," + Lugar_Nacimiento + "," + 
           Direccion + "," + Telefono + "," + Correo + "," + Estado_C;
}
