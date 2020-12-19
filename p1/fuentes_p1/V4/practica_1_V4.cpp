//*****************************************************************
// File:   practica_1_V4.cpp
// Author: PSCD-Unizar
// Date:   septiembre 2016
// Coms:   Parte del práctica 1 de PSCD
//         Compilar mediante el makefile asociado
//           make -f Makefile_V4
//         Se trata de versión V3, pero llevando a cabo una compilación separada
//         usando la utilidad "makefile"
//*****************************************************************

#include <iostream>
#include <thread>
#include <string>

#include "Saludador.hpp"

using namespace std;

//-----------------------------------------------------
int main() {

    //creación de los objetos: constructor con datos
    Saludador s1("Soy 1", 100, 10),
              s2("\tSoy 2", 150, 15),
              s3("\t\tSoy 3", 10, 40);
    //creación de los objetos: constructor por defecto         
    Saludador s4;

    //le damos datos a s4
    s4 = {"\t\t\tSoy 4", 2, 12};
    //equivalente a 
    // s4.mens = "\t\t\tSoy 4"; s4.retardo = 2; ...
    cout << "veces: " << s4.veces << endl;
    //puesta en ejecución
    thread th_1 = thread(&Saludador::run, s1);
    thread th_2 = thread(&Saludador::run, s2);
    thread th_3 = thread(&Saludador::run, s3);
    thread th_4 = thread(&Saludador::run, s4);
    //esperar a que vayan acabando
    th_1.join();
    th_2.join();
    th_3.join();
    th_4.join();

    return 0;
}