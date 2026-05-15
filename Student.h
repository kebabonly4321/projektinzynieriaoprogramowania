#ifndef STUDENT_H
#define STUDENT_H

#include "Uzytkownik.h"
#include <vector>
#include <string>

using namespace std;

class Student : public Uzytkownik {
private:
    int numerAlbumu;
    vector<string> zapisanePrzedmioty;

public:
    Student(string login, string haslo, int numerAlbumu);

    int getNumerAlbumu() const;

    void zapiszNaPrzedmiot(string nazwaPrzedmiotu);
    bool czyZapisany(string nazwaPrzedmiotu) const;
    vector<string> getZapisanePrzedmioty() const;

    string getTyp() const override;
};

#endif