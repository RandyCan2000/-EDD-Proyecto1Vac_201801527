#pragma once
#include <iostream>
#include <string>
class NodoMatriz
{
public:
	int Index = 0;
	std::string ID="";
	std::string Usuario = "";
	std::string Contrasena = "";
	std::string Departamento = "";
	std::string Empresa = "";
	bool Cabecera = false;
	//NodoListaActivoRentados
	//NodoArbolAVL
	NodoMatriz* Arriba = NULL;
	NodoMatriz* Abajo = NULL;
	NodoMatriz* Derecha = NULL;
	NodoMatriz* Izquierda = NULL;
	NodoMatriz* Adelante = NULL;
	NodoMatriz* Atras = NULL;

	NodoMatriz(std::string Usuario, std::string Contrasena, std::string Departamento, std::string Empresa);
	NodoMatriz(std::string Nombre,bool D_E);
	NodoMatriz();
	void BuscarNodo(std::string Usuario, std::string Contrasena, std::string Departamento, std::string Empresa);
	bool AgregarNodo(std::string Usuario, std::string Contrasena, std::string Departamento, std::string Empresa);
	std::string ImprimirMatriz();
};
typedef class NodoMatriz *NM;
