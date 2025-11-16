#ifndef STUDENT_H
#define STUDENT_H
struct Date {
    int day;
    int month;
    int year;
};
struct Student {
    char id[100];
    char fullName[100];
    float gpa;
    char address[100];
    Date dob;
};
#endif
