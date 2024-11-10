#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> // For _getch() to mask input

using namespace std;

class RockPaperScissors {
private:
    int user_score;
    int computer_score;

    // Function to generate a random number 
    int random(int start, int stop) {
        return start + rand() % (stop - start + 1); 
    }

public:
    // Constructor to initialize scores
    RockPaperScissors() : user_score(0), computer_score(0) {}

    void play() {
        int user_choice, computer_choice;
        char play_again = 'y';

        while (play_again == 'y') {
            cout << "Rock-Paper-Scissors Game!\n";
            cout << "Enter your choice:\n1 for Rock\n2 for Paper\n3 for Scissors\n";
            cin >> user_choice;

            // Computer's choice
            computer_choice = random(1, 3);

            // Use switch case 
            switch (user_choice) {
                case 1: // User chooses Rock
                    if (computer_choice == 1) {
                        cout << "Computer chose Rock. It's a tie!\n";
                    } else if (computer_choice == 2) {
                        cout << "Computer chose Paper. You lose!\n";
                        computer_score++;
                    } else {
                        cout << "Computer chose Scissors. You win!\n";
                        user_score++;
                    }
                    break;

                case 2: // User chooses Paper
                    if (computer_choice == 1) {
                        cout << "Computer chose Rock. You win!\n";
                        user_score++;
                    } else if (computer_choice == 2) {
                        cout << "Computer chose Paper. It's a tie!\n";
                    } else {
                        cout << "Computer chose Scissors. You lose!\n";
                        computer_score++;
                    }
                    break;

                case 3: // User chooses Scissors
                    if (computer_choice == 1) {
                        cout << "Computer chose Rock. You lose!\n";
                        computer_score++;
                    } else if (computer_choice == 2) {
                        cout << "Computer chose Paper. You win!\n";
                        user_score++;
                    } else {
                        cout << "Computer chose Scissors. It's a tie!\n";
                    }
                    break;

                default:
                    cout << "Invalid choice! Please select 1, 2, or 3.\n";
                    continue; // Re-ask 
            }

            // Display current scores
            cout << "Current Scores:\nYou: " << user_score << "\nComputer: " << computer_score << "\n";

            // Ask if the player wants to play again
            cout << "Do you want to play again? (y/n): ";
            cin >> play_again;
        }

        cout << "Final Scores:\nYou: " << user_score << "\nComputer: " << computer_score << "\n";
        cout << "Thank you for playing!\n";
    }
};

class RandomBox {
private:
    int falseBox;  // The box that is 'false'
    int falseBoxCount = 0;

    // Function to generate a random number 
    int random(int start, int stop) {
        return start + rand() % (stop - start + 1);
    }
    
public:
    void play() {
        char play_again = 'y';
        int choice;

        while (play_again == 'y') {
            falseBox = random(1, 4);
            cout << "Welcome to the 4-Box Game!\n";
            cout << "One of the boxes is a 'false' box. If you select it, the game is over.\n";
            cout << "Select a box (1-4): ";
            cin >> choice;

            if (choice == falseBox) {
                cout << "You selected the 'FALSE BOX'! Game over.\n";
                falseBoxCount++;
            } else if (choice >= 1 && choice <= 4) {
                cout << "Good choice! You selected a correct box.\n";
            } else {
                cout << "Please enter a valid choice (1 - 4).\n";
                continue;
            }

            cout << "Do you want to play again? (y/n): ";
            cin >> play_again;
        }
        cout << "Thanks for playing the 4-Box Game!\n";
        cout << "You selected the FALSE BOX " << falseBoxCount << " times.\n";
    }
};


class Menu {
private:
    string getHiddenInput() {
        string input;
        char ch;
        while ((ch = _getch()) != '\r') {
            if (ch == '\b' && !input.empty()) {
                cout << "\b \b";
                input.pop_back();
            } else {
                input += ch;
                cout << "*";
            }
        }
        cout << endl;
        return input;
    }

    bool isValidLogin(const string& id, const string& pass) {
        ifstream file("top_secret.txt");
        string stored_id, stored_pass;
        
        while (file >> stored_id >> stored_pass) {
            if (stored_id == id && stored_pass == pass) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    void registerUser(const string& id, const string& pass) {
        ofstream file("top_secret.txt", ios::app);
        file << id << " " << pass << endl;
        file.close();
        cout << "Registration successful.\n";
    }

    void user_menu() {
        int choice;
        RockPaperScissors rps;
        RandomBox rb;

        cout << "\033[92m";


        do {
            cout << "\nUser Menu:\n";
            cout << "1. Play Rock-Paper-Scissors\n";
            cout << "2. Play Random Box\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    rps.play();
                    break;
                case 2:
                    rb.play();
                    break;
                case 3:
                    cout << "Exiting to main menu.\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 3);
    }

public:
    void displayMenu() {
        int choice;
        cout << "1. Login\n2. Register\nEnter choice: ";
        cin >> choice;
        
        string id, pass;
        if (choice == 1) {
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Password: ";
            pass = getHiddenInput();

            if (isValidLogin(id, pass)) {
                cout << "Login successful. Welcome!\n";
                user_menu();
            } else {
                cout << "Invalid credentials. Try again.\n";
            }
        } else if (choice == 2) {
            cout << "Enter new ID: ";
            cin >> id;
            cout << "Enter new Password: ";
            pass = getHiddenInput();

            registerUser(id, pass);
        } else {
            cout << "Invalid choice.\n";
        }
    }
};

int main() {
    Menu menu;
    menu.displayMenu();
    cout << "\033[0m";
    return 0;
}
