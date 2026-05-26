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
    vector<Student*> studenci;
    vector<Wykladowca*> wykladowcy;
    vector<Przedmiot> przedmioty;

    vector<int> dozwoloneAlbumy;
    vector<int> dozwoloneIdWykladowcow;
    string path = "output/";

public:
    System(bool czyWczytajDane);
    ~System();

    void uruchom();

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
    bool czyAlbumZajety(int numer) const;
    bool czyIdWykladowcyZajete(int id) const;

    int wybierzPrzedmiot();

    void wczytajDane();

    void zapiszStudenta(Student *student);

    void zapiszStudenta(Student *student, string nazwaPliku);

    void zapiszWykladowce(Wykladowca *wykladowca);

    void zapiszWykladowce(Wykladowca *wykladowca, string nazwaPliku);

    void zapiszZapisStudentaNaPrzedmiot(Student *student, string nazwaPrzedmiotu);

    void zapiszUtworzonyPrzedmiot(string nazwa, string prowadzacy);

    void zapiszUtworzonyPrzedmiot(string nazwa, string prowadzacy, string nazwaPliku);

    void zapiszTemat(string nazwaPrzedmiotu, Temat temat);

    void wczytajUzytkownikow();

    void wczytajUzytkownikow(string nazwaPliku);

    void wczytajPrzedmioty();

    void wczytajPrzedmioty(string nazwaPliku);

    void wczytajZapisyStudentow();

    void zapiszTest(string nazwaPrzedmiotu, string nazwaTematu, Test *test);

    void wczytajTematy();
    void wczytajTesty();

    Przedmiot* znajdzPrzedmiotPoNazwie(string nazwa);

    Student* znajdzStudentaPoLoginie(string login);

    bool stworzFolder(string nazwa);

    vector<Wykladowca *> getWykladowcy() const;

    void setPath(string path);
    string getPath();

    string makePath(string nazwaPliku);

    bool clearFile(string nazwaPliku);

    vector<Przedmiot> getPrzedmioty() const;

    vector<Student *> getStudenci() const;
};

#endif