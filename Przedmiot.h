#ifndef PRZEDMIOT_H
#define PRZEDMIOT_H

#include <string>
#include <vector>
#include "Test.h"

using namespace std;

struct Temat {
    string nazwa;
    string material;
    Test test;
};

class Przedmiot {
private:
    string nazwa;
    string prowadzacy;
    vector<Temat> tematy;

public:
    Przedmiot(string nazwa, string prowadzacy);

    string getNazwa() const;
    string getProwadzacy() const;

    void dodajTemat();
    void przegladajTematy();
    void dodajTestDoTematu();
    vector<Temat>& getTematy();
    void dodajTematZPliku(string nazwa, string material);
};

#endif