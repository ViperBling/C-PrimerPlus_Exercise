#include <iostream>
#include <ctime>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    vector<string> wordlist;
    ifstream ifs;
    ifs.open("test.txt");
    if (!ifs.is_open()) {
        cout << "Open file failed!\n";
        exit(EXIT_FAILURE);
    }
    string str;
    while (ifs && ifs >> str)
        wordlist.push_back(str);
    ifs.close();

    srand(time(0));
    char play;
    cout << "Will you play a word game? <y/n> ";
    cin >> play;
    play = tolower(play);
    while (play == 'y') {
        string target = wordlist[rand() % wordlist.size()];
        size_t length = target.length();
        string attempt(length, '-');
        string badchars;
        int guesses = 6;
        cout << "Guess my secret word. It has " << length
             << " letters, and you guess\n"
             << "one letter at a time. You get " << guesses
             << " wrong guesses.\n";

        cout << "Your word: " << attempt << endl;
        while (guesses > 0 && attempt != target) {
            char letter;
            cout << "Guess a letter: ";
            cin >> letter;
            if (badchars.find(letter) != string::npos || attempt.find(letter) != string::npos) {
                cout << "You already guessed that. Try again.\n";
                continue;
            }
            size_t loc = target.find(letter);
            if (loc == string::npos) {
                cout << "Oh, bad guess!\n";
                --guesses;
                badchars += letter;
            } else {
                cout << "Good guess!\n";
                attempt[loc] = letter;
                loc = target.find(letter, loc+1);
                while (loc != string::npos){
                    attempt[loc] = letter;
                    loc = target.find(letter, loc+1);
                }
            }
            cout << "Your word: " << attempt << endl;
            if (attempt != target) {
                if (badchars.length() > 0)
                    cout << "Bad choice: " << badchars << endl;
                cout << guesses << " bad guesses left\n";
            }
        }
        if (guesses > 0)
            cout << "That's right!\n";
        else
            cout << "Sorry, the word is " << target << ".\n";
        cout << "Will you play another? <y/n> ";
        cin >> play;
        play = tolower(play);
    }
    cout << "Bye\n";

    return 0;
}
