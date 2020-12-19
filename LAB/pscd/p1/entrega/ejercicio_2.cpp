//*****************************************************************
// File:   ejercicio_2.cpp
// Author: Patricia Briones Yus
// Date:   septiembre 2018
// Coms:   Parte del práctica 1 de PSCD
//         Compilar mediante
//           g++ -std=c++11 -pthread ejercicio_2.cpp -o ejercicio_2
//*****************************************************************

#include <iostream>
#include <thread>
#include <string>
#include <chrono>

using namespace std;

void saludo(string m, int retardo, int veces) {
    for(int i=1; i<=veces; i++) {
        cout << m+"\n";
        this_thread::sleep_for(chrono::milliseconds(retardo));
    }
}

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
    srand(time(NULL));
    string m;
    thread P[N];

    for(int i = 0; i < N; i++){
	mensaje(i+1, m);
	P[i] = thread(&saludo, m, aleatorio(100,300), aleatorio(5,15));
    }
	
    for(int j = 0; j < N; j++){
	P[j].join();
    }

    cout << "Fin\n";
    return 0;
}