#!/bin/bash
#*****************************************************************
# File:   pract2_correcta.bash
# Author: PSCD-Universidad de Zaragoza
# Date:   octubre 2018
# Coms:   script de comprobación de entrega de la práctica 2 de PSCD (18/19)
#         Funcionamiento: 
#          1) Dar permisos de ejecución al script: "chmod u+x pract2_correcta.bash"
#          2) Ejecutar mediante "pract2_correcta.bash miNip" en el directorio donde esté el zip
#             a entregar, en este caso "practica2_miNip.zip". Creará un directorio temporal
#             donde descomprimirá el zip, comprobará is están los ficheros que tienen que estar
#             y si se compilan correctamente, informando de los problemas.
#             Posteriormente borra el directorio creado
#*****************************************************************


MAKE_FILE=Makefile_p2_e1
FUENTE_1=main_p2_e1.cpp
EJECUTABLE=main_p2_e1
FUENTE_ZIP="practica2_${1}.zip"
USER=a$1       #usuarios en Hendrix son "a" seguido del NIP
FALTAN=()      #ficheros que faltan
FICHEROS=($MAKE_FILE $FUENTE_1)

#si alguien usa esto como nombre de directorio, se merece el castigo de perderlo
DIR_TEMPORAL=./__PSCD_NO_ES_INTERESANTE__

echo "------------------------------------------"
#----------------------------------------------------------------
#el NIP como parámetro
if [[ "$#" -ne 1 ]]
then
	echo "Invocar como: pract2_correcta.sh miNip"
	echo "------------------------------------------"
	exit
fi
#----------------------------------------------------------------
#si no existe directorio de corrección, lo creo;
#si existe, borro su contenido
if [ ! -d "$DIR_TEMPORAL" ]
then
	mkdir $DIR_TEMPORAL
else
	/bin/rm -rf $DIR_TEMPORAL*
fi

#----------------------------------------------------------------
#  mirar si ha entregado el fichero "zip"
#----------------------------------------------------------------

if [ ! -f "$FUENTE_ZIP" ]
then
	FALTAN=( $FUENTE_ZIP "$FALTAN[@]")
else
	cp $FUENTE_ZIP $DIR_TEMPORAL/$FUENTE_ZIP
	cd $DIR_TEMPORAL
	echo "Extrayendo zip ..."
	unzip $FUENTE_ZIP
	for fich in "${FICHEROS[@]}"
	do
		if [ ! -f "$fich" ]
		then
			echo "Falta fichero $fich"
			FALTAN=($fich "$FALTAN[@]")
		fi
	done
fi

#Si faltan ficheros, no se compila
if [[ ${#FALTAN[@]} -eq 0 ]] 
then
	make -f $MAKE_FILE

	resMake=$?
	if [[ "$resMake" == 0 ]]
	then    #ha funcionado bien
		echo "Compila correctamente"
	else
		echo "ERROR: fallo al compilar"
	fi
else
	echo "ERROR: faltan ficheros obligatorios"
fi

#volver al directorio original
cd ..
#borrar el temporal
/bin/rm -rf $DIR_TEMPORAL*
echo "------------------------------------------"
stty erase "^?"
exit 0
