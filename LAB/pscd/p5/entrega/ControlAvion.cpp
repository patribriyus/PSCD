//*****************************************************************
// File:   ControlAvion.cpp
// Author: Patricia Briones Yus, 735576
// Date:   noviembre 2018
// Coms:   Completar para la práctica 4
//*****************************************************************

#include "ControlAvion.hpp"
#include <cassert>
#include <iostream>

//-----------------------------------------------------
ControlAvion::ControlAvion(const int nP, const int nF) {
	nPlazas = nP;
	nFilas = nF;
	nLibres = nP*nF;
	asiento = new bool [nLibres];
	for(int i=0; i<nLibres; i++){
		asiento[i] = {false};	// Todos los asientos no están reservados
	}
};

ControlAvion::~ControlAvion(){
	delete[] asiento;
};

void ControlAvion::reservarPlaza(const int fila, const string plaza, string& mensaje){
	unique_lock<mutex> lck(mtx);
	if(nLibres != 0){
		int p = convertirPlaza(plaza);
		// Si la letra introducida existe
		if(p != 0 && fila <= 4){
			// Si el asiento no está ocupado, se reserva
			if(!asiento[nFilas*(p-1)+(fila-1)]){
				asiento[nFilas*(p-1)+(fila-1)] = true;
				mensaje = "RESERVADA:" + to_string(fila) + plaza;
				nLibres--;
			}
			else {	// Si no, se informa de las plazas disponibles
				mensaje = "PLAZA OCUPADA:";
				for(int i=0; i<nFilas; i++){
					for(int j=0; j<nPlazas; j++){
						// Si el asiento está libre
						if(!asiento[nFilas*j+i]){
							mensaje += "L";
						}
						else{
							mensaje += "X";
						}
					}
					if(i != nFilas-1){
						mensaje += "-";
					}
				}
			}
		}
		else { mensaje = "La plaza introducida no existe"; }
	} 
	else {
		mensaje = "VUELO COMPLETO";
	}
};

//-----------------------------------------------------
int ControlAvion::convertirPlaza(const string letra){
	if(letra == "A"){
		return 1;
	}
	else if(letra == "B"){
		return 2;
	}
	else if(letra == "C"){
		return 3;
	}
	else if(letra == "D"){
		return 4;
	}
	else {
		return 0;
	}
};