#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class ColorSpray {
public:
    // Constructor that applies color spray for the entire session
    ColorSpray(bool isAdmin) {
        // Apply color only once based on user type
        if (isAdmin) {
            cout << "\033[1;31m";  // Bright red for admin
        } else {
            cout << "\033[1;32m";  // Bright green for user
        }
    }

    // Destructor that resets the color at the end of the program
    ~ColorSpray() {
        // Reset color to default at the end of the program
        cout << "\033[0m"; // Reset color to default
    }
};

namespace LoginSystem {
    bool isAdmin = false;

    bool login(const string& userId, const string& password) {
        ifstream file("xy.txt");
        string line, storedId, storedPassword;

        while (getline(file, line)) {
            istringstream ss(line);
            ss >> storedId >> storedPassword;

            if (storedId == userId && storedPassword == password) {
                // Check if ID contains '@#' to determine if the user is an admin
                if (userId.find("@#") != string::npos) {
                    isAdmin = true;
                } else {
                    isAdmin = false;
                }
                return true; // Successful login
            }
        }
        return false; // Login failed
    }
}

void readContacts() {
    ifstream file("xy.txt");
    string line;

    cout << "Contacts List:" << endl;
    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file." << endl;
    }
}

void writeContact(const string& name, const string& phone) {
    ofstream file("xy.txt", ios::app);
    if (file.is_open()) {
        file << name << " " << phone << endl;
        file.close();
        cout << "Contact saved successfully!" << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
}

void deleteContact(const string& name) {
    ifstream file("xy.txt");
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;

    if (file.is_open() && tempFile.is_open()) {
        while (getline(file, line)) {
            if (line.find(name) != 0) {
                tempFile << line << endl;
            } else {
                found = true;
            }
        }
        file.close();
        tempFile.close();

        remove("xy.txt");
        rename("temp.txt", "xy.txt");

        if (found) {
            cout << "Contact deleted successfully!" << endl;
        } else {
            cout << "Contact not found." << endl;
        }
    } else {
        cout << "Unable to open file." << endl;
    }
}

int main() {
    string userId, password;

    // Ask for login details
    cout << "Enter ID: ";
    getline(cin, userId);

    // Check if the user is admin or regular user and set color
    bool isAdmin = (userId.find("@#") != string::npos);

    // Color management based on user type (admin or regular user)
    ColorSpray colorEffect(isAdmin);  // Apply color once

    // Admin can log in without a password
    if (isAdmin) {
        // Admin doesn't need a password
        LoginSystem::isAdmin = true;
        cout << "Welcome, Admin!" << endl;
    } else {
        cout << "Enter your password: ";
        getline(cin, password);

        // Check login credentials (ID and password from xy.txt)
        if (!LoginSystem::login(userId, password)) {
            cout << "Invalid credentials. Exiting..." << endl;
            return 0;
        }
    }

    int choice;
    string name, phone;

    while (true) {
        
        cout << "1. View ID" << endl;

        // Admins have additional options to add and delete contacts
        if (LoginSystem::isAdmin) {
            cout << "2. Add ID" << endl;
            cout << "3. Delete ID" << endl;
        }

        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore leftover newline character

        switch (choice) {
            case 1:
                readContacts();
                break;
            case 2:
                if (LoginSystem::isAdmin) {
                    cout << "Enter Name: ";
                    getline(cin, name);
                    cout << "Enter Password: ";
                    getline(cin, phone);
                    writeContact(name, phone);
                } else {
                    cout << "Access Denied: Only admins can add contacts." << endl;
                }
                break;
            case 3:
                if (LoginSystem::isAdmin) {
                    cout << "Enter Name of Contact to Delete: ";
                    getline(cin, name);
                    deleteContact(name);
                } else {
                    cout << "Access Denied: Only admins can delete contacts." << endl;
                }
                break;
            case 4:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    // Reset color to default at the end of the program
    cout << "\033[0m"; // Reset color to default before the program exits
    return 0 ;
}