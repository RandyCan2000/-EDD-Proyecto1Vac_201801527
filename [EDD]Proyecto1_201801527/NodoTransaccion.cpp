#include "NodoTransaccion.h"
#include "NodoID.h"
#include "Globales.h"
#include <iomanip>
#include <fstream>
#pragma warning(disable:4996)

NodoTransaccion::NodoTransaccion(NodoMatriz &UserRenta, NodoAVL &Activo, int DiasRenta) {
	NID id = new NodoID();
	this->ID = id->GenerarID();
	this->Activo = &Activo;
	this->UserRenta = &UserRenta;//Es el usuario que renta
	this->UserRentador = UserLog;//es el usuario que pide el activo en renta
	this->FechaRenta = Fecha_y_Hora_Actual();
	this->DiasRenta = DiasRenta;
	this->Siguiente = NULL;
	this->Anterior = NULL;
	delete id;
}
NodoTransaccion::NodoTransaccion() {}

bool NodoTransaccion::AgregarRenta(NodoMatriz& UserRenta, NodoAVL& Activo, int DiasRenta) {
	NAVL Act = &Activo;
	NM User = &UserRenta;
	if (InicioTransacciones == NULL) {
		InicioTransacciones = new NodoTransaccion(*User, *Act, DiasRenta);
		FinTransacciones = InicioTransacciones;
		InicioTransacciones->Anterior = FinTransacciones;
		FinTransacciones->Siguiente = FinTransacciones;
		Act->Rentado = true;
		return true;
	}
	else {
		NT Nuevo = new NodoTransaccion(*User, *Act, DiasRenta);
		FinTransacciones->Siguiente = Nuevo;
		Nuevo->Anterior = FinTransacciones;
		FinTransacciones = Nuevo;
		FinTransacciones->Siguiente = InicioTransacciones;
		InicioTransacciones->Anterior = FinTransacciones;
		Act->Rentado = true;
		return true;
	}
	return false;
}
std::string NodoTransaccion::ListadoActivosRentados() {
	NT Aux = InicioTransacciones;
	tm* Fecha = NULL;
	std::string Texto ="";
	while (Aux!=NULL){
		if (Aux->UserRentador==UserLog) {
			Fecha = localtime(&Aux->FechaRenta);
			Texto += "ID RENTA: " + Aux->ID + " ACTIVO: " + Aux->Activo->Nombre + " PROPIEDAD DE: " + Aux->UserRenta->Usuario + " FECHA: " + std::to_string(Fecha->tm_mday) + "/" + std::to_string(Fecha->tm_mon + 1) + "/" + std::to_string(Fecha->tm_year + 1900) + " DIAS: " + std::to_string(Aux->DiasRenta)+"\n";
		}
		Aux = Aux->Siguiente;
		if (Aux == InicioTransacciones) { break; }
	}
	if (Texto==""){
		Texto = "NO HA RENTADO NINGUN ACTIVO\n";
	}
	return Texto;
}

bool NodoTransaccion::QuitarRenta(std::string ID_Renta){
	NT Aux = InicioTransacciones;
	while (Aux!=NULL){
		if(Aux->ID==ID_Renta){
			if (Aux==InicioTransacciones && Aux==FinTransacciones) {
				Aux->Activo->Rentado = false;
				InicioTransacciones = NULL;
				FinTransacciones = NULL;
				delete Aux;
				return true;
			}
			else {
				Aux->Activo->Rentado = false;
				NT Ant = Aux->Anterior;
				NT Sig = Aux->Siguiente;
				Ant->Siguiente = Sig;
				Sig->Anterior = Ant;
				if (Aux == InicioTransacciones) { InicioTransacciones = Sig; }
				if (Aux == FinTransacciones) { FinTransacciones = Ant; }
				delete Aux;
				return true;
			}
			break;
		}
		Aux = Aux->Siguiente;
		if (Aux == InicioTransacciones) { break; }
	}
	return false;
}

void NodoTransaccion::ReporteTransacciones() {
	std::ofstream fs("C:\\GraficasE\\TodasLasTransacciones.dot");
	fs << "digraph G {" << std::endl;
	fs << "node [margin=0, shape=box, style=filled];" << std::endl;
	NT Aux = InicioTransacciones;
	int Contador = 0;
	while (Aux!=NULL){
		fs << "R"<<Contador<<"[label=\"ID: " << Aux->ID << "\\n" << "RENTA: " << Aux->UserRenta->Usuario << "\\n" << "ACTIVO: " << Aux->Activo->Nombre << "\\n" << "RENTADOR: " << Aux->UserRentador->Usuario<<"\"];\n";
		Contador++;
		Aux = Aux->Siguiente;
		if (Aux == InicioTransacciones) { break; }
	}
	Contador=0;
	std::string Rank = "";
	Aux = InicioTransacciones;
	while (Aux != NULL){
		if (Aux->Siguiente!=InicioTransacciones) {
			fs << "R" << Contador << " -> " << "R" << Contador + 1 << " [dir=\"both\"];\n";
			Rank += "R" + std::to_string(Contador)+";";
		}
		Contador++;
		Aux = Aux->Siguiente;
		if (Aux == InicioTransacciones) { 
			Rank += "R" + std::to_string(Contador-1) + ";";
			fs << "R" << Contador-1 << " -> " << "R0" << " [dir=\"both\"];\n";
			break; 
		}
	}
	fs << "{" <<" rank = same ; "<<Rank<< "}";
	fs << "}" << std::endl;
	fs.close();
	system("C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng C:\\GraficasE\\TodasLasTransacciones.dot -o C:\\GraficasE\\TodasLasTransacciones.png");
	system("C:\\GraficasE\\TodasLasTransacciones.png &");
}