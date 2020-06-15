#pragma once
typedef class NodoMatriz* NM;
#include <iostream>
#include <string>
#include "NodoAVL.h"
class NodoMatriz
{
public:
	int Index = 0;
	std::string ID = "";
	std::string Usuario = "";
	std::string Contrasena = "";
	std::string Departamento = "";
	std::string Empresa = "";
	bool Cabecera = false;
	NodoMatriz* Arriba = NULL;
	NodoMatriz* Abajo = NULL;
	NodoMatriz* Derecha = NULL;
	NodoMatriz* Izquierda = NULL;
	NodoMatriz* Adelante = NULL;
	NodoMatriz* Atras = NULL;
public:
	NodoAVL* Activos;

	NodoMatriz(std::string Usuario, std::string Contrasena, std::string Departamento, std::string Empresa);
	NodoMatriz(std::string Nombre, bool D_E);
	NodoMatriz();
	void BuscarNodo(std::string Usuario, std::string Contrasena, std::string Departamento, std::string Empresa);
	bool AgregarNodo(std::string Usuario, std::string Contrasena, std::string Departamento, std::string Empresa);
	bool ReporteActivosEmpresa(std::string NombreEmpresa);
	bool ReporteActivosDepartamento(std::string NombreDepartamento);
	NM BuscarUsuario(std::string Usuario, std::string Departamento, std::string Empresa);
	std::string ImprimirMatriz();
	void RepMatriz();
	std::string ListarTodosLosActivos();
}; 