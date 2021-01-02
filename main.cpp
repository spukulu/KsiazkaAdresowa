#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

struct Kontakt {
    int id;
    string imie, nazwisko, adres, telefon, mail;
};

int LiczKontakty(vector <Kontakt> znajomi) {
    vector<Kontakt>::iterator itr=znajomi.begin();
    int LiczbaKontaktow=0;
    for(itr; itr!=znajomi.end(); ++itr) {
        LiczbaKontaktow++;
    }
    return LiczbaKontaktow;
}

char wczytajZnak() {
    string wejscie = "";
    char znak  = {0};

    while (true) {
        getline(cin, wejscie);

        if (wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}

char wczytajZnakTakLubNie() {
    string wejscie = "";
    char znak  = {0};

    while (true) {
        getline(cin, wejscie);

        if (wejscie == "t" || wejscie == "n") {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest poprawny znak. Wpisz ponownie." << endl;
    }
    return znak;
}

string wczytajLinie() {
    string wejscie = "";
    getline(cin, wejscie);
    return wejscie;
}

vector<Kontakt> dodajKontakt(vector<Kontakt> znajomi, int liczbaKontaktow) {
    system("cls");
    Kontakt Adresat;
    Kontakt OstatniAdresat=znajomi.at(liczbaKontaktow-1);
    string imie, nazwisko, adres, telefon, mail;

    cout<<"Podaj imie: ";
    imie=wczytajLinie();
    cout<<"Podaj nazwisko: ";
    nazwisko=wczytajLinie();
    cout<<"Podaj adres e-mail: ";
    mail=wczytajLinie();
    cout<<"Podaj numer telefonu: ";
    telefon=wczytajLinie();
    cout<<"Podaj adres zamieszkania: ";
    adres=wczytajLinie();

    Adresat.imie=imie;
    Adresat.nazwisko=nazwisko;
    Adresat.adres=adres;
    Adresat.mail=mail;
    Adresat.telefon=telefon;
    Adresat.id=OstatniAdresat.id+1;
    znajomi.push_back(Adresat);

    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("ksiazkaAdresowa.txt",ios::out | ios::app);

    if (ksiazkaAdresowa.good() == true) {
        ksiazkaAdresowa<<endl<<Adresat.id<<"|";
        ksiazkaAdresowa<<Adresat.imie<<"|";
        ksiazkaAdresowa<<Adresat.nazwisko<<"|";
        ksiazkaAdresowa<<Adresat.telefon<<"|";
        ksiazkaAdresowa<<Adresat.mail<<"|";
        ksiazkaAdresowa<<Adresat.adres<<"|";
        ksiazkaAdresowa.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
    cout << endl << "Osoba zostala dodana" << endl;
    system("pause");

    return znajomi;
}

void wyswietlKontakty(vector<Kontakt> znajomi) {

    system("cls");
    vector<Kontakt>::iterator itr=znajomi.begin();
    for(itr; itr!=znajomi.end(); ++itr) {
        Kontakt *Adresat=new Kontakt;
        *Adresat=*itr;
        cout<<Adresat->id<<"|";
        cout<<Adresat->imie<<"|";
        cout<<Adresat->nazwisko<<"|";
        cout<<Adresat->telefon<<"|";
        cout<<Adresat->mail<<"|";
        cout<<Adresat->adres<<"|"<<endl;
        delete Adresat;
    }
    system("pause");
}

void wyszukajPoImieniu(vector<Kontakt> znajomi) {

    string imie;

    system("cls");

    int licznikWyswietlen=0;

    cout<<"Podaj imie: ";
    imie=wczytajLinie();
    cout<<endl<<endl;

    vector<Kontakt>::iterator itr=znajomi.begin();
    for(itr; itr!=znajomi.end(); ++itr) {
        Kontakt *Adresat=new Kontakt;
        *Adresat=*itr;

        if(Adresat->imie==imie) {
            cout<<Adresat->imie;
            cout<<"|"<<Adresat->nazwisko;
            cout<<"|"<<Adresat->telefon;
            cout<<"|"<<Adresat->mail;
            cout<<"|"<<Adresat->adres<<endl;

            licznikWyswietlen++;
        }
        delete Adresat;
    }
    if(licznikWyswietlen==0) {
        cout<<"Brak kontaktow z podanym imieniem"<<endl<<endl;
        cout<<"Nacisnij dowolny klawisz by powrocic do menu glownego"<<endl;
    }
    system("pause");
}

void wyszukajPoNazwisku(vector<Kontakt> znajomi) {

    string nazwisko;

    system("cls");

    int licznikWyswietlen=0;

    cout<<"Podaj nazwisko: ";
    nazwisko=wczytajLinie();
    cout<<endl<<endl;

    vector<Kontakt>::iterator itr=znajomi.begin();
    for(itr; itr!=znajomi.end(); ++itr) {
        Kontakt *Adresat=new Kontakt;
        *Adresat=*itr;

        if(Adresat->nazwisko==nazwisko) {
            cout<<Adresat->imie;
            cout<<"|"<<Adresat->nazwisko;
            cout<<"|"<<Adresat->telefon;
            cout<<"|"<<Adresat->mail;
            cout<<"|"<<Adresat->adres<<endl;

            licznikWyswietlen++;
        }
        delete Adresat;
    }
    if(licznikWyswietlen==0) {
        cout<<"Brak kontaktow z podanym nazwiskiem"<<endl<<endl;
        cout<<"Nacisnij dowolny klawisz by powrocic do menu glownego"<<endl;
    }
    system("pause");
}

vector <Kontakt> wczytajKontakty(vector <Kontakt> znajomi) {

    string wers;
    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("ksiazkaAdresowa.txt", ios::in);
    if(ksiazkaAdresowa.good()==false) return znajomi;
    else {
        string separator="|";
        int pozycja;
        while(!ksiazkaAdresowa.eof()) {
            getline(ksiazkaAdresowa,wers);
            pozycja=wers.find(separator);
            Kontakt *Adresat=new Kontakt;

            string napisID;
            for(int i=0; i<pozycja; i++) {
                napisID+=wers[i];
            }
            Adresat->id=atoi(napisID.c_str());
            wers.erase(0,pozycja+1);

            pozycja=wers.find(separator);
            for(int i=0; i<pozycja; i++) {
                Adresat->imie+=wers[i];
            }
            wers.erase(0,pozycja+1);

            pozycja=wers.find(separator);
            for(int i=0; i<pozycja; i++) {
                Adresat->nazwisko+=wers[i];
            }
            wers.erase(0,pozycja+1);

            pozycja=wers.find(separator);
            for(int i=0; i<pozycja; i++) {
                Adresat->telefon+=wers[i];
            }
            wers.erase(0,pozycja+1);

            pozycja=wers.find(separator);
            for(int i=0; i<pozycja; i++) {
                Adresat->mail+=wers[i];
            }
            wers.erase(0,pozycja+1);

            pozycja=wers.find(separator);
            for(int i=0; i<pozycja; i++) {
                Adresat->adres+=wers[i];
            }
            wers.erase(0,pozycja+1);

            znajomi.push_back(*Adresat);
            delete Adresat;
        }
    }
    ksiazkaAdresowa.close();
    return znajomi;
}

vector<Kontakt> edytujKontakt(vector <Kontakt> znajomi) {
    char wybor;
    int id;
    system("cls");
    cin.sync();

    cout<<"Podaj ID kontaktu, ktory chcesz edytowac: ";
    cin>>id;
    cin.sync();
    vector<Kontakt>::iterator itr=znajomi.begin();
    Kontakt *Adresat=new Kontakt, AdresatPoEdycji;
    string imie, nazwisko, telefon, mail, adres;
    for(itr; itr!=znajomi.end(); ++itr) {

        *Adresat=*itr;

        if(Adresat->id==id) {
            system("cls");
            cout<<"Wybierz pozycje do edycji"<<endl;
            cout<<"1. imie"<<endl;
            cout<<"2. nazwisko"<<endl;
            cout<<"3. numer telefonu"<<endl;
            cout<<"4. email"<<endl;
            cout<<"5. adres"<<endl;
            cout<<"6. powrot do menu"<<endl;
            cout<<endl<<"Twoj wybor: ";
            wybor=wczytajZnak();

            switch(wybor) {
            case '1': {
                cout<<"Podaj nowe imie: ";
                imie=wczytajLinie();
                AdresatPoEdycji.imie=imie;
                AdresatPoEdycji.nazwisko=Adresat->nazwisko;
                AdresatPoEdycji.adres=Adresat->adres;
                AdresatPoEdycji.mail=Adresat->mail;
                AdresatPoEdycji.telefon=Adresat->telefon;
                AdresatPoEdycji.id=Adresat->id;

                itr=znajomi.insert(itr, AdresatPoEdycji);
                znajomi.erase( itr+1);
                return znajomi;

                break;
            }
            case '2': {
                cout<<"Podaj nowe nazwisko: ";
                nazwisko=wczytajLinie();
                AdresatPoEdycji.imie=Adresat->imie;
                AdresatPoEdycji.nazwisko=nazwisko;
                AdresatPoEdycji.adres=Adresat->adres;
                AdresatPoEdycji.mail=Adresat->mail;
                AdresatPoEdycji.telefon=Adresat->telefon;
                AdresatPoEdycji.id=Adresat->id;

                itr=znajomi.insert(itr, AdresatPoEdycji);
                znajomi.erase( itr+1);
                return znajomi;

                break;
            }
            case '3': {
                cout<<"Podaj nowy numer telefonu: ";
                telefon=wczytajLinie();
                AdresatPoEdycji.imie=Adresat->imie;
                AdresatPoEdycji.nazwisko=Adresat->nazwisko;
                AdresatPoEdycji.adres=Adresat->adres;
                AdresatPoEdycji.mail=Adresat->mail;
                AdresatPoEdycji.telefon=telefon;
                AdresatPoEdycji.id=Adresat->id;

                itr=znajomi.insert(itr, AdresatPoEdycji);
                znajomi.erase( itr+1);
                return znajomi;
                break;
            }
            case '4': {
                cout<<"Podaj nowy e-mail: ";
                mail=wczytajLinie();
                AdresatPoEdycji.imie=Adresat->imie;
                AdresatPoEdycji.nazwisko=Adresat->nazwisko;
                AdresatPoEdycji.adres=Adresat->adres;
                AdresatPoEdycji.mail=mail;
                AdresatPoEdycji.telefon=Adresat->telefon;
                AdresatPoEdycji.id=Adresat->id;

                itr=znajomi.insert(itr, AdresatPoEdycji);
                znajomi.erase( itr+1);
                return znajomi;
                break;
            }
            case '5': {
                cout<<"Podaj nowy adres: ";
                adres=wczytajLinie();
                AdresatPoEdycji.imie=Adresat->imie;
                AdresatPoEdycji.nazwisko=Adresat->nazwisko;
                AdresatPoEdycji.adres=adres;
                AdresatPoEdycji.mail=Adresat->mail;
                AdresatPoEdycji.telefon=Adresat->telefon;
                AdresatPoEdycji.id=Adresat->id;

                itr=znajomi.insert(itr, AdresatPoEdycji);
                znajomi.erase( itr+1);
                return znajomi;
                break;
            }
            case '6': {
                return znajomi;
                break;
            }
            }
        }
    }
    delete Adresat;
}

vector<Kontakt> usunKontakt(vector <Kontakt> znajomi) {
    char wybor;
    int id;
    system("cls");
    cin.sync();

    cout<<"Podaj ID kontaktu, ktory chcesz usunac: ";
    cin>>id;
    cout<<endl<<endl<<"Czy na pewno chcesz usunac ten kontakt?"<<endl<<"Jezeli tak, wybierz 't'. Jezeli nie, wybiez 'n'";
    cout<<endl<<"Twoj wybor: ";
    cin.sync();
    wybor=wczytajZnakTakLubNie();
    if(wybor=='t') {
        vector<Kontakt>::iterator itr=znajomi.begin();
        Kontakt *Adresat=new Kontakt;
        for(itr; itr!=znajomi.end(); ++itr) {

            *Adresat=*itr;

            if(Adresat->id==id) {
                cin.sync();
                znajomi.erase(itr);
            cout<<endl<<endl<<"Kontakt usuniety"<<endl;
                system("pause");
                return znajomi;
            }
        }
        delete Adresat;
    } else return znajomi;
}

void nadpiszEdytowanyPlikTesktowy(vector<Kontakt>znajomi) {
    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("ksiazkaAdresowa.txt",ios::trunc | ios::out);

    vector<Kontakt>::iterator itr=znajomi.begin();
    for(itr; itr!=znajomi.end(); ++itr) {
        Kontakt *Adresat=new Kontakt;
        *Adresat=*itr;

        if (ksiazkaAdresowa.good() == true) {
            ksiazkaAdresowa<<Adresat->id<<"|";
            ksiazkaAdresowa<<Adresat->imie<<"|";
            ksiazkaAdresowa<<Adresat->nazwisko<<"|";
            ksiazkaAdresowa<<Adresat->telefon<<"|";
            ksiazkaAdresowa<<Adresat->mail<<"|";
            ksiazkaAdresowa<<Adresat->adres<<"|";
            if(itr!=(znajomi.end()-1)) ksiazkaAdresowa<<endl;
        }
        delete Adresat;
    }
    ksiazkaAdresowa.close();
}

int main() {

    vector <Kontakt> znajomi;

    char wybor;
    znajomi=wczytajKontakty(znajomi);

    int liczbaKontaktow;

    while(true) {
        system("cls");
        cin.sync();

        cout<<"KSIAZKA ADRESOWA"<<endl;
        cout<<"1. Dodaj adresata"<<endl;
        cout<<"2. Wyszukaj po imieniu"<<endl;
        cout<<"3. Wyszukaj po nazwisku"<<endl;
        cout<<"4. Wyswietl wszystkich adresatow"<<endl;
        cout<<"5. Usun adresata"<<endl;
        cout<<"6. Edytuj adresata"<<endl;
        cout<<"9. Zakoncz program"<<endl;
        cout<<"Twoj wybor: ";
        wybor=wczytajZnak();


        switch(wybor) {
        case '1': {
            liczbaKontaktow=LiczKontakty(znajomi);
            znajomi=dodajKontakt(znajomi, liczbaKontaktow);
            break;
        }
        case '2': {

            wyszukajPoImieniu(znajomi);
            break;
        }
        case '3': {

            wyszukajPoNazwisku(znajomi);
            break;
        }
        case '4': {
            wyswietlKontakty(znajomi);
            break;
        }
        case '5': {
            znajomi=usunKontakt(znajomi);
            nadpiszEdytowanyPlikTesktowy(znajomi);
            break;
        }
        case '6': {
            znajomi=edytujKontakt(znajomi);
            nadpiszEdytowanyPlikTesktowy(znajomi);
            break;
        }

        case '9': {
            exit(0);
            break;
        }
        }
    }
}


