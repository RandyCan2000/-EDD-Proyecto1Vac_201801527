#include "NodoAVL.h"
#include <string>
#include <iostream>
#include "Globales.h"
#include <fstream>
#include <stdlib.h>
std::string ArbolAVL="";
int ContadorNodo=0;

NodoAVL::NodoAVL(std::string Nombre, std::string Descripcion) {
	this->Nombre = Nombre;
	this->Descripcion = Descripcion;
	this->ID = "";
	this->Index = IndexActivos;
	this->Derecha = NULL;
	this->Izquierda = NULL;
	this->Rentado = false;
	this->Altura = 0;
	IndexActivos++;
}
NodoAVL::NodoAVL() {
}
bool Aumento = false;

int CalAltura(NodoAVL& Nodo) {
	NAVL Aux = &Nodo;
	if (Aux->Derecha == NULL && Aux->Izquierda == NULL) {
		return 0;
	}
	else {
		if (Aux->Derecha != NULL) {
			Aux->Derecha->Altura = 0;
			int A = CalAltura(*Aux->Derecha) + 1;
			Aux->Altura += A;
			if (Aux->Izquierda != NULL) {
				Aux->Izquierda->Altura = 0;
				int A = CalAltura(*Aux->Izquierda) + 1;
				Aux->Altura -= A;
			}
			return A;
		}
		if (Aux->Izquierda != NULL) {
			Aux->Izquierda->Altura = 0;
			int A = CalAltura(*Aux->Izquierda) + 1;
			Aux->Altura -= A;
			if (Aux->Derecha != NULL) {
				Aux->Derecha->Altura = 0;
				int A = CalAltura(*Aux->Derecha) + 1;
				Aux->Altura += A;
			}
			return A;
		}
	}
}

void NodoAVL::CalcularAlturas(NodoAVL &Nodo) {
	NAVL Aux = &Nodo;
	Aux->Altura = 0;
	if (Aux->Izquierda == NULL && Aux->Derecha == NULL) {
		Aux->Altura = 0;
	}
	else {
		if (Aux->Izquierda != NULL) {
			Aux->Izquierda->Altura = 0;
			int A = CalAltura(*Aux->Izquierda) + 1;
			Aux->Altura -= A;
		}
		if (Aux->Derecha != NULL) {
			Aux->Derecha->Altura = 0;
			int A = CalAltura(*Aux->Derecha) + 1;
			Aux->Altura += A;
		}
	}
}

void RotacionDerecha(NodoAVL & P,NodoAVL &Q) {
	NAVL AuxP = &P, AuxQ = &Q;
	std::string NomP = AuxP->Nombre, NomQ = AuxQ->Nombre;
	std::string DesP = AuxP->Descripcion, DesQ = AuxQ->Descripcion;
	AuxP->Nombre = NomQ, AuxP->Descripcion = DesQ;
	AuxQ->Nombre = NomP, AuxQ->Descripcion = DesQ;
	AuxP->Izquierda = AuxQ->Izquierda;
	AuxQ->Izquierda = AuxQ->Derecha;
	AuxQ->Derecha = AuxP->Derecha;
	AuxP->Derecha = AuxQ;
	Aumento = false;
}
void RotacionIzquierda(NodoAVL& P, NodoAVL& Q) {
	NAVL AuxP = &P, AuxQ = &Q;
	std::string NomP = AuxP->Nombre, NomQ = AuxQ->Nombre;
	std::string DesP = AuxP->Descripcion, DesQ = AuxQ->Descripcion;
	AuxP->Nombre = NomQ; AuxP->Descripcion = DesQ;
	AuxP->Derecha = AuxQ->Derecha;
	AuxQ->Nombre = NomP; AuxQ->Descripcion = DesP;
	AuxQ->Derecha = AuxQ->Izquierda;
	AuxQ->Izquierda = AuxP->Izquierda;
	AuxP->Izquierda = NULL;
	AuxP->Izquierda = AuxQ;
	Aumento = false;
}

void Rotacion(NodoAVL &Nodo) {
	NAVL Aux = &Nodo;
	if (Aux->Altura==-2) {
		if (Aux->Derecha!=NULL && Aux->Izquierda!=NULL) {
			if (abs(Aux->Derecha->Altura)>abs(Aux->Izquierda->Altura)) {
				if (Aux->Derecha->Altura==-1) {
					RotacionDerecha(*Aux, *Aux->Derecha);
				}
				else if (Aux->Derecha->Altura == 1) {//Rotacion Doble a la Izquierda
					RotacionIzquierda(*Aux->Derecha,*Aux->Derecha->Derecha);
					RotacionDerecha(*Aux,*Aux->Derecha);
				}
			}
			else {
				if (Aux->Izquierda->Altura == -1) {
					RotacionDerecha(*Aux, *Aux->Izquierda);
				}
				else if (Aux->Izquierda->Altura == 1) {//Rotacion Doble a la izquierda
					RotacionIzquierda(*Aux->Izquierda, *Aux->Izquierda->Derecha);
					RotacionDerecha(*Aux, *Aux->Izquierda);
				}
			}
		}
		else if (Aux->Derecha!=NULL && Aux->Izquierda==NULL) {
			if (Aux->Derecha->Altura == -1) {
				RotacionDerecha(*Aux, *Aux->Derecha);
			}
			else if (Aux->Derecha->Altura == 1) {//Rotacion Doble a la izquierda
				RotacionIzquierda(*Aux->Derecha, *Aux->Derecha->Derecha);
				RotacionDerecha(*Aux, *Aux->Derecha);
			}
			else if (Aux->Derecha->Altura == 0) {
				RotacionDerecha(*Aux, *Aux->Derecha);
			}
		}
		else if (Aux->Derecha == NULL && Aux->Izquierda != NULL) {
			if (Aux->Izquierda->Altura == -1) {
				RotacionDerecha(*Aux, *Aux->Izquierda);
			}
			else if (Aux->Izquierda->Altura == 1) {//Rotacion Doble a la izquierda
				RotacionIzquierda(*Aux->Izquierda, *Aux->Izquierda->Derecha);
				RotacionDerecha(*Aux, *Aux->Izquierda);
			}
			else if (Aux->Izquierda->Altura == 0) {
				RotacionDerecha(*Aux, *Aux->Izquierda);
			}
		}
	}
	else if (Aux->Altura == 2) {
		if (Aux->Derecha != NULL && Aux->Izquierda != NULL) {
			if (abs(Aux->Derecha->Altura) > abs(Aux->Izquierda->Altura)) {
				if (Aux->Derecha->Altura == -1) {//Rotacion Doble a la derecha
					RotacionDerecha(*Aux->Derecha, *Aux->Derecha->Izquierda);
					RotacionIzquierda(*Aux, *Aux->Derecha);
				}
				else if (Aux->Derecha->Altura == 1) {
					RotacionIzquierda(*Aux,*Aux->Derecha);
				}
			}
			else {
				if (Aux->Izquierda->Altura == -1) {//Rotacion Doble a la derecha
					RotacionDerecha(*Aux->Izquierda, *Aux->Izquierda->Izquierda);
					RotacionIzquierda(*Aux, *Aux->Izquierda);
				}
				else if (Aux->Izquierda->Altura == 1) {
					RotacionIzquierda(*Aux, *Aux->Izquierda);
				}
				else if (Aux->Izquierda->Altura == 0) {
					RotacionIzquierda(*Aux, *Aux->Izquierda);
				}
			}
		}
		else if (Aux->Derecha != NULL && Aux->Izquierda == NULL) {
			if (Aux->Derecha->Altura == -1) {//Rotacion Doble a la derecha
				RotacionDerecha(*Aux->Derecha, *Aux->Derecha->Izquierda);
				RotacionIzquierda(*Aux, *Aux->Derecha);
			}
			else if (Aux->Derecha->Altura == 1) {
				RotacionIzquierda(*Aux, *Aux->Derecha);
			}
			else if (Aux->Derecha->Altura == 0) {
				RotacionIzquierda(*Aux, *Aux->Derecha);
			}
		}
		else if (Aux->Derecha == NULL && Aux->Izquierda != NULL) {
			if (Aux->Izquierda->Altura == -1) {//Rotacion Doble a la derecha
				RotacionDerecha(*Aux->Izquierda, *Aux->Izquierda->Izquierda);
				RotacionIzquierda(*Aux, *Aux->Izquierda);
			}
			else if (Aux->Izquierda->Altura == 1) {
				RotacionIzquierda(*Aux, *Aux->Izquierda);
			}
			else if (Aux->Izquierda->Altura == 0) {
				RotacionIzquierda(*Aux, *Aux->Izquierda);
			}
		}
	}
}

bool Agregar(std::string Nombre, std::string Descripcion, NodoAVL& Nodo) {
	NAVL AUX = &Nodo;
	if (strcmp(Nombre.c_str(), AUX->Nombre.c_str())==1) {
		if (AUX->Derecha!=NULL) { 
			bool agregado = Agregar(Nombre, Descripcion, *AUX->Derecha); 
			if (Aumento==true) {AUX->Altura++;}
			Rotacion(*AUX);
			return agregado;
		}
		else {
			NAVL Nuevo = new NodoAVL(Nombre,Descripcion);
			AUX->Derecha = Nuevo;
			AUX->Altura++;
			if (AUX->Izquierda == NULL) { Aumento = true; }
			return true;
		}
	}
	else if (strcmp(Nombre.c_str(), AUX->Nombre.c_str()) == -1) {
		if (AUX->Izquierda!=NULL) { 
			bool agregado=Agregar(Nombre, Descripcion, *AUX->Izquierda); 
			if (Aumento == true) { AUX->Altura--; }
			Rotacion(*AUX);
			return agregado;
		}
		else {
			NAVL Nuevo = new NodoAVL(Nombre, Descripcion);
			AUX->Izquierda = Nuevo;
			AUX->Altura--;
			if (AUX->Derecha == NULL) { Aumento = true; }
			return true;
		}
	}
	else {
		return false;
	}
}

bool NodoAVL::NuevoNodoAVL(std::string Nombre, std::string Descripcion) {
	Aumento = false;
	if (UserLog->Activos==NULL) {
		UserLog->Activos = new NodoAVL(Nombre,Descripcion);
		return true;
	}
	else {
		return Agregar(Nombre, Descripcion, *UserLog->Activos);
	}
}

bool NodoAVL::BuscarActivo(NodoAVL& Nodo, std::string Nombre) {
	NAVL Aux = &Nodo;
	if (Aux == NULL) {
		return false;
	}
	else if (Aux->Nombre == Nombre) {
		return true;
	}
	else if (strcmp(Nombre.c_str(), Aux->Nombre.c_str()) == -1) {
		return BuscarActivo(*Aux->Izquierda, Nombre);
	}
	else {
		return BuscarActivo(*Aux->Derecha, Nombre);
	}
}

NAVL Unir(NodoAVL &Izquierda, NodoAVL &Derecha){
	NAVL AuxIzq = &Izquierda;
	NAVL AuxDer = &Derecha;
	if (AuxIzq == NULL)
	{
		return AuxDer;
	}

	if (AuxDer == NULL)
	{
		return AuxIzq;
	}

	NAVL Centro = Unir(*AuxIzq->Derecha, *AuxDer->Izquierda);
	AuxIzq->Derecha = Centro;
	AuxDer->Izquierda = AuxIzq;
	return AuxDer;
}

void NodoAVL::Eliminar(NodoAVL& Nodo, std::string Nombre){
	NAVL Aux = &Nodo;
	if (Aux == NULL)
	{
		return;
	}
	if (strcmp(Nombre.c_str(), Aux->Nombre.c_str()) == -1)
		{
		Eliminar(*Aux->Izquierda, Nombre);
		}
	else if (strcmp(Nombre.c_str(), Aux->Nombre.c_str()) == 1)
	{
		Eliminar(*Aux->Derecha, Nombre);
	}
	else
	{
		NAVL Aux2 = Aux;
		Aux = Unir(*Aux->Izquierda, *Aux->Derecha);
		delete Aux2;
	}
}


void NodoAVL::EstructuraArbol(NodoAVL& Nodo, std::string NodoPadre) {
	NAVL Aux = &Nodo;
	if (Aux->Izquierda!=NULL) {
		EstrucArbol += "N" + std::to_string(NNodoARBOl);
		if (Aux->Izquierda->Rentado==true) {
			EstrucArbol += "[fillcolor=red ";
		}
		else {
			EstrucArbol += "[fillcolor=green ";
		}
		EstrucArbol+="label=\"" + Aux->Izquierda->Nombre + " A:" + std::to_string(Aux->Izquierda->Altura) + "\"];\n";
		EstrucArbol += NodoPadre + "->" + "N" + std::to_string(NNodoARBOl) + ";\n";
		std::string NodoP = "N" + std::to_string(NNodoARBOl);
		NNodoARBOl++;
		EstructuraArbol(*Aux->Izquierda,NodoP);
	}
	if (Aux->Derecha != NULL) {
		EstrucArbol += "N" + std::to_string(NNodoARBOl);
		if (Aux->Derecha->Rentado == true) {
			EstrucArbol += "[fillcolor=red ";
		}
		else {
			EstrucArbol += "[fillcolor=green ";
		}
		EstrucArbol += "label=\"" + Aux->Derecha->Nombre +" A:" + std::to_string(Aux->Derecha->Altura) + "\"];\n";
		EstrucArbol += NodoPadre + "->" + "N" + std::to_string(NNodoARBOl) + ";\n";
		std::string NodoP = "N" + std::to_string(NNodoARBOl);
		NNodoARBOl++;
		EstructuraArbol(*Aux->Derecha, NodoP);
	}
}

void NodoAVL::ImagenArbol() {
	std::ofstream fs("C:\\GraficasE\\ArbolUnicoUser.dot");
	fs << "digraph G {" << std::endl;
	fs << "node [margin=0, shape=circle, style=filled];"<<std::endl;
	EstrucArbol = ""; ContadorNodo = 0;
	EstrucArbol += "N"+std::to_string(ContadorNodo);
	std::string NP = "N" + std::to_string(ContadorNodo);
	if (UserLog->Activos->Rentado == true) {
		EstrucArbol += "[fillcolor=red ";
	}
	else {
		EstrucArbol += "[fillcolor=green ";
	}
	EstrucArbol += "label=\"" + UserLog->Activos->Nombre +" A:"+ std::to_string(UserLog->Activos->Altura) +"\"];\n";
	NNodoARBOl++;
	EstructuraArbol(*UserLog->Activos, NP);
	fs << EstrucArbol;
	fs << "}" << std::endl;
	fs.close();
	system("C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng C:\\GraficasE\\ArbolUnicoUser.dot -o C:\\GraficasE\\ArbolUnicoUser.png");
	system("C:\\GraficasE\\ArbolUnicoUser.png &");
}



