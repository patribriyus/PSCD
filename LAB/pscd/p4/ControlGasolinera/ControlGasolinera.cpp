//*****************************************************************
// File:   ControlGasolinera.cpp
// Author: Patricia Briones Yus, 735576
// Date:   noviembre 2018
// Coms:   Completar para la práctica 4
//*****************************************************************

#include "ControlGasolinera.hpp"
#include <cassert>


//si DEBUG_MODE, generará eventos en log; si no, no hará nada
#if DEBUG_MODE 
    #define LOG(l,s) l->addMessage(s); //LOG(log, mensaje): añade "mensaje" evento en "log"
#else
    #define LOG(l,s)                   //LOG(log, mensaje): no hace nada
#endif

//-----------------------------------------------------
ControlGasolinera::ControlGasolinera(const int NS) {
	this->NS = NS;
	log = NULL;
	nLibres = NS;
	surtidor = new bool [NS-1];
	for(int i=0; i<NS; i++){
		surtidor[i] = true;
	}
};

ControlGasolinera::ControlGasolinera(const int NS, Logger *logger) {
	this->NS = NS;
	log = logger;
	nLibres = NS;
	surtidor = new bool [NS-1];
	for(int i=0; i<NS; i++){
		surtidor[i] = true;	// Todos los surtidores están libres
	}
};

ControlGasolinera::~ControlGasolinera(){
	delete[] surtidor;
};

void ControlGasolinera::dameSurtidor(int &surt){
	unique_lock<mutex> lck(mtx);
	LOG(log, "BEGIN_FUNC_PROC, dameSurtidor," + to_string(nLibres));
	while(nLibres==0 || mantenimiento){	// Si no hay sitio o esta en mantenimiento, espera
		esperandoSurt.wait(lck);
	}
	int i=0;
	while(!surtidor[i]){i++;}
	nLibres--;
	surt = i;
	surtidor[i] = false;	// Ocupa el surtidor
	LOG(log, "END_FUNC_PROC, dameSurtidor," + to_string(nLibres));
};

void ControlGasolinera::dejoSurtidor(const int surt){
	unique_lock<mutex> lck(mtx);
	LOG(log, "BEGIN_FUNC_PROC, dejoSurtidor," + to_string(nLibres));
	surtidor[surt] = true;
	nLibres++;
	if(mantenimiento && nLibres==NS){
		// Si se está esperando para la revisión y están todos los surtidores libres, se avisa al de mantenimiento
		esperandoMant.notify_all();
	}
	else{
		esperandoSurt.notify_all();
	}
	LOG(log, "END_FUNC_PROC, dejoSurtidor," + to_string(nLibres));
};

void ControlGasolinera::beginMantenimiento(){
	unique_lock<mutex> lck(mtx);
	LOG(log, "BEGIN_FUNC_PROC, beginMantenimiento," + to_string(nLibres));
	mantenimiento = true;
	while(nLibres!=NS){	// Si no están todos los surtidores libres
		// Entonces espera a que estén todos libres
		esperandoMant.wait(lck);
	}
	LOG(log, "END_FUNC_PROC, beginMantenimiento," + to_string(nLibres));
};

void ControlGasolinera::endMantenimiento(){
	unique_lock<mutex> lck(mtx);
	LOG(log, "BEGIN_FUNC_PROC, endMantenimiento," + to_string(nLibres));
	mantenimiento = false;
	esperandoSurt.notify_all();
	LOG(log, "END_FUNC_PROC, endMantenimiento," + to_string(nLibres));
};