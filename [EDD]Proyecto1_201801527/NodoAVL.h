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
	void EstructuraArbol(NodoAVL& Nodo,std::string NodoPadre);
	bool EditarActivo(NodoAVL& Nodo, std::string Descripcion, std::string Nombre);
	bool EliminarActivo(NodoAVL& Nodo, std::string Nombre,int Y);
	void ImagenArbol();
	std::string ListaActivo(NodoAVL &Nodo);
};


