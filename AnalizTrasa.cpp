#include "AnalizTrasa.h"
#include <iomanip>
#include <cmath>



const double R = 6371000.0; // promie� Ziemi w metrach

AnalizTrasa::AnalizTrasa()
{

}

AnalizTrasa::AnalizTrasa(vector<PunktMapa>PunktyV)
{
    this->PunktyV = PunktyV;

}

// zmienna pomocnicza konwersuj�ca (To radian) stopnie na radiany
double tor(double stopnie) {
    return stopnie * 3.1415 / 180.0;
}

// funkcja Haversinea
double haversine(double lat1, double lon1, double lat2, double lon2)
{
    double dLat = tor(lat2 - lat1);
    double dLon = tor(lon2 - lon1);
    lat1 = tor(lat1);
    //lat1 = fabs(lat1);//uzyskanie warto�ci bezwgl�dnej - jednak nie potrzebne 
    lat2 = tor(lat2);
    //lat2 = fabs(lat2);//uzyskanie warto�ci bezwgl�dnej - jednak nie potrzebne 

    double a = sin(dLat / 2) * sin(dLat / 2) + cos(lat1) * cos(lat2) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c; // odleg�o�� w metrach
}

//TAK WIEMY �E CA�KOWITY DYSTANS JEST PODANY NA KO�CU PLIKU GPX
//TU GO PO PORSOTU DODATKOWO OBLICZAMY
void AnalizTrasa::dystansCalkowity()
{
    //double dystans = 0.0; ta zmienna zosta�a dodana do zmiennej klasowej aby u�y� jej przy pomiarach predkosci
    for (int i = 1; i < PunktyV.size(); i++)
    {
        double lon1 = PunktyV[i - 1].getDlugoscG(); // lon = long = d�ugo��
        double lat1 = PunktyV[i - 1].getSzerrokoscG();// lat = latitude = d�ugo��
        double ele1 = PunktyV[i - 1].getWysokosc();// ele = elevation = wysoko��

        double lon2 = PunktyV[i].getDlugoscG();
        double lat2 = PunktyV[i].getSzerrokoscG();
        double ele2 = PunktyV[i].getWysokosc();

        double odleglosc = haversine(lat1, lon1, lat2, lon2);

        double rWysokosci = ele2 - ele1;

        double odlegosc3D = sqrt(rWysokosci * rWysokosci + odleglosc * odleglosc);

        //dystans += odleglosc;
        dystans += odlegosc3D;


    }

    cout << "Calkowity dystans pokonanej trasy wynosci: " << dystans << " metrow;";// wyniuk pokazuje odleg�o�� uwzgledniaj�c wzniesenia oraz spadki

}


// funkcja pomocnicza do ujednolicenia danych na intigery
int parseInt(string KP, int start, int dlugosc)//parseInt wyciaga ze stringa elementy od zmiennej 'start' o d�ugosci o zmiennej 'dlugosc', stoi - String To Int (zamiana na inty), KP - Koniec czy poczatek (wybieramy z jakiego punktu naszego wektora korzystamy)
{
    return stoi(KP.substr(start, dlugosc));
}
double czasWsekundach;//do tej zmiennej wrzucamy czasy zsumowane, aby kozysta� z niej w nastepnej metodzie
void AnalizTrasa::czasCalkowity()
{


    //Z naszego wektora pomoar�w bierzemy pierwsze i ostatnie watrosci czasu aby go obliczy�
    if (!PunktyV.empty()) {
        // Czas pocz�tkowy
        string czasP = PunktyV.front().getCzas();
        int rokP = parseInt(czasP, 0, 4);
        int miesiacP = parseInt(czasP, 5, 2);
        int dzienP = parseInt(czasP, 8, 2);
        int godzinaP = parseInt(czasP, 11, 2);
        int minutaP = parseInt(czasP, 14, 2);
        int sekundaP = parseInt(czasP, 17, 2);

        // Czas ko�cowy
        string czasK = PunktyV.back().getCzas();
        int rokK = parseInt(czasK, 0, 4);
        int miesiacK = parseInt(czasK, 5, 2);
        int dzienK = parseInt(czasK, 8, 2);
        int godzinaK = parseInt(czasK, 11, 2);
        int minutaK = parseInt(czasK, 14, 2);
        int sekundaK = parseInt(czasK, 17, 2);

        //odliczanie czasu podrozy
        int sekundaS = sekundaK - sekundaP;
        if (sekundaS < 0) {
            sekundaS += 60;
            minutaK--;
        }

        int minutaS = minutaK - minutaP;
        if (minutaS < 0) {
            minutaS += 60;
            godzinaK--;
        }

        int godzinaS = godzinaK - godzinaP;
        if (godzinaS < 0) {
            godzinaS += 24;
            dzienK--;
        }

        int dzienS = dzienK - dzienP;
        if (dzienS < 0) {
            dzienS += 30; // UWAGA uproszczenie � mo�na doda� dok�adne dni miesi�ca
            miesiacK--;
        }

        int miesiacS = miesiacK - miesiacP;
        if (miesiacS < 0) {
            miesiacS += 12;
            rokK--;
        }

        int rokS = rokK - rokP;

        cout << "Twoja podroz trwala: "
            << rokS << " lat | "
            << miesiacS << " miesiecy | "
            << dzienS << " dni | "
            << godzinaS << " godzin | "
            << minutaS << " minut | "
            << sekundaS << " sekund!" << endl;



        //dodajemy tu sekundy z kazdej zmiennej     //np. rok mno�my przez ilosc miesiecy, dni, godzin i. aby uzyskac sekundy
        czasWsekundach = (rokS * (12 * 30 * 24 * 60 * 60)) + (miesiacS * (30 * 24 * 60 * 60)) + (dzienS * (24 * 60 * 60)) + (godzinaS * (60 * 60)) + (minutaS * 60) + sekundaS;
        cout << "czas w sekundach: " << czasWsekundach << endl;;
    }
    else {
        cout << "Wektor jest pusty!" << endl;
    }


}


void AnalizTrasa::predkosci()
{
    //srednia predkosc calej podrozy
    srPredkosc = dystans / czasWsekundach;
    cout << "\nSrednia predkosc wynosi: " << srPredkosc << " m/s" << endl;

}

void AnalizTrasa::wysokosciMinMax()
{
    double minWysokosc = PunktyV[0].getWysokosc();
    double maxWysokosc = PunktyV[0].getWysokosc();
    double minKM = 0.0;
    double maxKM = 0.0;
    for (int i = 1; i < PunktyV.size(); i++) {
        double punkt = PunktyV[i].getWysokosc();
        if (punkt < minWysokosc) {
            minWysokosc = punkt;
            minKM = i;
        }
        if (punkt > maxWysokosc) {
            maxWysokosc = punkt;
            maxKM = i;
        }
    }
    minKM = ktoryKM(minKM);
    maxKM = ktoryKM(maxKM);
    cout << "Wysokosc minimalna: " << minWysokosc << " na km: " << minKM << endl;
    cout << "Wysokosc maksymalna: " << maxWysokosc << " na km:  " << maxKM << endl;
}

double AnalizTrasa::ktoryKM(int pkt)
{
    if (pkt <= 0 or pkt >= PunktyV.size()) {
        return 0.0;
    }
    double km = 0.0;
    for (int i = 1; i <= pkt; ++i)
    {
        double lon1 = PunktyV[i - 1].getDlugoscG();
        double lat1 = PunktyV[i - 1].getSzerrokoscG();
        double ele1 = PunktyV[i - 1].getWysokosc();

        double lon2 = PunktyV[i].getDlugoscG();
        double lat2 = PunktyV[i].getSzerrokoscG();
        double ele2 = PunktyV[i].getWysokosc();

        double h = haversine(lat1, lon1, lat2, lon2);
        double dh = ele2 - ele1;

        double d3D = sqrt(h * h + dh * dh);

        km += d3D;
    }

    return km / 1000.0;
}

void AnalizTrasa::wyswietlDane()
{
    czasCalkowity();
    dystansCalkowity();
    predkosci();
    wysokosciMinMax();
}