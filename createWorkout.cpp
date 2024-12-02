struct Exercise {
    string name;
    int sets;
    int reps;
};

struct BodyPartWorkouts {
        string bodyPart;
        vector<string> exercises;
    };

//make a workout function
void createWorkout() {
    string typeTraining;
    int workoutPerWeek;
    
    vector<BodyPartWorkouts> workoutPlan;

    workoutPlan.push_back({"Chest", {"Bench Press", "Incline Dumbbell Press", "Cable Flys"}});
    workoutPlan.push_back({"Back", {"Deadlifts", "Lat Pulldowns", "Cable Rows"}});
    workoutPlan.push_back({"Legs", {"Squats", "Lunges", "Leg Press"}});
    workoutPlan.push_back({"Shoulders", {"Overhead Press", "Lateral Raises", "Front Raises"}});
    workoutPlan.push_back({"Triceps", {"Tricep Dips", "Skull Crushers", "Tricep Pushdowns"}});
    workoutPlan.push_back({"Biceps", {"Bicep Curls", "Hammer Curls", "Preacher Curls"}});

    srand(time(0));

    cout << "What type of training are you looking for? (Hypertrophy or Strength): ";
    cin >> typeTraining;

    cout << "How many times a week do you plan on working out?: ";
    cin >> workoutPerWeek;

     while (typeTraining != "Hypertrophy" || typeTraining != "Strength"){
        cout << "Invalid training type. Please restart and select Hypertrophy or Strength." << endl;
        return;
    }
    if (typeTraining == "Hypertrophy") {
        cout << "Hypertrophy selected. Suggested sets and reps: 3-5 x 8-12" << endl;
    } else if (typeTraining == "Strength") {
        cout << "Strength selected. Suggested sets and reps: 2-6 x 1-6" << endl;
    }

    while (workoutPerWeek < 2 || workoutPerWeek > 6) {
        cout << "Invalid input. Please select between 2 and 6 days per week." << endl;
        cin >> workoutPerWeek;
    }

    vector<string> workoutSplit;
    //Determining what kind of split based on workout per week
    if (workoutPerWeek == 3 || workoutPerWeek == 6) {
        cout << "\nUsing Push/Pull/Legs split:" << endl;
        cout << "Day 1: Push (Chest, Triceps)" << endl;
        cout << "Day 2: Pull (Back, Biceps, Shoulders)" << endl;
        cout << "Day 3: Legs (Legs)" << endl;
        workoutSplit = {"Chest, Triceps", "Back, Biceps, Shoulders", "Legs"};

    } else if (workoutPerWeek == 2 || workoutPerWeek == 4) {
        cout << "\nUsing Lower/Upper Body split:" << endl;
        cout << "Day 1: Lower Body (Legs)" << endl;
        cout << "Day 2: Upper Body (Chest, Back, Shoulders, Arms)" << endl;
        workoutSplit = {"Legs","Chest", "Triceps", "Back", "Biceps", "Shoulders"}; 

    } else if (workoutPerWeek == 5) {
        cout << "\nUsing Separated Body Parts split:" << endl;
        cout << "Day 1: Chest" << endl;
        cout << "Day 2: Back" << endl;
        cout << "Day 3: Legs" << endl;
        cout << "Day 4: Shoulders" << endl;
        cout << "Day 5: Arms" << endl;
        workoutSplit = {"Chest" ,"Back", "Legs", "Shoulders" , "Arms"};
    }

    cout << "\nCreating Your Workout Schedule: " << endl;
    //Creating workout schedule based on type of training and workout per week
    for (int day = 0; day < workoutPerWeek; day++){
        cout << "\nDay " << day + 1 << ": ";

        for (const auto& bodyPart: workoutPlan){
            Exercise e;
            e.name = bodyPart.exercises;

            //Determining sets and reps
            if (typeTraining == "Hypertrophy"){
                e.sets = rand() % (5 - 3 + 1) + 1; // randomize reps between 3-5
                e.reps = rand() % (12 - 8 + 1) + 1; // randomize reps between 8-12

            } else if (typeTraining == "Strength"){
                e.sets = rand() % (6 - 2 + 1) + 1; // randomize sets between 2-6
                e.reps = rand() % (6 - 1 + 1) + 1; // randomize reps between 1-6
            }
        }

        cout << e.name << ": " << e.sets << "x" << e.reps << endl;   
    }

}
