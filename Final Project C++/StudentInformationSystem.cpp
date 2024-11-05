#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Student {
public:
    string firstName, lastName;
    int studentNumber;
    double midterm1, midterm2, finalExam;
    static double weightMidterm1, weightMidterm2, weightFinal;

    Student(string fName, string lName, int sNumber, double m1, double m2, double final)
        : firstName(fName), lastName(lName), studentNumber(sNumber), midterm1(m1), midterm2(m2), finalExam(final) {}

    double calculateAverage() const {
        return (midterm1 * weightMidterm1) + (midterm2 * weightMidterm2) + (finalExam * weightFinal);
    }

    char calculateLetterGrade() const {
        double avg = calculateAverage();
        if (avg >= 90) return 'A';
        if (avg >= 80) return 'B';
        if (avg >= 70) return 'C';
        if (avg >= 60) return 'D';
        return 'F';
    }
};

double Student::weightMidterm1 = 0.25;
double Student::weightMidterm2 = 0.25;
double Student::weightFinal = 0.50;

vector<Student> students;

void addStudent() {
    string firstName, lastName;
    int studentNumber;
    double midterm1, midterm2, finalExam;

    cout << "Enter First Name: "; cin >> firstName;
    cout << "Enter Last Name: "; cin >> lastName;
    cout << "Enter Student Number: "; cin >> studentNumber;
    cout << "Enter Grade for Midterm 1: "; cin >> midterm1;
    cout << "Enter Grade for Midterm 2: "; cin >> midterm2;
    cout << "Enter Grade for Final: "; cin >> finalExam;

    students.emplace_back(firstName, lastName, studentNumber, midterm1, midterm2, finalExam);
    cout << "Student added successfully.\n";
}

void displayAllStudents() {
    for (const auto& student : students) {
        cout << student.firstName << " " << student.lastName
            << " (" << student.studentNumber << ") - Grade: " << student.calculateLetterGrade()
            << " (Avg: " << student.calculateAverage() << ")\n";
    }
}

void sortStudents() {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.lastName == b.lastName ? a.firstName < b.firstName : a.lastName < b.lastName;
        });
    cout << "Students sorted by last name.\n";
}

void calculateAllGrades() {
    for (const auto& student : students) {
        cout << student.firstName << " " << student.lastName << ": "
            << student.calculateLetterGrade() << " (Avg: " << student.calculateAverage() << ")\n";
    }
}

void printStudent(int studentNumber) {
    for (const auto& student : students) {
        if (student.studentNumber == studentNumber) {
            cout << "Name: " << student.firstName << " " << student.lastName << endl;
            cout << "Student Number: " << student.studentNumber << endl;
            cout << "Grades - Midterm 1: " << student.midterm1
                << ", Midterm 2: " << student.midterm2
                << ", Final: " << student.finalExam << endl;
            cout << "Average: " << student.calculateAverage()
                << ", Letter Grade: " << student.calculateLetterGrade() << endl;
            return;
        }
    }
    cout << "Student not found.\n";
}

void modifyStudent(int studentNumber) {
    for (auto& student : students) {
        if (student.studentNumber == studentNumber) {
            cout << "Modifying data for " << student.firstName << " " << student.lastName << " (Student Number: " << student.studentNumber << ")\n";
            cout << "Enter New First Name: "; cin >> student.firstName;
            cout << "Enter New Last Name: "; cin >> student.lastName;
            cout << "Enter New Grade for Midterm 1: "; cin >> student.midterm1;
            cout << "Enter New Grade for Midterm 2: "; cin >> student.midterm2;
            cout << "Enter New Grade for Final: "; cin >> student.finalExam;
            cout << "Student data updated successfully.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void removeStudent(int studentNumber) {
    students.erase(remove_if(students.begin(), students.end(), [studentNumber](const Student& student) {
        return student.studentNumber == studentNumber;
        }), students.end());
    cout << "Student removed.\n";
}

void deleteAllStudents() {
    students.clear();
    cout << "All student data deleted.\n";
}

void setGradeWeights(double wMid1, double wMid2, double wFinal) {
    if (wMid1 + wMid2 + wFinal == 1.0) {
        Student::weightMidterm1 = wMid1;
        Student::weightMidterm2 = wMid2;
        Student::weightFinal = wFinal;
        cout << "Grading scheme updated.\n";
    }
    else {
        cout << "Error: Weights must add up to 1.0.\n";
    }
}

void showMenu() {
    cout << "\nStudent Information System Menu:\n";
    cout << "1. Print all student data\n";
    cout << "2. Sort the list of students in alphabetical order of last name\n";
    cout << "3. Add a new student\n";
    cout << "4. Calculate the letter grade of all students\n";
    cout << "5. Change the information of a previous student\n";
    cout << "6. Print the data of a specific student\n";
    cout << "7. Remove a student from the list\n";
    cout << "8. Delete all student data\n";
    cout << "9. Change grading scheme\n";
    cout << "10. Exit\n";
}

int main() {
    char changeScheme;
    cout << "The following grading scheme is used for calculating letter grades:\n";
    cout << "Midterm 1: 25%, Midterm 2: 25%, Final: 50%\n";
    cout << "Do you want to change the grading scheme? (y/n): ";
    cin >> changeScheme;

    if (changeScheme == 'y' || changeScheme == 'Y') {
        double wMid1, wMid2, wFinal;
        cout << "Enter weight for Midterm 1: ";
        cin >> wMid1;
        cout << "Enter weight for Midterm 2: ";
        cin >> wMid2;
        cout << "Enter weight for Final: ";
        cin >> wFinal;
        setGradeWeights(wMid1, wMid2, wFinal);
    }

    int choice, studentNumber;
    while (true) {
        showMenu();
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayAllStudents();
            break;
        case 2:
            sortStudents();
            displayAllStudents();
            break;
        case 3:
            addStudent();
            break;
        case 4:
            calculateAllGrades();
            break;
        case 5:
            cout << "Enter Student Number to Modify: ";
            cin >> studentNumber;
            modifyStudent(studentNumber);
            break;
        case 6:
            cout << "Enter Student Number to Print: ";
            cin >> studentNumber;
            printStudent(studentNumber);
            break;
        case 7:
            cout << "Enter Student Number to Remove: ";
            cin >> studentNumber;
            removeStudent(studentNumber);
            break;
        case 8:
            deleteAllStudents();
            break;
        case 9:
            double wMid1, wMid2, wFinal;
            cout << "Enter weight for Midterm 1: ";
            cin >> wMid1;
            cout << "Enter weight for Midterm 2: ";
            cin >> wMid2;
            cout << "Enter weight for Final: ";
            cin >> wFinal;
            setGradeWeights(wMid1, wMid2, wFinal);
            break;
        case 10:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
