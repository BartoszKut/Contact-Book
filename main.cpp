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

void wyszukajKontaktPoImieniu(vector<Kontakt> kontakty, int idZalogowanegoUzytkownika);

void wyszukajKontaktPoNazwisku(vector<Kontakt> kontakty, int idZalogowanegoUzytkownika);

void wyswietlKontakty (vector<Kontakt> kontakty, int idZalogowanegoUzytkownika);

vector<Kontakt> wczytajDane(vector<Kontakt> kontakty, int idZalogowanegoUzytkownika);

bool czyTakiIdistnieje(vector<Kontakt> kontakty, int idDoUsuniecia, int idZalogowanegoUzytkownika);

vector<Kontakt> usunKontakt(vector<Kontakt> kontakty, int idDoUsuniecia, int idZalogowanegoUzytkownika);

vector<Kontakt> edytujKontakty(vector<Kontakt> kontakty, int idZalogowanegoUzytkownika);


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

            if (Plik.good()==false)
            {
                cout << "KSIAZKA ADRESOWA" << endl;
                cout << "----------------" << endl;
                cout << "Plik do odczytu nie istnieje. Utworz nowego uzytkownika."<<endl;
                system("pause");
            }
             else
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

            else
            {
                kontakty = wczytajDane(kontakty, idZalogowanegoUzytkownika);
            }

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
                    kontakty = dodawanieKontaktu(kontakty, idZalogowanegoUzytkownika);
                }
                if (wybor == '2')
                {
                    wyszukajKontaktPoImieniu(kontakty, idZalogowanegoUzytkownika);
                }
                if (wybor == '3')
                {
                    wyszukajKontaktPoNazwisku(kontakty, idZalogowanegoUzytkownika);
                }
                if (wybor == '4')
                {
                    wyswietlKontakty(kontakty, idZalogowanegoUzytkownika);
                }
                if (wybor == '5')
                {
                    cout << "Podaj nr id kontaktu do usuniecia: " << endl;
                    cin >> idDoUsuniecia;
                    kontakty = usunKontakt(kontakty, idDoUsuniecia, idZalogowanegoUzytkownika);
                }
                if (wybor == '6')
                {
                    kontakty = edytujKontakty(kontakty, idZalogowanegoUzytkownika);
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


void wyszukajKontaktPoImieniu(vector<Kontakt> kontakty, int idZalogowanegoUzytkownika)
{
    string imie;
    int numerKontaktu = kontakty.size();
    int pom = 1;

    system("cls");

    cout << "Podaj imie" << endl;
    cin >> imie;

    for (int i=0; i < numerKontaktu; i++)
    {
        if (kontakty[i].imie == imie && kontakty[i].iduzytkownika == idZalogowanegoUzytkownika)
        {
            cout << pom << ". ";
            cout << kontakty[i].imie;
            cout << " " << kontakty[i].nazwisko << endl;
            cout << kontakty[i].telefon << endl;
            cout << kontakty[i].email << endl;
            cout << kontakty[i].adres << endl;
            cout << kontakty[i].idKontaktu << endl;
            pom++;
        }
        //else if () cout << "Brak kontaktu o takim imieniu." << endl;

    }
    system("pause");
}


void wyszukajKontaktPoNazwisku(vector<Kontakt> kontakty, int idZalogowanegoUzytkownika)
{
    string nazwisko;
    int numerKontaktu = kontakty.size();
    int pom = 1;

    system("cls");

    cout << "Podaj nazwisko" << endl;
    cin >> nazwisko;

    for (int i=0; i < numerKontaktu; i++)
    {
        if (kontakty[i].nazwisko == nazwisko && kontakty[i].iduzytkownika == idZalogowanegoUzytkownika)
        {
            cout << pom << ". ";
            cout << kontakty[i].imie;
            cout << " " << kontakty[i].nazwisko << endl;
            cout << kontakty[i].telefon << endl;
            cout << kontakty[i].email << endl;
            cout << kontakty[i].adres << endl;
            cout << kontakty[i].idKontaktu << endl;
            pom++;
        }
        //else cout << "Brak kontaktu o takim nazwisku." << endl;
    }
    system("pause");
}


void wyswietlKontakty (vector<Kontakt> kontakty, int idZalogowanegoUzytkownika)
{
    system("cls");

    if (!kontakty.empty())
    {
        for (int i=0; i < kontakty.size(); i++)
        {
            if(kontakty[i].iduzytkownika == idZalogowanegoUzytkownika)
            {
                cout << "Kontakt " << i+1 << "." << endl;
                cout << kontakty[i].imie;
                cout << " " << kontakty[i].nazwisko << endl;
                cout << kontakty[i].telefon << endl;
                cout << kontakty[i].email << endl;
                cout << kontakty[i].adres << endl;
                cout << kontakty[i].idKontaktu << endl;
                cout << endl;
            }
        }
    }

    else
    {
        cout << "Brak kontaktow. Dodaj nowe kontakty" << endl;
    }
    system("pause");
}


vector<Kontakt> wczytajDane(vector<Kontakt> kontakty, int idZalogowanegoUzytkownika)
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

bool czyTakiIdistnieje(vector<Kontakt> kontakty, int idDoUsuniecia, int idZalogowanegoUzytkownika)
{
    for(int i = 0; i < kontakty.size(); i++)
    {
        if(kontakty[i].idKontaktu == idDoUsuniecia && kontakty[i].iduzytkownika == idZalogowanegoUzytkownika)
        {
            return true;
        }
    }
    return false;
}


vector<Kontakt> usunKontakt(vector<Kontakt> kontakty, int idDoUsuniecia, int idZalogowanegoUzytkownika)
{
    char choice;
    fstream plik;

    bool validId = czyTakiIdistnieje(kontakty, idDoUsuniecia, idZalogowanegoUzytkownika);

    system("cls");

    if(validId)
    {
        cout << "Czy na pewno chcesz usunac ten kontakt? Aby potwierdzic wybierz <t>" << endl;
        cin >> choice;
        if(choice == 't')
        {
            plik.open("pomocniczy.txt", ios::out);
            if(plik.good())
            {
                for(int i = 0; i < kontakty.size(); i++)
                {
                    if(idDoUsuniecia == kontakty[i].idKontaktu && kontakty[i].iduzytkownika == idZalogowanegoUzytkownika)
                    {
                        continue;
                    }
                    else
                    {
                        plik << kontakty[i].idKontaktu << "|";
                        plik << kontakty[i].iduzytkownika << "|";
                        plik << kontakty[i].imie << "|";
                        plik << kontakty[i].nazwisko << "|";
                        plik << kontakty[i].telefon << "|";
                        plik << kontakty[i].email << "|";
                        plik << kontakty[i].adres << "|" << endl;
                    }
                }

                plik.close();

                remove("ksiazka.txt");
                rename("pomocniczy.txt", "ksiazka.txt");

                int indexDoUsuniecia = 0;
                for(int i = 0; i < kontakty.size(); i++)
                {
                    if(kontakty[i].idKontaktu == idDoUsuniecia && kontakty[i].iduzytkownika == idZalogowanegoUzytkownika)
                    {
                        indexDoUsuniecia = i;
                    }
                }
                kontakty.erase(kontakty.begin() + indexDoUsuniecia);

                cout << "Kontakt usuniety!" << endl;
                Sleep(1000);
                return kontakty;
            }
            else
            {
                plik.close();
                cout << "Blad odczytu pliku!" << endl;
                Sleep(1000);
                return kontakty;
            }
        }
        else
        {
            cout << "Nie usunieto kontaktu!";
            Sleep(1000);
            return kontakty;
        }
    }
    else
    {
        cout << "Kontakt o podanym id nie istnieje!";
        Sleep(1000);
        return kontakty;
    }
}


vector<Kontakt> edytujKontakty(vector<Kontakt> kontakty, int idZalogowanegoUzytkownika)
{
    fstream plik;
    string Imie, Nazwisko, Telefon, Adres, Email;
    int numerKontaktu = kontakty.size();
    char wybor;
    int id;

    system("cls");

    cout << "Podaj id kontaktu" << endl;
    cin >> id;

    plik.open("ksiazka.txt", ios::out);
    if(plik.good())
    {
        for(int i = 0; i < numerKontaktu; i++)
        {
            if(kontakty[i].idKontaktu == id && kontakty[i].iduzytkownika == idZalogowanegoUzytkownika)
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
                    cout << "Aktualne imie to: " << kontakty[i].imie << endl;
                    cout << "Wprowadz nowe imie: ";
                    cin >> Imie;
                    kontakty[i].imie = Imie;
                    plik << kontakty[i].imie;
                    cout << "Zaktualizowano" << endl;
                    Sleep(1250);
                }

                if (wybor == '2')
                {
                    cout << "Aktualne nazwisko to: " << kontakty[i].nazwisko << endl;
                    cout << "Wprowadz nowe nazwisko: ";
                    cin >> Nazwisko;
                    kontakty[i].nazwisko = Nazwisko;
                    plik << kontakty[i].nazwisko;
                    cout << "Zaktualizowano" << endl;
                    Sleep(1250);
                }
                if (wybor == '3')
                {
                    cout << "Aktualny numer to: " << kontakty[i].telefon << endl;
                    cout << "Wprowadz nowy numer: ";
                    cin >> Telefon;
                    kontakty[i].telefon = Telefon;
                    plik << kontakty[i].telefon;
                    cout << "Zaktualizowano" << endl;
                    Sleep(1250);
                }
                if (wybor == '4')
                {
                    cout << "Aktualny email to: " << kontakty[i].email << endl;
                    cout << "Wprowadz nowy email: ";
                    cin >> Email;
                    kontakty[i].email = Email;
                    plik << kontakty[i].email;
                    cout << "Zaktualizowano" << endl;
                    Sleep(1250);
                }
                if (wybor == '5')
                {
                    cout << "Aktualny adres to: " << kontakty[i].adres << endl;
                    cout << "Wprowadz nowy adres: ";
                    cin >> Adres;
                    kontakty[i].adres = Adres;
                    plik << kontakty[i].adres;
                    cout << "Zaktualizowano" << endl;
                    Sleep(1250);
                }
                if (wybor == '6')
                {
                    break;
                }
            }
        }
    }
    plik.close();
    return kontakty;
}
