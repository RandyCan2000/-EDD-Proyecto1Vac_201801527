#ifndef __MY_GLOBALS_H__
#define __MY_GLOBALS_H__
#pragma once
#include "NodoMatriz.h"
#include <stdio.h>  
#include <windows.h>
#include <cctype>
	extern int IndexUsuarios;
	extern NM InicioMatriz;
	extern NM UserLog;
	extern bool Admin;

	std::string ToUpperCase(std::string Texto);
	void gotoxy(int x, int y);
	bool EsUnNumero(std::string Texto);
	void SetColor(int ForgC);

#endif