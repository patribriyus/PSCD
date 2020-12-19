//*****************************************************************
// File:   Cliente.cpp
// Author: PSCD-Unizar
// Date:   noviembre 2015
// Coms:   Ejemplo de cliente con comunicación síncrona mediante sockets
//        
//*****************************************************************

#include <iostream>
#include <chrono>
#include <thread>
#include "Socket.hpp"

using namespace std;

const int MESSAGE_SIZE = 4001; //mensajes de no más 4000 caracteres

int main(int argc, char* argv[]) {
	const string RESERVADA("RESERVADA:");
	const string MENS_FIN("VUELO COMPLETO");
	int contador = 0; // Cuenta el numero de asientos reservados
    // Dirección y número donde escucha el proceso servidor
    string SERVER_ADDRESS = "localhost";
    int SERVER_PORT = atoi(argv[1]);

	// Creación del socket con el que se llevará a cabo
	// la comunicación con el servidor.
	Socket socket(SERVER_ADDRESS, SERVER_PORT);

    // Conectamos con el servidor. Probamos varias conexiones
	const int MAX_ATTEMPS = 10;
	int count = 0;
	int socket_fd;
	do {
		// Conexión con el servidor
    	socket_fd = socket.Connect();
    	count++;

    	// Si error --> esperamos 1 segundo para reconectar
    	if(socket_fd == -1){
    	    this_thread::sleep_for(chrono::seconds(1));
    	}
    } while(socket_fd == -1 && count < MAX_ATTEMPS);

    // Chequeamos si se ha realizado la conexión
    if(socket_fd == -1){
    	return socket_fd;
    }

    // Buffer para almacenar la respuesta, como char[]
	string buffer;
    string mensaje;
	do{
		// Leer mensaje de la entrada estandar
		getline(cin, mensaje);
		// Enviamos el mensaje, como cadena de C
	    int send_bytes = socket.Send(socket_fd, mensaje);

	    if(send_bytes == -1){
			cerr << "Error al enviar datos: " << strerror(errno) << endl;
			// Cerramos el socket
			socket.Close(socket_fd);
			exit(1);
		}
		
		if(mensaje.substr(0,14) == "INICIO COMPRA:" || mensaje.substr(0,9) == "RESERVAR:"){
			// Recibimos la respuesta del servidor  
			int read_bytes = socket.Recv(socket_fd, buffer, MESSAGE_SIZE);
			cout << buffer << endl;
		}
		
		if(buffer.substr(0,10) == RESERVADA){
			contador++;
		}
		
	} while(buffer != MENS_FIN);

    // Cerramos el socket
    int error_code = socket.Close(socket_fd);
    if(error_code == -1){
		cerr << "Error cerrando el socket: " << strerror(errno) << endl;
    }
	
	cout << "Numero de plazas reservadas: " << contador << endl;

    return error_code;
}
