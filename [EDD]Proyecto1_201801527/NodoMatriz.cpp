#include "NodoMatriz.h"
#include "Globales.h"
#include <iostream>
#include <string>

NodoMatriz::NodoMatriz(std::string Usuario, std::string Contrasena, std::string Departamento, std::string Empresa) {
	this->Index = IndexUsuarios;
	this->Usuario = Usuario;
	this->Contrasena = Contrasena;
	this->Departamento = Departamento;
	this->Empresa = Empresa;
	this->Abajo = NULL;
	this->Arriba = NULL;
	this->Derecha = NULL;
	this->Izquierda = NULL;
	this->Adelante = NULL;
	this->Atras = NULL;
	this->Cabecera = false;
	this->ID = "algo";
	IndexUsuarios++;
}
NodoMatriz::NodoMatriz(std::string Nombre, bool D_E) {
	if (D_E==true){//con true Cabecera Departamento
		this->Departamento = Nombre;
	}
	else {//con false Cabecera Empresa
		this->Empresa = Nombre;
	}
	this->Cabecera = true;
}
NodoMatriz::NodoMatriz(){
}

void NodoMatriz::BuscarNodo(std::string Usuario, std::string Contrasena, std::string Departamento, std::string Empresa) {
	NM Aux = InicioMatriz;
	if (Aux->Usuario==Usuario && Aux->Contrasena==Contrasena && Aux->Departamento==Departamento && Aux->Empresa==Empresa) {
		UserLog = Aux;
		Admin = true;
	}
	else {
		while(Aux!=NULL){
			if (Departamento == Aux->Departamento) {
				while (Aux != NULL) {
					if (Empresa==Aux->Empresa) {
						while(Aux!=NULL) {
							if (Usuario == Aux->Usuario && Contrasena ==Aux->Contrasena) {
								UserLog = Aux;
								break;
							}
							Aux = Aux->Atras;
						} 
						break;
					}
					Aux = Aux->Abajo;
				} 
				break;
			}
			Aux = Aux->Derecha;
		}
	}
	
}