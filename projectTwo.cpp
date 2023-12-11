//============================================================================
// Name        : HashTable.cpp
// Author      : Joseph J. Les
// Version     : 1.0
// Description : C++
//============================================================================

#include <iostream>
#include <time.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

// Gloal variables to store filename and course number
string filename;
string courseNumber;

// Class to represent a course with its number, title, and prerequisites
class Course {
	public:
		string courseNumber;
		string courseTitle;
		vector<string> prerequisites;
};

// Hash table to store courses with course number as the key
unordered_map<string, Course> courses;

// Function to load course data from a file
void loadCourseData(const string& filename) {

	ifstream file(filename);
	// Check if file is open, if not open display error message
	if (!file.is_open()) {
		cerr << "Error opening file: " << filename << endl;
		return;
	}

	string line;

	// Read each line from the file
	while (getline(file, line)) {
		stringstream ss(line);
		string courseNumer, courseTitle, prerequisite;
		getline(ss, courseNumber, ',');

		Course newCourse;
		newCourse.courseNumber = courseNumber;

		getline(ss, courseTitle, ',');
		newCourse.courseTitle = courseTitle;

		// read prerequisites
		while (getline(ss, prerequisite, ',')) {
			newCourse.prerequisites.push_back(prerequisite);
		}

		// Store the course in the has table
		courses[courseNumber] = newCourse;
	}
}

// Function to print information of a specific course
void printCourseInformation(const string& courseNumber) {

	// CHeck if course exists in the hash table
	if (courses.find(courseNumber) != courses.end()) {
		Course course = courses[courseNumber];
		cout << course.courseTitle << endl;
		cout << "Prerequisites: ";
		for (const auto& prerequisite : course.prerequisites) {
			cout << prerequisite << ", ";
		}
		cout << endl;
	}
	else {
		cout << "Course not found." << endl;
	}
}

// Function to print a sorted list of all courses
void printSortedCourseList() {

	vector<string> courseNumbers;
	// Extract course numbers
	for (const auto& pair : courses) {
		courseNumbers.push_back(pair.first);
	}

	// Sort course numbers
	sort(courseNumbers.begin(), courseNumbers.end());

	// Print course details in sorted order
	for (const auto& courseNumber : courseNumbers) {
		const Course& course = courses[courseNumber];
		cout << course.courseNumber << ", " << course.courseTitle << endl;
	}
}

// Function to display the menu options
void printMenu() {
	cout << endl;
	cout << "1. Load Data Structure" << endl;
	cout << "2. Print Course List" << endl;
	cout << "3. Print Course" << endl;
	cout << "9. Exit" << endl;
	cout << "" << endl;
	cout << "What would you like to do? ";
}

// Main menu function to handle user interactions
void mainMenu() {
	while (true) {
		printMenu();
		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			// Ask for filename and load course data
			cout << "Enter file name: ";
			cin >> filename;
			loadCourseData(filename);
			break;
		case 2:
			// Print the sorted list of courses
			cout << endl;
			printSortedCourseList();
			break;
		case 3:
			// Prompt for course numer and print course information
			cout << "What course do you want to know about? ";
			cin >> courseNumber;

			// converts each character to upper case
			for (char& c : courseNumber) {
				c = toupper(c);
			}

			printCourseInformation(courseNumber);
			break;
		case 9:
			// Exit program
			cout << "Thank you for using the course planner!";
			return;
		default:
			cout << choice << " is not a vallid option." << endl;
		}
	}
}

// Main function
int main() {
	cout << "Welcome to the course planner." << endl;
	mainMenu();
	return 0;
}