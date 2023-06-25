//Author: Nathan Johnson
//Date: June 18th, 2023

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

vector<Course> courseData;

void loadDataStructure(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Course course;
        size_t pos = line.find(",");
        if (pos == string::npos) {
            cout << "Invalid line format: " << line << endl;
            continue;
        }
        course.courseNumber = line.substr(0, pos);
        line = line.substr(pos + 1);

        pos = line.find(",");
        if (pos == string::npos) {
            course.courseTitle = line;
        }
        else {
            course.courseTitle = line.substr(0, pos);
            line = line.substr(pos + 1);
            pos = line.find(",");
            while (pos != string::npos) {
                course.prerequisites.push_back(line.substr(0, pos));
                line = line.substr(pos + 1);
                pos = line.find(",");
            }
            course.prerequisites.push_back(line);
        }

        courseData.push_back(course);
    }

    file.close();
}

void printCourseList() {
    vector<string> courseNumbers;
    for (const auto& course : courseData) {
        courseNumbers.push_back(course.courseNumber);
    }
    sort(courseNumbers.begin(), courseNumbers.end());

    cout << "Here is a sample schedule:" << endl;
    for (const auto& courseNumber : courseNumbers) {
        for (const auto& course : courseData) {
            if (course.courseNumber == courseNumber) {
                cout << course.courseNumber << ", " << course.courseTitle << endl;
                break;
            }
        }
    }
    cout << endl;
}

void printCourse(const string& courseNumber) {
    string lowercaseCourseNumber = courseNumber;
    transform(lowercaseCourseNumber.begin(), lowercaseCourseNumber.end(), lowercaseCourseNumber.begin(), ::tolower);
    for (const auto& course : courseData) {
        if (course.courseNumber == lowercaseCourseNumber) {
            cout << course.courseNumber << ", " << course.courseTitle << endl;
            if (!course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (size_t i = 0; i < course.prerequisites.size(); i++) {
                    cout << course.prerequisites[i];
                    if (i != course.prerequisites.size() - 1)
                        cout << ", ";
                }
                cout << endl;
            }
            cout << endl;
            return;
        }
    }
    cout << "Course not found: " << courseNumber << endl << endl;
}

int main() {
    cout << "Welcome to the course planner." << endl;

    while (true) {
        int choice;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you         like to do? ";
        cin >> choice;
        cout << endl;

        if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
            break;
        }
        else if (choice == 1) {
            string filename;
            cout << "Enter the file name that contains the course data: ";
            cin >> filename;
            cout << endl;
            loadDataStructure(filename);
        }
        else if (choice == 2) {
            printCourseList();
        }
        else if (choice == 3) {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            cout << endl;
            printCourse(courseNumber);
        }
        else {
            cout << choice << " is not a valid option." << endl << endl;
        }
    }

    return 0;
}