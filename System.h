#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <string>
#include "Uzytkownik.h"
#include "Student.h"
#include "Wykladowca.h"
#include "Przedmiot.h"

using namespace std;

class System {
private:
    vector<Uzytkownik*> uzytkownicy;
    vector<Przedmiot> przedmioty;

    vector<int> dozwoloneAlbumy;
    vector<int> dozwoloneIdWykladowcow;

public:
    System();
    ~System();

    void uruchom();

private:
    void menuGlowne();
    void rejestracja();
    Uzytkownik* logowanie();

    void menuStudenta(Student* student);
    void menuWykladowcy(Wykladowca* wykladowca);

    void zapiszStudentaNaPrzedmiot(Student* student);
    void wybierzPrzedmiotJakoStudent(Student* student);

    void utworzPrzedmiot(Wykladowca* wykladowca);
    void uzupelnijMaterialy();
    void dodajTest();

    bool czyLoginIstnieje(string login) const;
    bool czyAlbumDozwolony(int numer) const;
    bool czyIdWykladowcyDozwolone(int id) const;

    int wybierzPrzedmiot();

    void zapiszDane();
    void wczytajDane();

    void zapiszUzytkownikow();
    void zapiszPrzedmioty();
    void zapiszZapisyStudentow();

    void wczytajUzytkownikow();
    void wczytajPrzedmioty();
    void wczytajZapisyStudentow();

    void zapiszTematy();
    void zapiszTesty();

    void wczytajTematy();
    void wczytajTesty();

Przedmiot* znajdzPrzedmiotPoNazwie(string nazwa);

    Student* znajdzStudentaPoLoginie(string login);
};

#endif