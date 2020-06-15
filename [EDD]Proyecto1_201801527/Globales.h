#ifndef __MY_GLOBALS_H__
#define __MY_GLOBALS_H__
#pragma once
#include "NodoAVL.h"
#include "NodoMatriz.h"
#include <iostream>
#include "NodoID.h"
#include "NodoTransaccion.h"

	extern int IndexUsuarios;//Variable que cuenta el numero de usuarios en el sistema
	extern int IndexActivos;//Variable que cuenta el numero de activos en el sistema
	extern NM InicioMatriz;//Primer nodo de la matriz dispersa
	extern NM UserLog;//usuario logueado
	extern NID ListaID;//Nodo inicial de la lista de ID'S
	extern bool Admin;//Verifica si el usuario logueado es el administrador
	extern std::string EstrucArbol;//Guarda la estructura de un arbol para generar el reporte en graphviz
	extern int NNodoARBOl;//cuenta los nodos que se utilizan en la estructura del arbol
	extern int ContadorNodo;//no se que hace
	extern NT InicioTransacciones;//Nodo Inicial de la lista doble enlazada circular
	extern NT FinTransacciones;//Nodo Final de la lista doble enlazada circular

	std::string ToUpperCase(std::string Texto);
	void gotoxy(int x, int y);
	bool EsUnNumero(std::string Texto);
	void SetColor(int ForgC);
	time_t Fecha_y_Hora_Actual();

#endif