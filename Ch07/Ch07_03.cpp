#include <iostream>
using namespace std;

struct box{
    char maker[40];
    float height;
    float width;
    float length;
    float volume;
};

void show(box a);
void set(box * a);

int main()
{
    box Bigbox{"Harm", 20.0, 30.0, 10.0, 0.0};

    set(&Bigbox);
    show(Bigbox);

    return 0;
}

void show(box a)
{
    cout << "Maker: " << a.maker << endl;
    cout << "Height: " << a.height << endl;
    cout << "Width: " << a.width << endl;
    cout << "Length: " << a.length << endl;
    cout << "Volume: " << a.volume << endl;
}

void set(box * a)
{
    a->volume = a->height * a->width * a->length;
}