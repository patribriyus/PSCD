#!/bin/bash
#*****************************************************************
# Funcionamiento: 
#          1) Dar permisos de ejecución al script: "chmod u+x script_Admin.bash"
#          2) Ejecutar mediante "script_Admin.bash puerto"
#*****************************************************************

MAKE_FILE=Makefile_Admin

#----------------------------------------------------------------
#Comprueba que se invoque con un parámetro (ip y puerto)
if [[ "$#" -ne 2 ]]
then
	echo "Numero de parámetros incorrecto"
	exit
fi

make -f $MAKE_FILE &>/dev/null
resMake=$?
if [[ "$resMake" == 0 ]]
then    #ha funcionado bien
	echo "**************************************"
	echo "* Se ha compilado todo correctamente *"
	echo "**************************************"
	./admin "$1" "$2"
else
	exit
fi

exit 0
