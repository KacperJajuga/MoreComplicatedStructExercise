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
void wyswietlanieStudentow(STUDENT tab[], int ilosc);
double sredniaWszystkichStudentow(STUDENT tab[], int ilosc);
int iloscStudentowPowyzejSredniej(STUDENT tab[], int ilosc, double srednia);
void studenciNajwyzszaSrednia(STUDENT tab[], int ilosc);

int main()
{
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|                         Program wyswietli liste studentow oraz wylosowane dla nich oceny.                         |" << endl;
    cout << "|               Zostanie wyswietlona rowniez srednia ocen kazdego studenta oraz wszystkich studentow.               |" << endl;
    cout << "|     Dane studentow, ktorzy uzyskali najwieksza srednia, zostana wyswietlone na ekranie oraz zapisane do pliku.    |" << endl;
    cout << "| Program umozliwi wyszukiwanie konkretnego studenta po wpisaniu pelnego imienia i nazwiska poszukiwanego studenta. |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    srand(time(NULL));
    int N, powyzej_sredniej;
    pobierzIloscStudentow(N);
    STUDENT* tablica = new STUDENT[N];
    pobierzStudentow(tablica, N);
    losowanieOcen(tablica, N);
    sredniaStudenta(tablica, N);
    wyswietlanieStudentow(tablica, N);
    double srednia_wszystkich;
    srednia_wszystkich = sredniaWszystkichStudentow(tablica, N);
    cout << "\nSrednia wszystkich studentow w bazie danych to: " << srednia_wszystkich << endl;
    powyzej_sredniej = iloscStudentowPowyzejSredniej(tablica, N, srednia_wszystkich);
    cout << "\nSrednia wieksza, niz srednia wszystkich studentow zdobylo " << powyzej_sredniej << " studentow." << endl;
    studenciNajwyzszaSrednia(tablica, N);
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
    for (int i = 0; i < ilosc; i++) {
        for (int j = 0; j < rozmiar; j++) {
            tab[i].oceny[j] = rand() % 7 * 0.5 + 2;
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

void wyswietlanieStudentow(STUDENT tab[], int ilosc) {
    cout << "W bazie danych znajduje sie " << ilosc << " studentow" << endl;
    for (int i = 0; i < ilosc; i++) {
        cout << "\n\nImie i nazwisko " << i+1 << ". studenta w bazie danych to: " << tab[i].imie << " " << tab[i].nazwisko << endl;
        for (int j = 0; j < rozmiar; j++) {
            cout << "Ocena " << j+1 << " tego studenta to: " << tab[i].oceny[j] << endl;
        }
        cout << "Srednia ocen tego studenta to: " << tab[i].srednia_ocen << endl;
    }
}

double sredniaWszystkichStudentow(STUDENT tab[], int ilosc) {
    double srednia = 0;
    for (int i = 0; i < ilosc; i++) {
        srednia += tab[i].srednia_ocen;
    }
    srednia = srednia / ilosc;
    return srednia;
}

int iloscStudentowPowyzejSredniej(STUDENT tab[], int ilosc, double srednia) {
    int suma = 0;
    for (int i = 0; i < ilosc; i++) {
        if (tab[i].srednia_ocen > srednia) {
            suma++;
        }
    }
    return suma;
}

void studenciNajwyzszaSrednia(STUDENT tab[], int ilosc) {
    cout << "Wyswietlanie i zapisywanie do pliku studentow, ktorzy zdobyli srednia z przedzialu <4.0, 5.0>." << endl;
    ofstream plik_z_wynikami;
    plik_z_wynikami.open("wyniki.txt");
    if (plik_z_wynikami.is_open()) {
        for (int i = 0; i < ilosc; i++) {
            if (tab[i].srednia_ocen >= 4.0 && tab[i].srednia_ocen <= 5.0) {
                cout << "\n\nImie i nazwisko " << i + 1 << ". studenta w bazie danych to: " << tab[i].imie << " " << tab[i].nazwisko << endl;
                for (int j = 0; j < rozmiar; j++) {
                    cout << "Ocena " << j + 1 << " tego studenta to: " << tab[i].oceny[j] << endl;
                }
                cout << "Srednia ocen tego studenta to: " << tab[i].srednia_ocen << endl;
            }
        }
    }
    else {
        cout << "Blad otwierania pliku!" << endl;
    }
    plik_z_wynikami.close();
}