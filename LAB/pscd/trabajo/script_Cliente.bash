#!/bin/bash
#*****************************************************************
# Funcionamiento: 
#          1) Dar permisos de ejecuci�n al script: "chmod u+x script_Cliente.bash"
#          2) Ejecutar mediante "script_Cliente.bash puerto"
#*****************************************************************

MAKE_FILE=Makefile_Cliente

#----------------------------------------------------------------
#Comprueba que se invoque con un par�metro (ip y puerto)
if [[ "$#" -ne 2 ]]
then
	echo "Numero de par�metros incorrecto"
	exit
fi

make -f $MAKE_FILE &>/dev/null
resMake=$?
if [[ "$resMake" == 0 ]]
then    #ha funcionado bien
	echo "**************************************"
	echo "* Se ha compilado todo correctamente *"
	echo "**************************************"
	./clienteprueba "$1" "$2"
else
	exit
fi

exit 0
