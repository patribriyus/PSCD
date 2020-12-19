//*****************************************************************
// File:   main_p2_e2.cpp
// Author: Patricia Briones Yus
// Date:   octubre 2018
// Coms:   Parte de la practica 2 de PSCD
//         Compilar mediante
//           g++ -std=c++11 -pthread main_p2_e2.cpp -o main_p2_e2
//*****************************************************************

#include <iostream>
#include <thread>
#include <atomic>
#include <string>
#include <chrono>
#include <math.h>

using namespace std;
atomic_flag lock_stream = ATOMIC_FLAG_INIT;

const int N = 256; 		// num. de  filas
typedef double IM[N][N]; 	// matriz  de  datos
const int n = 16; 		// numero de procesos
double suma = 0.0;
int contador = 0;

// -----------------------------------------------------
//PRE:
//POST: m se ha  inicializado  con  valores  aleatorios
void generateMatrix(IM m){
	srand(time(NULL));
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			m[i][j] = double (rand() / (RAND_MAX+1.0))*100.0; // en cada posicion de la matriz se guarda un numero real aleatorio
		}
	}
}

// -----------------------------------------------------
//PRE: (0 <= i1 <= i2 <= N - 1)^(0 <= j1 <= j2 <= N - 1)
//POST: suma = sumatorio...sumatorio... A[i][j]
void addsubMatrix(IM A, int i1, int j1, int i2, int j2, double& suma){
	while(lock_stream.test_and_set()){}
	for(int i = i1; i < i2; i++){
		for(int j = j1; j < j2; j++){
			suma += A[i][j];
			contador++;
		}
	}
	lock_stream.clear();
}

int main(){
	thread P[n];	// vector de threads
	IM A;		// matriz A
	
	generateMatrix(A);	// Genera la matriz A con numeros reales aleatorios

	for(int i = 0; i < n; i++){
		P[i] = thread(&addsubMatrix,A,i*n,0,(i+1)*n,N,ref(suma));
	}

	cout << "La media global es: " << suma/double(contador) << endl;
	
	for(int j = 0; j < n; j++){
		P[j].join();
	}

	return 0;
}