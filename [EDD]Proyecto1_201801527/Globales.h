#ifndef __MY_GLOBALS_H__
#define __MY_GLOBALS_H__
#pragma once
#include "NodoAVL.h"
#include "NodoMatriz.h"
#include <iostream>

	extern int IndexUsuarios;
	extern int IndexActivos;
	extern NM InicioMatriz;
	extern NM UserLog;
	extern bool Admin;
	extern std::string EstrucArbol;
	extern int NNodoARBOl;
	extern int ContadorNodo;

	std::string ToUpperCase(std::string Texto);
	void gotoxy(int x, int y);
	bool EsUnNumero(std::string Texto);
	void SetColor(int ForgC);

#endif