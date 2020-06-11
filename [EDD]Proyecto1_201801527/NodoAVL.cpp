#include "NodoAVL.h"
#include <string>
#include <iostream>
#include "Globales.h"
#include <fstream>
#include <stdlib.h>
std::string ArbolAVL="";
int ContadorNodo=0;
std::string ListadoActivos="";
bool Equilibrado = false;

void Rotacion(NodoAVL& Nodo);


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
			if ((Aux->Altura == -2 || Aux->Altura == 2)&& Equilibrado==true) {
				Rotacion(*Aux);
				Equilibrado = false;
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
			if ((Aux->Altura == -2 || Aux->Altura == 2) && Equilibrado == true) {
				Rotacion(*Aux);
				Equilibrado = false;
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
		if ((Aux->Altura == -2 || Aux->Altura == 2) && Equilibrado == true) {
			Rotacion(*Aux);
			Equilibrado = false;
		}
	}
}

void RotacionDerecha(NodoAVL & P,NodoAVL &Q) {
	NAVL AuxP = &P, AuxQ = &Q;
	bool RentadoP = AuxP->Rentado, RentadoQ = AuxQ->Rentado;
	AuxP->Rentado = RentadoQ;
	AuxQ->Rentado = RentadoP;
	std::string NomP = AuxP->Nombre, NomQ = AuxQ->Nombre;
	std::string DesP = AuxP->Descripcion, DesQ = AuxQ->Descripcion;
	std::string IDP = AuxP->ID, IDQ = AuxQ->ID;
	AuxP->Nombre = NomQ, AuxP->Descripcion = DesQ; AuxP->ID = IDQ;
	AuxQ->Nombre = NomP, AuxQ->Descripcion = DesQ; AuxQ->ID = IDP;
	AuxP->Izquierda = AuxQ->Izquierda;
	AuxQ->Izquierda = AuxQ->Derecha;
	AuxQ->Derecha = AuxP->Derecha;
	AuxP->Derecha = AuxQ;
	Aumento = false;
}
void RotacionIzquierda(NodoAVL& P, NodoAVL& Q) {
	NAVL AuxP = &P, AuxQ = &Q;
	bool RentadoP = AuxP->Rentado, RentadoQ = AuxQ->Rentado;
	AuxP->Rentado = RentadoQ;AuxQ->Rentado = RentadoP;
	std::string NomP = AuxP->Nombre, NomQ = AuxQ->Nombre;
	std::string DesP = AuxP->Descripcion, DesQ = AuxQ->Descripcion;
	std::string IDP = AuxP->ID, IDQ = AuxQ->ID;
	AuxP->Nombre = NomQ; AuxP->Descripcion = DesQ; AuxP->ID = IDQ;
	AuxP->Derecha = AuxQ->Derecha;
	AuxQ->Nombre = NomP; AuxQ->Descripcion = DesP; AuxQ->ID = IDP;
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

bool NodoAVL::EditarActivo(NodoAVL& Nodo, std::string Descripcion, std::string Nombre) {
	NAVL Aux = &Nodo;
	if (Aux!=NULL) {
		if (strcmp(Nombre.c_str(), Aux->Nombre.c_str()) == 0) {
			Aux->Descripcion = Descripcion;
			return true;
		}
		else if (strcmp(Nombre.c_str(), Aux->Nombre.c_str()) == 1) {
			if (Aux->Derecha != NULL) {
				bool Editado = NodoAVL::EditarActivo(*Aux->Derecha, Descripcion, Nombre);
				return Editado;
			}
			else {
				return false;
			}
		}
		else if (strcmp(Nombre.c_str(), Aux->Nombre.c_str()) == -1) {
			if (Aux->Izquierda != NULL) {
				bool Editado = NodoAVL::EditarActivo(*Aux->Izquierda, Descripcion, Nombre);
				return Editado;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void EliminarNodoVacio(NodoAVL &Nodo) {
	NAVL Aux = &Nodo;
	if (Aux!=NULL) {
		if (Aux->Izquierda != NULL) {
			if (Aux->Izquierda->Nombre == "") {
				delete Aux->Izquierda;
				Aux->Izquierda = NULL;
			}
			else {
				EliminarNodoVacio(*Aux->Izquierda);
			}
		}
		if (Aux->Derecha != NULL) {
			if (Aux->Derecha->Nombre == "") {
				delete Aux->Derecha;
				Aux->Derecha = NULL;
			}
			else {
				EliminarNodoVacio(*Aux->Derecha);
			}
		}
	}
}

NAVL MayorDeLosMenores(NodoAVL& Nodo) {
	NAVL Aux = &Nodo;
	if (Aux!=NULL) {
		if (Aux->Derecha == NULL) {
			return Aux;
		}
		else {
			return MayorDeLosMenores(*Aux->Derecha);
		}
	}
}

bool CasosEliminacion(NodoAVL &Nodo) {
	NAVL Aux = &Nodo;
	if (Aux!=NULL) {
		if (Aux->Derecha == NULL && Aux->Izquierda == NULL) {
			Aux->Nombre = "";
			Aux = NULL;
			return true;
		}
		else if (Aux->Derecha != NULL && Aux->Izquierda == NULL) {
			NAVL AUX2 = Aux->Derecha;
			Aux->Izquierda = Aux->Derecha->Izquierda;
			Aux->Derecha = Aux->Derecha->Derecha;
			Aux->ID = AUX2->ID;
			Aux->Nombre = AUX2->Nombre;
			Aux->Descripcion = AUX2->Descripcion;
			Aux->Rentado = AUX2->Rentado;
			AUX2->Nombre = "";
			return true;
		}
		else if (Aux->Derecha == NULL && Aux->Izquierda != NULL) {
			NAVL Aux2 = Aux->Izquierda;
			Aux->Derecha = Aux->Izquierda->Derecha;
			Aux->Izquierda = Aux->Izquierda->Izquierda;
			Aux->ID = Aux2->ID;
			Aux->Nombre = Aux2->Nombre;
			Aux->Descripcion = Aux2->Descripcion;
			Aux->Rentado = Aux2->Rentado;
			Aux2->Nombre = "";
			return true;
		}
		else if (Aux->Derecha != NULL && Aux->Izquierda != NULL) {
			NAVL Aux2 = MayorDeLosMenores(*Aux->Izquierda);
			if (Aux2->Derecha == NULL && Aux2->Izquierda == NULL) {
				Aux->ID = Aux2->ID;
				Aux->Nombre = Aux2->Nombre;
				Aux->Descripcion = Aux2->Descripcion;
				Aux->Rentado = Aux2->Rentado;
				Aux2->Nombre = "";
				return true;
			}
			else {
				Aux->Izquierda = Aux2->Izquierda;
				Aux->ID = Aux2->ID;
				Aux->Nombre = Aux2->Nombre;
				Aux->Descripcion = Aux2->Descripcion;
				Aux->Rentado = Aux2->Rentado;
				Aux2->Nombre = "";
				return true;
			}
		}
	}
}

bool NodoAVL::EliminarActivo(NodoAVL& Nodo, std::string Nombre, int Y) {
	NAVL Aux = &Nodo;
	if (Aux!=NULL) {
		if (strcmp(Nombre.c_str(), Aux->Nombre.c_str()) == 0) {//Aqui Se elimina
			gotoxy(30, Y + 2); SetColor(6); std::cout << "ACTIVO A ELIMINAR"; SetColor(12);
			gotoxy(30, Y + 4); std::cout << "ID: " << Aux->ID;
			gotoxy(30, Y + 6); std::cout << "NOMBRE: " << Aux->Nombre;
			gotoxy(30, Y + 8); std::cout << "DESCRIPCION: " << Aux->Descripcion;
			bool Eliminado = false;
			if (Aux==UserLog->Activos &&  UserLog->Activos->Derecha==NULL && UserLog->Activos->Izquierda==NULL) {
				UserLog->Activos = NULL;
				Eliminado = true;
			}
			else {
				if (Aux->Rentado == false) {
					Eliminado = CasosEliminacion(*Aux);
					EliminarNodoVacio(*UserLog->Activos);
					Equilibrado = true;
					CalcularAlturas(*UserLog->Activos);
					if (Equilibrado == false) {
						Equilibrado = true;
						CalcularAlturas(*UserLog->Activos);
					}
				}
			}
			return Eliminado;
		}
		else if (strcmp(Nombre.c_str(), Aux->Nombre.c_str()) == 1) {
			if (Aux->Derecha != NULL) {
				return EliminarActivo(*Aux->Derecha, Nombre, Y);
			}
			else {
				return false;
			}
		}
		else if (strcmp(Nombre.c_str(), Aux->Nombre.c_str()) == -1) {
			if (Aux->Izquierda != NULL) {
				return EliminarActivo(*Aux->Izquierda, Nombre, Y);
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
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

void RecInOrden(NodoAVL& Nodo) {
	NAVL Aux = &Nodo;
	if (Aux->Izquierda==NULL && Aux->Derecha==NULL) {
		ListadoActivos += "Nombre: " + Aux->Nombre + " Descripcion: " + Aux->Descripcion+"\n";
	}
	else {
		if (Aux->Izquierda != NULL) {
			RecInOrden(*Aux->Izquierda);
			
		}
		ListadoActivos += "Nombre: " + Aux->Nombre + " Descripcion: " + Aux->Descripcion + "\n";
		if (Aux->Derecha != NULL) {
			RecInOrden(*Aux->Derecha);
		}
	}
}

std::string NodoAVL::ListaActivo(NodoAVL& Nodo) {
	NAVL AUX = &Nodo;
	ListadoActivos = "";
	if (AUX!=NULL) {
		RecInOrden(*AUX);
	}
	else {
		ListadoActivos = "SIN ACTIVOS\n";
	}
	return ListadoActivos;
}