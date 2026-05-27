#include  <iostream>
#include <cassert>

#include "../System.h"
#include "../Student.h"

int main() {

    // Test 1: Student
    {
        std::cout << "Test 1: [START]" << std::endl;

        Student student("loginTest", "haslo123", 1001);

        assert(student.getLogin() == "loginTest");
        assert(student.getHaslo() == "haslo123");
        assert(student.getNumerAlbumu() == 1001);
        assert(student.getTyp() == "Student");
        assert(student.sprawdzHaslo("blednehaslo321") == false);
        assert(student.sprawdzHaslo("haslo123") == true);

        std::cout << "Test 1: [OK]" << std::endl;
    }

    // Test 2: System + Student i Przedmiot
    {
        std::cout << "Test 2: [START]" << std::endl;

        bool wczytajDane = false;
        System system(wczytajDane);

        Student* student = new Student("testLogin", "haslo321", 1001);
        system.getStudenci().push_back(student);

        Przedmiot przedmiot("przedmiotTest", "admin");
        system.getPrzedmioty().push_back(przedmiot);

        assert(student->czyZapisany(przedmiot.getNazwa()) == false);
        student->zapiszNaPrzedmiot(przedmiot.getNazwa());
        assert(student->czyZapisany(przedmiot.getNazwa()) == true);

        std::cout << "Test 2: [OK]" << std::endl;
    }

    // Test 3: System + pliki zapis/odczyt + Wykladowca

    {
        std::cout << "Test 3: [START]" << std::endl;

        bool wczytajDane = false;
        System system(wczytajDane);

        assert(system.stworzFolder(system.getPath()));
        assert(system.clearFile("uzytkownicy_test.txt"));

        Wykladowca* w = new Wykladowca("w1", "123", 501);

        system.zapiszWykladowce(w, "uzytkownicy_test.txt");
        system.wczytajUzytkownikow("uzytkownicy_test.txt");

        assert(system.getWykladowcy().size() == 1);
        assert(system.getWykladowcy().back()->getLogin() == "w1");
        assert(system.getWykladowcy().back()->getId() == 501);

        std::cout << "Test 3: [OK]" << std::endl;
    }

    std::cout << "Wszystkie testy zakończone sukcesem" << std::endl;
}
