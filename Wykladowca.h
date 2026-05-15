#ifndef WYKLADOWCA_H
#define WYKLADOWCA_H

#include "Uzytkownik.h"

class Wykladowca : public Uzytkownik {
private:
    int id;

public:
    Wykladowca(string login, string haslo, int id);

    int getId() const;

    string getTyp() const override;
};

#endif