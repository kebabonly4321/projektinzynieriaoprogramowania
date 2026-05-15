#include "System.h"
#include <iostream>
#include <fstream>

using namespace std;

System::System() {
    dozwoloneAlbumy = {1001, 1002, 1003, 1004};
    dozwoloneIdWykladowcow = {501, 502, 503};

    wczytajDane();

    if (przedmioty.empty()) {
        przedmioty.push_back(Przedmiot("Programowanie C++", "admin"));
        przedmioty.push_back(Przedmiot("Matematyka dyskretna", "admin"));
    }
}

System::~System() {
    zapiszDane();

    for (Uzytkownik* u : uzytkownicy) {
        delete u;
    }
}

void System::uruchom() {
    menuGlowne();
}

void System::menuGlowne() {
    int wybor;

    do {
        cout << "\n===== SYSTEM EDUKACYJNY =====\n";
        cout << "1. Logowanie\n";
        cout << "2. Rejestracja\n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";
        cin >> wybor;

        switch (wybor) {
            case 1: {
                Uzytkownik* u = logowanie();

                if (u != nullptr) {
                    if (u->getTyp() == "Student") {
                        menuStudenta(dynamic_cast<Student*>(u));
                    } else if (u->getTyp() == "Wykladowca") {
                        menuWykladowcy(dynamic_cast<Wykladowca*>(u));
                    }
                }

                break;
            }

            case 2:
                rejestracja();
                break;

            case 0:
                cout << "Koniec programu.\n";
                break;

            default:
                cout << "Niepoprawny wybor.\n";
        }

    } while (wybor != 0);
}

void System::rejestracja() {
    string login, haslo;
    int typ;

    cout << "\n===== REJESTRACJA =====\n";
    cout << "Login: ";
    cin >> login;

    if (czyLoginIstnieje(login)) {
        cout << "Taki login juz istnieje.\n";
        return;
    }

    cout << "Haslo: ";
    cin >> haslo;

    cout << "Wybierz typ konta:\n";
    cout << "1. Student\n";
    cout << "2. Wykladowca\n";
    cout << "Wybor: ";
    cin >> typ;

    if (typ == 1) {
        int album;
        cout << "Podaj numer albumu: ";
        cin >> album;

        if (!czyAlbumDozwolony(album)) {
            cout << "Nie ma takiego numeru albumu w bazie.\n";
            return;
        }

        uzytkownicy.push_back(new Student(login, haslo, album));
        cout << "Zarejestrowano studenta.\n";

    } else if (typ == 2) {
        int id;
        cout << "Podaj ID wykladowcy: ";
        cin >> id;

        if (!czyIdWykladowcyDozwolone(id)) {
            cout << "Nie ma takiego ID wykladowcy w bazie.\n";
            return;
        }

        uzytkownicy.push_back(new Wykladowca(login, haslo, id));
        cout << "Zarejestrowano wykladowce.\n";

    } else {
        cout << "Niepoprawny typ konta.\n";
    }
}

Uzytkownik* System::logowanie() {
    string login, haslo;

    cout << "\n===== LOGOWANIE =====\n";
    cout << "Login: ";
    cin >> login;

    cout << "Haslo: ";
    cin >> haslo;

    for (Uzytkownik* u : uzytkownicy) {
        if (u->getLogin() == login && u->sprawdzHaslo(haslo)) {
            cout << "Zalogowano jako: " << u->getTyp() << endl;
            return u;
        }
    }

    cout << "Bledny login lub haslo.\n";
    return nullptr;
}

void System::menuStudenta(Student* student) {
    int wybor;

    do {
        cout << "\n===== MENU STUDENTA =====\n";
        cout << "1. Zapisz sie na przedmiot\n";
        cout << "2. Wybierz przedmiot i przegladaj baze wiedzy\n";
        cout << "0. Wyloguj\n";
        cout << "Wybor: ";
        cin >> wybor;

        switch (wybor) {
            case 1:
                zapiszStudentaNaPrzedmiot(student);
                break;

            case 2:
                wybierzPrzedmiotJakoStudent(student);
                break;

            case 0:
                cout << "Wylogowano.\n";
                break;

            default:
                cout << "Niepoprawny wybor.\n";
        }

    } while (wybor != 0);
}

void System::menuWykladowcy(Wykladowca* wykladowca) {
    int wybor;

    do {
        cout << "\n===== MENU WYKLADOWCY =====\n";
        cout << "1. Utworz nowy przedmiot\n";
        cout << "2. Uzupelnij materialy z przedmiotu\n";
        cout << "3. Dodaj test do tematu\n";
        cout << "0. Wyloguj\n";
        cout << "Wybor: ";
        cin >> wybor;

        switch (wybor) {
            case 1:
                utworzPrzedmiot(wykladowca);
                break;

            case 2:
                uzupelnijMaterialy();
                break;

            case 3:
                dodajTest();
                break;

            case 0:
                cout << "Wylogowano.\n";
                break;

            default:
                cout << "Niepoprawny wybor.\n";
        }

    } while (wybor != 0);
}

void System::zapiszStudentaNaPrzedmiot(Student* student) {
    int indeks = wybierzPrzedmiot();

    if (indeks == -1) return;

    string nazwa = przedmioty[indeks].getNazwa();

    if (student->czyZapisany(nazwa)) {
        cout << "Jestes juz zapisany na ten przedmiot.\n";
        return;
    }

    student->zapiszNaPrzedmiot(nazwa);
    cout << "Zapisano na przedmiot: " << nazwa << endl;
}

void System::wybierzPrzedmiotJakoStudent(Student* student) {

    vector<int> dostepneIndeksy;

    cout << "\n===== TWOJE PRZEDMIOTY =====\n";

    for (int i = 0; i < przedmioty.size(); i++) {

        if (student->czyZapisany(przedmioty[i].getNazwa())) {

            dostepneIndeksy.push_back(i);

            cout << dostepneIndeksy.size()
                 << ". "
                 << przedmioty[i].getNazwa()
                 << " | prowadzacy: "
                 << przedmioty[i].getProwadzacy()
                 << endl;
        }
    }

    if (dostepneIndeksy.empty()) {
        cout << "Nie jestes zapisany na zaden przedmiot.\n";
        return;
    }

    cout << "0. Powrot\n";

    int wybor;

    cout << "Wybor: ";
    cin >> wybor;

    if (wybor == 0) {
        return;
    }

    if (wybor < 1 || wybor > dostepneIndeksy.size()) {
        cout << "Niepoprawny wybor.\n";
        return;
    }

    int indeksPrzedmiotu = dostepneIndeksy[wybor - 1];

    przedmioty[indeksPrzedmiotu].przegladajTematy();
}

void System::utworzPrzedmiot(Wykladowca* wykladowca) {
    string nazwa;

    cin.ignore();

    cout << "Podaj nazwe nowego przedmiotu: ";
    getline(cin, nazwa);

    przedmioty.push_back(Przedmiot(nazwa, wykladowca->getLogin()));

    cout << "Dodano przedmiot.\n";
}

void System::uzupelnijMaterialy() {
    int indeks = wybierzPrzedmiot();

    if (indeks == -1) return;

    przedmioty[indeks].dodajTemat();
}

void System::dodajTest() {
    int indeks = wybierzPrzedmiot();

    if (indeks == -1) return;

    przedmioty[indeks].dodajTestDoTematu();
}

bool System::czyLoginIstnieje(string login) const {
    for (Uzytkownik* u : uzytkownicy) {
        if (u->getLogin() == login) {
            return true;
        }
    }
    return false;
}

bool System::czyAlbumDozwolony(int numer) const {
    for (int n : dozwoloneAlbumy) {
        if (n == numer) {
            return true;
        }
    }
    return false;
}

bool System::czyIdWykladowcyDozwolone(int id) const {
    for (int i : dozwoloneIdWykladowcow) {
        if (i == id) {
            return true;
        }
    }
    return false;
}

int System::wybierzPrzedmiot() {
    if (przedmioty.empty()) {
        cout << "Brak przedmiotow w systemie.\n";
        return -1;
    }

    int wybor;

    cout << "\nLista przedmiotow:\n";
    for (int i = 0; i < przedmioty.size(); i++) {
        cout << i + 1 << ". " << przedmioty[i].getNazwa()
             << " | prowadzacy: " << przedmioty[i].getProwadzacy() << endl;
    }

    cout << "0. Powrot\n";
    cout << "Wybor: ";
    cin >> wybor;

    if (wybor == 0) return -1;

    if (wybor < 1 || wybor > przedmioty.size()) {
        cout << "Niepoprawny wybor.\n";
        return -1;
    }

    return wybor - 1;
}

vector<string> podziel(string tekst, char separator) {
    vector<string> wynik;
    string aktualny = "";

    for (char znak : tekst) {
        if (znak == separator) {
            wynik.push_back(aktualny);
            aktualny = "";
        } else {
            aktualny += znak;
        }
    }

    wynik.push_back(aktualny);

    return wynik;
}

void System::zapiszDane() {
    zapiszUzytkownikow();
    zapiszPrzedmioty();
    zapiszZapisyStudentow();
    zapiszTematy();
    zapiszTesty();
}

void System::wczytajDane() {
    wczytajUzytkownikow();
    wczytajPrzedmioty();
    wczytajZapisyStudentow();
    wczytajTematy();
    wczytajTesty();
}

void System::zapiszUzytkownikow() {
    ofstream plik("uzytkownicy.txt");

    for (Uzytkownik* u : uzytkownicy) {
        if (u->getTyp() == "Student") {
            Student* s = dynamic_cast<Student*>(u);

            plik << "Student;"
                 << s->getLogin() << ";"
                 << s->getHaslo() << ";"
                 << s->getNumerAlbumu() << endl;
        }

        else if (u->getTyp() == "Wykladowca") {
            Wykladowca* w = dynamic_cast<Wykladowca*>(u);

            plik << "Wykladowca;"
                 << w->getLogin() << ";"
                 << w->getHaslo() << ";"
                 << w->getId() << endl;
        }
    }

    plik.close();
}

void System::zapiszPrzedmioty() {
    ofstream plik("przedmioty.txt");

    for (Przedmiot p : przedmioty) {
        plik << p.getNazwa() << ";"
             << p.getProwadzacy() << endl;
    }

    plik.close();
}

void System::zapiszZapisyStudentow() {
    ofstream plik("zapisy.txt");

    for (Uzytkownik* u : uzytkownicy) {
        if (u->getTyp() == "Student") {
            Student* s = dynamic_cast<Student*>(u);

            vector<string> zapisy = s->getZapisanePrzedmioty();

            for (string przedmiot : zapisy) {
                plik << s->getLogin() << ";"
                     << przedmiot << endl;
            }
        }
    }

    plik.close();
}

void System::wczytajUzytkownikow() {
    ifstream plik("uzytkownicy.txt");

    if (!plik.is_open()) {
        return;
    }

    string linia;

    while (getline(plik, linia)) {
        vector<string> dane = podziel(linia, ';');

        if (dane.size() != 4) {
            continue;
        }

        string typ = dane[0];
        string login = dane[1];
        string haslo = dane[2];
        int numer = stoi(dane[3]);

        if (typ == "Student") {
            uzytkownicy.push_back(new Student(login, haslo, numer));
        }

        else if (typ == "Wykladowca") {
            uzytkownicy.push_back(new Wykladowca(login, haslo, numer));
        }
    }

    plik.close();
}

void System::wczytajPrzedmioty() {
    ifstream plik("przedmioty.txt");

    if (!plik.is_open()) {
        return;
    }

    string linia;

    while (getline(plik, linia)) {
        vector<string> dane = podziel(linia, ';');

        if (dane.size() != 2) {
            continue;
        }

        string nazwa = dane[0];
        string prowadzacy = dane[1];

        przedmioty.push_back(Przedmiot(nazwa, prowadzacy));
    }

    plik.close();
}

void System::wczytajZapisyStudentow() {
    ifstream plik("zapisy.txt");

    if (!plik.is_open()) {
        return;
    }

    string linia;

    while (getline(plik, linia)) {
        vector<string> dane = podziel(linia, ';');

        if (dane.size() != 2) {
            continue;
        }

        string loginStudenta = dane[0];
        string nazwaPrzedmiotu = dane[1];

        Student* student = znajdzStudentaPoLoginie(loginStudenta);

        if (student != nullptr) {
            student->zapiszNaPrzedmiot(nazwaPrzedmiotu);
        }
    }

    plik.close();
}

Przedmiot* System::znajdzPrzedmiotPoNazwie(string nazwa) {
    for (Przedmiot& p : przedmioty) {
        if (p.getNazwa() == nazwa) {
            return &p;
        }
    }

    return nullptr;
}

void System::zapiszTematy() {
    ofstream plik("tematy.txt");

    for (Przedmiot& p : przedmioty) {
        vector<Temat>& tematy = p.getTematy();

        for (Temat& t : tematy) {
            plik << p.getNazwa() << ";"
                 << t.nazwa << ";"
                 << t.material << endl;
        }
    }

    plik.close();
}

void System::zapiszTesty() {
    ofstream plik("testy.txt");

    for (Przedmiot& p : przedmioty) {
        vector<Temat>& tematy = p.getTematy();

        for (Temat& t : tematy) {
            vector<Pytanie> pytania = t.test.getPytania();

            for (Pytanie pytanie : pytania) {
                plik << p.getNazwa() << ";"
                     << t.nazwa << ";"
                     << pytanie.tresc << ";"
                     << pytanie.a << ";"
                     << pytanie.b << ";"
                     << pytanie.c << ";"
                     << pytanie.d << ";"
                     << pytanie.poprawna << endl;
            }
        }
    }

    plik.close();
}

void System::wczytajTematy() {
    ifstream plik("tematy.txt");

    if (!plik.is_open()) {
        return;
    }

    string linia;

    while (getline(plik, linia)) {
        vector<string> dane = podziel(linia, ';');

        if (dane.size() != 3) {
            continue;
        }

        string nazwaPrzedmiotu = dane[0];
        string nazwaTematu = dane[1];
        string material = dane[2];

        Przedmiot* przedmiot = znajdzPrzedmiotPoNazwie(nazwaPrzedmiotu);

        if (przedmiot != nullptr) {
            przedmiot->dodajTematZPliku(nazwaTematu, material);
        }
    }

    plik.close();
}

void System::wczytajTesty() {
    ifstream plik("testy.txt");

    if (!plik.is_open()) {
        return;
    }

    string linia;

    while (getline(plik, linia)) {
        vector<string> dane = podziel(linia, ';');

        if (dane.size() != 8) {
            continue;
        }

        string nazwaPrzedmiotu = dane[0];
        string nazwaTematu = dane[1];

        Przedmiot* przedmiot = znajdzPrzedmiotPoNazwie(nazwaPrzedmiotu);

        if (przedmiot == nullptr) {
            continue;
        }

        vector<Temat>& tematy = przedmiot->getTematy();

        for (Temat& t : tematy) {
            if (t.nazwa == nazwaTematu) {
                Pytanie p;
                p.tresc = dane[2];
                p.a = dane[3];
                p.b = dane[4];
                p.c = dane[5];
                p.d = dane[6];
                p.poprawna = dane[7][0];

                t.test.dodajPytanieZPliku(p);
                break;
            }
        }
    }

    plik.close();
}

Student* System::znajdzStudentaPoLoginie(string login) {
    for (Uzytkownik* u : uzytkownicy) {
        if (u->getTyp() == "Student" && u->getLogin() == login) {
            return dynamic_cast<Student*>(u);
        }
    }

    return nullptr;
}