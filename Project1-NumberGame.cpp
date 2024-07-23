#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;

map<string, int> mi;
map<string, int> hints;

void playGame() {
    string name;
    cout << "*==============================*" << endl;
    cout << "|   | Guess the Number Game |  |" << endl;
    cout << "*===============================*" << endl;
    cout << "Enter your Name: ";
    cin >> name;

    int difficulty;
    cout << "Choose difficulty level:" << endl;
    cout << "1. Easy    (Range: 0-49, 10 tries)" << endl;
    cout << "2. Medium  (Range: 0-99, 6 tries)" << endl;
    cout << "3. Hard    (Range: 0-199, 4 tries)" << endl;
    cout << "Enter your choice: ";
    cin >> difficulty;

    int maxRange, trials;
    switch (difficulty) {
        case 1:
            maxRange = 50; // Easy: 0-49
            trials = 10;
            break;
        case 2:
            maxRange = 100; // Medium: 0-99
            trials = 6;
            break;
        case 3:
            maxRange = 200; // Hard: 0-199
            trials = 4;
            break;
        default:
            cout << "Invalid difficulty level. Defaulting to Medium." << endl;
            maxRange = 100;
            trials = 6;
    }

    if (hints.find(name) == hints.end()) {
        hints[name] = 3; // Everyone starts with 3 hints
    }

    bool playAgain = true;
    while (playAgain) {
        int ranNum = rand() % maxRange;
        bool win = false;
        int guess;
        int pTries = 0;

        cout << "*===============================*" << endl;
        cout << "|   Game Started - Good Luck!   |" << endl;
        cout << "*===============================*" << endl;

        while (!win && pTries != trials) {
            cout << "Guess a Number (0-" << maxRange - 1 << "): ";
            cin >> guess;
            pTries++;

            if (guess == ranNum) {
                cout << "*===============================*" << endl;
                cout << "| Congratulations! You Guessed  |" << endl;
                cout << "|   the Number in " << pTries << " Tries!   |" << endl;
                cout << "*===============================*" << endl;
                win = true;

                // Update leaderboard
                if (mi.find(name) == mi.end()) {
                    mi[name] = 1;
                } else {
                    mi[name]++;
                    if (mi[name] % 3 == 0) { // Award an extra hint for every 3 correct answers
                        hints[name]++;
                        cout << "You earned an extra hint! You now have " << hints[name] << " hints." << endl;
                    }
                }
            } else {
                cout << "****> You've guessed it wrong <****" << endl;
                cout << "Do you want a hint? (yes/no): ";
                string useHint;
                cin >> useHint;

                if (useHint == "yes" && hints[name] > 0) {
                    hints[name]--;
                    if (guess < ranNum) {
                        int diff = ranNum - guess;
                        if (diff <= 10) {
                            cout << "Low but very close!!" << endl;
                        } else if (diff <= 20) {
                            cout << "Low, but close. Guess again." << endl;
                        } else {
                            cout << "Too low and too far. Guess again." << endl;
                        }
                    } else {
                        int diff = guess - ranNum;
                        if (diff <= 10) {
                            cout << "High but very close!!" << endl;
                        } else if (diff <= 20) {
                            cout << "High, but close. Guess again." << endl;
                        } else {
                            cout << "Too high and too far. Guess again." << endl;
                        }
                    }
                    cout << "You have " << hints[name] << " hints remaining." << endl;
                } else if (useHint == "yes" && hints[name] == 0) {
                    cout << "Sorry, you have no hints remaining." << endl;
                } else if (useHint == "no") {
                    if (guess < ranNum) {
                        cout << "Guess again." << endl;
                    } else {
                        cout << "Guess again." << endl;
                    }
                }

                // Ask if the player wants to exit
                cout << "Do you want to exit? (yes/no): ";
                string exitResponse;
                cin >> exitResponse;
                if (exitResponse == "yes") {
                    cout << "****Thank you for playing! Visit again.****" << endl;
                    exit(0); // Terminate the program
                }
            }
        }

        if (!win) {
            cout << "*===============================*" << endl;
            cout << "|   Game Over! You ran out of   |" << endl;
            cout << "|    tries. The correct number  |" << endl;
            cout << "|        was " << ranNum << ".              |" << endl;
            cout << "*===============================*" << endl;
        }

        cout << "Do you want to play again? (yes/no): ";
        string response;
        cin >> response;
        playAgain = (response == "yes");
    }
}

void displayLeaderBoard() {
    cout << "*===============================*" << endl;
    cout << "|        |_Leaderboard_|        |" << endl;
    cout << "*===============================*" << endl;
    cout << "Name\tScore\tHints" << endl;

    for (auto i : mi) {
        cout << i.first << "\t" << i.second << "\t" << hints[i.first] << endl;
    }
    cout << "===============================" << endl;
}

void displayMenu() {
    int choice;

    do {
        cout << "*===============================*" << endl;
        cout << "|         |_Main Menu_|         |" << endl;
        cout << "*===============================*" << endl;
        cout << "1. Play" << endl;
        cout << "2. View Leaderboard" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                displayLeaderBoard();
                break;
            case 3:
                cout << "Thanks for Playing. Goodbye!" << endl;
                break;
            default:
                cout << "Please enter a valid choice." << endl;
                break;
        }
    } while (choice != 3);
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    displayMenu();
    return 0;
}
