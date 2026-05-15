#ifndef TEST_H
#define TEST_H

#include <string>
#include <vector>

using namespace std;

struct Pytanie {
    string tresc;
    string a, b, c, d;
    char poprawna;
};

class Test {
private:
    vector<Pytanie> pytania;

public:
    void dodajPytanie();
    void przeprowadzTest() const;
    bool czyPusty() const;
    vector<Pytanie> getPytania() const;
    void dodajPytanieZPliku(Pytanie p);
};

#endif