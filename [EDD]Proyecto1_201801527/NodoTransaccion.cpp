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

void NodoTransaccion::ReporteTransaccionesUnUsuario(NodoMatriz& User) {
	NM USER = &User;
	std::ofstream fs("C:\\GraficasE\\TransaccionesUnUsuario.dot");
	fs << "digraph G {" << std::endl;
	fs << "node [margin=0, shape=box, style=filled];" << std::endl;
	NT Aux = InicioTransacciones;
	int Contador = 0;
	while (Aux != NULL) {
		if (Aux->UserRentador== USER) {
			fs << "R" << Contador << " [label=\"ID: " << Aux->ID << "\\n" << "RENTA: " << Aux->UserRenta->Usuario << "\\n" << "ACTIVO: " << Aux->Activo->Nombre << "\\n" << "RENTADOR: " << Aux->UserRentador->Usuario << "\"];\n";
			Contador++;
		}
		Aux = Aux->Siguiente;
		if (Aux == InicioTransacciones) { break; }
	}
	std::string Rank = "";
	Aux = InicioTransacciones;
	for (int i = 0; i < Contador; i++){
		fs << "R"<<std::to_string(i)<<" -> ";
		Rank += "R" + std::to_string(i) + ";";
	}
	if (Contador>0) {
		fs << "R0 [dir=\"both\"]; \n";
		fs << "{" << " rank = same ; " << Rank << "}\n";
	}
	fs << "}" << std::endl;
	fs.close();
	system("C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe -Tpng C:\\GraficasE\\TransaccionesUnUsuario.dot -o C:\\GraficasE\\TransaccionesUnUsuario.png");
	system("C:\\GraficasE\\TransaccionesUnUsuario.png &");
}

void NodoTransaccion::BubbleSort(bool ASC_DESC) {//true ASCENDENTE false DESCENDENTE
	if (InicioTransacciones!=FinTransacciones) {
		std::string ID = "";
		NAVL Activo = NULL;
		NM UserRenta = NULL;
		NM UserRentador = NULL;
		time_t FechaRenta = NULL;
		int DiasRenta = 0;
		if (ASC_DESC==true) {
			NT Aux1 = InicioTransacciones;
			while (Aux1!=NULL){
				NT Aux2 = Aux1->Siguiente;
				while (Aux2!=NULL){
					if (strcmp(Aux1->ID.c_str(), Aux2->ID.c_str()) == 1) {
						ID = Aux1->ID; 
						Activo = Aux1->Activo; 
						UserRenta = Aux1->UserRenta; 
						UserRentador = Aux1->UserRentador;
						FechaRenta = Aux1->FechaRenta; 
						DiasRenta = Aux1->DiasRenta;
						Aux1->ID = Aux2->ID; 
						Aux1->Activo = Aux2->Activo; 
						Aux1->UserRenta = Aux2->UserRenta;
						Aux1->UserRentador = Aux2->UserRentador; 
						Aux1->FechaRenta = Aux2->FechaRenta;
						Aux1->DiasRenta = Aux2->DiasRenta;
						Aux2->ID = ID; 
						Aux2->Activo = Activo; 
						Aux2->UserRenta =UserRenta;
						Aux2->UserRentador = UserRentador; 
						Aux2->FechaRenta = FechaRenta;
						Aux2->DiasRenta = DiasRenta;
					}
					Aux2 = Aux2->Siguiente;
					if (Aux2 == InicioTransacciones) { break; }
				}
				Aux1 = Aux1->Siguiente;
				if (Aux1 == FinTransacciones) { break; }
			}
		}
		else{
			NT Aux1 = InicioTransacciones;
			while (Aux1 != NULL) {
				NT Aux2 = Aux1->Siguiente;
				while (Aux2 != NULL) {
					if (strcmp(Aux1->ID.c_str(), Aux2->ID.c_str()) == -1) {
						ID = Aux1->ID;
						Activo = Aux1->Activo;
						UserRenta = Aux1->UserRenta;
						UserRentador = Aux1->UserRentador;
						FechaRenta = Aux1->FechaRenta;
						DiasRenta = Aux1->DiasRenta;
						Aux1->ID = Aux2->ID;
						Aux1->Activo = Aux2->Activo;
						Aux1->UserRenta = Aux2->UserRenta;
						Aux1->UserRentador = Aux2->UserRentador;
						Aux1->FechaRenta = Aux2->FechaRenta;
						Aux1->DiasRenta = Aux2->DiasRenta;
						Aux2->ID = ID;
						Aux2->Activo = Activo;
						Aux2->UserRenta = UserRenta;
						Aux2->UserRentador = UserRentador;
						Aux2->FechaRenta = FechaRenta;
						Aux2->DiasRenta = DiasRenta;
					}
					Aux2 = Aux2->Siguiente;
					if (Aux2 == InicioTransacciones) { break; }
				}
				Aux1 = Aux1->Siguiente;
				if (Aux1 == FinTransacciones) { break; }
			}
		}
	}
}