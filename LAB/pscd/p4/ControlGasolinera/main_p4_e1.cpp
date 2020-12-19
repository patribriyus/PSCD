//*****************************************************************
// File:   mainGasolinera.cpp
// Author: Patricia Briones Yus, 735576
// Date:   noviembre 2016
// Coms:   Parte de la práctica 4 de PSCD
//*****************************************************************

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include "ControlGasolinera.hpp"

using namespace std;

//-----------------------------------------------------
void vehiculo(ControlGasolinera& cG, int NI){
	srand(time(NULL));
	int surt, retardo;
	for(int i=0; i<NI; i++){
		cG.dameSurtidor(surt);
		// Tiempo requerido para el repostaje entre 100 y 900 milisegundos
		retardo = 100 + rand() % (900 - 100 + 1);
		this_thread::sleep_for(chrono::milliseconds(retardo));
		cG.dejoSurtidor(surt);
	}
}

void mantenimiento(ControlGasolinera& cG, int NM){
	srand(time(NULL));
	int retardo;
	for(int i=0; i<NM; i++){
		// Retardo opcional para que las revisiones estén más repartidas
		//this_thread::sleep_for(chrono::milliseconds(1000));
		cG.beginMantenimiento();
		// Tiempo requerido para la revisión de los surtidores entre 200 y 400 milisegundos
		retardo = 200 + rand() % (400 - 200 + 1);
		this_thread::sleep_for(chrono::milliseconds(retardo));
		cG.endMantenimiento();
	}
}
//-----------------------------------------------------
int main(int argc, char* argv[]) {
    const int NS = 6;  //num. de surtidores
    const int NC = 20; //num. de coches (procesos)
    const int NI = 10; //num. de iteraciones por coche
	const int NM = 10;	// num. de revisiones

    #if DEBUG_MODE
        Logger logger("elLog.log", cerr);
        ControlGasolinera cG(NS, &logger);
    #else
        ControlGasolinera cG(NS);
    #endif

    thread P[NC+1];	// vector de threads (NC los coches + 1 del mantenimiento)
	P[0] = thread(&mantenimiento,ref(cG),NM); // Proceso de revisión
	for(int i = 1; i < NC+1; i++){
		P[i] = thread(&vehiculo,ref(cG),NI);
	}
	
	for(int j = 0; j < NC+1; j++){
		P[j].join();
	}

    return 0;
}