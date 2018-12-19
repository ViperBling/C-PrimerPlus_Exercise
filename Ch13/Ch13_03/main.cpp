#include <iostream>
using namespace std;
#include "dma.h"

const int SIZE = 3;

int main()
{
    abcDMA * pdma[SIZE];
    char *tmp_label = new char[50];
    char *tmp_color = new char[50];
    char *tmp_style = new char[50];
    int tmp_rating;
    char kind;

    for (int i = 0; i < SIZE; i++) {
        cout << "Enter Label: ";
        cin.getline(tmp_label, 50);
        cout << "Enter Rating: ";
        cin >> tmp_rating;
        cout << "Enter 1 for baseDMA, 2 for lacksDMA, 3 for hasDMA: ";
        while (cin >> kind && (kind != '1' && kind != '2' && kind != '3'))
            cout << "Enter 1 or 2 or 3: ";
        cin.get();
        if (kind == '1')
            pdma[i] = new baseDMA(tmp_label, tmp_rating);
        else if (kind == '2') {
            cout << "Enter Color: ";
            cin.getline(tmp_color, 50);
            pdma[i] = new lacksDMA(tmp_color, tmp_label, tmp_rating);
        }
        else if (kind == '3') {
            cout << "Enter Style: ";
            cin.getline(tmp_style, 50);
            pdma[i] = new hasDMA(tmp_style, tmp_label, tmp_rating);
        }
        while (cin.get() != '\n')
            continue;
    }

    cout << endl;
    for (auto dma : pdma) {
        dma->View();
        cout << endl;
    }
    for (auto dma : pdma)
        delete dma;

    delete [] tmp_label;
    delete [] tmp_color;
    delete [] tmp_style;
    cout << "Done.\n";

    return 0;
}