#include <iostream> 
#include <conio.h>
#include <string>
#include "player.h"
#include "inventory.h"
#include "map.h"
#include "battle.h"
using namespace std;

// Function Declarations
void input(int& inpt, int min = INT_MIN, int max = INT_MAX);
void inputs(string& str, size_t minLen = 1, size_t maxLen = 100);

int main() {
    LegendOfValor game;
    game.mainMenu();
    return 0;
}

// Definitions
//input fucntion for int input
void input(int& inpt, int min, int max) {
    cin >> inpt;
    if (cin.fail() || inpt < min || inpt > max) {
        cin.clear();
        cin.ignore(1000, '\n'); // Ignore invalid input
        cout << "Enter a number from " << min << " to " << max << ": ";
        return input(inpt, min, max); // Recursively ask for input again
    }
}
//input function for string input
void inputs(string& str, size_t minLen, size_t maxLen)
{
    cin.ignore();

    getline(cin, str);

    while (!str.empty() && str[0] == ' ') // Remove leading spaces
        str.erase(0, 1);
    while (!str.empty() && str[str.length() - 1] == ' ') // Remove trailing spaces
        str.erase(str.length() - 1, 1);

    if (str.length() < minLen || str.length() > maxLen) {
        cout << "Input must be between " << minLen << " and " << maxLen << " characters. Try again: ";
        return inputs(str, minLen, maxLen); // Prompt again if invalid input
    }
    else
        return;
}
