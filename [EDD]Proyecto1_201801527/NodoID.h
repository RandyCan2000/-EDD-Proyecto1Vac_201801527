#pragma once
#include <iostream>
typedef class NodoID* NID;
class NodoID{
public:
	std::string ValID="";
	NodoID* Sig=NULL;

	NodoID(std::string ValID);
	NodoID();

	std::string GenerarID();
};

