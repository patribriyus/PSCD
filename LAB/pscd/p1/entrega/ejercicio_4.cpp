//*****************************************************************
// File:   ejercicio_4.cpp
// Author: PSCD-Unizar
// Date:   septiembre 2018
// Coms:   Parte del práctica 1 de PSCD
//         Compilar mediante
//           g++ -std=c++11 -pthread ejercicio_4.cpp -o ejercicio_4
//*****************************************************************

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <math.h>

using namespace std;
const int N = 100;

double media(double num[]){
	double m = 0.0;
	for(int i=0; i<N; i++){
		m += num[i];	
    	}
	return m/N;
}

void max_min(double num[], double& max, double& min){
	max = num[0], min = num[0];
	for(int i=1; i<N; i++){
		if(num[i]>max){
			max = num[i];
		} else if(num[i]<min){
			min = num[i];
		}
    	}
}

double sigma(double num[], double media){
	double suma = 0.0;
	for(int i=0; i<N; i++){
		suma += pow(abs(media-num[i]),2.0);	
    	}
	return sqrt(suma/N);
}

int main() {
    double num[N];
    srand(time(NULL));
    double max, min, m, s;

    for(int i=0; i<N; i++){
	num[i] = (double(rand()) / (RAND_MAX+1.0) )*10.0;	
    }

    max_min(num,max,min);
    m = media(num);
    s = sigma(num,m);

    cout << "#datos:\t" << N << endl;
    cout << "media:\t" << m << endl;
    cout << "max:\t" << max << endl;
    cout << "min:\t" << min << endl;
    cout << "sigma:\t" << s << endl;

    return 0;
}