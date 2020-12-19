//*****************************************************************
// File:   main_p3_e1.cpp
// Author: PSCD-Unizar
// Date:   octubre 2018
// Coms:   Parte del práctica 1 de PSCD
//         Compilar mediante el makefile asociado
//*****************************************************************

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include "ConcurrentBoundedQueue.hpp"

using namespace std;

//-----------------------------------------------------
void insertar(ConcurrentBoundedQueue<int>& cbq){
	srand(time(NULL));
	for(int i=1; i<=9; i++){
		cbq.enqueue(rand());
	}
}

void sacar(ConcurrentBoundedQueue<int>& cbq){
	for(int i=1; i<=8; i++){
		cbq.dequeue();
	}
}
//-----------------------------------------------------
int main(int argc, char* argv[]) {
	const int N = 10; //tamano de la cola

	#if DEBUG_MODE
		Logger logger("elLog.log");
	        ConcurrentBoundedQueue<int> cbq(N, &logger);
	#else
		ConcurrentBoundedQueue<int> cbq(N);
	#endif

	thread P[N];	// vector de threads
	for(int i = 0; i < 5; i++){
		P[i] = thread(&insertar,ref(cbq));
	}

	for(int i = 5; i < N; i++){
		P[i] = thread(&sacar,ref(cbq));
	}
	
	for(int j = 0; j < N; j++){
		P[j].join();
	}

	cbq.print();
	return 0;
}