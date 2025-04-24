#include <iostream>
#include"PlikGPX.h"
#include"AnalizTrasa.h"
int main()
{
	//z jakegos powodu plik nie wczutuje sie gdy uzywamy \ lub \\(blad cerr), ale juz tak gdy/ tak jak ponizej
	//trzeba zmienic plik .gpx na .txt

	//L.R
	//PlikGPX GdyniaPlik("C:/Users/leonr/OneDrive/Pulpit/Gdynia.txt");
	//PlikGPX CzernicaPlik("C:/Users/leonr/OneDrive/Pulpit/Czernica.txt");
	//O.R
	
	PlikGPX GdyniaPlik("C:/Users/plack/Downloads/gdynia.txt");
	//PlikGPX CzernicaPlik("sciezka rybaczyk");
	
	GdyniaPlik.wczytaj();
	//GdyniaPlik.wypiszPunkty();
	GdyniaPlik.oszukajObliczanie();
	AnalizTrasa GdyniaAnaliza(GdyniaPlik.zwrocPunkty());
	GdyniaAnaliza.wyswietlDane();

}