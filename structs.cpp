#ifndef STRUCTS_CPP
#define STRUCTS_CPP

#include "structs.h"

using namespace std;
// struct Teacher
// {
//     std::string name;
//     std::vector<int> preferences;
// };
// struct Course
// {
//     int hours;
//     std::string name;
//     std::vector<Teacher> teachers;
// };


Course::Course(int h, string n)
{
    name = n; hours = h;
}

void Course::print()
{
    cout <<     "\n    Printing course      ::" << endl;
    cout <<     "        name             :: " << name << endl;
    cout <<     "        hours            :: " << hours << endl;
    cout <<     "        teachers         :: ";
    for(Teacher teacher : teachers)
        teacher.print();
    cout << endl;
}

Teacher::Teacher(vector<int> prefs, string n)
{
    preferences = prefs; name = n;
}

void Teacher::print()
{                   //   Printing course      ::"
    cout <<     "\n\n        Printing teacher     ::" << endl;
    cout <<     "            name             :: " << name << endl;
    cout <<     "            preferences      :: ";
    for(int preference : preferences)
        cout << preference << ",";
    cout << endl;
}

#endif
