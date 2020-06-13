#pragma once
#include <iostream>
typedef class NodoTransaccion* NT;
#include "NodoAVL.h"
#include "NodoMatriz.h"

class NodoTransaccion{
public:
	std::string ID="";
	NodoMatriz* UserRenta = NULL;
	NodoAVL* Activo = NULL;
	NodoMatriz* UserRentador = NULL;
};

