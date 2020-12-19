//*****************************************************************
// File:   main_p3_e1.cpp (esqueleto)
// Author: PSCD-Unizar
// Date:   octubre 2018
// Coms:   Parte del práctica 1 de PSCD
//         Compilar mediante el makefile asociado
//         Invocación: main_p3_e1 nProcs nVeces
//*****************************************************************

#include <iostream>
#include <thread>
#include <string>
#include "ConcurrentBoundedQueue.hpp"

using namespace std;

//-----------------------------------------------------
// ...
//-----------------------------------------------------
int main(int argc, char* argv[]) {
    const int N = 10; //tamaño de la cola

    #if DEBUG_MODE
        Logger logger("elLog.log");
        ConcurrentBoundedQueue<int> cbq(N, &logger);
    #else
        ConcurrentBoundedQueue<int> cbq(N);
    #endif

    // ...

    cbq.print();
    return 0;
}