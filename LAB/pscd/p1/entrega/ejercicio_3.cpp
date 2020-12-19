//*****************************************************************
// File:   ejercicio_3.cpp
// Author: Patricia Briones Yus
// Date:   septiembre 2018
// Coms:   Parte del práctica 1 de PSCD
//         Compilar mediante
//           g++ -std=c++11 -pthread ejercicio_3.cpp -o ejercicio_3
//*****************************************************************

#include "Saludador.hpp"

int aleatorio(int desde, int hasta){
	return desde + rand() % (hasta - desde + 1);
}

void mensaje(int i, string& m){
	m = "Soy " + to_string(i);
	if(i > 1){
		for(int j = 1; j < i; j++){
			m = "\t" + m;
		}
	}	
}

int main() {
    const int N = 10;
    string m;
    Saludador S[N];
    thread P[N];

    for(int i = 0; i < N; i++){
	mensaje(i+1, m);
	S[i] = Saludador (m, aleatorio(100,300), aleatorio(5,15));
    }

    for(int x = 0; x < N; x++){
	P[x] = thread(&Saludador::run, S[x]);
    }
	
    for(int j = 0; j < N; j++){
	P[j].join();
    }

    cout << "Fin\n";
    return 0;
}