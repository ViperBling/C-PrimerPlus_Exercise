#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
using namespace std;

struct Review {
    std::string title;
    int rating;
    double price;
};

bool operator<(shared_ptr<Review> r1, shared_ptr<Review> r2);
bool worseThan(shared_ptr<Review> r1, shared_ptr<Review> r2);
bool expensiveThan(shared_ptr<Review> r1, shared_ptr<Review> r2);
bool FillReview(Review & rr);
void ShowReview(shared_ptr<Review> rr);

int main()
{
    Review tmp;
    vector<shared_ptr<Review>> ptr;
    while (FillReview(tmp))
        ptr.push_back(shared_ptr<Review> (new Review(tmp)));
    vector<shared_ptr<Review>> pt1(ptr);
    sort(pt1.begin(), pt1.end());

    vector<shared_ptr<Review>> pt2(ptr);
    sort(pt2.begin(), pt2.end(), worseThan);

    vector<shared_ptr<Review>> pt3(ptr);
    sort(pt3.begin(), pt3.end(), expensiveThan);

    if (!ptr.empty()) {
        cout << "Thank you, You entered the following "
             << ptr.size() << " informations: \n";
        cout << "Rating\t\t\tBook\t\t\t\tPrice\n";
        for_each(ptr.begin(), ptr.end(), ShowReview);
        cout << "\nWhich way you want display the information? \n";
        cout << "a. Orginal order        b. Alphabetic order\n"
             << "c. Rating ascending order\n"
                "d. Rating descending order\n"
                "e. Price ascending order\n"
                "f. Price descending order\n"
                "q. quit\n";
        char choice;
        while (cin >> choice && tolower(choice) != 'q') {
            switch (choice) {
                case 'A' :
                case 'a' :
                    for_each(ptr.begin(), ptr.end(), ShowReview);
                    break;
                case 'B' :
                case 'b' :
                    for_each(pt1.begin(), pt1.end(), ShowReview);
                    break;
                case 'C' :
                case 'c' :
                    for_each(pt2.begin(), pt2.end(), ShowReview);
                    break;
                case 'D' :
                case 'd' :
                    for_each(pt2.rbegin(), pt2.rend(), ShowReview);
                    break;
                case 'E' :
                case 'e' :
                    for_each(pt3.begin(), pt3.end(), ShowReview);
                    break;
                case 'F' :
                case 'f' :
                    for_each(pt3.rbegin(), pt3.rend(), ShowReview);
                    break;
                default:
                    break;
            }
            cout << "\nWhich way you want display the information? \n";
            cout << "a. Orginal order        b. Alphabetic order\n"
                 << "c. Rating ascending order\n"
                    "d. Rating descending order\n"
                    "e. Price ascending order\n"
                    "f. Price descending order\n"
                    "q. quit\n";
        }
    } else
        cout << "No data!\n";
    cout << "Bye.\n";

    return 0;
}

bool operator<(shared_ptr<Review> r1, shared_ptr<Review> r2) {
    if (r1->title < r2->title)
        return true;
    else if (r1->title == r2->title && r1->rating < r2->rating)
        return true;
    else
        return false;
}

bool worseThan(shared_ptr<Review> r1, shared_ptr<Review> r2) {
    return r1->rating < r2->rating;
}

bool expensiveThan(shared_ptr<Review> r1, shared_ptr<Review> r2) {
    return r1->price < r2->price;
}

bool FillReview(Review & rr) {
    cout << "Enter book title (quit to quit): ";
    getline(cin, rr.title);
    if (rr.title == "quit")
        return false;
    cout << "Enter the book rating: ";
    cin >> rr.rating;
    if (!cin)
        return false;
    cout << "Enter the book price: ";
    cin >> rr.price;
    if (!cin)
        return false;
    while (cin.get() != '\n')
        continue;
    return true;
}

void ShowReview(shared_ptr<Review> rr) {
    cout << rr->rating << "\t\t\t\t" << rr->title << "\t\t\t\t$"
    << rr->price << std::endl;
}