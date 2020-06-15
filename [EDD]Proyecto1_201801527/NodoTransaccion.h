#pragma once
#include <iostream>
typedef class NodoTransaccion* NT;
#include "NodoAVL.h"
#include "NodoMatriz.h"

class NodoTransaccion{
public:
	std::string ID="";
	NAVL Activo = NULL;
	NM UserRenta = NULL;//Es el usuario que renta
	NM UserRentador = NULL;//es el usuario que pide el activo en renta
	time_t FechaRenta = NULL;
	int DiasRenta = 0;
	NodoTransaccion* Siguiente=NULL;
	NodoTransaccion* Anterior = NULL;

	NodoTransaccion(NodoMatriz& UserRenta, NodoAVL& Activo, int DiasRenta);
	NodoTransaccion();
	bool AgregarRenta(NodoMatriz& UserRenta, NodoAVL& Activo, int DiasRenta);
	std::string ListadoActivosRentados();
	bool QuitarRenta(std::string ID_Renta);
	void ReporteTransacciones();
};

