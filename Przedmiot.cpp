#include "Przedmiot.h"
#include <iostream>

using namespace std;

Przedmiot::Przedmiot(string nazwa, string prowadzacy) {
    this->nazwa = nazwa;
    this->prowadzacy = prowadzacy;
}

string Przedmiot::getNazwa() const {
    return nazwa;
}

string Przedmiot::getProwadzacy() const {
    return prowadzacy;
}

void Przedmiot::dodajTemat() {
    Temat t;

    cin.ignore();

    cout << "Podaj nazwe tematu: ";
    getline(cin, t.nazwa);

    cout << "Podaj material do tematu: ";
    getline(cin, t.material);

    tematy.push_back(t);

    cout << "Dodano temat.\n";
}

void Przedmiot::przegladajTematy() {
    if (tematy.empty()) {
        cout << "Brak tematow w tym przedmiocie.\n";
        return;
    }

    int wybor;

    cout << "\nTematy:\n";
    for (int i = 0; i < tematy.size(); i++) {
        cout << i + 1 << ". " << tematy[i].nazwa << endl;
    }

    cout << "0. Powrot\n";
    cout << "Wybierz temat: ";
    cin >> wybor;

    if (wybor == 0) return;

    if (wybor < 1 || wybor > tematy.size()) {
        cout << "Niepoprawny wybor.\n";
        return;
    }

    Temat &t = tematy[wybor - 1];

    cout << "\nTemat: " << t.nazwa << endl;
    cout << "Material:\n" << t.material << endl;

    cout << "\nCzy chcesz rozwiazac test? 1. Tak 0. Nie: ";
    int decyzja;
    cin >> decyzja;

    if (decyzja == 1) {
        t.test.przeprowadzTest();
    }
}

void Przedmiot::dodajTestDoTematu() {
    if (tematy.empty()) {
        cout << "Brak tematow. Najpierw dodaj temat.\n";
        return;
    }

    int wybor;

    cout << "\nWybierz temat do dodania testu:\n";
    for (int i = 0; i < tematy.size(); i++) {
        cout << i + 1 << ". " << tematy[i].nazwa << endl;
    }

    cout << "0. Powrot\n";
    cout << "Wybor: ";
    cin >> wybor;

    if (wybor == 0) return;

    if (wybor < 1 || wybor > tematy.size()) {
        cout << "Niepoprawny wybor.\n";
        return;
    }

    int ile;
    cout << "Ile pytan chcesz dodac? ";
    cin >> ile;

    for (int i = 0; i < ile; i++) {
        cout << "\nDodawanie pytania " << i + 1 << endl;
        tematy[wybor - 1].test.dodajPytanie();
    }

    cout << "Dodano test.\n";
}

vector<Temat>& Przedmiot::getTematy() {
    return tematy;
}

void Przedmiot::dodajTematZPliku(string nazwa, string material) {
    Temat t;
    t.nazwa = nazwa;
    t.material = material;
    tematy.push_back(t);
}