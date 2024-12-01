/***************
CSCE201 PROJECT
Group: (idk if we have a number or a name or whatever)
WORKOUT PROGRAM
12/01/2024
****************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map> // will need this for food database

using namespace std;

//data base of foods, and calories per ounce
map<string,double> foodDatabase = {
    {"apple", 0.52},
    {"banana", 0.9},
    {"chicken", 1.65},
    {"broccoli", 0.35},
    {"rice", 1.3},
    {"almonds", 7.0},
//add more foods here
};

// ensures input is a number
bool numberValidation(double& value, const string& prompt) {
    while (!(cin >> value) || value <= 0.0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << prompt;
    }
    return true;
}

// ensures input is within range
bool rangeValidation(int& value, const string& prompt, int min, int max) {
    while (!(cin >> value) || value < min || value > max) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << prompt;
    }
    return true;
}

bool checkForExistingAcc(const string& name, const string& password, double& height, double& weight, double& age, char& gender, int& calories, string& goal) {
    ifstream accountFile("accounts.txt");
    string line;
    while (getline(accountFile, line)) {
        istringstream iss(line);
        string tempName, tempPassword;
        iss >> tempName >> tempPassword >> height >> weight >> age >> gender >> calories >> goal;
        if (tempName == name && tempPassword == password) return true;
    }
    return false;
}

void saveToFile(const string& name, const string& password, double height, double weight, double age, char gender, int calories, const string& goal) {
    ifstream accountFile("accounts.txt");
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;

    while (getline(accountFile, line)) {
        istringstream iss(line);
        string tempName, tempPassword;
        iss >> tempName >> tempPassword;

        if (tempName == name) {
            tempFile << name << " " << password << " " << height << " " << weight << " " << age << " " << gender << " " << calories << " " << goal << endl;
            found = true;
        } else {
            tempFile << line << endl;
        }
    }

    if (!found) {
        tempFile << name << " " << password << " " << height << " " << weight << " " << age << " " << gender << " " << calories << " " << goal << endl;
    }

    accountFile.close();
    tempFile.close();
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}

// function to login or create an account
void loginOrCreateAccount(string& name, string& password, double& height, double& weight, double& age, char& gender, int& calories, string& goal) {
    while (true) {
        cout << "\nEnter your username: ";
        cin >> name;
        cout << "Enter your password: ";
        cin >> password;

        if (checkForExistingAcc(name, password, height, weight, age, gender, calories, goal)) {
            cout << "\nWelcome back, " << name << "!\n";
            return;
        }

        cout << "\nAccount not found. Please enter a new username and password to sign up for an account.\n";
        cout << "Enter your name: ";
        cin >> name;
        cout << "Create a password: ";
        cin >> password;

        height = weight = age = 0.0;
        calories = 0;
        gender = ' ';
        goal = "None";
        return;
    }
}

// function to calculate daily calorie needs based on user input
void calorieCalculator(double& height, double& weight, double& age, char& gender, int& calories, string& goal) {
    // used the Mifflin-St Jeor Equation from BMR website
    double bmr = (gender == 'M')
        ? (66 + (6.23 * weight) + (12.7 * height) - (6.8 * age))
        : (655 + (4.35 * weight) + (4.7 * height) - (4.7 * age));

    int activityLevel;
    cout << "\nSelect Physical activity level: " << endl;
    cout << "1. Not active at all \n2. Lightly Active \n3. Moderately Active \n4. Very active\n5. Super active\n";
    cout << "Enter choice: ";
    rangeValidation(activityLevel, "Error! Please enter a valid option (1-5): ", 1, 5);

    double factors[] = {1.2, 1.375, 1.55, 1.725, 1.9};
    calories = bmr * ((activityLevel >= 1 && activityLevel <= 5) ? factors[activityLevel - 1] : 1.2);

    cout << "\nSet your goal:" << endl;
    cout << "1. Lose weight\n2. Gain weight\n3. Maintain weight\nEnter choice (1, 2, 3): ";
    int goalChoice;
    rangeValidation(goalChoice, "Error! Please enter a valid option (1, 2, 3): ", 1, 3);

    int paceChoice = 0, calorieSubtraction = 0;

    if (goalChoice == 1 || goalChoice == 2) {
        cout << "\nChoose your pace:\n1. Fast (2 lbs/week)\n2. Moderate (1 lb/week)\n3. Slow (0.5 lb/week)" << endl;
        cout << "DISCLAIMER!!!!!!! Faster does not mean better. Consult your healthcare provider BEFORE any drastic measures." << endl;
        cout << "Enter choice (1, 2, 3): ";
        rangeValidation(paceChoice, "Error! Please enter a valid option (1, 2, 3): ", 1, 3);

        calorieSubtraction = (paceChoice == 1) ? (goalChoice == 1 ? -1000 : 1000)
                  : (paceChoice == 2) ? (goalChoice == 1 ? -500 : 500)
                  : (goalChoice == 1 ? -250 : 250);
    }

    goal = (goalChoice == 1) ? "Lose weight" : (goalChoice == 2) ? "Gain weight" : "Maintain weight";
    calories += calorieSubtraction;

    cout << "\nYour adjusted daily calorie goal is: " << calories << " calories.\n";
}

// displays menu options
void displayMenu() {
    cout << "\n***********************************" << endl;
    cout << "*          MAIN MENU              *" << endl;
    cout << "* 1. Option 1 - Manage Profile    *" << endl;
    cout << "* 2. Option 2 - (INSERT HERE)     *" << endl;
    cout << "* 3. Option 3 - (INSERT HERE)     *" << endl;
    cout << "* 4. Exit                         *" << endl;
    cout << "***********************************" << endl;
}

// handle the user's choice
void getChoice(int choice, string& name, string& password, double& height, double& weight, double& age, char& gender, int& calories, string& goal) {
    switch (choice) {
        case 1: {
            cout << "\n1. View Profile\n2. Update Profile\nEnter choice: ";
            int profileChoice;
            rangeValidation(profileChoice, "Error! Please enter a valid option (1 or 2): ", 1, 2);

            if (profileChoice == 1) {
                cout << "\nName: " << name << "\nHeight: " << height << " inches\nWeight: " << weight
                     << " pounds\nAge: " << age << " years\nGender: " << ((gender == 'M') ? "Male" : "Female")
                     << "\nGoal: " << goal << "\nCalories: " << calories << " calories\n";
            } else if (profileChoice == 2) {
                cout << "\nUpdate Profile:\nGender (M/F): ";
                cin >> gender;
                gender = toupper(gender);

                cout << "Height (inches): ";
                doubleValidation(height, "Error! Enter a valid height: ");

                cout << "Weight (pounds): ";
                doubleValidation(weight, "Error! Enter a valid weight: ");

                cout << "Age: ";
                doubleValidation(age, "Error! Enter a valid age: ");

                calorieCalculator(height, weight, age, gender, calories, goal);
                saveToFile(name, password, height, weight, age, gender, calories, goal);
                cout << "\nProfile updated successfully.\n";
            } else {
                cout << "\nInvalid choice. Returning to menu.\n";
            }
            break;
        }
        case 2:
            cout << "\nYou selected Option 2." << endl;
            break;
        case 3:
            cout << "\nYou selected Option 3." << endl;
            break;
        case 4:
            cout << "\nExiting program..." << endl;
            break;
        default:
            cout << "\nInvalid selection! Please select 1, 2, 3, or 4." << endl;
    }
}

int main() {
    string name, password, goal = "None";
    double height = 0.0, weight = 0.0, age = 0.0;
    int calories = 0;
    char gender = ' ';

    cout << "\n*******************************" << endl;
    cout << "*   CALORIE CALCULATOR 3000   *" << endl;
    cout << "*******************************" << endl;
    loginOrCreateAccount(name, password, height, weight, age, gender, calories, goal);

    if (height == 0.0 || weight == 0.0 || age == 0.0 || gender == ' ') {
        cout << "\nAccount Created. Welcome!" << endl;
        cout << "\nLet's get your account personalized! Enter the following information:\nGender (M/F): ";
        cin >> gender;
        gender = toupper(gender);

        cout << "Height (inches): ";
        doubleValidation(height, "Error! Enter a valid height: ");

        cout << "Weight (pounds): ";
        doubleValidation(weight, "Error! Enter a valid weight: ");

        cout << "Age: ";
        doubleValidation(age, "Error! Enter a valid age: ");

        calorieCalculator(height, weight, age, gender, calories, goal);
        saveToFile(name, password, height, weight, age, gender, calories, goal);
    }

    int userChoice;
    do {
        displayMenu();
        cout << "\nEnter your choice (1, 2, 3, 4): ";
        rangeValidation(userChoice, "Error! Please enter a valid option (1-4): ", 1, 4);
        getChoice(userChoice, name, password, height, weight, age, gender, calories, goal);
    } while (userChoice != 4);

    return 0;
}
