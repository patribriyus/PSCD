//*****************************************************************
// File:   Saludador.cpp
// Author: PSCD-Unizar
// Date:   septiembre 2016
// Coms:   Especificación de la clase
//*****************************************************************

#include "Saludador.hpp"
//-----------------------------------------------------
// Implementación (las funciones de los objetos de la clase)
// Normalmente iría en el fichero "Saludador.cpp"

Saludador::Saludador(string mens, int retardo, int veces) {
    this->mens = mens; //mens: parámetro de la función
                       //this->mens: variable propia
    this->retardo = retardo;
    this->veces = veces;
};

Saludador::Saludador() {
    mens = ""; //mens: parámetro de la función
                       //this->mens: variable propia
    retardo = 0;
    veces = 0;
};

void Saludador::run() {
    for(int i=1; i<=veces; i++) {
        cout << mens +"\n";
        this_thread::sleep_for(chrono::milliseconds(retardo));
    }
};