#include <iostream>

using namespace std;

#define rozmiar 5

struct STUDENT {
    string imie;
    string nazwisko;
    int oceny[rozmiar];
    double srednia_ocen;
};

int main()
{
    int N;
    cout << "Podaj liczbe studentow: ";
    cin >> N;
    while (N < 1) {
        cout << "Liczba studentow nie moze byc mniejsza od 1!" << endl;
        cout << "Podaj poprawna liczbe studentow: ";
        cin >> N;
    }
    STUDENT * tablica = new STUDENT[N];
}