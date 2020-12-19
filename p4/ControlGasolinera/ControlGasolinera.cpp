//*****************************************************************
// File:   ControlGasolinera.cpp
// Author: PSCD-Unizar
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
   //  ...
};

ControlGasolinera::ControlGasolinera(const int NS, Logger *logger) {
   //  ...
};

   //  ...