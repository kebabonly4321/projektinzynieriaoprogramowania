#include "Wykladowca.h"

Wykladowca::Wykladowca(string login, string haslo, int id)
    : Uzytkownik(login, haslo) {
    this->id = id;
}

int Wykladowca::getId() const {
    return id;
}

string Wykladowca::getTyp() const {
    return "Wykladowca";
}