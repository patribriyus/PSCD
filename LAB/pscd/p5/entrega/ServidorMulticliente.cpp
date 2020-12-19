//******************************************************************
// File:   ServidorMulticliente.cpp
// Author: Patricia Briones Yus, 735576
// Date:   Diciembre 2018
// Coms:   Ejemplo de servidor multicliente con comunicación síncrona mediante sockets
//*****************************************************************

#include "Socket.hpp"
#include "ControlAvion.hpp"
#include <iostream>
#include <thread>
#include <string>
#include <cstring> //manejo de cadenas tipo C
#include <csignal>

using namespace std;
int numClientes;
bool servAbierto, clienAbierto;

//-------------------------------------------------------------
void errordos(int n){
	cout << "Un cliente ha terminado." << endl;
	clienAbierto = false;
	numClientes--;
}
void error(int n){
	signal(SIGPIPE,errordos);
	servAbierto = false;
	if(numClientes == 0){
		cout << "\n** CIERRE DEL SERVIDOR **" << endl;
		exit(0);
	}
	else {
		cout << "\n[x] Cuando no haya ningún cliente conectado --> EL SERVIDOR SE CERRARÁ." << endl;
	}
}
//-------------------------------------------------------------
void servCliente(Socket& soc, int client_fd, ControlAvion& cA) {
	string cliente;		// Nombre del cliente
	const string COMPRA("INICIO COMPRA:");
	const string BIENVENIDA("BIENVENIDO AL SERVICIO");
	const string RESERVAR("RESERVAR:");
	
	// Buffer para recibir el mensaje
	int length = 100;
	string buffer;
	
	// Si se detecta un cierre inesperado de un cliente
	signal(SIGPIPE,errordos);	
	
	bool out = false; // Inicialmente no salir del bucle
	bool permisoCompra = false;
	
	while(!out && clienAbierto) {
		// Recibimos el mensaje del cliente
		int rcv_bytes = soc.Recv(client_fd,buffer,length);
		if (rcv_bytes == -1) {
			string mensError(strerror(errno));
			cerr << "Error al recibir datos: " + mensError + "\n";
			// Cerramos los sockets
			soc.Close(client_fd);
		}
		
		// Esperamos a que el cliente envie "INICIO COMPRA:nomCliente"
		if(buffer.substr(0,14) == COMPRA && !permisoCompra){
			cliente = buffer.substr(14);
			int send_bytes = soc.Send(client_fd,BIENVENIDA);
			if(send_bytes == -1){
				string mensError(strerror(errno));
				cerr << "Error al enviar datos: " + mensError + "\n";
				// Cerramos los sockets
				soc.Close(client_fd);
				exit(1);
			}
			cout << "CLIENTE[" << numClientes <<"]: " << cliente << " ha iniciado su compra" << endl;
			permisoCompra = true;
		}
		
		// Si recibimos "RESERVAR:asiento"
		else if(buffer.substr(0,9) == RESERVAR && permisoCompra){
				string mensaje;
				
				int fila = stoi(buffer.substr(9,10));
				string plaza = buffer.substr(10,11);
				cA.reservarPlaza(fila,plaza,mensaje);

				if(mensaje.substr(0,9) == "RESERVADA"){
					cout << "\t- [OK] " << cliente << " ha reservado la plaza " << buffer.substr(9,11) << endl;
				}
				else {
					cout << "\t- [X] " << cliente << " ha intentado reservar la plaza " << buffer.substr(9,11) << endl;
				}
				
				int send_bytes = soc.Send(client_fd,mensaje);
				if(send_bytes == -1) {
					string mensError(strerror(errno));
					cerr << "Error al enviar datos: " + mensError + "\n";
					// Cerramos los sockets
					soc.Close(client_fd);
					exit(1);
				}
			}
		else {
			cout << buffer << endl;
		}
	}
	clienAbierto = true;
	soc.Close(client_fd);
	if(numClientes == 0 && !servAbierto){
		// Al ser el numClientes=0 y el servidor quiere cerrarse, salimos
		cout << "** Ningún cliente conectado. CIERRE DEL SERVIDOR **" << endl;
		exit(1);
	}
}
//-------------------------------------------------------------
int main(int argc, char* argv[]) {
	servAbierto = true;
	clienAbierto = true;
	numClientes = 0;
	
	const int nPlazas = 4;	// Num de asientos por fila
	const int nFilas = 4; // Num de filas

	// Si se detecta un ctrl+C o ctrl+Z en el servidor
	signal(SIGINT,error);
	signal(SIGTSTP,error);
	
	// Creamos el monitor que controla las plazas del avion
    ControlAvion cA(nPlazas, nFilas);
	// Numero maximo de conexiones
	const int N = 10;
	// Dirección y número donde escucha el proceso servidor
	string SERVER_ADDRESS = "localhost";
    int SERVER_PORT = atoi(argv[1]);
    thread cliente[N];
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

	for (int i=0; i<max_connections; i++) {
		// Accept
		client_fd[i] = socket.Accept();
		
		// Si el servidor se quiere cerrar no puede entrar ningun cliente más
		if(servAbierto){
			if(client_fd[i] == -1) {
				string mensError(strerror(errno));
				cerr << "Error en el accept: " + mensError + "\n";
				// Cerramos el socket
				socket.Close(socket_fd);
				exit(1);
			}
			numClientes++; // Un cliente nuevo conectado
			cout << "+ Se ha conectado un nuevo cliente." << endl;
			cliente[i] = thread(&servCliente, ref(socket), client_fd[i], ref(cA));
			cliente[i].detach();
		}
		// Si el servidor esta en modo cerrado, cerramos el cliente que se ha intentado conectar
		else{ socket.Close(client_fd[i]); }
	}
	
    // Cerramos el socket del servidor
    error_code = socket.Close(socket_fd);
    if (error_code == -1) {
		string mensError(strerror(errno));
    	cerr << "Error cerrando el socket del servidor: " + mensError + "\n";
	}

	// Despedida
	cout << "Bye bye" << endl;

    return error_code;
}
//-------------------------------------------------------------