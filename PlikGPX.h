
#pragma once
#include "PunktMapa.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;


class PlikGPX
{
private:
	string sciezka;
protected:
	vector<PunktMapa>PunktyV;
public:

	PlikGPX();//konstruktor domyslny
	PlikGPX(string sciezka);


	//metody
	void wczytaj();
	void wypiszPunkty();//metoda próbna do wyœwietlenia zgodnoœci danych z plikiem
	void oszukajObliczanie();//metoda która zwraca nam ostantie wartosci z pliku tzn. <exerciseinfo>
	vector<PunktMapa> zwrocPunkty();// zwraca wektor punktow wyciagnietych z pliku
};
