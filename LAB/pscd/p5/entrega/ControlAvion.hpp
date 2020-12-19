//*****************************************************************
// File:   ControlAvion.hpp
// Author: Patricia Briones Yus, 735576
// Date:   noviembre 2018
// Coms:   
//*****************************************************************

#ifndef CONTROL_AVION
#define CONTROL_AVION

#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>

using namespace std;

class ControlAvion {
public:
    //----------------- Constructores
    // <nP>: número de asientos por fila
	// <nF>: número de filas en el avión
    ControlAvion(const int nP, const int nF);

    //----------------- Destructor
    ~ControlAvion();
	
	// Se reserva el asiento indicado si este está libre y devuelve un mensaje informando de la reserva
	// Si el asiento está ocupado devuelve un mensaje informando de las plazas disponibles
	// Si el avión está completo devuelve un mensaje de vuelo completo
	void reservarPlaza(const int fila, const string plaza, string& mensaje);

private:
    int nLibres; 	//num de plazas libres
	int nPlazas;	// Num de asientos por fila
	int nFilas; 	// Num de filas
	bool* asiento;	// Puntero a cada estado de cada asiento (false = no reservado)
	mutex mtx;
	int convertirPlaza(const string letra); // Devuelve el número de asiento correspondiente a la letra
};
#endif