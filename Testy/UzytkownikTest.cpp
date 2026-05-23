#include <iostream>
#include <cassert>

#include "Wykladowca.h"
#include "../Student.h"

void getLoginTest() {
    Student s("test", "321", 1001);
    assert(s.getLogin() == "test");
}

void studentZapisTest() {
    Student s("student", "haslo123", 1003);
    s.zapiszNaPrzedmiot("Programowanie C++");
    assert(s.czyZapisany("Programowanie C++") == true);
}

void getIDWykladowcaTest() {
    Wykladowca w("hubi", "123", 501);
    assert(w.getId() == 501);
}

int main() {
    getLoginTest();

    return 0;
}

