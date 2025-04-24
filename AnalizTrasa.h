#include "PlikGPX.h"
//klasa pochodna do klasy PLIKGPX, sluzaca do analizowania tras(np. dlugosc trasy)
class AnalizTrasa : public PlikGPX
{
private:
	double dystans;
	double srPredkosc;//srednia predkosc
public:
	AnalizTrasa();//konstruktor domyslny;
	AnalizTrasa(vector<PunktMapa>PunktyV);

	//metody
	//dystans calkowity
	void dystansCalkowity();
	//czas calkowity
	void czasCalkowity();
	//predkosc maks, minimalna
	void predkosci();
	// wysokosc Minimalna i maksymalna
	void wysokosciMinMax();
	//zwraca ktory km dla punktu
	double ktoryKM(int pkt);
	//uzywa wszystkich metod do wysweitlania danych
	void wyswietlDane();

};