//*****************************************************************
// File:   mainGasolinera.cpp
// Author: PSCD-Unizar
// Date:   noviembre 2016
// Coms:   Parte de la práctica 4 de PSCD
//*****************************************************************

#include <iostream>
#include <thread>
#include <string>
#include "ControlGasolinera.hpp"

using namespace std;

//-----------------------------------------------------
int main(int argc, char* argv[]) {
    const int NS = 6;  //num. de surtidores
    const int NC = 20; //num. de coches
    const int NI = 10; //num. de iteraciones por coche

    #if DEBUG_MODE
        Logger logger("elLog.log", cerr);
        ControlGasolinera cG(NS, &logger);
    #else
        ControlGasolinera cG(NS);
    #endif

    

    return 0;
}