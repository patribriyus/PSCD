#!/bin/bash
#*****************************************************************
# File:   ejecuta_p5_SERVER.bash
# Author: Patricia Briones Yus, 735576
# Date:   diciembre 2018
# Coms:   script de comprobación de entrega de la práctica 4 de PSCD (18/19)
#         Funcionamiento: 
#          1) Dar permisos de ejecución al script: "chmod u+x ejecuta_p5_SERVER.bash"
#          2) Ejecutar mediante "ejecuta_p5_SERVER.bash puerto"
#*****************************************************************

MAKE_FILE=Makefile_p5_SERVER

#----------------------------------------------------------------
#Comprueba que se invoque con un parámetro (que es un puerto)
if [[ "$#" -ne 1 ]]
then
	exit
fi

make -f $MAKE_FILE &>/dev/null
resMake=$?
if [[ "$resMake" == 0 ]]
then    #ha funcionado bien
	echo "**************************************"
	echo "* Se ha compilado todo correctamente *"
	echo "**************************************"
	echo -e "<< SERVIDOR ESCUCHANDO EN EL PUERTO $1 >>\n"
	./ServidorMulticliente "$1"
else
	exit
fi

exit 0
