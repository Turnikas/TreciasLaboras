#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct menuItemType {
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

    if (!fin) {
        cout << "Nepavyko atidaryti menu.txt failo.\n";
        itemCount = 0;
        return;
    }

    itemCount = 0;

    while (fin >> menuList[itemCount].menuItem >> menuList[itemCount].menuPrice) {
        itemCount++;
    }

    fin.close();
}

void showMenu(menuItemType menuList[], int itemCount)
{
    linija();
    cout << "=============== PUSRYCIU MENIU ===================\n";
    linija();

    for (int i = 0; i < itemCount; i++) {
        cout << i + 1 << ". " << menuList[i].menuItem << " - ";
        cout << fixed << setprecision(2) << menuList[i].menuPrice << " EUR\n";
    }

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

    int kiekSkirtingu;
    cout << "Kiek skirtingu patiekalu norite uzsakyti?\n> ";
    cin >> kiekSkirtingu;

    while (kiekSkirtingu < 1 || kiekSkirtingu > MAX_ORDER_ITEMS) {
        cout << "Blogas kiekis. Iveskite nuo 1 iki " << MAX_ORDER_ITEMS << ".\n> ";
        cin >> kiekSkirtingu;
    }

    int pasirinktiIndeksai[MAX_ORDER_ITEMS];
    int porcijos[MAX_ORDER_ITEMS];

    for (int i = 0; i < kiekSkirtingu; i++) {
        int numeris;
        int porcija;

        cout << "Iveskite " << i + 1 << "-ojo patiekalo numeri.\n> ";
        cin >> numeris;

        while (numeris < 1 || numeris > itemCount) {
            cout << "Tokio patiekalo nera.\n> ";
            cin >> numeris;
        }

        cout << "Iveskite porciju kieki.\n> ";
        cin >> porcija;

        while (porcija < 1) {
            cout << "Porcija turi buti bent 1.\n> ";
            cin >> porcija;
        }

        pasirinktiIndeksai[i] = numeris - 1;
        porcijos[i] = porcija;
    }

    linija();
    cout << "Uzsakymas:\n";

    for (int i = 0; i < kiekSkirtingu; i++) {
        cout << porcijos[i] << " x " << menuList[pasirinktiIndeksai[i]].menuItem << endl;
    }

    linija();

    return 0;
}