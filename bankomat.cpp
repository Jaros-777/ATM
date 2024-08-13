#include <iostream>
#include <windows.h>
#include <time.h>
#include <fstream>
using namespace std;

class Bankomat
{
public:
    void Menu()
    {
        int wybor;

        cout << endl
             << "Obecna waluta: " << waluta << endl;
        cout << endl
             << "Wybierz opcje" << endl;
        cout << "1. Zobacz saldo" << endl;
        cout << "2. Wyplac pieniadze" << endl;
        cout << "3. Wplac pieniadze" << endl;
        cout << "4. Zmien debet" << endl;
        cout << "5. Zmien walute" << endl;
        cout << "6. Zobacz konto" << endl;
        cout << "7. Zakoncz" << endl;

        cin >> wybor;
        switch (wybor)
        {
        case 1:
            SprawdzSaldo();
            break;
        case 2:
            Wyplac();
            break;
        case 3:
            Wplac();
            break;
        case 4:
            ZmienDebet();
            break;
        case 5:
            UstawWalute();
            cout << "Pomyslnie zmieniono walute na: " << waluta << endl;
            Menu();
            break;
        case 6:
            PokazKonto();
            break;

        case 7:
            cout << "Dziekujemy za skorzystanie z naszych uslug" << endl;
            KoniecProgramu();
            break;

        default:
            cout << "Nie ma takiej opcji" << endl;
            ZmienSekcje();
            break;
        }
    };
    void ZmienSekcje()
    {
        int pomylka = 2;
        int wybor = 0;
        cout << "Jesli chcesz przejsc do innej sekcji wpisz 1, jesli chcesz wyjsc nacisnij 0" << endl;

        for (int i = 0; i < 3; i++)
        {

            cin >> wybor;
            if (wybor == 1)
            {
                Menu();
                break;
            }
            else if (wybor == 0)
            {
                cout << "Dziekujemy za skorzystanie z naszych uslug" << endl;
                KoniecProgramu();
                break;
            }
            else
            {
                if (pomylka > 0)
                {
                    pomylka--;
                    cout << "Nie ma takiej opcji, zostalo " << pomylka + 1 << " prob." << endl;
                }
                else
                    cout << "Zostal osiagniety limit pomylek" << endl;
                    KoniecProgramu();
            }
        }
    }

    void Start()
    {
        cout << "---- Prosze wsunac karte ----" << endl;
        cout << "\"Wkladanie karty\"" << endl;
        Sleep(3000);
        cout << "---- Prosze czekac trwa przetwarzanie ----" << endl;
        Sleep(5000);

        Logowanie();
    };
    void Logowanie()
    {
        string name, surname;
        int money, debet;
        bool poprawny = false;
        string wiersz;
        string pin;

        // sprawdzanie PINU

        ifstream odczyt("konta.txt");

        if (odczyt.good() == true)
        {
            cout << "--- Wpisz PIN ---" << endl;
            cin >> pin;
            pin = 'P' + pin;
            while (!odczyt.eof())
            {
                getline(odczyt, wiersz);
                if (wiersz == pin)
                {
                    poprawny = true;
                    
                    for (int i = 0; i < 4; i++)
                    {
                        getline(odczyt, wiersz);
                        if (i == 0)
                        {
                            this->imie = wiersz;
                            wiersz = "";
                        }
                        if (i == 1)
                        {
                            this->nazwisko = wiersz;
                            wiersz = "";
                        }
                        if (i == 2)
                        {
                            this->saldo = stoi(wiersz);
                            wiersz = "";
                        }
                        if (i == 3)
                        {
                            this->maxDebet = stoi(wiersz);
                            wiersz = "";
                        }
                    }
                    break;
                }
            }

            if (poprawny == false)
            {
                cout << "Nie znaleziono konta o takim PIN-ie" << endl;
            }
            else
            {
                cout << endl
                     << "--- Witaj Uzytkowniku ---" << endl;
                odczyt.close();
                Menu();
            }
        }
        else
            cout << endl
                 << "--- Przepraszamy awaria bankomatu ---" << endl;
        odczyt.close();
    };
    void UstawWalute()
    {
        int wybor;
        cout << "Wybierz walute:" << endl;
        cout << "1. Zlotowki" << endl;
        cout << "2. Euro" << endl;
        cout << "3. Dolary Amerykanskie" << endl;
        cin >> wybor;

        switch (wybor)
        {
        case 1: // PLN

            if (waluta == "PLN")
            {
                this->saldo = saldo / 1;
                this->maxDebet = maxDebet / 1;
            }
            if (waluta == "EUR")
            {
                this->waluta = "EUR";
                this->saldo = saldo * 4.2945;
                this->maxDebet = maxDebet * 4.2945;
            }
            if (waluta == "USD")
            {
                this->waluta = "USD";
                this->saldo = saldo * 3.9314;
                this->maxDebet = maxDebet * 3.9314;
            }
            this->waluta = "PLN";
            break;

        case 2: // EUR

            if (waluta == "PLN")
            {
                this->saldo = saldo * 0.2329;
                this->maxDebet = maxDebet * 0.2329;
            }
            if (waluta == "EUR")
            {
                this->waluta = "EUR";
                this->saldo = saldo / 1;
                this->maxDebet = maxDebet / 1;
            }
            if (waluta == "USD")
            {
                this->waluta = "USD";
                this->saldo = saldo * 0.9154;
                this->maxDebet = maxDebet * 0.9154;
            }
            this->waluta = "EUR";
            break;

        case 3: // USD

            if (waluta == "PLN")
            {
                this->saldo = saldo * 0.2544;
                this->maxDebet = maxDebet * 0.2544;
            }
            if (waluta == "EUR")
            {
                this->waluta = "EUR";
                this->saldo = saldo * 1.0924;
                this->maxDebet = maxDebet * 1.0924;
            }
            if (waluta == "USD")
            {
                this->waluta = "USD";
                this->saldo = saldo / 1;
                this->maxDebet = maxDebet / 1;
            }
            this->waluta = "USD";
            break;

        default:
            cout << "Wybrano nie poprawna opcje." << endl;
            ZmienSekcje();
            break;
        }
    }
    void Wplac()
    {
        int wplata;
        int piecset = 0, dwiescie = 0, sto = 0, piecdziesiat = 0, dwadziescia = 0, dziesiec = 0;
        int kwotaWplacona = 0;

        UstawWalute();
        cout << "--- Wplacanie Gotowki ---" << endl;
        cout << "Bankomat przyjmuje banknoty o nominalach 10, 20, 50, 100, 200 " << waluta << endl;
        cout << "Wpisz kwote do wplaty [" << waluta << "]" << endl;
        cin >> wplata;

        if (wplata % 10 != 0)
        {
            cout << "Podana kwota jest nie prawidlowa. Bankomat przyjmuje banknoty o najmniejszszym nominale rownym 10 " << waluta << "." << endl;
            cout << "Podaj kwote do wyplaty [" << waluta << "]" << endl;
            cin >> wplata;
        }

        if (wplata % 10 != 0)
        {
            cout << "Podana kwota jest nie prawidlowa." << endl;
            Menu();
        }

        cout << "Podaj ilosc poszczegolnych banknotow" << endl;
        cout << "Banknoty 200 " << waluta << endl;
        cin >> dwiescie;
        cout << "Banknoty 100 " << waluta << endl;
        cin >> sto;
        cout << "Banknoty 50 " << waluta << endl;
        cin >> piecdziesiat;
        cout << "Banknoty 20 " << waluta << endl;
        cin >> dwadziescia;
        cout << "Banknoty 10 " << waluta << endl;
        cin >> dziesiec;

        cout << "Prosze wlozyc banknoty od najwiekszego nominalem do najmniejszego" << endl;
        Sleep(800);
        cout << "Wlozono " << dwiescie << " banknotow o nominale 200 " << waluta << endl;
        Sleep(800);
        cout << "Wlozono " << sto << " banknotow o nominale 100 " << waluta << endl;
        Sleep(800);
        cout << "Wlozono " << piecdziesiat << " banknotow o nominale 50 " << waluta << endl;
        Sleep(800);
        cout << "Wlozono " << dwadziescia << " banknotow o nominale 20 " << waluta << endl;
        Sleep(800);
        cout << "Wlozono " << dziesiec << " banknotow o nominale 10 " << waluta << endl;
        Sleep(800);

        kwotaWplacona = piecset * 500 + dwiescie * 200 + sto * 100 + piecdziesiat * 50 + dwadziescia * 20 + dziesiec * 10;

        if (wplata != kwotaWplacona)
        {
            cout << "Podano zla kwote wplacenia. Bankomat przyjal " << kwotaWplacona << " " << waluta << endl;
        }

        cout << "Saldo przed wplata: " << saldo << " " << waluta << endl;
        saldo += kwotaWplacona;
        cout << "Saldo po wplacie: " << saldo << " " << waluta << endl;

        ZmienSekcje();
    };
    void Wyplac()
    {
        int wyplata;
        cout << "--- Wyplacanie Gotowki ---" << endl;
        UstawWalute();
        cout << "Obecne saldo: " << saldo << " " << waluta << endl;
        double stareSaldo = saldo;
        cout << "Podaj kwote do wyplaty [" << waluta << "]" << endl;
        cin >> wyplata;

        if (wyplata % 10 != 0)
        {
            cout << "Podana kwota jest nie prawidlowa. Bankomat wydaje banknoty o najmniejszszym nominale rownym 10 " << waluta << "." << endl;
            cout << "Podaj kwote do wyplaty [" << waluta << "]" << endl;
            cin >> wyplata;
        }

        if (wyplata % 10 != 0)
        {
            cout << "Podana kwota jest nie prawidlowa." << endl;
            Menu();
        }

        if (wyplata > saldo)
        {
            if (wyplata <= (saldo + maxDebet))
            {
                int wybor = 1;
                cout << "Masz niewystarczajaco ilosc pieniedzy na koncie" << endl;
                cout << "Chcesz wyplacic pieniadze i miec debet?" << endl;
                cout << "Jesli tak, wpisz 1 jesli nie, wpisz 0" << endl;

                while (wybor != 0)
                {
                    cin >> wybor;

                    if (wybor == 1)
                    {
                        cout << "Wyplacono " << wyplata << " " << waluta << endl;
                        saldo -= wyplata;
                        cout << "Twoje saldo to " << saldo << " " << waluta << endl;
                        cout << "Pamietaj ze odsetki za debet rosna z kazdym dniem. W razie jakichkolwiek informacji w tym zakresie skonsultuj sie ze swoim bankiem" << endl;
                        ZmienSekcje();
                        break;
                    }
                    else if (wybor == 0)
                    {
                        ZmienSekcje();
                        break;
                    }
                    else
                    {
                        cout << "Podano zla opcje. Wpisz opcje jeszcze raz" << endl;
                    }
                };
            }
            else
            {

                cout << "Masz niewystarczajaco ilosc pieniedzy na koncie" << endl;
                cout << "Jesli pomimo tego chcesz wyplacic taka kwote. Zmien limit debetu w sekcji \"Moje Konto\"" << endl;
                ZmienSekcje();
            }
        }
        else
        {

            // zrob dla roznych walut
            saldo -= wyplata;

            if (wyplata >= 200)
            {
                cout << "Bankomat wyplaci " << wyplata / 200 << " banknotow o nominale 200 " << waluta << endl;
                wyplata -= (wyplata / 200) * 200;
            }
            if (wyplata >= 100)
            {
                cout << "Bankomat wyplaci " << wyplata / 100 << " banknotow o nominale 100 " << waluta << endl;
                wyplata -= (wyplata / 100) * 100;
            }
            if (wyplata >= 50)
            {
                cout << "Bankomat wyplaci " << wyplata / 50 << " banknotow o nominale 50 " << waluta << endl;
                wyplata -= (wyplata / 50) * 50;
            }
            if (wyplata >= 20)
            {
                cout << "Bankomat wyplaci " << wyplata / 20 << " banknotow o nominale 20 " << waluta << endl;
                wyplata -= (wyplata / 20) * 20;
            }
            if (wyplata >= 10)
            {
                cout << "Bankomat wyplaci " << wyplata / 10 << " banknotow o nominale 10zł" << endl;
                wyplata -= (wyplata / 20) * 20;
            }
            Sleep(1000);
            cout << "---- Prosze czekac bankomat przygotowywuje pieniadze ----" << endl;
            cout << "\"Wyplacenie gotowki\"" << endl;

            cout << "Saldo przed wyplata: " << stareSaldo << " " << waluta << endl;

            cout << "Saldo po wyplacie: " << saldo << " " << waluta << endl;

            ZmienSekcje();
        }
    };
    void SprawdzSaldo()
    {
        cout << "Twoje saldo to: " << saldo << " " << waluta << endl;
        ZmienSekcje();
    };
    void ZmienDebet()
    {
        double Nowydebet;
        string PIN;

        cout << "--- Zmiana Debetu ---" << endl;
        cout << "Aktualny maksymalny debet: " << maxDebet << " " << waluta << endl;

        cout << "Wprowadz maksymalny limit debetu [" << waluta << "]" << endl;
        cin >> Nowydebet;
        maxDebet = Nowydebet;
        cout << "Pomyslnie ustawiono nowy debet na kwote " << Nowydebet << " " << waluta << endl;

        ZmienSekcje();
    }
    void PokazKonto()
    {
        cout << "------- Twoje konto -------" << endl;
        cout << "Imie: " + imie << endl;
        cout << "Nazwisko: " + nazwisko << endl;
        cout << "Saldo: " << saldo << " " << waluta << endl;
        cout << "Mozliwy debet: " << maxDebet << " " << waluta << endl;
        cout << "---------------------------" << endl;
        ZmienSekcje();
    };
    void KoniecProgramu()
    {
        cout << "\"Wysuwanie karty\"" << endl;
        Sleep(3000);
        cout << "---- Prosze odebrac karte ----" << endl;
    }

    Bankomat()
    {
        this->waluta = "PLN";
        this->pin = "0000";
        this->saldo = 0;
        this->maxDebet = 0;
        this->imie = "User Name";
        this->nazwisko = "User Surname";
    }
    ~Bankomat()
    {
        this->saldo = 0;
        this->maxDebet = 0;
        this->imie = "User Name";
        this->nazwisko = "User Surname";
    }
    void WpiszRecznie(string p, int s, int mD, string i, string n)
    {
        pin = p;
        saldo = s;
        maxDebet = mD;
        imie = i;
        nazwisko = n;
    }

private:
    string waluta;
    string pin;
    double saldo;
    double maxDebet;
    string imie;
    string nazwisko;
};

int main()
{
    Bankomat b1;

    b1.Start();

    return 0;
}