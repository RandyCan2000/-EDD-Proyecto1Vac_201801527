#pragma once
#include <iostream>
typedef class NodoAVL* NAVL;
class NodoAVL{
public:
	int Index = 0;
	int Altura = 0;
	std::string ID="";
	std::string Nombre = "";
	std::string Descripcion = "";
	bool Rentado = false;
	NodoAVL* Derecha = NULL;
	NodoAVL* Izquierda = NULL;

	NodoAVL(std::string Nombre, std::string Descripcion);
	NodoAVL();
	void CalcularAlturas(NodoAVL& Nodo);
	bool NuevoNodoAVL(std::string Nombre,std::string Descripcion);
	bool BuscarActivo(NodoAVL& Nodo, std::string Nombre);
	void Eliminar(NodoAVL& Nodo, std::string Nombre);
	void EstructuraArbol(NodoAVL& Nodo,std::string NodoPadre);
	void ImagenArbol();
};


