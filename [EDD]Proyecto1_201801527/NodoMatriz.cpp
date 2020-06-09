#include "NodoAVL.h"
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
	//activos
	this->Activos = NULL;
	IndexUsuarios++;
}
NodoMatriz::NodoMatriz(std::string Nombre, bool D_E) {
	if (D_E==true){//con true Cabecera Departamento
		this->Departamento = Nombre;
		this->Empresa = "";
	}
	else {//con false Cabecera Empresa
		this->Empresa = Nombre;
		this->Departamento = "";
	}
	//activo
	this->Activos = NULL;
	//fin activo
	this->Cabecera = true;
	this->Abajo = NULL;
	this->Arriba = NULL;
	this->Derecha = NULL;
	this->Izquierda = NULL;
	this->Adelante = NULL;
	this->Atras = NULL;
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

bool AgregarNodoEmpresa(std::string Empresa, NodoMatriz& User, NodoMatriz& Empre) {
	NM NuevoUser = &User;
	NM NuevoEmp = &Empre;
	NM Emp = InicioMatriz;
	while (Emp != NULL) {
		if (strcmp(Empresa.c_str(), Emp->Empresa.c_str()) == 1) {
			if (Emp->Abajo != NULL) {
				if (strcmp(Empresa.c_str(), Emp->Abajo->Empresa.c_str()) == -1) {
					NM Aux1 = Emp->Abajo;
					Emp->Abajo = NuevoEmp;
					Aux1->Arriba = NuevoEmp;
					NuevoEmp->Arriba = Emp;
					NuevoEmp->Abajo = Aux1;
					NuevoEmp->Derecha = NuevoUser;
					NuevoUser->Izquierda = NuevoEmp;
					return true;
				}
			}
			else {
				Emp->Abajo = NuevoEmp;
				NuevoEmp->Arriba = Emp;
				NuevoEmp->Derecha = NuevoUser;
				NuevoUser->Izquierda = NuevoEmp;
				return true;
			}
		}
		Emp = Emp->Abajo;
	}
	return false;
}
bool AgregarNodoDepartamento(std::string Departamento, NodoMatriz& User, NodoMatriz& Depa) {
	NM NuevoUser = &User;
	NM NuevoDep = &Depa;
	NM Dep = InicioMatriz;
	while (Dep != NULL) {
		if (strcmp(Departamento.c_str(), Dep->Departamento.c_str()) == 1) {
			if (Dep->Derecha != NULL) {
				if (strcmp(Departamento.c_str(), Dep->Derecha->Departamento.c_str()) == -1) {
					NM Aux = Dep->Derecha;
					Dep->Derecha = NuevoDep;
					Aux->Izquierda = NuevoDep;
					NuevoDep->Izquierda = Dep;
					NuevoDep->Derecha = Aux;
					NuevoDep->Abajo = NuevoUser;
					NuevoUser->Arriba = NuevoDep;
					return true;
				}
			}
			else {
				Dep->Derecha = NuevoDep;
				NuevoDep->Izquierda = Dep;
				NuevoDep->Abajo = NuevoUser;
				NuevoUser->Arriba = NuevoDep;
				return true;
			}
		}
		Dep = Dep->Derecha;
	}
	return false;
}

bool NodoMatriz::AgregarNodo(std::string Usuario, std::string Contrasena, std::string Departamento, std::string Empresa) {
	NM Dep = InicioMatriz;
	NM Emp = InicioMatriz;
	while (Dep != NULL){
		if (Departamento == Dep->Departamento) { break; }
		Dep = Dep->Derecha;
	}
	while (Emp != NULL) {
		if (Empresa == Emp->Empresa) { break; }
		Emp = Emp->Abajo;
	}
	if (Dep!=NULL && Emp!=NULL) {
		while (Dep!=NULL){
			if (Dep->Departamento==Departamento && Dep->Empresa==Empresa) {
				while (Dep!=NULL){
					if (Dep->Usuario == Usuario) { return false; }
					else if (Dep->Atras==NULL) {
						NM Nuevo = new NodoMatriz(Usuario,Contrasena,Departamento,Empresa);
						Dep->Atras = Nuevo;
						Nuevo->Adelante = Dep;
						return true;
					}
					Dep = Dep->Atras;
				}
			}
			Dep = Dep->Abajo;
		}
	}
	else if (Dep == NULL && Emp == NULL) {
		NM NuevoDep = new NodoMatriz(Departamento, true);
		NM NuevoEmp = new NodoMatriz(Empresa, false);
		NM NuevoUser = new NodoMatriz(Usuario, Contrasena, Departamento, Empresa);
		if (AgregarNodoDepartamento(Departamento,*NuevoUser,*NuevoDep)==true) {
			if (AgregarNodoEmpresa(Empresa, *NuevoUser, *NuevoEmp) == true) { return true; }
		}
	}
	else if (Dep != NULL && Emp == NULL) {
		NM NuevoEmp = new NodoMatriz(Empresa,false);
		NM NuevoUser = new NodoMatriz(Usuario, Contrasena, Departamento, Empresa);
		AgregarNodoEmpresa(Empresa, *NuevoUser, *NuevoEmp);
		NM Aux = NuevoEmp->Arriba;
		std::string EmpAnterior = Aux->Empresa;
		while (Dep!=NULL){
			if (Dep->Empresa==EmpAnterior) {
				if (Dep->Abajo!=NULL) {
					NM Aux = Dep->Abajo;
					Dep->Abajo = NuevoUser;
					Aux->Arriba = NuevoUser;
					NuevoUser->Arriba = Dep;
					NuevoUser->Abajo = Aux;
					return true;
				}
				else {
					Dep->Abajo = NuevoUser;
					NuevoUser->Arriba = Dep;
					return true;
				}
			}
			Dep = Dep->Abajo;
		}
	}
	else if (Dep == NULL && Emp != NULL) {
		NM NuevoDep = new NodoMatriz(Empresa, true);
		NM NuevoUser = new NodoMatriz(Usuario, Contrasena, Departamento, Empresa);
		AgregarNodoDepartamento(Departamento,*NuevoUser,*NuevoDep);
		NM Aux = NuevoDep->Izquierda;
		std::string DepAnterior = Aux->Departamento;
		while (Emp != NULL) {
			if (Emp->Departamento==DepAnterior) {
				if (Emp->Derecha!=NULL) {
					NM Aux = Emp->Derecha;
					Emp->Derecha = NuevoUser;
					Aux->Izquierda = NuevoUser;
					NuevoUser->Derecha = Aux;
					NuevoUser->Izquierda = Emp;
					return true;
				}
				else {
					Emp->Derecha = NuevoUser;
					NuevoUser->Izquierda = Emp;
					return true;
				}
			}
			Emp = Emp->Derecha;
		}
	}
	return false;
}


std::string NodoMatriz::ImprimirMatriz() {
	std::string Texto="";
	NM Aux = InicioMatriz->Derecha;
	while (Aux != NULL) {
		Texto += Aux->Departamento + "->";
		Aux = Aux->Derecha;
	}
	Texto += "NULL";
	NM Aux1 = InicioMatriz->Abajo;
	while (Aux1 != NULL) {
		Texto += Aux1->Empresa + "->";
		Aux1 = Aux1->Abajo;
	}
	Texto += "NULL";
	return Texto;
}