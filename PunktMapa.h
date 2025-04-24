#pragma once
#include<string>

using namespace std;

class PunktMapa
{
private:
	double szerokoscG;
	double dlugoscG;
	double wysokosc;
	string czas;

public:
	PunktMapa();//konstruktor domyslny
	PunktMapa(double szerokoscG, double dlugoscG, double wysokosc, string czas);//konstruktor zdefiniowany


	//G-geograficzna
	//set
	void setSzerokoscG(double szerokoscG);
	void setDlugoscG(double dlugoscG);
	void setWysokosc(double wysokosc);
	void setCzas(string czas);

	//get
	double getSzerrokoscG();
	double getDlugoscG();
	double getWysokosc();
	string getCzas();

};