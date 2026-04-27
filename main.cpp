#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct menuItemType
{
    string menuItem;
    double menuPrice;
};

const int MAX_ITEMS = 50;
const int MAX_ORDER_ITEMS = 20;

void linija()
{
    cout << "**************************************************\n";
}

void getData(menuItemType menuList[], int& itemCount)
{
    ifstream fin("menu.txt");

    if (!fin)
    {
        cout << "Nepavyko atidaryti menu.txt failo.\n";
        itemCount = 0;
        return;
    }

    itemCount = 0;
	// nuskaitai patiekala is failo, pirma pavadinima, tada kaina
    while (itemCount < MAX_ITEMS && fin >> menuList[itemCount].menuItem >> menuList[itemCount].menuPrice)
    {
		// cia itemcount rodo i kuria masyvo specific vieta isiraso duomenys
        itemCount++;
    }

    fin.close();
}

void showMenu(menuItemType menuList[], int itemCount)
{
    linija();
    cout << "=============== PUSRYCIU MENIU ===================\n";
    linija();
	// eina per visus patiekalus
    for (int i = 0; i < itemCount; i++)
    {
		// patieka numeris ir pavadinimas +1 nes nuo 1
        cout << i + 1 << ". " << menuList[i].menuItem << " - ";
		// cia rodome 2 skaiciai po decimal
        cout << fixed << setprecision(2) << menuList[i].menuPrice << " EUR\n";
    }

    linija();
}

void printCheck(menuItemType menuList[], int indeksai[], int porcijos[], int kiek)
{
    ofstream fout("receipt.txt");

    double suma = 0;

    cout << fixed << setprecision(2);
    fout << fixed << setprecision(2);

    linija();
    cout << "********************  SASKAITA *******************\n";
    linija();

    fout << "********************  SASKAITA *******************\n";

    for (int i = 0; i < kiek; i++)
    {
		// cia apskaiciuoja visos eilutes suma
		// patiekalo kaina * porciju kiekis
        double eilute = menuList[indeksai[i]].menuPrice * porcijos[i];
        suma += eilute;

        cout << porcijos[i] << " x "
             << menuList[indeksai[i]].menuItem
             << " = " << eilute << " EUR\n";

        fout << porcijos[i] << " x "
             << menuList[indeksai[i]].menuItem
             << " = " << eilute << " EUR\n";
    }

    double pvm = suma * 0.21;
    double galutine = suma + pvm;

    linija();
    cout << "PVM (21%): " << pvm << " EUR\n";
    cout << "Galutine suma: " << galutine << " EUR\n";

    fout << "PVM (21%): " << pvm << " EUR\n";
    fout << "Galutine suma: " << galutine << " EUR\n";

    fout.close();

    linija();
    cout << "Jusu cekis buvo issaugotas i receipt.txt\n";
    linija();
}

int main()
{
    menuItemType menuList[MAX_ITEMS];
    int itemCount;

    getData(menuList, itemCount);

    if (itemCount == 0) {
        cout << "Meniu tuscias.\n";
        return 0;
    }

    showMenu(menuList, itemCount);

    int kiekPatiekalu;
    cout << "Kiek patiekalu norite uzsakyti?\n> ";
    cin >> kiekPatiekalu;

    while (kiekPatiekalu < 1 || kiekPatiekalu > MAX_ORDER_ITEMS)
    {
        cout << "Blogas kiekis. Iveskite nuo 1 iki " << MAX_ORDER_ITEMS << ".\n> ";
        cin >> kiekPatiekalu;
    }

    int indeksai[MAX_ORDER_ITEMS];
    int porcijos[MAX_ORDER_ITEMS];

    for (int i = 0; i < kiekPatiekalu; i++)
    {
        int numeris;
        int porcija;

        cout << "Iveskite patiekalo numeri:\n> ";
        cin >> numeris;

        while (numeris < 1 || numeris > itemCount)
        {
            cout << "Tokio patiekalo nera.\n> ";
            cin >> numeris;
        }

        cout << "Iveskite porciju kieki:\n> ";
        cin >> porcija;
		// tikrina ar gera porcija ivesta
        while (porcija < 1)
        {
            cout << "Porcija >= 1\n> ";
            cin >> porcija;
        }
		// useris mato nuo 1
        indeksai[i] = numeris - 1;
		// shortcutas issaugot kiek porciju tam patiekalui
        porcijos[i] = porcija;
    }

    printCheck(menuList, indeksai, porcijos, kiekPatiekalu);

    return 0;
}