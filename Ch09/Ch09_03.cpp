#include <iostream>
using namespace std;

const int BufferSize = 100;

struct chaff{
    char dross[20];
    int slag;
};

int main()
{
    char buffer[BufferSize];
    chaff * arr;
    arr = new (buffer) chaff [2];
    for (int i = 0; i < 2; i++){
        cout << "Enter dross: ";
        cin.getline(arr[i].dross, 20);
        cout << "Enter slag: ";
        cin >> arr[i].slag;
        cin.get();
    }

    for (int i = 0; i < 2; i++){
        cout << arr[i].dross << ", " << arr[i].slag << endl;
    }

    return 0;
}
