#include <iostream>
#include <string>
using namespace std;

void chooseTrainingType(string &trainingChoice) {
    cout << "What type of workout do you want? (Muscle or Power): ";
    cin >> trainingChoice;

    while (trainingChoice != "Muscle" && trainingChoice != "Power") {
        cout << "Invalid choice! Please type 'Muscle' or 'Power': ";
        cin >> trainingChoice;
    }
}

void pickWorkoutDays(int &workoutDays) {
    cout << "How many days a week can you train? (2-6): ";
    cin >> workoutDays;

    while (workoutDays < 2 || workoutDays > 6) {
        cout << "Please pick a number between 2 and 6: ";
        cin >> workoutDays;
    }
}

void makePlan(string trainingChoice, int workoutDays) {
    cout << "\nYour workout plan: " << endl;

    switch (workoutDays) {
        case 3:
        case 6:
            cout << "\nYou should do Push/Pull/Legs:" << endl;
            cout << "Day 1: Push (Chest, Triceps)" << endl;
            cout << "Day 2: Pull (Back, Biceps, Shoulders)" << endl;
            cout << "Day 3: Legs (Legs)" << endl;
            break;
        case 2:
        case 4:
            cout << "\nYou should do Upper/Lower Body split:" << endl;
            cout << "Day 1: Lower Body (Legs)" << endl;
            cout << "Day 2: Upper Body (Chest, Back, Shoulders, Arms)" << endl;
            break;
        case 5:
            cout << "\nYou should do Separate Body Parts:" << endl;
            cout << "Day 1: Chest" << endl;
            cout << "Day 2: Back" << endl;
            cout << "Day 3: Legs" << endl;
            cout << "Day 4: Shoulders" << endl;
            cout << "Day 5: Arms" << endl;
            break;
        default:
            cout << "Invalid input." << endl;
            return;
    }

    switch (trainingChoice[0]) {
        case 'M': 
            cout << "\nFor Muscle growth, do 3-5 sets of 8-12 reps." << endl;
            break;
        case 'P': 
            cout << "\nFor Power, do 2-6 sets of 1-6 reps." << endl;
            break;
        default:
            cout << "Something went wrong." << endl;
            return;
    }
}

int main() {
    string workoutType;
    int daysPerWeek;

    chooseTrainingType(workoutType);
    pickWorkoutDays(daysPerWeek);

    makePlan(workoutType, daysPerWeek);

    return 0;
}
