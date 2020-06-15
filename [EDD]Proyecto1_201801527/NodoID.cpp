#include "NodoID.h"
#include <iostream>
#include "Globales.h"

NodoID::NodoID(std::string ValID){
	this->ValID = ValID;
	this->Sig = NULL;
}
NodoID::NodoID() {}

char CARACTERES[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5' ,'6' ,'7' ,'8' ,'9' };

bool RecorrerLista(std::string NuevoID) {
	NID Aux = ListaID;
	bool Existe = false;
	while (Aux!=NULL){
		if (Aux->ValID == NuevoID) {
			Existe = true;
			break;
		}
		Aux = Aux->Sig;
	}
	return Existe;
}

bool AgregarNodo(std::string ID) {
	if (ListaID ==NULL) {
		ListaID = new NodoID(ID);
		return true;
	}else {
		NID Nuevo = new NodoID(ID);
		Nuevo->Sig = ListaID;
		ListaID = Nuevo;
		return true;
	}
	return false;
}

std::string NodoID::GenerarID() {
	std::string ID = "";
	int valor = 0;
	bool Seguir = false;
	do{
		ID = "";
		for (int i = 0; i < 15; i++) {
			valor = rand() % 36;
			ID += CARACTERES[valor];
		}
		Seguir = RecorrerLista(ID);
	} while (Seguir);
	AgregarNodo(ID);
	return ID;
}