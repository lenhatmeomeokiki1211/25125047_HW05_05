#include <iostream>  // For console input/output (cin, cout, endl)
#include <fstream>   // For file input/output (ifstream, ofstream)
#include <cstring>   // For C-style string functions (strcmp, strcpy, strlen)
#include <iomanip>   // For output formatting (setprecision, fixed)

// Using namespace as requested
using namespace std;

// --- Constants (using #define as 'const' is disallowed) ---
#define MAX_NAME 101
#define MAX_ADDRESS 201
#define MAX_ID 11

// --- Struct Definitions ---

// A simple struct to hold date components
struct DateOfBirth {
    int day;
    int month;
    int year;
};

// The main Student struct
struct Student {
    char id[MAX_ID];
    char fullName[MAX_NAME];
    double gpa;
    char address[MAX_ADDRESS];
    DateOfBirth dob;
};

// --- Helper Functions (for Name Parsing and Age) ---

/**
 * Helper to get the first word (First Name) from a full name.
 * Copies the first name into the 'firstName' output array.
 */
void GetFirstName(char fullName[], char firstName[]) {
    int i = 0;
    // Copy until the first space or the end of the string
    while (fullName[i] != ' ' && fullName[i] != '\0') {
        firstName[i] = fullName[i];
        i++;
    }
    firstName[i] = '\0'; // Add null terminator
}

/**
 * Helper to get the remaining words (Last Name) from a full name.
 * Copies the last name into the 'lastName' output array.
 */
void GetLastName(char fullName[], char lastName[]) {
    int i = 0; // Index for fullName
    int k = 0; // Index for lastName

    // 1. Find the first space
    while (fullName[i] != ' ' && fullName[i] != '\0') {
        i++;
    }

    // 2. If there is a space, start copying from the character *after* it
    if (fullName[i] == ' ') {
        i++; // Move past the space
        while (fullName[i] != '\0') {
            lastName[k] = fullName[i];
            i++;
            k++;
        }
    }
    // 3. Add null terminator. If no space was found, k is 0,
    //    so this creates an empty string.
    lastName[k] = '\0';
}

/**
 * Helper to get the number of days in a specific month and year.
 * Required for accurate age calculation.
 */
int daysInMonth(int month, int year) {
    if (month == 2) {
        // Leap year check
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return 29;
        }
        else {
            return 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else {
        return 31;
    }
}

/**
 * Helper to calculate and output age to a file stream.
 * Calculates age based on the current date of "November 16, 2025".
 */
void CalculateAndOutputAge(ofstream& file, DateOfBirth dob) {
    // Hardcoded "today" as per the context date (Nov 16, 2025)
    int todayDay = 16;
    int todayMonth = 11;
    int todayYear = 2025;

    int ageYears, ageMonths, ageDays;

    // Calculate initial differences
    ageYears = todayYear - dob.year;
    ageMonths = todayMonth - dob.month;
    ageDays = todayDay - dob.day;

    // Handle "borrowing" for days
    if (ageDays < 0) {
        ageMonths--; // Borrow from months
        // Get days in the *previous* month
        int prevMonth = (todayMonth - 1);
        int prevMonthYear = todayYear;
        if (prevMonth == 0) { // Handle January borrowing
            prevMonth = 12;
            prevMonthYear--;
        }
        ageDays += daysInMonth(prevMonth, prevMonthYear);
    }

    // Handle "borrowing" for months
    if (ageMonths < 0) {
        ageYears--; // Borrow from years
        ageMonths += 12; // Add 12 months
    }

    file << "Age: " << ageYears << " years, " << ageMonths << " months, " << ageDays << " days" << endl;
}

// --- Required Functions (1-12) ---

/**
 * 1. Input a student (from console).
 * We return the struct by value to avoid pointers/references.
 */
Student InputStudentFromConsole() {
    Student s;

    cout << "Enter ID (max 10 chars): ";
    cin.getline(s.id, MAX_ID);

    cout << "Enter Full Name: ";
    cin.getline(s.fullName, MAX_NAME);

    cout << "Enter GPA: ";
    cin >> s.gpa;
    cin.ignore(1000, '\n'); // Consume the leftover newline

    cout << "Enter Address: ";
    cin.getline(s.address, MAX_ADDRESS);

    cout << "Enter Date of Birth (dd mm yyyy): ";
    cin >> s.dob.day >> s.dob.month >> s.dob.year;
    cin.ignore(1000, '\n'); // Consume the leftover newline

    return s;
}

/**
 * 2. Output a student (to console).
 * We pass the struct by value (a copy is made).
 */
void OutputStudentToConsole(Student s) {
    cout << "--- Student Information ---" << endl;
    cout << "ID: " << s.id << endl;
    cout << "Full Name: " << s.fullName << endl;
    cout << "GPA: " << fixed << setprecision(2) << s.gpa << endl;
    cout << "Address: " << s.address << endl;
    cout << "Date of Birth: " << s.dob.day << "/" << s.dob.month << "/" << s.dob.year << endl;
    cout << "---------------------------" << endl;
}

/**
 * 3. Input a student (from text file).
 * We must pass the file stream by reference to read sequentially.
 * This assumes a multi-line format per student, matching the console input.
 */
Student InputStudentFromFile(ifstream& file) {
    Student s;

    file.getline(s.id, MAX_ID);
    file.getline(s.fullName, MAX_NAME);
    file >> s.gpa;
    file.ignore(1000, '\n'); // Consume newline
    file.getline(s.address, MAX_ADDRESS);
    file >> s.dob.day >> s.dob.month >> s.dob.year;
    file.ignore(1000, '\n'); // Consume newline

    return s;
}

/**
 * 4. Output a student: id, full name, gpa, address, dob (to text file).
 */
void OutputStudentToFile(ofstream& file, Student s) {
    file << s.id << endl;
    file << s.fullName << endl;
    file << fixed << setprecision(2) << s.gpa << endl;
    file << s.address << endl;
    file << s.dob.day << "/" << s.dob.month << "/" << s.dob.year << endl;
}

/**
 * 5. Output a student: id, first name, last name, gpa, address,
 * dob, age (to text file).
 */
void OutputStudentDetailedToFile(ofstream& file, Student s) {
    char firstName[MAX_NAME];
    char lastName[MAX_NAME];

    GetFirstName(s.fullName, firstName);
    GetLastName(s.fullName, lastName);

    file << "ID: " << s.id << endl;
    file << "First Name: " << firstName << endl;
    file << "Last Name: " << lastName << endl;
    file << "GPA: " << fixed << setprecision(2) << s.gpa << endl;
    file << "Address: " << s.address << endl;
    file << "DOB: " << s.dob.day << "/" << s.dob.month << "/" << s.dob.year << endl;

    // Call the helper to calculate and output age
    CalculateAndOutputAge(file, s.dob);
}

/**
 * 6. Extract the class of input student (to text file).
 * Example: 19127001 -> K19
 */
void OutputStudentClass(ofstream& file, Student s) {
    // Check if ID has at least 2 characters
    if (strlen(s.id) >= 2) {
        file << "Class: K" << s.id[0] << s.id[1] << endl;
    }
    else {
        file << "Class: K_INVALID_ID" << endl;
    }
}

/**
 * 7. Compare 2 students by id.
 * Returns:
 * < 0 if s1.id < s2.id
 * 0 if s1.id == s2.id
 * > 0 if s1.id > s2.id
 */
int CompareByID(Student s1, Student s2) {
    return strcmp(s1.id, s2.id);
}

/**
 * 8. Compare 2 students by gpa, and then by id.
 * Sorts by GPA descending (higher is better), then ID ascending.
 * Returns:
 * < 0 if s1 comes *before* s2
 * > 0 if s1 comes *after* s2
 * 0 if they are identical (for this comparison)
 */
int CompareByGPAAndID(Student s1, Student s2) {
    if (s1.gpa > s2.gpa) {
        return -1; // s1 comes first (is "lesser")
    }
    else if (s1.gpa < s2.gpa) {
        return 1;  // s1 comes second (is "greater")
    }
    else {
        // GPAs are equal, compare by ID ascending
        return strcmp(s1.id, s2.id);
    }
}

/**
 * 9. Compare 2 students by name, and then by id.
 * Sorts by Full Name ascending, then ID ascending.
 */
int CompareByNameAndID(Student s1, Student s2) {
    int nameCompare = strcmp(s1.fullName, s2.fullName);
    if (nameCompare != 0) {
        return nameCompare;
    }
    else {
        // Names are equal, compare by ID
        return strcmp(s1.id, s2.id);
    }
}

/**
 * 10. Compare 2 students by first name, and then by id.
 */
int CompareByFirstNameAndID(Student s1, Student s2) {
    char firstName1[MAX_NAME];
    char firstName2[MAX_NAME];
    GetFirstName(s1.fullName, firstName1);
    GetFirstName(s2.fullName, firstName2);

    int nameCompare = strcmp(firstName1, firstName2);
    if (nameCompare != 0) {
        return nameCompare;
    }
    else {
        return strcmp(s1.id, s2.id);
    }
}

/**
 * 11. Compare 2 students by last name, and then by id.
 */
int CompareByLastNameAndID(Student s1, Student s2) {
    char lastName1[MAX_NAME];
    char lastName2[MAX_NAME];
    GetLastName(s1.fullName, lastName1);
    GetLastName(s2.fullName, lastName2);

    int nameCompare = strcmp(lastName1, lastName2);
    if (nameCompare != 0) {
        return nameCompare;
    }
    else {
        return strcmp(s1.id, s2.id);
    }
}

/**
 * 12. Compare 2 students by dob, and then by id.
 * Sorts by DOB ascending (older students first).
 */
int CompareByDOBAndID(Student s1, Student s2) {
    // Compare Year
    if (s1.dob.year < s2.dob.year) return -1;
    if (s1.dob.year > s2.dob.year) return 1;

    // Years are equal, compare Month
    if (s1.dob.month < s2.dob.month) return -1;
    if (s1.dob.month > s2.dob.month) return 1;

    // Months are equal, compare Day
    if (s1.dob.day < s2.dob.day) return -1;
    if (s1.dob.day > s2.dob.day) return 1;

    // DOBs are equal, compare by ID
    return strcmp(s1.id, s2.id);
}


// --- Main Function (for Demonstration) ---



int main() {
    cout << "--- Part 1 & 2: Console I/O ---" << endl;
    // 1. Input a student (from console)
    Student s1 = InputStudentFromConsole();
    // 2. Output a student (to console)
    OutputStudentToConsole(s1);

    cout << "\n--- Part 4: Basic File Output ---" << endl;
    // 4. Output a student (to text file)
    ofstream outFile("student.txt");
    if (outFile.is_open()) {
        OutputStudentToFile(outFile, s1);
        outFile.close();
        cout << "Wrote basic data to student.txt" << endl;
    }
    else {
        cout << "Error: Could not open student.txt for writing." << endl;
    }

    cout << "\n--- Part 3: Basic File Input ---" << endl;
    // 3. Input a student (from text file)
    Student s2;
    ifstream inFile("student.txt");
    if (inFile.is_open()) {
        s2 = InputStudentFromFile(inFile);
        inFile.close();
        cout << "Read student from student.txt. Verifying:" << endl;
        OutputStudentToConsole(s2); // Show what we read
    }
    else {
        cout << "Error: Could not open student.txt for reading." << endl;
    }

    cout << "\n--- Part 5 & 6: Detailed File Output ---" << endl;
    // 5. Output detailed student info (to text file)
    // 6. Output class info (to text file)
    ofstream detailFile("detailed.txt");
    if (detailFile.is_open()) {
        OutputStudentDetailedToFile(detailFile, s1);
        detailFile << "---" << endl;
        OutputStudentClass(detailFile, s1);
        detailFile.close();
        cout << "Wrote detailed data and class to detailed.txt" << endl;
    }
    else {
        cout << "Error: Could not open detailed.txt for writing." << endl;
    }

    cout << "\n--- Part 7-12: Comparison Functions ---" << endl;
    // Create a new student s3 to make comparisons interesting.
    // This is the part that uses the "safer" strncpy.
    Student s3;

    // --- SAFER C-STRING COPY ---
    // Copy (max_size - 1) chars, then manually set the last char to '\0'
    // This guarantees no buffer overflow AND ensures null-termination.

    strncpy(s3.id, "19127002", MAX_ID - 1);
    s3.id[MAX_ID - 1] = '\0';

    strncpy(s3.fullName, "Jane Doe", MAX_NAME - 1);
    s3.fullName[MAX_NAME - 1] = '\0';

    s3.gpa = 3.5;

    strncpy(s3.address, "456 Other St", MAX_ADDRESS - 1);
    s3.address[MAX_ADDRESS - 1] = '\0';

    s3.dob.day = 15;
    s3.dob.month = 5;
    s3.dob.year = 2001;
    // --- END SAFER COPY ---


    cout << "Comparing " << s1.fullName << " and " << s3.fullName << ":" << endl;
    // 7. Compare by ID
    cout << "Compare by ID: " << CompareByID(s1, s3) << endl;
    // 8. Compare by GPA
    cout << "Compare by GPA/ID: " << CompareByGPAAndID(s1, s3) << endl;
    // 9. Compare by Full Name
    cout << "Compare by Name/ID: " << CompareByNameAndID(s1, s3) << endl;
    // 10. Compare by First Name
    cout << "Compare by First Name/ID: " << CompareByFirstNameAndID(s1, s3) << endl;
    // 11. Compare by Last Name
    cout << "Compare by Last Name/ID: " << CompareByLastNameAndID(s1, s3) << endl;
    // 12. Compare by DOB
    cout << "Compare by DOB/ID: " << CompareByDOBAndID(s1, s3) << endl;

    return 0;
}