//*****************************************************************
// File:   main_p2_e1.cpp
// Author: Patricia Briones Yus
// Date:   octubre 2018
// Coms:   Parte del practica 2 de PSCD
//         Compilar mediante
//           g++ -std=c++11 -pthread main_p2_e1.cpp -o main_p2_e1
//*****************************************************************

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <math.h>

using namespace std;

const int N = 256; 		// num. de  filas
typedef double IM[N][N]; 	// matriz  de  datos
const int n = 16; 		// numero de procesos
bool finalizado[n];		// indica si el proceso n ha acabado o no

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
	suma = 0.0;
	for(int i = i1; i < i2; i++){
		for(int j = j1; j < j2; j++){
			suma += A[i][j];
		}
	}
}

// -----------------------------------------------------
//PRE: (0 <= i1 <= i2 <= N - 1)^(0 <= j1 <= j2 <= N - 1)^(i < n)
//POST: suma = sumatorio...sumatorio... A[i][j] ^ finalizado[i] = true
void subMatrix(IM A, int i1, int j1, int i2, int j2, double& suma, int i){
	addsubMatrix(A,i1,j1,i2,j2,suma);	// llamamos al proceso que suma la submatriz
	finalizado[i] = true;	// el proceso i ha finalizado
}

// -----------------------------------------------------
//PRE:
//POST: total es la media de la matriz
void informador(double vector[]){
	double total = 0.0;
	for(int i = 0; i < n; i++){
		total += vector[i];
	}
	total = total/(N*N);
	
	cout << "La media global es: " << total << endl;
}

int main(){
	thread P[n];	// vector de threads
	IM A;		// matriz A
	double vector[n];	// vector donde se guardaran la suma de las componentes de una submatriz
	
	generateMatrix(A);	// Genera la matriz A con numeros reales aleatorios

	for(int i = 0; i < n; i++){
		finalizado[i] = false;		// el proceso i no ha finalizado
		P[i] = thread(&subMatrix,A,i*n,0,(i+1)*n,N,ref(vector[i]),i);		// llamamos a un proceso secundario
	}
	
	for(int j = 0; j < n; j++){
		while(!finalizado[j]){}	// espera hasta que el proceso j haya terminado
	}

	informador(vector);
	
	for(int j = 0; j < n; j++){
		P[j].join();
	}

	return 0;
}