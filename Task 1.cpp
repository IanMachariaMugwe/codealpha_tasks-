#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>  // For input validation

using namespace std;

int main() {
    srand(time(0) + rand());  // Seed with time and extra randomness
    int randomNum = rand() % 11;  // Generate number between 0 and 10
    int guess;

    cout << " Welcome to the Number Guessing Game! \n";
    cout << "Try to guess the number (between 0 and 10).\n\n";

    while (true) {
        cout << "Enter your guess: ";

        // Input validation
        while (!(cin >> guess)) {
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            cout << "Invalid input! Please enter a number between 0 and 10: ";
        }

        if (guess == randomNum) {
            cout << "?? Right guess! You win! ??\n";
            break;
        } else if (guess > randomNum) {
            cout << "?? Too high! Try again.\n";
        } else {
            cout << "?? Too low! Try again.\n";
        }

        // Regenerate the random number to change it after each guess (optional)
        randomNum = rand() % 11;
    }

    cout << "Thanks for playing! ??\n";
    return 0;
}


