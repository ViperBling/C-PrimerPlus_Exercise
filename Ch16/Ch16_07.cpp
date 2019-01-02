#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> Lotto(int all, int pick);
void out(int n) { std::cout << n << " "; }

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    cout << "This is a Test Program of Lottery card.\n";
    int all, pick;
    cout << "Enter a range (q to quit): ";
    while (cin >> all && all > 0) {
        cout << "How many times you draw the card: ";
        cin >> pick;
        std::vector<int> winners;
        winners = Lotto(all, pick);
        cout << "The winners cards is: \n";
        std::for_each(winners.begin(), winners.end(), out);
        cout << "\nEnter a range (q to quit): ";
    }
    cout << "Done.\n";

    return 0;
}

std::vector<int> Lotto(int all, int pick) {
    std::vector<int> tmp;
    std::vector<int> res;
    for (int i = 0; i < all; i++)
//        tmp[i] = i+1;
        tmp.push_back(i+1);
    for (int i = 0; i < pick; i++) {
        std::random_shuffle(tmp.begin(), tmp.end());
        res.push_back(tmp[0]);
    }
    return res;
}