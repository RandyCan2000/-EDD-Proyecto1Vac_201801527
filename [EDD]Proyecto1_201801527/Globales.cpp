#include "Globales.h"
#include "NodoMatriz.h"
#include <stdio.h>  
#include <windows.h>  


int IndexUsuarios = 1;
NM InicioMatriz = NULL;
bool Admin = false;
NM UserLog = NULL;


std::string ToUpperCase(std::string Texto) {
    int i = 0;
    char c;
    std::string TEXT="";
    while (Texto[i]){
        c = Texto[i];
        TEXT+=(char)toupper(c);
        i++;
    }
    return TEXT;
}

bool EsUnNumero(std::string Texto){
    int i = 0;
    while (Texto[i]) {
        if (!std::isdigit(Texto[i])){
            return false;
        }
        i++;
    }
    return true;
}

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)){
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}