#*****************************************************************
# File:   Makefile
# Author: PSCD-Unizar
# Date:   octubre 2017
# Coms:   Ejemplo de Makefile
#         Ejecutar 'make' para compilar (o 'make -f Makefile')
#         Ejecutar 'make' clean para limpiar (borrar lo que genere)
#         Suponemos que 'main_p2_e1.cpp' contiene un '#include "otroFuente.hpp"' cuya
#         implementación está en 'otroFuente.cpp'.
#         El objetivo es generar el ejecutable 'main_p2_e1'
#*****************************************************************

#---------------------------------------------------------
# macros
RM = /bin/rm -f  # para limpiar
CC = g++         # para compilar
#---------------------------------------------------------
# para compilación y enlazado ("linkado")
CPPFLAGS=-I. -std=c++11     # opciones compilación
LDFLAGS=-pthread            # opciones de "linkado"
#---------------------------------------------------------
# vars
EJEC = main_p2_e1

all: ${EJEC} #lo que se generará al ejecutar "make"
#---------------------------------------------------------
# "linkar" y generar ejecutable. Indicamos que "main_p2_e1" requiere tanto "main_p2_e1.o" como "otroFuente.o"
${EJEC}: ${EJEC}.o otroFuente.o
	${CC} ${EJEC}.o otroFuente.o -o ${EJEC} ${CPPFLAGS} ${LDFLAGS}

#---------------------------------------------------------
# compilar: generará "main_p2_e1.o". Indicamos que depende de "main_p2_e1.cpp"
${EJEC}.o: ${EJEC}.cpp otroFuente.hpp
	${CC} -c ${EJEC}.cpp ${CPPFLAGS}

# compilar: generará "otroFuente.o". Indicamos que depende de "otroFuente.hpp" y "otroFuente.cpp"
otroFuente.o: otroFuente.hpp otroFuente.cpp
	${CC} -c otroFuente.cpp ${CPPFLAGS}

#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${EJEC}.o ${EJEC} otroFuente.o
