#include "Test.h"
#include <iostream>

using namespace std;

void Test::dodajPytanie() {
    Pytanie p;

    cin.ignore();

    cout << "Podaj tresc pytania: ";
    getline(cin, p.tresc);

    cout << "Odpowiedz A: ";
    getline(cin, p.a);

    cout << "Odpowiedz B: ";
    getline(cin, p.b);

    cout << "Odpowiedz C: ";
    getline(cin, p.c);

    cout << "Odpowiedz D: ";
    getline(cin, p.d);

    do {
        cout << "Podaj poprawna odpowiedz A/B/C/D: ";
        cin >> p.poprawna;
        p.poprawna = toupper(p.poprawna);
    } while (p.poprawna != 'A' && p.poprawna != 'B' && p.poprawna != 'C' && p.poprawna != 'D');

    pytania.push_back(p);
}

void Test::przeprowadzTest() const {
    if (pytania.empty()) {
        cout << "Brak testu dla tego tematu.\n";
        return;
    }

    int punkty = 0;
    char odp;

    for (int i = 0; i < pytania.size(); i++) {
        cout << "\nPytanie " << i + 1 << ": " << pytania[i].tresc << endl;
        cout << "A. " << pytania[i].a << endl;
        cout << "B. " << pytania[i].b << endl;
        cout << "C. " << pytania[i].c << endl;
        cout << "D. " << pytania[i].d << endl;

        cout << "Twoja odpowiedz: ";
        cin >> odp;
        odp = toupper(odp);

        if (odp == pytania[i].poprawna) {
            punkty++;
        }
    }

    cout << "\nWynik testu: " << punkty << "/" << pytania.size() << endl;
}

bool Test::czyPusty() const {
    return pytania.empty();
}

vector<Pytanie> Test::getPytania() const {
    return pytania;
}

void Test::dodajPytanieZPliku(Pytanie p) {
    pytania.push_back(p);
}