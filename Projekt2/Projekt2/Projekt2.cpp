#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

#define rozmiar 5

struct STUDENT {
    string imie;
    string nazwisko;
    double oceny[rozmiar];
    double srednia_ocen;
};

void pobierzIloscStudentow(int &ilosc);
void pobierzStudentow(STUDENT tab[], int ilosc);
void losowanieOcen(STUDENT tab[], int ilosc);
void sredniaStudenta(STUDENT tab[], int ilosc);

int main()
{
    srand(time(NULL));
    int N;
    pobierzIloscStudentow(N);
    STUDENT* tablica = new STUDENT[N];
    pobierzStudentow(tablica, N);
    losowanieOcen(tablica, N);
    sredniaStudenta(tablica, N);
}

void pobierzIloscStudentow(int &ilosc) {
    cout << "Podaj liczbe studentow: ";
    cin >> ilosc;
    while (ilosc < 1) {
        cout << "Liczba studentow nie moze byc mniejsza od 1!" << endl;
        cout << "Podaj poprawna liczbe studentow: ";
        cin >> ilosc;
    }
}

void pobierzStudentow(STUDENT tab[], int ilosc) {
    ifstream plik;
    plik.open("Studenci.txt");
    if (plik.is_open()) {
        for (int i = 0; i < ilosc; i++) {
            plik >> tab[i].imie >> tab[i].nazwisko;
        }
    }
    else {
        cout << "Blad otwierania pliku, sprawdz czy plik znajduje sie w tym samym folderze co program!" << endl;
    }
    plik.close();
}

void losowanieOcen(STUDENT tab[], int ilosc) {
    double tab_oceny[7] = {2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5};
    for (int i = 0; i < ilosc; i++) {
        for (int j = 0; j < rozmiar; j++) {
            tab[i].oceny[j] = tab_oceny[rand() % 7];
        }
    }
}

void sredniaStudenta(STUDENT tab[], int ilosc) {
    double suma;
    for (int i = 0; i < ilosc; i++) {
        suma = 0;
        for (int j = 0; j < rozmiar; j++) {
            suma += tab[i].oceny[j];
        }
        tab[i].srednia_ocen = suma / rozmiar;
    }
}