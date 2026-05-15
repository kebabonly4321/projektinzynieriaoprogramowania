#include "Uzytkownik.h"

Uzytkownik::Uzytkownik(string login, string haslo) {
    this->login = login;
    this->haslo = haslo;
}

Uzytkownik::~Uzytkownik() {}

string Uzytkownik::getLogin() const {
    return login;
}

string Uzytkownik::getHaslo() const {
    return haslo;
}

bool Uzytkownik::sprawdzHaslo(string podaneHaslo) const {
    return haslo == podaneHaslo;
}

