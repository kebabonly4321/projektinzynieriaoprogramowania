#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H

#include <string>

using namespace std;

class Uzytkownik {
protected:
    string login;
    string haslo;

public:
    Uzytkownik(string login, string haslo);
    virtual ~Uzytkownik();

    string getLogin() const;
    string getHaslo() const;
    bool sprawdzHaslo(string podaneHaslo) const;
    

    virtual string getTyp() const = 0;
};

#endif