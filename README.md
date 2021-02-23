# Trabajo práctico final de Taller de Programación.

Este proyecto es un remake del juego Wolfestein 3D, juego del año 1992.
En esta versión el juego contará con partidas del estilo deathmatch, de manera multijugador, soportando el uso de inteligencia artificial para ingresar jugadores manejados por la computadora.

## Librerias necesarias para compilar:
sudo apt-get install 

	libsdl2-mixer-dev
	libsdl2-dev 
	libsdl2-image-dev
	libsdl2-ttf-dev
	lua5.3
	liblua5.3-dev
	(yaml-cpp) https://github.com/jbeder/yaml-cpp/releases/tag/yaml-cpp-0.6.3

## Para instalar Wolfestein3D:
	
	mkdir build
	cd build
	cmake ..
	make install
	
Para ejecutar el servidor:
	
	./server <port/service>
	
Para ejecutar el cliente:

	./client <ip/hostname> <port/service>

Para ejecutar el editor:
	
	./editor 
	

## Grupo 14

    Ariel Lowy.                 Padrón: 98298
    Axel Aparicio Rotermund.    Padrón: 96283
    Leandro Sosa.               Padrón: 97412
    Marcos Wagner.              Padrón: 98607
