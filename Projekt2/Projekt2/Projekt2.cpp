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
void szukanieStudenta(STUDENT tab[], int ilosc);

int main()
{
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|                         Program wyswietli liste studentow oraz wylosowane dla nich oceny.                         |" << endl;
    cout << "|               Zostanie wyswietlona rowniez srednia ocen kazdego studenta oraz wszystkich studentow.               |" << endl;
    cout << "|     Dane studentow, ktorzy uzyskali najwieksza srednia, zostana wyswietlone na ekranie oraz zapisane do pliku.    |" << endl;
    cout << "| Program umozliwi wyszukiwanie konkretnego studenta po wpisaniu pelnego imienia i nazwiska poszukiwanego studenta. |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Nacisnij ENTER, aby rozpoczac dzialanie programu..." << endl;
    cin.get();
    srand(time(NULL));
    int N, powyzej_sredniej;
    pobierzIloscStudentow(N);
    STUDENT* tablica = new STUDENT[N];
    pobierzStudentow(tablica, N);
    losowanieOcen(tablica, N);
    sredniaStudenta(tablica, N);
    cout << "\nNacisnij ENTER, by wyswietlic wszystkich studentow na liscie..." << endl;
    cin.get();
    cin.get(); //z jakiegos powodu program potrzebuje dwoch instrukcji cin.get();, aby zatrzymac dzialanie
    wyswietlanieStudentow(tablica, N);
    double srednia_wszystkich;
    srednia_wszystkich = sredniaWszystkichStudentow(tablica, N);
    cout << "\nNacisnij ENTER, by wyswietlic srednia wszystkich studentow na liscie..." << endl;
    cin.get();
    cout << "Srednia wszystkich studentow na liscie to: " << srednia_wszystkich << endl;
    powyzej_sredniej = iloscStudentowPowyzejSredniej(tablica, N, srednia_wszystkich);
    cout << "\nNacisnij ENTER, by wyswietlic ilu studentow zdobylo srednia wieksza niz srednia wszystkich studentow..." << endl;
    cin.get();
    cout << "Srednia wieksza, niz srednia wszystkich studentow zdobylo " << powyzej_sredniej << " studentow." << endl;
    cout << "\nNacisnij ENTER, by wyswietlic najlepszych studentow na liscie..." << endl;
    cin.get();
    studenciNajwyzszaSrednia(tablica, N);
    cout << "\n\nNacisnij ENTER, by rozpoczac szukanie studentow..." << endl;
    cin.get();
    szukanieStudenta(tablica, N);
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
    cout << "Na liscie znajduje sie " << ilosc << " studentow" << endl;
    for (int i = 0; i < ilosc; i++) {
        cout << "\n\nImie i nazwisko " << i+1 << ". studenta na liscie to: " << tab[i].imie << " " << tab[i].nazwisko << endl;
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
                cout << "\n\nImie i nazwisko " << i + 1 << ". studenta na liscie to: " << tab[i].imie << " " << tab[i].nazwisko << endl;
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

void szukanieStudenta(STUDENT tab[], int ilosc) {
    int wybor;
    char jeszcze_raz = 'n', znaleziono;
    string imie_studenta;
    string nazwisko_studenta;
    do {
        znaleziono = 'n';
        cout << "Za pomoca jakich danych chcesz wyszukac studenta? " << endl;
        cout << "1. Imie" << endl;
        cout << "2. Nazwisko" << endl;
        cout << "3. Imie i nazwisko" << endl;
        cout << "Wpisz numer wybranej opcji: ";
        cin >> wybor;
        switch (wybor) {
        case 1:
            cout << "\n\nPodaj imie studenta, ktorego dane chcesz wyswietlic: ";
            cin >> imie_studenta;
            for (int i = 0; i < ilosc; i++) {
                if (imie_studenta == tab[i].imie) {
                    cout << "\n\nZnaleziono studenta numer " << i + 1 << ", a imie i nazwisko to: " << tab[i].imie << " " << tab[i].nazwisko << endl;
                    for (int j = 0; j < rozmiar; j++) {
                        cout << "Ocena " << j + 1 << " szukanego studenta to: " << tab[i].oceny[j] << endl;
                    }
                    cout << "Srednia ocen szukanego studenta to: " << tab[i].srednia_ocen << endl;
                    znaleziono = 't';
                }
            }
            if (znaleziono == 'n') {
                cout << "Nie znaleziono studenta o podanym imieniu!" << endl;
            }
            break;
        case 2:
            cout << "\n\nPodaj nazwisko studenta, ktorego dane chcesz wyswietlic: ";
            cin >> nazwisko_studenta;
            for (int i = 0; i < ilosc; i++) {
                if (nazwisko_studenta == tab[i].nazwisko) {
                    cout << "\n\nZnaleziono studenta numer " << i + 1 << ", a imie i nazwisko to: " << tab[i].imie << " " << tab[i].nazwisko << endl;
                    for (int j = 0; j < rozmiar; j++) {
                        cout << "Ocena " << j + 1 << " szukanego studenta to: " << tab[i].oceny[j] << endl;
                    }
                    cout << "Srednia ocen szukanego studenta to: " << tab[i].srednia_ocen << endl;
                    znaleziono = 't';
                }
            }
            if (znaleziono == 'n') {
                cout << "Nie znaleziono studenta o podanym nazwisku!" << endl;
            }
            break;
        case 3:
            cout << "\n\nPodaj imie studenta, ktorego dane chcesz wyswietlic: ";
            cin >> imie_studenta;
            cout << "Podaj nazwisko studenta, ktorego dane chcesz wyswietlic: ";
            cin >> nazwisko_studenta;
            for (int i = 0; i < ilosc; i++) {
                if (imie_studenta == tab[i].imie && nazwisko_studenta == tab[i].nazwisko) {
                    cout << "\n\nZnaleziono studenta numer " << i + 1 << ", a imie i nazwisko to: " << tab[i].imie << " " << tab[i].nazwisko << endl;
                    for (int j = 0; j < rozmiar; j++) {
                        cout << "Ocena " << j + 1 << " szukanego studenta to: " << tab[i].oceny[j] << endl;
                    }
                    cout << "Srednia ocen szukanego studenta to: " << tab[i].srednia_ocen << endl;
                    znaleziono = 't';
                }
            }
            if (znaleziono == 'n') {
                cout << "Nie znaleziono studenta o podanym imieniu i nazwisku!" << endl;
            }
            break;
        default:
            cout << "\n\nPodany zostal bledny numer opcji!" << endl;
            break;
        }
        cout << "\nCzy chcesz ponowic wyszukiwanie? (T/N): ";
        cin >> jeszcze_raz;
    } while (jeszcze_raz == 't' || jeszcze_raz == 'T');
}