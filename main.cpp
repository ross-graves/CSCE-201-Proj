/***************
CSCE201 PROJECT
Group: Gym Brogrammers
WORKOUT PROGRAM
12/01/2024
****************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

map<string, double> foodDatabase = {
    {"apple", 15.0},
    {"banana", 25.0},
    {"chicken", 31.0},
    {"broccoli", 25.0},
    {"rice", 37.0},
    {"almonds", 164.0},
    {"rice krispies", 130.0},
    {"pepperoni pizza", 84.0},
    {"cheese pizza", 78.0},
    {"pizza", 81.0},
    {"hamburger", 62.5},
    {"cheeseburger", 89.0},
    {"burger", 75.8},
    {"fries", 58.0},
    {"french fries", 58.0},
    {"chocolate ice cream", 57.0},
    {"vanilla ice cream", 57.0},
    {"ice cream", 57.0},
    {"red bull", 13.1},
    {"sprite", 11.9},
    {"coca cola", 11.6},
    {"coke", 11.6},
    {"pepsi", 12.5},
    {"dr pepper", 12.5},
    {"steak", 53.0},
    {"pork", 67.5},
    {"carrot", 10.0},
    {"caesar salad", 140.0}
};

void addCustomFood() {
    string foodName;
    double caloriePerOz;
    char addFood;

    cout << "\nFood not found in database. Would you like to add it? (Y/N): ";
    cin >> addFood;

    if (toupper(addFood) == 'Y') {
        cout << "Enter food name: ";
        cin >> foodName;
        if (foodDatabase.find(foodName) != foodDatabase.end()) {
            cout << "Food already in database." << endl;
            return;
        }
        cout << "Enter calories per oz for " << foodName << ": ";
        cin >> caloriePerOz;

        foodDatabase[foodName] = caloriePerOz;
        cout << foodName << " has been added to the database with " << caloriePerOz << " calories/oz" << endl;
    } else {
        cout << "Food not added to the database." << endl;
    }
}

void trackFood(int& totalCalories) {
    string foodName;
    double foodAmount;
    char continueTracking;

    do {
        cout << "\nEnter food item: ";
        cin >> foodName;

        auto it = foodDatabase.find(foodName);
        if (it != foodDatabase.end()) {
            cout << "Enter the amount (ounces) you ate: ";
            cin >> foodAmount;

            double foodCalories = it->second * foodAmount;
            totalCalories += foodCalories;
            cout << "You ate " << foodCalories << " calories of " << foodName << "." << endl;
        } else {
            cout << "Food not included in database." << endl;
            addCustomFood();
        }
        cout << "Add more food? (Y/N): ";
        cin >> continueTracking;

    } while (toupper(continueTracking) == 'Y');

    cout << "\nTotal calories tracked today: " << totalCalories << " calories.\n";
}

bool doubleValidation(double& value, const string& prompt) {
    while (!(cin >> value) || value <= 0.0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << prompt;
    }
    return true;
}

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

        cout << "\nAccount not found! Sign up here:\n";
        cout << "Create a username (no spaces): ";
        cin >> name;
        cout << "Create a password (no spaces): ";
        cin >> password;

        height = weight = age = 0.0;
        calories = 0;
        gender = ' ';
        goal = "None";
        return;
    }
}

void calorieCalculator(double& height, double& weight, double& age, char& gender, int& calories, string& goal) {
    double bmr = (gender == 'M')
        ? (66 + (6.23 * weight) + (12.7 * height) - (6.8 * age))
        : (655 + (4.35 * weight) + (4.7 * height) - (4.7 * age));

    int activityLevel;
    cout << "\nSelect Physical activity level: " << endl;
    cout << "1. Not active (Sedentary) \n2. Lightly Active (Light walking or jogging) \n3. Moderately Active (Exercise 1-2 times a week) \n4. Very active (Exercise 4-5 times a week) \n5. Super active (Exercise 6-7 times a week or Physical job) \n";
    cout << "Enter choice: ";
    rangeValidation(activityLevel, "Error! Please enter a valid option (1-5): ", 1, 5);

    double factors[] = {1.2, 1.375, 1.55, 1.725, 1.9};
    calories = bmr * factors[activityLevel - 1];

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

    cout << "\nYour calorie intake based on your goal is: " << calories << " calories.\n";
}

void displayMenu() {
    cout << "\n***********************************" << endl;
    cout << "*          MAIN MENU              *" << endl;
    cout << "* 1. Option 1 - Manage Profile    *" << endl;
    cout << "* 2. Option 2 - Log Calories      *" << endl;
    cout << "* 3. Option 3 - Workout Guide     *" << endl;
    cout << "* 4. Exit                         *" << endl;
    cout << "***********************************" << endl;
}

void createWorkout() {
    string typeTraining;
    int workoutPerWeek;

    cout << "What type of training are you looking for? (Hypertrophy or Strength): ";
    cin >> typeTraining;
    
    //Input Validation
    while (typeTraining != "Hypertrophy" && typeTraining != "Strength") {
        cout << "Invalid training type. Please select Hypertrophy or Strength: ";
        cin >> typeTraining;
    }

    cout << "How many times a week do you plan on working out? (2-6): ";
    rangeValidation(workoutPerWeek, "Invalid input. Please select between 2 and 6 days per week: ", 2, 6);
    
    //Suggesting type of training based on user input
    if (typeTraining == "Hypertrophy") {
        cout << "\nHypertrophy selected. Suggested sets and reps: 3-5 x 8-12" << endl;
    } else if (typeTraining == "Strength") {
        cout << "\nStrength selected. Suggested sets and reps: 2-6 x 1-6" << endl;
    }
    
    //Suggesting type of workout split based on how many days user is willing to workout
    if (workoutPerWeek == 3 || workoutPerWeek == 6) {
        cout << "\nUsing Push/Pull/Legs split:" << endl;
        cout << "Day 1: Push (Chest, Triceps)" << endl;
        cout << "Day 2: Pull (Back, Biceps, Shoulders)" << endl;
        cout << "Day 3: Legs (Quads, Hamstrings, Calves)" << endl;
        if (workoutPerWeek == 6) {
            cout << "Day 4: Push (Chest, Triceps)" << endl;
            cout << "Day 5: Pull (Back, Biceps, Shoulders)" << endl;
            cout << "Day 6: Legs (Quads, Hamstrings, Calves)" << endl;
        }
    } else if (workoutPerWeek == 2 || workoutPerWeek == 4) {
        cout << "\nUsing Lower/Upper Body split:" << endl;
        cout << "Day 1: Lower Body (Legs)" << endl;
        cout << "Day 2: Upper Body (Chest, Back, Shoulders, Arms)" << endl;
        if (workoutPerWeek == 4) {
            cout << "Day 3: Lower Body (Legs)" << endl;
            cout << "Day 4: Upper Body (Chest, Back, Shoulders, Arms)" << endl;
        }
    } else if (workoutPerWeek == 5) {
        cout << "\nUsing Separated Body Parts split:" << endl;
        cout << "Day 1: Chest" << endl;
        cout << "Day 2: Back" << endl;
        cout << "Day 3: Legs" << endl;
        cout << "Day 4: Shoulders" << endl;
        cout << "Day 5: Arms" << endl;
    }

    cout << "\nYour customized workout plan has been generated!\n";

    //Return back to main menu
    cout << "\nPress Enter to return to the main menu...";
    cin.ignore(); // Clear the input buffer
    cin.get();    // Wait for the user to press Enter
}


void getChoice(int choice, string& name, string& password, double& height, double& weight, double& age, char& gender, int& calories, string& goal) {
    int totalCalories = 0;
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
                cout << "\nUpdate Profile: ";
                do {
                    cout << "Gender (M/F): ";
                    cin >> gender;
                    cin.ignore(1000, '\n');
                    gender = toupper(gender);

                    if (gender != 'M' && gender != 'F') {
                        cout << "Error! Input must be 'M' for male or 'F' for female: ";
                        cin.clear();
                    }
                } while (gender != 'M' && gender != 'F');

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
            trackFood(totalCalories);
            break;
        case 3:
            createWorkout();
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
        do {
            cin >> gender;
            gender = toupper(gender);
            if (gender != 'M' && gender != 'F') {
                cout << "Error! Input must be 'M' for male or 'F' for female: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        } while (gender != 'M' && gender != 'F');

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
