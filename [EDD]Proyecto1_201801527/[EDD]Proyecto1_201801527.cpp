#include <iostream>
#include "NodoMatriz.h"
#include "Globales.h"
#include <stdio.h>  
#include <windows.h> 
#include <cctype>
using namespace std;

void MenuAdmin() {

}
void MenuUser() {

}

void Login() {
	system("cls");
	char U[100],C[100],D[100],E[100];
	char* Usuario=U,*Contrasena =C,*Departamento = D,*Empresa = E;
	gotoxy(50, 5);
	cout << "LOGIN";
	gotoxy(30, 7);
	cout << "Usuario: "; cin.getline(Usuario,100);
	gotoxy(30, 9);
	cout << "Contrasena: "; cin.getline(Contrasena,100);
	gotoxy(30, 11);
	cout << "Departamento: "; cin.getline(Departamento,100);
	gotoxy(30, 13);
	cout << "Empresa: "; cin.getline(Empresa,100);
	NM Log = new NodoMatriz();
	Log->BuscarNodo(U,C,ToUpperCase(D), ToUpperCase(E));
	if (UserLog!=NULL) {
		gotoxy(30, 15);
		SetColor(2);
		cout << "BIENVENIDO " << UserLog->Usuario;
		SetColor(15);
		if (Admin == true) {
			MenuAdmin();
		}
		else {
			MenuUser();
		}
	}
	else {
		gotoxy(30, 15);
		SetColor(4);
		cout << "USUARIO NO ENCONTRADO";
		SetColor(15);
	}
	delete Log;
	getchar();
}

int main(){
	InicioMatriz = new NodoMatriz("admin", "admin", "", "");
	NM US1 = new NodoMatriz("Randy", "Intercan1", "GUATEMALA", "USAC");
	NM US2 = new NodoMatriz("a", "a", "GUATEMALA", "USAC");
	NM C1 = new NodoMatriz("GUATEMALA",true);
	NM C2 = new NodoMatriz("USAC", false);
	InicioMatriz->Derecha = C1;
	C1->Izquierda = InicioMatriz;
	InicioMatriz->Abajo = C2;
	C2->Arriba = InicioMatriz;
	C1->Abajo = US1;
	US1->Arriba = C1;
	C2->Derecha = US1;
	US1->Izquierda = C2;
	US1->Atras = US2;
	US2->Adelante = US1;
	do
	{
		char N[10];
		char* Opcion=N;
		system("cls");
		gotoxy(50, 5);
		cout << "BIENVENIDO";
		gotoxy(20, 7);
		cout << "Opciones";
		gotoxy(30, 9);
		cout << "1. LOGIN";
		gotoxy(30, 11);
		cout << "2. SALIR";
		gotoxy(30, 13);
		cout << "SELECCIONAR OPCION: ";
		cin.getline(Opcion,10);
		if (EsUnNumero(N)==true) {
			string val = N;
			if (val=="1") {
				Login();
				UserLog = NULL;
				Admin = false;
			}
			else if(val=="2"){
				break;
			}
			else {
				gotoxy(30, 15);
				cout << "OPCION NO ENCONTRADA";
				getchar();
			}
		}
		else {
			gotoxy(30, 15);
			cout << "SOLO INGRESE NUMEROS";
			getchar();
		}
	} while (true);
	return 0;
}