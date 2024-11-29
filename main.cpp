/***************
CSCE201 PROJECT
Group: (idk if we have a number or a name or whatever)
WORKOUT PROGRAM
12/01/2024
****************/
#include <iostream>
using namespace std;

// displays menu options
void displayMenu() {
    cout << "***********************************" << endl;
    cout << "*          MAIN MENU              *" << endl;
    cout << "* 1. Option 1 - (INSERT HERE)     *" << endl;
    cout << "* 2. Option 2 - (INSERT HERE)     *" << endl;
    cout << "* 3. Option 3 - (INSERT HERE)     *" << endl;
    cout << "* 4. Exit                         *" << endl;
    cout << "* Enter your choice (1, 2, 3, 4): *" << endl;
    cout << "***********************************";
}

// handle the user's choice
void getChoice(int choice) {
    switch (choice) {
        case 1:
            cout << "You selected Option 1." << endl;
            // insert feature for Option 1
            break;
        case 2:
            cout << "You selected Option 2." << endl;
            // insert feature for Option 2
            break;
        case 3:
            cout << "You selected Option 3." << endl;
            // insert feature for Option 3.
            break;
        case 4:
            cout << "Exiting program..." << endl;
            //exit program
            break;
        default:
            cout << "Invalid selection! Please select 1, 2, 3 or 4." << endl;
    }
}

int main() {
    int userChoice;

    do {
        // Display menu
        displayMenu();
        
        // Get user input
        cin >> userChoice;

        // Handle the user's choice
        getChoice(userChoice);

    } while (userChoice != 4); // Repeat until the user chooses to exit

    return 0;
}
