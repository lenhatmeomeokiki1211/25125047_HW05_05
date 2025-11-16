#include <iostream>
#include <fstream> 
using namespace std;


int my_strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}


int my_strcmp(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i]) return -1;
        if (s1[i] > s2[i]) return 1;
        i++;
    }
  
    if (s1[i] == '\0' && s2[i] == '\0') return 0;
    if (s1[i] == '\0') return -1; 
    return 1; 
}


#define MAX_LEN 101
#define ID_LEN 11


struct Date {
    int day;
    int month;
    int year;
};

struct Student {
    char id[ID_LEN];
    char fullName[MAX_LEN];
    double gpa;
    char address[MAX_LEN];
    Date dob;
};


void inputStudentConsole(Student& s) {
    cout << "Enter ID: ";
    cin.getline(s.id, ID_LEN);

    cout << "Enter Full Name: ";
    cin.getline(s.fullName, MAX_LEN);

    cout << "Enter GPA: ";
    cin >> s.gpa;
    
    cin.ignore(1000, '\n');

    cout << "Enter Address: ";
    cin.getline(s.address, MAX_LEN);

    cout << "Enter Date of Birth (dd mm yyyy): ";
    cin >> s.dob.day >> s.dob.month >> s.dob.year;
    
    cin.ignore(1000, '\n');
}


void outputStudentConsole(Student s) {
    cout << "--- Student Info ---" << endl;
    cout << "ID: " << s.id << endl;
    cout << "Full Name: " << s.fullName << endl;
    cout << "GPA: " << s.gpa << endl;
    cout << "Address: " << s.address << endl;
    cout << "Date of Birth: " << s.dob.day << "/" << s.dob.month << "/" << s.dob.year << endl;
}

void inputStudentFile(ifstream& fin, Student& s) {
    fin.getline(s.id, ID_LEN);
    fin.getline(s.fullName, MAX_LEN);

    fin >> s.gpa;
    fin.ignore(1000, '\n'); 

    fin.getline(s.address, MAX_LEN);

    fin >> s.dob.day >> s.dob.month >> s.dob.year;
    fin.ignore(1000, '\n'); 
}


void outputStudentFile(ofstream& fout, Student s) {
    fout << s.id << endl;
    fout << s.fullName << endl;
    fout << s.gpa << endl;
    fout << s.address << endl;
    fout << s.dob.day << " " << s.dob.month << " " << s.dob.year << endl;
}


bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    if (month == 2) {
        return isLeap(year) ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else {
        return 31;
    }
}


void outputStudentAdvanced(ofstream& fout, Student s) {
    
    char firstName[MAX_LEN];
    char lastName[MAX_LEN];
    int i = 0;
    int j = 0;

   
    while (s.fullName[i] != '\0' && s.fullName[i] != ' ') {
        firstName[i] = s.fullName[i];
        i++;
    }
    firstName[i] = '\0'; 

    
    if (s.fullName[i] == ' ') {
        i++;
    }

    
    while (s.fullName[i] != '\0') {
        lastName[j] = s.fullName[i];
        i++;
        j++;
    }
    lastName[j] = '\0'; 

    
    Date today = { 16, 11, 2025 }; 

    int years, months, days;
    years = today.year - s.dob.year;
    months = today.month - s.dob.month;
    days = today.day - s.dob.day;

    
    if (days < 0) {
        months--;
        int prevMonth = (today.month == 1) ? 12 : today.month - 1;
        int prevMonthYear = (today.month == 1) ? today.year - 1 : today.year;
        days += daysInMonth(prevMonth, prevMonthYear);
    }

    
    if (months < 0) {
        years--;
        months += 12;
    }

    
    fout << "--- Advanced Student Report ---" << endl;
    fout << "ID: " << s.id << endl;
    fout << "First Name: " << firstName << endl;
    fout << "Last Name: " << lastName << endl;
    fout << "GPA: " << s.gpa << endl;
    fout << "Address: " << s.address << endl;
    fout << "DOB: " << s.dob.day << "/" << s.dob.month << "/" << s.dob.year << endl;
    fout << "Age: " << years << " years, " << months << " months, " << days << " days" << endl;
}


void outputStudentClass(ofstream& fout, Student s) {
   
    if (my_strlen(s.id) >= 2) {
        fout << "Student " << s.id << " is in class K" << s.id[0] << s.id[1] << endl;
    }
    else {
        fout << "Student " << s.id << " ID is too short to extract class." << endl;
    }
}


int compareByID(Student s1, Student s2) {
    return my_strcmp(s1.id, s2.id);
}


int compareByGPA(Student s1, Student s2) {
    if (s1.gpa < s2.gpa) return -1;
    if (s1.gpa > s2.gpa) return 1;
   
    return my_strcmp(s1.id, s2.id);
}


int compareByName(Student s1, Student s2) {
    int nameCmp = my_strcmp(s1.fullName, s2.fullName);
    if (nameCmp != 0) {
        return nameCmp;
    }
    return my_strcmp(s1.id, s2.id);
}


void getFirstName(char dest[], char fullName[]) {
    int i = 0;
    while (fullName[i] != '\0' && fullName[i] != ' ') {
        dest[i] = fullName[i];
        i++;
    }
    dest[i] = '\0';
}

void getLastName(char dest[], char fullName[]) {
    int i = 0;
    int j = 0;
    while (fullName[i] != '\0' && fullName[i] != ' ') {
        i++;
    }
    if (fullName[i] == ' ') {
        i++;
    }
    while (fullName[i] != '\0') {
        dest[j] = fullName[i];
        i++;
        j++;
    }
    dest[j] = '\0';
}


int compareByFirstName(Student s1, Student s2) {
    char firstName1[MAX_LEN];
    char firstName2[MAX_LEN];
    getFirstName(firstName1, s1.fullName);
    getFirstName(firstName2, s2.fullName);

    int nameCmp = my_strcmp(firstName1, firstName2);
    if (nameCmp != 0) {
        return nameCmp;
    }
    return my_strcmp(s1.id, s2.id);
}


int compareByLastName(Student s1, Student s2) {
    char lastName1[MAX_LEN];
    char lastName2[MAX_LEN];
    getLastName(lastName1, s1.fullName);
    getLastName(lastName2, s2.fullName);

    int nameCmp = my_strcmp(lastName1, lastName2);
    if (nameCmp != 0) {
        return nameCmp;
    }
    return my_strcmp(s1.id, s2.id);
}


int compareByDOB(Student s1, Student s2) {
   
    if (s1.dob.year < s2.dob.year) return -1;
    if (s1.dob.year > s2.dob.year) return 1;

    if (s1.dob.month < s2.dob.month) return -1;
    if (s1.dob.month > s2.dob.month) return 1;

   
    if (s1.dob.day < s2.dob.day) return -1;
    if (s1.dob.day > s2.dob.day) return 1;

    return my_strcmp(s1.id, s2.id);
}



int main() {
    Student s1, s2;

   
    cout << "--- Input Student 1 ---" << endl;
    inputStudentConsole(s1);
    cout << endl;
    outputStudentConsole(s1);
    cout << endl;

    ofstream fout;
    fout.open("student_output.txt");
    if (fout.is_open()) {
        cout << "Writing to student_output.txt..." << endl;

       
        outputStudentFile(fout, s1);

       
        fout << endl; 
        outputStudentAdvanced(fout, s1);

       
        fout << endl; 
        outputStudentClass(fout, s1);

        fout.close();
        cout << "File writing complete." << endl;
    }
    else {
        cout << "Error: Could not open file for writing." << endl;
    }
    cout << endl;

    cout << "--- Input Student 2 (for comparison) ---" << endl;
    inputStudentConsole(s2);
    cout << endl;

    int gpaComparison = compareByGPA(s1, s2);
    cout << "--- GPA Comparison (s1 vs s2) ---" << endl;
    if (gpaComparison < 0) {
        cout << "Student 1 has a lower GPA than Student 2 (or same GPA and lower ID)." << endl;
    }
    else if (gpaComparison > 0) {
        cout << "Student 1 has a higher GPA than Student 2 (or same GPA and higher ID)." << endl;
    }
    else {
        cout << "Students have the same GPA and ID." << endl;
    }

    return 0;
}