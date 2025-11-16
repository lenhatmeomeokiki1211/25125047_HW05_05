#include <iostream>
#include <fstream>
#include "Date.h"
using namespace std;




bool isLeap(int year) {
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) return true;
    else return false;
}


int daysInMonth(int month, int year) {
    if (month < 1 || month > 12) return 0;

    int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int d = days[month];

    if (month == 2 && isLeap(year)) {
        d = 29;
    }
    return d;
}




bool isValidDate(Date & d) {
    if (d.year < 1 || d.month < 1 || d.month > 12 || d.day < 1 ) return false;
    return d.day <= daysInMonth(d.month, d.year);
}

long long dateToDays(Date& d) {
    long long totalDays = 0;

    for (int y = 1; y < d.year; ++y) {
        totalDays += (isLeap(y) ? 366 : 365);
    }

    for (int m = 1; m < d.month; ++m) {
        totalDays += daysInMonth(m, d.year);
    }

    totalDays += d.day;
    return totalDays;
}
Date daysToDate(long long totalDays) {
    int y = 1;
    while (totalDays > (isLeap(y) ? 366 : 365)) {
        totalDays -= (isLeap(y) ? 366 : 365);
        y++;
    }

    int m = 1;
    while (totalDays > daysInMonth(m, y)) {
        totalDays -= daysInMonth(m, y);
        m++;
    }

    return { (int)totalDays, m, y };
}
   

void inputDate(Date& d) {
    cout << "Enter day: ";
    cin >> d.day;
    cout << "Enter month: ";
    cin >> d.month;
    cout << "Enter year: ";
    cin >> d.year;

    while (!isValidDate(d)) {
        cout << "Invalid date. Please re-enter: ";
        cin >> d.day >> d.month >> d.year;
    }
}

void outputDate( Date& d) {
    
    cout << d.day << "/" << d.month << "/" << d.year << endl;
}


//7

void findTomorrow(Date d) {
        Date next = d;
        next.day++;

        if (next.day > daysInMonth(next.month, next.year)) {
            next.day = 1;
            next.month++;
            if (next.month > 12) {
                next.month = 1;
                next.year++;
            }
        }
        cout << next.day << "/" << next.month << "/" << next.year;
    }
    //8
    void findYesterday(Date  d) {
        Date prev = d;
        prev.day--;

        if (prev.day < 1) {
            prev.month--;
            if (prev.month < 1) {
                prev.month = 12;
                prev.year--;
            }
            prev.day = daysInMonth(prev.month, prev.year);
        }
        cout << prev.day << "/" << prev.month << "/" << prev.year;
    }
    //9
    Date increaseDateByK(Date & d, int k) {
        long long totalDays = dateToDays(d);
        return daysToDate(totalDays + k);
    }
    //10
    Date decreaseDateByK(Date & d, int k) {
        long long totalDays = dateToDays(d);

        if (totalDays - k < 1) return { 1, 1, 1 };
        return daysToDate(totalDays - k);
    }


//11
int distanceToStartOfYear( Date& d) {
    int dayCount = 0;
    for (int m = 1; m < d.month; ++m) {
        dayCount += daysInMonth(m, d.year);
    }
    dayCount += d.day;
    return dayCount; 
}

//12
long long distanceToGiven( Date& d) {
    Date given = { 1, 1, 1970 };
    long long days_d = dateToDays(d);
    long long days_given = dateToDays(given);
    return days_d - days_given; 
}
//6
long long distanceBetweenDates( Date& d1,  Date& d2) {
    long long days_d1 = dateToDays(d1);
    long long days_d2 = dateToDays(d2);
    return abs(days_d1 - days_d2);
}

//14
int dayOfWeek( Date& d) {
    
    long long dist = distanceToGiven(d);

    
    int start = 4; 
    int day = (start + dist) % 7;
    if (day < 0) day += 7;
    
    return day;
}

int main() {
    Date d;
    inputDate(d); outputDate(d);

    ifstream fin; ofstream fout;

    fin.open("InputHW5.txt"); fout.open("OutputHW5.txt");

    fin >> d.day >> d.month >> d.year;
    fout << d.year << d.month << d.day;

    fin.close(); fout.close();

    Date d1, d2;
    cout << "Input 2 dates here: " << endl;

    inputDate(d1); inputDate(d2);
    cout << "Distance between 2 dates: " << distanceBetweenDates(d1, d2) << endl;

    findTomorrow(d); cout << endl;
    findYesterday(d); cout << endl;

    if (d1.year > d2.year) cout << "1st is later";
    else if (d1.year < d2.year) cout << "2nd is later";
    else {
        if (d1.month > d2.month) cout << "1st is later";
        else if (d1.month < d2.month) cout << "2nd is later";
        else {
            if (d1.day > d2.day) cout << "1st is later";
            else if (d1.day < d2.day) cout << "2nd is later";
            else cout << " U input the same date! ";
        }
    }
    cout << endl;

    cout << "Input k: "; int k; cin >> k;
    Date inc = increaseDateByK(d, k);
    Date dec = decreaseDateByK(d, k);

    cout << "Inc date by 1: " << inc.day << inc.month << inc.year << endl;
    cout << "Dec date by 1: " << dec.day << dec.month << dec.year << endl;

    cout <<"Distance to Start of the Year: " << distanceToStartOfYear(d) << endl;
    cout <<"Distance to Given Date: " << distanceToGiven(d) << endl;

    int b14 = dayOfWeek(d);
    switch (b14) {
    case 0: cout << " Sunday "; break;
    case 1: cout << " Monday "; break;
    case 2: cout << " Tuesday "; break;
    case 3: cout << " Wednesday "; break;
    case 4: cout << " Thursday "; break;
    case 5: cout << " Friday "; break;
    case 6: cout << " Saturday "; break;
    }
}