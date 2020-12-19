//*****************************************************************
// File:   ConcurrentConcurrentBoundedQueue.cpp
// Author: PSCD-Unizar
// Date:   Octubre 2018
// Coms:   Especificación de una clase cd cola limitada con gestión de acceso concurrente
//*****************************************************************

#include "ConcurrentBoundedQueue.hpp"
#include <cassert>


//-----------------------------------------------------
template <class T>
ConcurrentBoundedQueue<T>::ConcurrentBoundedQueue(const int N) {
	this->N = N;
	log = NULL;
	bq = new BoundedQueue<T>(N);
	empty();
};
//-----------------------------------------------------
template <class T>
ConcurrentBoundedQueue<T>::ConcurrentBoundedQueue(const int N, Logger *log) {
	this->N = N;
	this->log = log;
	bq = new BoundedQueue<T>(N);
	empty();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::empty() {
	mutex.setInitValue(1);
	mutex.setLogInfo(log,"mutex");

	b_hay_hueco.setInitValue(0);
	b_hay_hueco.setLogInfo(log,"b_hay_hueco");

	b_hay_dato.setInitValue(0);
	b_hay_dato.setLogInfo(log,"b_hay_dato");

	d_hay_hueco = 0;
	d_hay_dato = 0;
};
//-----------------------------------------------------
template <class T>
ConcurrentBoundedQueue<T>::~ConcurrentBoundedQueue() {
	mutex.wait();
	bq->~BoundedQueue<T>();
	mutex.signal();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::enqueue(const T d) {
	mutex.wait();
	if(bq->length()== N){
		d_hay_hueco++;
		mutex.signal();
		b_hay_hueco.wait();
	}
	bq->enqueue(d);
	AVISAR();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::dequeue() {
	mutex.wait();
	if(bq->length()==0){
		d_hay_dato++;
		mutex.signal();
		b_hay_dato.wait();		
	}
	bq->dequeue();
	AVISAR();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::first(T &f) {
	mutex.wait();
	//<await bq->length()>0
	//	f = bq->first();>
	if(bq->length()==0){
		d_hay_dato++;
		mutex.signal();
		b_hay_dato.wait();
	}
	f = bq->first();
	AVISAR();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::length(int &l) {
	mutex.wait();
	l = bq->length();
	mutex.signal();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::size(int &s) {
	mutex.wait();
	s = bq->size();
	mutex.signal();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::print() {
	mutex.wait();
	bq->print();
	mutex.signal();
};

//-----------------------------------------------------
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::AVISAR() {
	if(bq->length()<N && d_hay_hueco>0){
		d_hay_hueco--; b_hay_hueco.signal();
	}
	else if(bq->length()>0 && d_hay_dato>0){
		d_hay_dato--; b_hay_dato.signal();
	}
	else{
		mutex.signal();
	}
}