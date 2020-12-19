//*****************************************************************
// File:   Saludador.hpp
// Author: PSCD-Unizar
// Date:   septiembre 2016
// Coms:   Especificación de la clase
//*****************************************************************

//-----------------------------------------------------
// Parte de especificación: variables y funciones
// de los objetos de esta clase.
// Normalmente iría en el fichero "Saludador.h"
// Dejamos todo público, para centrarnos en los conceptos
// de la concurrencia. Lo adecuado es distinguir entre
// parte pública y privada, con operadores para acceder
// a los atributos, por ejemplo. Lo estudiaréis en otras
// asignaturas

#ifndef SALUDADOR_HPP
#define SALUDADOR_HPP

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

class Saludador {
public:
    Saludador(string mens,  //constructor suministrando datos
              int retardo,
              int veces);
    Saludador(); //constructor por defecto
    void run();
    //más funciones, si las hubiera
    string mens;
    int retardo, veces;
};

#endif