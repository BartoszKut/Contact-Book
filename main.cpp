#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;


struct Kontakt
{
    int idKontaktu, iduzytkownika;
    string imie, nazwisko, telefon, email, adres;
};

struct Uzytkownik
{
    int idUzytkownika;
    string nazwa, haslo;
};

vector<Uzytkownik> rejestracja(vector <Uzytkownik> uzytkownicy);

vector<Uzytkownik> wczytajUzytkownikow(vector<Uzytkownik> uzytkownicy);

int logowanie(vector <Uzytkownik> uzytkownicy);

vector<Kontakt> dodawanieKontaktu(vector<Kontakt> kontakty, int idZalogowanegoUzytkownika);

void wyszukajKontaktPoImieniu(vector<Kontakt> kontaktyKonkretnegoId);

void wyszukajKontaktPoNazwisku(vector<Kontakt> kontaktyKonkretnegoId);

void wyswietlKontakty (vector<Kontakt> kontaktyKonkretnegoId);

vector<Kontakt> wczytajDane(vector<Kontakt> kontakty);

bool czyTakiIdistnieje(vector<Kontakt> kontaktyKonkretnegoId, int idDoUsuniecia);

vector<Kontakt> usunKontakt(vector<Kontakt> kontaktyKonkretnegoId, int idDoUsuniecia);

vector<Kontakt> edytujKontakty(vector<Kontakt> kontaktyKonkretnegoId);

vector<Kontakt> wczytajkontaktyKonkretnegoId (vector<Kontakt> kontakty, int idZalogowanegoUzytkownika);

void aktualizacjaKsiazki(vector<Kontakt> kontaktyKonkretnegoId, int idZalogowanegoUzytkownika, vector<Kontakt> kontakty);


int main()
{
    vector <Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;

    char wybor;

    while (1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            fstream Plik;
            Plik.open("uzytkownicy.txt", ios::in);

            if (Plik.good() == false)
            {
                cout << "KSIAZKA ADRESOWA" << endl;
                cout << "----------------" << endl;
                cout << "Plik do odczytu nie istnieje. Utworz nowego uzytkownika."<<endl;
                system("pause");
            }

            {
                uzytkownicy = wczytajUzytkownikow(uzytkownicy);
            }

            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz porgram" << endl;
            cin >> wybor;

            if (wybor == '1')
            {
                uzytkownicy = rejestracja(uzytkownicy);
            }

            else if (wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            }

            else if (wybor == '9')
            {
                exit(0);
            }
        }

        else
        {
            vector<Kontakt> kontakty;
            vector<Kontakt> kontaktyKonkretnegoId;

            fstream plik;
            int idDoUsuniecia;

            plik.open("ksiazka.txt", ios::in);

            if (plik.good()==false)
            {
                system("cls");
                cout << "KSIAZKA ADRESOWA" << endl;
                cout << "----------------" << endl;
                cout << "Plik do odczytu nie istnieje. Utworz nowy kontakt."<<endl;
                system("pause");
            }
            plik.close();

            char wybor;
            while(1)
            {
                system("cls");
                cout << "KSIAZKA ADRESOWA" << endl;
                cout << "----------------" << endl;
                cout << "1. Dodaj kontakt" << endl;
                cout << "2. Wyszukaj kontakt po imieniu" << endl;
                cout << "3. Wyszukaj kontakt po nazwisku" << endl;
                cout << "4. Wyswietl kontakty" << endl;
                cout << "5. Usun kontakt" << endl;
                cout << "6. Edytuj kontakt" << endl;
                cout << "9. Wyloguj sie" << endl;
                cin >> wybor;

                if (wybor == '1')
                {
                    kontakty = wczytajDane(kontakty);
                    kontakty = dodawanieKontaktu(kontakty, idZalogowanegoUzytkownika);
                }
                if (wybor == '2')
                {
                    kontaktyKonkretnegoId = wczytajkontaktyKonkretnegoId(kontakty, idZalogowanegoUzytkownika);
                    wyszukajKontaktPoImieniu(kontaktyKonkretnegoId);
                }
                if (wybor == '3')
                {
                    kontaktyKonkretnegoId = wczytajkontaktyKonkretnegoId(kontakty, idZalogowanegoUzytkownika);
                    wyszukajKontaktPoNazwisku(kontaktyKonkretnegoId);
                }
                if (wybor == '4')
                {
                    kontaktyKonkretnegoId = wczytajkontaktyKonkretnegoId(kontakty, idZalogowanegoUzytkownika);
                    wyswietlKontakty(kontaktyKonkretnegoId);
                }
                if (wybor == '5')
                {
                    kontaktyKonkretnegoId = wczytajkontaktyKonkretnegoId(kontakty, idZalogowanegoUzytkownika);
                    cout << "Podaj nr id kontaktu do usuniecia: " << endl;
                    cin >> idDoUsuniecia;
                    if(!cin)
                    {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    kontaktyKonkretnegoId = usunKontakt(kontaktyKonkretnegoId, idDoUsuniecia);
                    aktualizacjaKsiazki(kontaktyKonkretnegoId, idZalogowanegoUzytkownika, kontakty);
                }
                if (wybor == '6')
                {
                    kontaktyKonkretnegoId = wczytajkontaktyKonkretnegoId(kontakty, idZalogowanegoUzytkownika);
                    kontaktyKonkretnegoId = edytujKontakty(kontaktyKonkretnegoId);
                    aktualizacjaKsiazki(kontaktyKonkretnegoId, idZalogowanegoUzytkownika, kontakty);
                }
                if (wybor == '9')
                {
                    idZalogowanegoUzytkownika = 0;
                    break;
                }
            }
        }
    }
    return 0;
}


vector<Uzytkownik> rejestracja(vector <Uzytkownik> uzytkownicy)
{
    fstream plik;
    string nazwa, haslo;
    Uzytkownik pojedynczyUzytkownik;

    int numerUzytkownika = uzytkownicy.size();
    int IdOstatniego;

    if(uzytkownicy.empty())
    {
        IdOstatniego = 0;
    }
    else
    {
        IdOstatniego = uzytkownicy[numerUzytkownika - 1].idUzytkownika;
    }

    system("cls");
    cout << "DODAWANIE UZYTKOWNIKA" << endl;
    cout << "------------------" << endl;
    cout << "Podaj nazwe uzytkownika: " << endl;
    cin >> nazwa;

    int i = 0;
    while(i<numerUzytkownika)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika.";
            cin >> nazwa;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: " << endl;
    cin >> haslo;

    pojedynczyUzytkownik = {IdOstatniego + 1, nazwa, haslo};

    uzytkownicy.push_back(pojedynczyUzytkownik);

    plik.open("uzytkownicy.txt", ios::out | ios::app);
    if(plik.good())
    {
        plik << uzytkownicy[numerUzytkownika].idUzytkownika << "|";
        plik << uzytkownicy[numerUzytkownika].nazwa << "|";
        plik << uzytkownicy[numerUzytkownika].haslo << "|"<<endl;

        cout << "Uzytkownik zostal dodany!" << endl;
        plik.close();
        Sleep(1000);
        return uzytkownicy;
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku" << endl;
        Sleep(1000);
        exit(0);
    }
}


vector<Uzytkownik> wczytajUzytkownikow(vector<Uzytkownik> uzytkownicy)
{
    string linia;
    fstream plik;
    Uzytkownik pojedynczyUzytkownik;

    plik.open("uzytkownicy.txt", ios::in);

    if(plik.is_open())
    {
        while(getline(plik, linia))
        {
            string uzytkownik[3];
            int koniecStringa = linia.length();
            int index = 0;
            int poczatekWyrazu = 0;
            int dlugoscWyrazu = 0;
            int indexUzytkownika = 0;

            for(index = 0; index < koniecStringa; index++)
            {
                if((int)linia[index] == 124)
                {
                    dlugoscWyrazu = index - poczatekWyrazu;
                    uzytkownik[indexUzytkownika] = linia.substr(poczatekWyrazu, dlugoscWyrazu);
                    poczatekWyrazu = index + 1;
                    indexUzytkownika++;
                }
            }
            pojedynczyUzytkownik.idUzytkownika = atoi(uzytkownik[0].c_str());
            pojedynczyUzytkownik.nazwa = uzytkownik[1];
            pojedynczyUzytkownik.haslo = uzytkownik[2];

            uzytkownicy.push_back(pojedynczyUzytkownik);
        }
        plik.close();

        return uzytkownicy;
    }
    else
    {
        plik.close();
        return uzytkownicy;
    }
}


int logowanie(vector <Uzytkownik> uzytkownicy)
{
    uzytkownicy = wczytajUzytkownikow(uzytkownicy);

    string nazwa, haslo;
    int iloscUzytkownikow = uzytkownicy.size();
    cout << "Podaj nazwe: " << endl;
    cin >> nazwa;

    int i = 0;
    while (i < iloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Podaj haslo: " << endl;
            cin >> haslo;

            if(uzytkownicy[i].haslo == haslo)
            {
                    cout << "Zalogowano." << endl;
                    Sleep(1500);
                    return uzytkownicy[i].idUzytkownika;
            }

            else
            {
                cout << "Niepoprawne haslo. Sprobuj jeszcze raz.";
                return 0;
            }

        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem." << endl;
    Sleep(3000);
    return 0;
}


vector<Kontakt> dodawanieKontaktu(vector<Kontakt> kontakty, int idZalogowanegoUzytkownika)
{
    int iduzytkownika = idZalogowanegoUzytkownika;
    fstream plik;
    string imie, nazwisko, telefon, adres, email;
    Kontakt pojedynczyKontakt;

    int numerKontaktu = kontakty.size();
    int IdOstatniego;
    if(kontakty.empty())
    {
        IdOstatniego = 0;
    }
    else
    {
        IdOstatniego = kontakty[numerKontaktu - 1].idKontaktu;
    }

    system("cls");
    cout << "DODAWANIE KONTAKTU" << endl;
    cout << "------------------" << endl;
    cout << "Podaj imie nowego kontaktu: " << endl;
    cin >> imie;
    cout << "Podaj nazwisko nowego kontaktu: " << endl;
    cin >> nazwisko;

    int i = 0;
    while(i < numerKontaktu)
    {
        if((kontakty[i].imie == imie) && (kontakty[i].nazwisko == nazwisko))
        {
            cout << "Ten kontakt jest juz zapisany" << endl;
            cout << "Podaj imie nowego kontaktu: " << endl;
            cin >> imie;
            cout << "Podaj nazwisko nowego kontaktu: " << endl;
            cin >> nazwisko;
            i = 0;
        }
        else
        {
            i++;
        }
    }

    cout << "Podaj numer telefonu: " << endl;
    cin.sync();
    getline(cin,telefon);

    cout << "Podaj adres mailowy: " << endl;
    cin.sync();
    getline(cin,email);

    cout << "Podaj adres korespondencyjny: " << endl;
    cin.sync();
    getline(cin,adres);

    pojedynczyKontakt = {IdOstatniego + 1, iduzytkownika, imie, nazwisko, telefon, email, adres};

    kontakty.push_back(pojedynczyKontakt);

    plik.open("ksiazka.txt", ios::out | ios::app);
    if(plik.good())
    {
        plik << kontakty[numerKontaktu].idKontaktu << "|";
        plik << kontakty[numerKontaktu].iduzytkownika << "|";
        plik << kontakty[numerKontaktu].imie << "|";
        plik << kontakty[numerKontaktu].nazwisko << "|";
        plik << kontakty[numerKontaktu].telefon << "|";
        plik << kontakty[numerKontaktu].email << "|";
        plik << kontakty[numerKontaktu].adres << "|" << endl;
        cout << "Kontakt zostal dodany!" << endl;
        plik.close();
        Sleep(1000);
        return kontakty;
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku" << endl;
        Sleep(1000);
        exit(0);
    }
}


void wyszukajKontaktPoImieniu(vector<Kontakt> kontaktyKonkretnegoId)
{
    string imie;
    int numerKontaktu = kontaktyKonkretnegoId.size();
    int pom = 1;

    system("cls");

    cout << "Podaj imie" << endl;
    cin >> imie;

    for (int i=0; i < numerKontaktu; i++)
    {
        if (kontaktyKonkretnegoId[i].imie == imie)
        {
            cout << pom << ". ";
            cout << kontaktyKonkretnegoId[i].imie;
            cout << " " << kontaktyKonkretnegoId[i].nazwisko << endl;
            cout << kontaktyKonkretnegoId[i].telefon << endl;
            cout << kontaktyKonkretnegoId[i].email << endl;
            cout << kontaktyKonkretnegoId[i].adres << endl;
            cout << kontaktyKonkretnegoId[i].idKontaktu << endl;
            pom++;
        }
        //else if () cout << "Brak kontaktu o takim imieniu." << endl;

    }
    system("pause");
}


void wyszukajKontaktPoNazwisku(vector<Kontakt> kontaktyKonkretnegoId)
{
    string nazwisko;
    int numerKontaktu = kontaktyKonkretnegoId.size();
    int pom = 1;

    system("cls");

    cout << "Podaj nazwisko" << endl;
    cin >> nazwisko;

    for (int i=0; i < numerKontaktu; i++)
    {
        if (kontaktyKonkretnegoId[i].nazwisko == nazwisko)
        {
            cout << pom << ". ";
            cout << kontaktyKonkretnegoId[i].imie;
            cout << " " << kontaktyKonkretnegoId[i].nazwisko << endl;
            cout << kontaktyKonkretnegoId[i].telefon << endl;
            cout << kontaktyKonkretnegoId[i].email << endl;
            cout << kontaktyKonkretnegoId[i].adres << endl;
            cout << kontaktyKonkretnegoId[i].idKontaktu << endl;
            pom++;
        }
        //else cout << "Brak kontaktu o takim nazwisku." << endl;
    }
    system("pause");
}


void wyswietlKontakty (vector<Kontakt> kontaktyKonkretnegoId)
{
    system("cls");

    if (!kontaktyKonkretnegoId.empty())
    {
        for (int i=0; i < kontaktyKonkretnegoId.size(); i++)
        {
            cout << "Kontakt " << i+1 << "." << endl;
            cout << kontaktyKonkretnegoId[i].imie;
            cout << " " << kontaktyKonkretnegoId[i].nazwisko << endl;
            cout << kontaktyKonkretnegoId[i].telefon << endl;
            cout << kontaktyKonkretnegoId[i].email << endl;
            cout << kontaktyKonkretnegoId[i].adres << endl;
            cout << kontaktyKonkretnegoId[i].idKontaktu << endl;
            cout << endl;
        }
    }

    else
    {
        cout << "Brak kontaktow. Dodaj nowe kontakty" << endl;
    }
    system("pause");
}


vector<Kontakt> wczytajDane(vector<Kontakt> kontakty)
{
    string linia;
    fstream plik;
    Kontakt pojedynczyKontakt;

    plik.open("ksiazka.txt", ios::in);

    if(plik.is_open())
    {
        while(getline(plik, linia))
        {
            string kontakt[7];
            int koniecStringa = linia.length();
            int index = 0;
            int poczatekWyrazu = 0;
            int dlugoscWyrazu = 0;
            int indexKontaktu = 0;

            for(index = 0; index < koniecStringa; index++)
            {
                if((int)linia[index] == 124)
                {
                    dlugoscWyrazu = index - poczatekWyrazu;
                    kontakt[indexKontaktu] = linia.substr(poczatekWyrazu, dlugoscWyrazu);
                    poczatekWyrazu = index + 1;
                    indexKontaktu++;
                }
            }
            pojedynczyKontakt.idKontaktu = atoi(kontakt[0].c_str());
            pojedynczyKontakt.iduzytkownika = atoi(kontakt[1].c_str());
            pojedynczyKontakt.imie = kontakt[2];
            pojedynczyKontakt.nazwisko = kontakt[3];
            pojedynczyKontakt.telefon = kontakt[4];
            pojedynczyKontakt.email = kontakt[5];
            pojedynczyKontakt.adres = kontakt[6];

            kontakty.push_back(pojedynczyKontakt);
        }
        plik.close();

        return kontakty;
    }
    else
    {
        plik.close();
        return kontakty;
    }
}

bool czyTakiIdistnieje(vector<Kontakt> kontaktyKonkretnegoId, int idDoUsuniecia)
{
    for(int i = 0; i < kontaktyKonkretnegoId.size(); i++)
    {
        if(kontaktyKonkretnegoId[i].idKontaktu == idDoUsuniecia)
        {
            return true;
        }
    }
    return false;
}


vector<Kontakt> usunKontakt(vector<Kontakt> kontaktyKonkretnegoId, int idDoUsuniecia)
{
    char choice;
    fstream plik;

    bool validId = czyTakiIdistnieje(kontaktyKonkretnegoId, idDoUsuniecia);

    system("cls");

    if(validId)
    {
        cout << "Czy na pewno chcesz usunac ten kontakt? Aby potwierdzic wybierz <t>" << endl;
        cin >> choice;
        if(choice == 't')
        {
            int indexDoUsuniecia = 0;
            for(int i = 0; i < kontaktyKonkretnegoId.size(); i++)
            {
                if(kontaktyKonkretnegoId[i].idKontaktu == idDoUsuniecia)
                {
                    indexDoUsuniecia = i;
                    continue;
                }
            }

            kontaktyKonkretnegoId.erase(kontaktyKonkretnegoId.begin() + indexDoUsuniecia);

            cout << "Kontakt usuniety!" << endl;
            Sleep(1000);
            return kontaktyKonkretnegoId;
        }

        else
        {
            cout << "Nie usunieto kontaktu!";
            Sleep(1000);
            return kontaktyKonkretnegoId;
        }
    }

    else if (!validId)
    {
        cout << "Kontakt o podanym id nie istnieje!";
        Sleep(1000);
        return kontaktyKonkretnegoId;
    }
}


vector<Kontakt> edytujKontakty(vector<Kontakt> kontaktyKonkretnegoId)
{
    string Imie, Nazwisko, Telefon, Adres, Email;
    int numerKontaktu = kontaktyKonkretnegoId.size();
    char wybor;
    int idEdytowanegoKontaktu;
    fstream plik;

    system("cls");

    cout << "Podaj id kontaktu" << endl;
    cin >> idEdytowanegoKontaktu;

    for(int i = 0; i < numerKontaktu; i++)
    {
        if(kontaktyKonkretnegoId[i].idKontaktu == idEdytowanegoKontaktu)
        {
            cout << "Co chcialbys zedytowac?" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Email" << endl;
            cout << "5. Adres" << endl;
            cout << "9. Powrot" << endl;
            cin >> wybor;

            if (wybor == '1')
            {
                cout << "Aktualne imie to: " << kontaktyKonkretnegoId[i].imie << endl;
                cout << "Wprowadz nowe imie: ";
                cin >> Imie;
                kontaktyKonkretnegoId[i].imie = Imie;
                cout << "Zaktualizowano" << endl;
                Sleep(1250);
            }

            if (wybor == '2')
            {
                cout << "Aktualne nazwisko to: " << kontaktyKonkretnegoId[i].nazwisko << endl;
                cout << "Wprowadz nowe nazwisko: ";
                cin >> Nazwisko;
                kontaktyKonkretnegoId[i].nazwisko = Nazwisko;
                cout << "Zaktualizowano" << endl;
                Sleep(1250);
            }
            if (wybor == '3')
            {
                cout << "Aktualny numer to: " << kontaktyKonkretnegoId[i].telefon << endl;
                cout << "Wprowadz nowy numer: ";
                cin >> Telefon;
                kontaktyKonkretnegoId[i].telefon = Telefon;
                cout << "Zaktualizowano" << endl;
                Sleep(1250);
            }
            if (wybor == '4')
            {
                cout << "Aktualny email to: " << kontaktyKonkretnegoId[i].email << endl;
                cout << "Wprowadz nowy email: ";
                cin >> Email;
                kontaktyKonkretnegoId[i].email = Email;
                cout << "Zaktualizowano" << endl;
                Sleep(1250);
            }
            if (wybor == '5')
            {
                cout << "Aktualny adres to: " << kontaktyKonkretnegoId[i].adres << endl;
                cout << "Wprowadz nowy adres: ";
                cin >> Adres;
                kontaktyKonkretnegoId[i].adres = Adres;
                cout << "Zaktualizowano" << endl;
                Sleep(1250);
            }
            if (wybor == '6')
            {
                break;
            }
        }
    }

    return kontaktyKonkretnegoId;
}


vector<Kontakt> wczytajkontaktyKonkretnegoId (vector<Kontakt> kontakty, int idZalogowanegoUzytkownika)
{
    vector<Kontakt> kontaktyKonkretnegoId;
    string linia;
    fstream plik;
    Kontakt pojedynczyKontakt;

    plik.open("ksiazka.txt", ios::in);

    if(plik.is_open())
    {
        while(getline(plik, linia))
        {
            string kontakt[7];
            int koniecStringa = linia.length();
            int index = 0;
            int poczatekWyrazu = 0;
            int dlugoscWyrazu = 0;
            int indexKontaktu = 0;

            for(index = 0; index < koniecStringa; index++)
            {
                if((int)linia[index] == 124)
                {
                    dlugoscWyrazu = index - poczatekWyrazu;
                    kontakt[indexKontaktu] = linia.substr(poczatekWyrazu, dlugoscWyrazu);
                    poczatekWyrazu = index + 1;
                    indexKontaktu++;
                }
            }
            pojedynczyKontakt.idKontaktu = atoi(kontakt[0].c_str());
            pojedynczyKontakt.iduzytkownika = atoi(kontakt[1].c_str());
            pojedynczyKontakt.imie = kontakt[2];
            pojedynczyKontakt.nazwisko = kontakt[3];
            pojedynczyKontakt.telefon = kontakt[4];
            pojedynczyKontakt.email = kontakt[5];
            pojedynczyKontakt.adres = kontakt[6];

            if(pojedynczyKontakt.iduzytkownika == idZalogowanegoUzytkownika)
            {
               kontaktyKonkretnegoId.push_back(pojedynczyKontakt);
            }
        }
        plik.close();

        return kontaktyKonkretnegoId;
    }
    else
    {
        plik.close();
        return kontaktyKonkretnegoId;
    }
}

void aktualizacjaKsiazki(vector<Kontakt> kontaktyKonkretnegoId, int idZalogowanegoUzytkownika, vector<Kontakt> kontakty)
{
    fstream plik;
    vector<Kontakt> pomocniczy;

    system("pause");

    for (int i = 0; i < kontakty.size(); i++)
    {
        if(kontakty[i].iduzytkownika == idZalogowanegoUzytkownika)
        {
            continue;
        }
        else
            pomocniczy.push_back(kontakty[i]);
    }

    for (int j = 0; j < kontaktyKonkretnegoId.size(); j++)
    {
        pomocniczy.push_back(kontaktyKonkretnegoId[j]);
    }

    plik.open("ksiazka_tymczasowa.txt", ios::out | ios::app);
    if(plik.good())
    {
        for (int i = 0; i < pomocniczy.size(); i++)
        {
            plik << pomocniczy[i].idKontaktu << "|";
            plik << pomocniczy[i].iduzytkownika << "|";
            plik << pomocniczy[i].imie << "|";
            plik << pomocniczy[i].nazwisko << "|";
            plik << pomocniczy[i].telefon << "|";
            plik << pomocniczy[i].email << "|";
            plik << pomocniczy[i].adres << "|" << endl;
        }
        plik.close();
        remove("ksiazka.txt");
        rename("ksiazka_tymczasowa.txt", "ksiazka.txt");
    }
}
