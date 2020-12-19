
//*****************************************************************
// File:   Servidor.cpp
// Author: PSCD-Unizar
// Date:   noviembre 2015
// Coms:   Ejemplo de servidor con comunicación síncrona mediante sockets
//         Compilar el fichero "Makefile" asociado, mediante
//         "make".
//*****************************************************************

#include <iostream>
#include <thread>
#include "Socket.hpp"

using namespace std;

const int MESSAGE_SIZE = 4001; //mensajes de no más 4000 caracteres

//-------------------------------------------------------------
// Cuenta el número de vocales existentes en un mensaje
// PRE: 
// POST: Devuelve el número de vocales existentes en el mensaje 'message'
int cuentaVocales(string message) {
	int count = 0;

	for (int i=0; i < message.length(); i++) {

		switch(message[i]) {
			case 'a': case 'A': 
			case 'e': case 'E': 
			case 'i': case 'I': 
			case 'o': case 'O': 
			case 'u': case 'U': 
						count++;
					  	break;
		}
	}

	return count;
}

//-------------------------------------------------------------
void multicliente(Socket& socket,int socket_fd,int client_fd,int error_code){
	char MENS_FIN[]="END OF SERVICE";

	// Buffer para recibir el mensaje
	int length = 100;
	string buffer;

	bool out = false; // Inicialmente no salir del bucle
	while (!out) {
		// Recibimos el mensaje del cliente
		int rcv_bytes = socket.Recv(client_fd, buffer, MESSAGE_SIZE);
		if(rcv_bytes == -1) {
			string mensError(strerror(errno));
    		cerr << "Error al recibir datos: " + mensError + "\n";
			// Cerramos los sockets
			socket.Close(client_fd);
			socket.Close(socket_fd);
		}

		cout << "Mensaje recibido: '" + buffer + "'\n";

		// Si recibimos "END OF SERVICE" --> Fin de la comunicación
		if (buffer == MENS_FIN) {
			out = true; // Salir del bucle
		} else {
			// Contamos las vocales recibidas en el mensaje anterior
			int num_vocales = cuentaVocales(buffer);

			// Enviamos la respuesta
			string resp = to_string(num_vocales);
		
			int send_bytes = socket.Send(client_fd, resp);
			if(send_bytes == -1) {
				string mensError(strerror(errno));
    			cerr << "Error al enviar datos: " + mensError + "\n";
				// Cerramos los sockets
				socket.Close(client_fd);
				socket.Close(socket_fd);
				exit(1);
			}
		}
	}

	// Cerramos el socket del cliente
    error_code = socket.Close(client_fd);
    if (error_code == -1) {
    	string mensError(strerror(errno));
    	cerr << "Error cerrando el socket del cliente: " + mensError + "\n";
    }
}

//-------------------------------------------------------------
int main(int argc, char* argv[]) {
	// Orden de los parámetros a introducir: ./Cliente IP puerto
	if(argc != 2){
		exit(1);
	}
	// Numero de conexiones maximas
	int N = 10;
	// Puerto donde escucha el proceso servidor
    int SERVER_PORT = atoi(argv[1]);
	
	thread P[N];
    int client_fd[N];
	
	// Creación del socket con el que se llevará a cabo
	// la comunicación con el servidor.
	Socket socket(SERVER_PORT);

	// Bind 
	int socket_fd =socket.Bind();
	if (socket_fd == -1) {
		string mensError(strerror(errno));
    	cerr << "Error en el bind: " + mensError + "\n";
		exit(1);
	}

	// Listen
    int max_connections = N;
	int error_code = socket.Listen(max_connections);
	if (error_code == -1) {
		string mensError(strerror(errno));
    	cerr << "Error en el listen: " + mensError + "\n";
		// Cerramos el socket
		socket.Close(socket_fd);
		exit(1);
	}
	
	for(int i=0; i<max_connections; i++){
		// Accept
		client_fd[i] = socket.Accept();

		if(client_fd[i] == -1) {
			string mensError(strerror(errno));
    		cerr << "Error en el accept: " + mensError + "\n";
			// Cerramos el socket
			socket.Close(socket_fd);
			exit(1);
		}

		P[i] = thread(&multicliente,ref(socket),socket_fd,client_fd[i],error_code);
	}
	
	for(int i=0; i<max_connections; i++){
		P[i].join();
	}
	
	// Cerramos el socket del servidor
    error_code = socket.Close(socket_fd);
    if (error_code == -1) {
    	string mensError(strerror(errno));
    	cerr << "Error cerrando el socket del servidor: " + mensError + "\n";
    }
	// Mensaje de despedida
	cout << "Bye bye" << endl;

    return error_code;
}
