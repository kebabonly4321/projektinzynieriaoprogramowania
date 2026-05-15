#include "Student.h"

Student::Student(string login, string haslo, int numerAlbumu)
    : Uzytkownik(login, haslo) {
    this->numerAlbumu = numerAlbumu;
}

int Student::getNumerAlbumu() const {
    return numerAlbumu;
}

void Student::zapiszNaPrzedmiot(string nazwaPrzedmiotu) {
    if (!czyZapisany(nazwaPrzedmiotu)) {
        zapisanePrzedmioty.push_back(nazwaPrzedmiotu);
    }
}

bool Student::czyZapisany(string nazwaPrzedmiotu) const {
    for (string p : zapisanePrzedmioty) {
        if (p == nazwaPrzedmiotu) {
            return true;
        }
    }
    return false;
}

vector<string> Student::getZapisanePrzedmioty() const {
    return zapisanePrzedmioty;
}

string Student::getTyp() const {
    return "Student";
}