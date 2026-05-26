#include "System.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>

#ifdef _WIN32
    #include <direct.h>
    #define mkdir _mkdir
#else
    #include <unistd.h>
#endif

using namespace std;

System::System(bool czyWczytajDane) {
    stworzFolder("output");

    dozwoloneAlbumy = {1001, 1002, 1003, 1004, 1005};
    dozwoloneIdWykladowcow = {501, 502, 503};

    if (czyWczytajDane) {
        wczytajDane();
    }

    if (przedmioty.empty()) {
        przedmioty.push_back(Przedmiot("Programowanie C++", "admin"));
        przedmioty.push_back(Przedmiot("Matematyka dyskretna", "admin"));
    }
}

System::~System() {
    for (Student* s : studenci) delete s;
    for (Wykladowca* w : wykladowcy) delete w;
}

void System::uruchom() {
    menuGlowne();
}

void System::menuGlowne() {
    char wybor;

    do {
        cout << "\n===== SYSTEM EDUKACYJNY =====\n";
        cout << "1. Logowanie\n";
        cout << "2. Rejestracja\n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";
        cin >> wybor;
        cin.ignore(1000, '\n');

        switch (wybor) {
            case '1': {
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

            case '2':
                rejestracja();
                break;

            case '0':
                cout << "Koniec programu.\n";
                break;

            default:
                cout << "Niepoprawny wybor.\n";
        }

    } while (wybor != '0');
}

void System::rejestracja() {
    string login, haslo, hasloPowtorzone, typ;
    int counter = 0;

    cout << "\n===== REJESTRACJA =====\n";
    while (true) {
        if (counter >= 3) {
            cout << "Przekroczono limit prob rejestracji.\n";
            return;
        }

        cout << "Login: ";
        cin >> login;

        if (czyLoginIstnieje(login)) {
            cout << "Taki login juz istnieje.\n";
            counter++;
            continue;
        }
        break;
    }

    counter = 0;

    while (true) { // Hasło
        if (counter >= 3) {
            cout << "Przekroczono limit prob rejestracji.\n";
            return;
        }

        cout << "Haslo: ";
        cin >> haslo;
        cout << "Powtorz haslo: ";
        cin >> hasloPowtorzone;

        if (haslo == hasloPowtorzone) break;

        cout << "Hasla nie sa takie same. Sprobuj ponownie.\n";
        counter++;
    }

    counter = 0;

    while (true) { // Typ konta
        cout << "Wybierz typ konta:\n";
        cout << "1. Student\n";
        cout << "2. Wykladowca\n";
        cout << "Wybor: ";
        cin >> typ;

        if (typ == "1") { // Student
            while (true) {
                if (counter >= 3) {
                    cout << "Przekroczono limit prob rejestracji.\n";
                    return;
                }
                int album;
                cout << "Podaj numer albumu: ";
                cin >> album;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Niepoprawny numer.\n";
                    counter++;
                    continue;
                }

                if (!czyAlbumDozwolony(album)) {
                    cout << "Nie ma takiego numeru albumu w bazie.\n";
                    counter++;
                    continue;
                }

                if (czyAlbumZajety(album)) {
                    cout << "Podany numer albumu jest zajety.\n";
                    continue;
                }

                Student* nowyStudent = new Student(login, haslo, album);
                studenci.push_back(nowyStudent);
                zapiszStudenta(nowyStudent);
                cout << "Zarejestrowano studenta.\n";
                return;
            }
        }

        if (typ == "2") { // Wykladowca
            while (true) {
                if (counter >= 3) {
                    cout << "Przekroczono limit prob rejestracji.\n";
                    return;
                }

                int id;
                cout << "Podaj ID wykladowcy: ";
                cin >> id;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Niepoprawne ID.\n";
                    counter++;
                    continue;
                }

                if (!czyIdWykladowcyDozwolone(id)) {
                    cout << "Nie ma takiego ID wykladowcy w bazie.\n";
                    counter++;
                    continue;
                }

                if (czyIdWykladowcyZajete(id)) {
                    cout << "Podane id jest zajete.\n";
                    continue;
                }

                Wykladowca* nowyWykladowca = new Wykladowca(login, haslo, id);
                wykladowcy.push_back(nowyWykladowca);
                zapiszWykladowce(nowyWykladowca);
                cout << "Zarejestrowano wykladowce.\n";
                return;
            }
        }
        cout << "Niepoprawny typ konta.\n";
    }
}

Uzytkownik* System::logowanie() {
    string login, haslo;
    int counter = 0;

    while (counter < 3) {
        cout << "\n===== LOGOWANIE =====\n";
        cout << "Login: ";
        cin >> login;

        cout << "Haslo: ";
        cin >> haslo;

        for (Student* s : studenci) {
            if (s->getLogin() == login && s->sprawdzHaslo(haslo)) {
                cout << "Zalogowano jako: Student"  << endl;
                return s;
            }
        }

        for (Wykladowca* w : wykladowcy) {
            if (w->getLogin() == login && w->sprawdzHaslo(haslo)) {
                cout << "Zalogowano jako: Wykladowca" << endl;
                return w;
            }
        }

        cout << "Bledny login lub haslo.\n";
        counter++;
    }
    cout << "Przekroczono limit prob logowania.\n";
    return nullptr;
}

void System::menuStudenta(Student* student) {
    int wybor = -1;

    do {
        cout << "\n===== MENU STUDENTA =====\n";
        cout << "1. Zapisz sie na przedmiot\n";
        cout << "2. Wybierz przedmiot i przegladaj baze wiedzy\n";
        cout << "0. Wyloguj\n";
        cout << "Wybor: ";

        if (!(cin >> wybor)) {
            cin.clear();
            cin.ignore(1000, '\n');
            wybor = -1;
            cout << "Niepoprawny wybor.\n";
            continue;
        }

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
                break;
        }

    } while (wybor != 0);
}

void System::menuWykladowcy(Wykladowca* wykladowca) {
    int wybor = -1;

    do {
        cout << "\n===== MENU WYKLADOWCY =====\n";
        cout << "1. Utworz nowy przedmiot\n";
        cout << "2. Uzupelnij materialy z przedmiotu\n";
        cout << "3. Dodaj test do tematu\n";
        cout << "0. Wyloguj\n";
        cout << "Wybor: ";

        if (!(cin >> wybor)) {
            cin.clear();
            cin.ignore(1000, '\n');
            wybor = -1;
            cout << "Niepoprawny wybor.\n";
            continue;
        }

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
                break;
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
    zapiszZapisStudentaNaPrzedmiot(student, nazwa);
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

    while (true) {
        cout << "Wybor: ";
        cin >> wybor;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Niepoprawny wybor. Sprobuj ponownie.\n";
            continue;
        }

        if (wybor == 0) return;

        if (wybor < 1 || wybor > dostepneIndeksy.size()) {
            cout << "Niepoprawny wybor.\n";
            continue;
        }

        int indeksPrzedmiotu = dostepneIndeksy[wybor - 1];
        przedmioty[indeksPrzedmiotu].przegladajTematy();

        // wraca do przedmiotow po wyjsciu z tematow
        cout << "\n===== TWOJE PRZEDMIOTY =====\n";
        dostepneIndeksy.clear();

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

        cout << "0. Powrot\n";
    }
}

void System::utworzPrzedmiot(Wykladowca* wykladowca) {
    string nazwa;

    cin.clear();
    cin.ignore(1000, '\n');

    cout << "Podaj nazwe nowego przedmiotu: ";
    getline(cin, nazwa);

    przedmioty.push_back(Przedmiot(nazwa, wykladowca->getLogin()));
    zapiszUtworzonyPrzedmiot(nazwa, wykladowca->getLogin());
    cout << "Dodano przedmiot.\n";
}

void System::uzupelnijMaterialy() {
    int indeks = wybierzPrzedmiot();

    if (indeks == -1) return;

    Temat t = przedmioty[indeks].dodajTemat();

    zapiszTemat(przedmioty[indeks].getNazwa(), t);
}

void System::dodajTest() {
    int indeks = wybierzPrzedmiot();

    if (indeks == -1) return;

    int indeksTematu = przedmioty[indeks].dodajTestDoTematu();
    if (indeksTematu == -1) return;

    vector<Temat>& tematy = przedmioty[indeks].getTematy();
    Temat& t = tematy[indeksTematu];

    zapiszTest(przedmioty[indeks].getNazwa(), t.nazwa, &t.test);
}

bool System::czyLoginIstnieje(string login) const {
    for (Student* s : studenci)
        if (s->getLogin() == login) return true;
    for (Wykladowca* w : wykladowcy)
        if (w->getLogin() == login) return true;
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

bool System::czyAlbumZajety(int numer) const {
    for (Student* s : studenci) {
        if (s->getNumerAlbumu() == numer) return true;
    }
    return false;
}

bool System::czyIdWykladowcyZajete(int id) const {
    for (Wykladowca* w : wykladowcy) {
        if (w->getId() == id) return true;
    }
    return false;
}


int System::wybierzPrzedmiot() {
    if (przedmioty.empty()) {
        cout << "Brak przedmiotow w systemie.\n";
        return -1;
    }

    while (true) {
        int wybor;

        cout << "\nLista przedmiotow:\n";
        for (int i = 0; i < przedmioty.size(); i++) {
            cout << i + 1 << ". " << przedmioty[i].getNazwa()
                 << " | prowadzacy: " << przedmioty[i].getProwadzacy() << endl;
        }

        cout << "0. Powrot\n";
        cout << "Wybor: ";
        cin >> wybor;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Niepoprawny wybor. Sprobuj ponownie.\n";
            continue;
        }
        cin.ignore(1000, '\n');

        if (wybor == 0) return -1;

        if (wybor < 1 || wybor > przedmioty.size()) {
            cout << "Niepoprawny wybor. Sprobuj ponownie.\n";
            continue;
        }

        return wybor - 1;
    }
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

void System::wczytajDane() {
    wczytajUzytkownikow();
    wczytajPrzedmioty();
    wczytajZapisyStudentow();
    wczytajTematy();
    wczytajTesty();
}

void System::zapiszStudenta(Student* student) {
    ofstream plik(makePath("uzytkownicy.txt"), ios::app);

    if (!plik.is_open()) {
        cout << "Blad zapisu studenta.\n";
        return;
    }

    plik << "Student;"
        << student->getLogin()
        << ';' << student->getHaslo()
        << ';' << student->getNumerAlbumu() << endl;
    plik.close();
}

void System::zapiszStudenta(Student* student, string nazwaPliku) {
    ofstream plik(makePath(nazwaPliku), ios::app);

    if (!plik.is_open()) {
        cout << "Blad zapisu studenta.\n";
        return;
    }

    plik << "Student;"
        << student->getLogin()
        << ';' << student->getHaslo()
        << ';' << student->getNumerAlbumu() << endl;
    plik.close();
}

void System::zapiszWykladowce(Wykladowca* wykladowca) {
    ofstream plik(makePath("uzytkownicy.txt"), ios::app);

    if (!plik.is_open()) {
        cout << "Blad zapisu wykladowcy.\n";
        return;
    }

    plik << "Wykladowca;"
        << wykladowca->getLogin()
        << ';' << wykladowca->getHaslo()
        << ';' << wykladowca->getId() << endl;
    plik.close();
}

void System::zapiszWykladowce(Wykladowca* wykladowca, string nazwaPliku) {
    ofstream plik(makePath(nazwaPliku), ios::app);

    if (!plik.is_open()) {
        cout << "Blad zapisu wykladowcy.\n";
        return;
    }

    plik << "Wykladowca;"
        << wykladowca->getLogin()
        << ';' << wykladowca->getHaslo()
        << ';' << wykladowca->getId() << endl;
    plik.close();
}

void System::zapiszZapisStudentaNaPrzedmiot(Student* student, string nazwaPrzedmiotu) {
    ofstream plik(makePath("zapisy.txt"), ios::app);

    if (!plik.is_open()) {
        cout << "Blad zapisu do przedmiotu.\n";
        return;
    }
    plik << student->getLogin() << ';'
                << nazwaPrzedmiotu << endl;
    plik.close();
}

void System::zapiszUtworzonyPrzedmiot(string nazwa, string prowadzacy) {
    ofstream plik(makePath("przedmioty.txt"), ios::app);

    if (!plik.is_open()) {
        cout << "Blad zapisu przedmiotow.\n";
        return;
    }

    plik << nazwa << ';'
             << prowadzacy << endl;

    plik.close();
}

void System::zapiszUtworzonyPrzedmiot(string nazwa, string prowadzacy, string nazwaPliku) {
    ofstream plik(makePath(nazwaPliku), ios::app);

    if (!plik.is_open()) {
        cout << "Blad zapisu przedmiotow.\n";
        return;
    }

    plik << nazwa << ';'
             << prowadzacy << endl;

    plik.close();
}

void System::zapiszTemat(string nazwaPrzedmiotu, Temat temat) {
    ofstream plik(makePath("tematy.txt"), ios::app);

    if (!plik.is_open()) {
        cout << "Blad zapisu tematu.\n";
        return;
    }

    plik << nazwaPrzedmiotu << ';'
            << temat.nazwa << ';'
            << temat.material << endl;
    plik.close();
}

void System::wczytajUzytkownikow() {
    ifstream plik(makePath("uzytkownicy.txt"));

    if (!plik.is_open()) {
        cout << "Blad odczytu z systemu.\n";
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
            studenci.push_back(new Student(login, haslo, numer));
        }

        else if (typ == "Wykladowca") {
            wykladowcy.push_back(new Wykladowca(login, haslo, numer));
        }
    }

    plik.close();
}

void System::wczytajUzytkownikow(string nazwaPliku) {
    ifstream plik(makePath(nazwaPliku));

    if (!plik.is_open()) {
        cout << "Blad odczytu z systemu.\n";
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
            studenci.push_back(new Student(login, haslo, numer));
        }

        else if (typ == "Wykladowca") {
            wykladowcy.push_back(new Wykladowca(login, haslo, numer));
        }
    }

    plik.close();
}

void System::wczytajPrzedmioty() {
    ifstream plik(makePath("przedmioty.txt"));

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

void System::wczytajPrzedmioty(string nazwaPliku) {
    ifstream plik(makePath(nazwaPliku));

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
    ifstream plik(makePath("zapisy.txt"));

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

void System::zapiszTest(string nazwaPrzedmiotu, string nazwaTematu, Test* test) {
    ofstream plik(makePath("testy.txt"), ios::app);

    if (!plik.is_open()) {
        cout << "Blad zapisu testu.\n";
        return;
    }

    for (Pytanie& p : test->getPytania()) {
        plik << nazwaPrzedmiotu << ';'
            << nazwaTematu << ';'
            << p.tresc << ';'
            << p.a << ';'
            << p.b << ';'
            << p.c << ';'
            << p.d << ';'
            << p.poprawna << endl;
    }
    plik.close();
}

void System::wczytajTematy() {
    ifstream plik(makePath("tematy.txt"));

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
    ifstream plik(makePath("testy.txt"));

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
    for (Student* s : studenci) {
        if (s->getLogin() == login) return s;
    }
    return nullptr;
}

bool System::stworzFolder(string nazwa) {
    struct stat info;

    if (stat(nazwa.c_str(), &info) == 0) {
        if (S_ISDIR(info.st_mode)) {
            return true; // istnieje, ok
        }
        cout << "Istnieje juz plik o nazwie: " << nazwa << '\n';
        return false;
    }

    int result;

#ifdef _WIN32
    result = _mkdir(nazwa.c_str());
#else
    result = mkdir(nazwa.c_str(), 0755);
#endif

    if (result != 0) {
        cout << "Blad tworzenia folderu: " << nazwa << endl;
        return false;
    }

    return true;
}

vector<Wykladowca *> System::getWykladowcy() const {
    return wykladowcy;
}

void System::setPath(string path) {
    this->path = path;
}

string System::getPath() {
    return path;
}

string System::makePath(string nazwaPliku) {
    return path + nazwaPliku;
}

bool System::clearFile(string nazwaPliku) {
    std::ofstream plik(makePath(nazwaPliku), std::ios::trunc);

    if (!plik.is_open()) {
        std::cout << "Blad odczytu pliku: " << nazwaPliku << "\n";
        return false;
    }

    if (plik.fail()) {
        std::cout << "Blad operacji na pliku: " << nazwaPliku << "\n";
    }

    plik.close();
    return true;
}

vector<Przedmiot> System::getPrzedmioty() const {
    return przedmioty;
}

vector<Student*> System::getStudenci() const {
    return studenci;
}