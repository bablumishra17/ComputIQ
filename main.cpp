
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
using namespace std;

struct Question {
    string question;
    string options[4];
    int correctAnswer;
};

struct Student {
    string name;
    string rollNo;
};

int getNumber() {
    int n;
    while (!(cin >> n)) {
        cout << "Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return n;
}

vector<Question> computingQuestions = {
    {"Which language is used to develop this project?",
     {"HTML", "C++", "CSS", "SQL"}, 2},

    {"What does CPU stand for?",
     {"Central Processing Unit", "Computer Personal Unit",
      "Central Program Utility", "Control Processing User"}, 1},

    {"Which of the following is an input device?",
     {"Monitor", "Printer", "Keyboard", "Speaker"}, 3},

    {"Which data type stores whole numbers in C++?",
     {"float", "int", "char", "string"}, 2},

    {"Which symbol ends a statement in C++?",
     {".", ",", ";", ":"}, 3}
};

vector<Question> logicalQuestions = {
    {"Find the next number: 2, 4, 6, 8, ?",
     {"9", "10", "12", "14"}, 2},

    {"Find the next number: 5, 10, 15, 20, ?",
     {"22", "25", "30", "35"}, 2},

    {"Which one is different?",
     {"Apple", "Mango", "Carrot", "Banana"}, 3},

    {"If A = 1, B = 2, then C = ?",
     {"1", "2", "3", "4"}, 3},

    {"Find the next number: 1, 4, 9, 16, ?",
     {"20", "24", "25", "36"}, 3}
};

vector<Question> mathQuestions = {
    {"What is the average of 10, 20 and 30?",
     {"10", "15", "20", "30"}, 3},

    {"What is 25% of 200?",
     {"25", "40", "50", "75"}, 3},

    {"What is 12 x 5?",
     {"50", "55", "60", "65"}, 3},

    {"What is the square of 9?",
     {"18", "72", "81", "99"}, 3},

    {"What is 100 divided by 4?",
     {"20", "25", "40", "50"}, 2}
};

void saveResult(Student s, int correct, int total,
                double percentage) {
    ofstream file("results.txt", ios::app);

    if (file.is_open()) {
        file << "Student Name: " << s.name << '\n';
        file << "Roll Number: " << s.rollNo << '\n';
        file << "Correct Answers: " << correct << '\n';
        file << "Total Questions: " << total << '\n';
        file << fixed << setprecision(2);
        file << "Percentage: " << percentage << "%\n";
        file << "-----------------------------\n";
        file.close();
        cout << "\nResult saved in results.txt\n";
    } else {
        cout << "\nUnable to save the result.\n";
    }
}

void startAssessment(Student s, vector<Question> questions) {
    int correct = 0;
    int answer;

    cout << "\n====================================\n";
    cout << "          COMPUTIQ ASSESSMENT\n";
    cout << "====================================\n";

    for (int i = 0; i < (int)questions.size(); i++) {
        cout << "\nQ" << i + 1 << ". "
             << questions[i].question << '\n';

        for (int j = 0; j < 4; j++) {
            cout << j + 1 << ". "
                 << questions[i].options[j] << '\n';
        }

        cout << "Enter your answer (1-4): ";
        answer = getNumber();

        while (answer < 1 || answer > 4) {
            cout << "Choose a number between 1 and 4: ";
            answer = getNumber();
        }

        if (answer == questions[i].correctAnswer) {
            cout << "Correct answer!\n";
            correct++;
        } else {
            cout << "Wrong answer! Correct answer: "
                 << questions[i].options[
                        questions[i].correctAnswer - 1]
                 << '\n';
        }
    }

    int total = (int)questions.size();
    double percentage = (correct * 100.0) / total;

    cout << "\n====================================\n";
    cout << "             FINAL RESULT\n";
    cout << "====================================\n";
    cout << "Student Name: " << s.name << '\n';
    cout << "Roll Number: " << s.rollNo << '\n';
    cout << "Total Questions: " << total << '\n';
    cout << "Correct Answers: " << correct << '\n';
    cout << "Wrong Answers: " << total - correct << '\n';
    cout << "Total Marks: " << correct << "/" << total << '\n';
    cout << fixed << setprecision(2);
    cout << "Percentage: " << percentage << "%\n";

    if (percentage >= 80)
        cout << "Performance: Excellent!\n";
    else if (percentage >= 60)
        cout << "Performance: Good!\n";
    else if (percentage >= 40)
        cout << "Performance: Average\n";
    else
        cout << "Performance: Needs Improvement\n";

    cout << "====================================\n";

    saveResult(s, correct, total, percentage);
}

int main() {
    Student student;
    int choice;

    cout << "====================================\n";
    cout << "              COMPUTIQ\n";
    cout << " Computing Aptitude and Logical Reasoning\n";
    cout << "====================================\n";

    cout << "Enter Student Name: ";
    getline(cin, student.name);

    cout << "Enter Roll Number: ";
    getline(cin, student.rollNo);

    do {
        cout << "\n============= MAIN MENU =============\n";
        cout << "1. Computing Aptitude\n";
        cout << "2. Logical Reasoning\n";
        cout << "3. Mathematical Aptitude\n";
        cout << "4. Full Assessment\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        choice = getNumber();

        switch (choice) {
            case 1:
                startAssessment(student, computingQuestions);
                break;

            case 2:
                startAssessment(student, logicalQuestions);
                break;

            case 3:
                startAssessment(student, mathQuestions);
                break;

            case 4: {
                vector<Question> allQuestions;

                allQuestions.insert(allQuestions.end(),
                    computingQuestions.begin(),
                    computingQuestions.end());

                allQuestions.insert(allQuestions.end(),
                    logicalQuestions.begin(),
                    logicalQuestions.end());

                allQuestions.insert(allQuestions.end(),
                    mathQuestions.begin(),
                    mathQuestions.end());

                startAssessment(student, allQuestions);
                break;
            }

            case 5:
                cout << "\nThank you for using ComputIQ!\n";
                break;

            default:
                cout << "Invalid choice. Please select 1-5.\n";
        }

    } while (choice != 5);

    return 0;
}
