#include "structs.h"

using namespace std;

Teacher::Teacher(vector<int> prefs, string n, int id_)
{
    preferences = prefs; name = n; id = id_;
}

void Teacher::print()
{                   //   Printing course      ::"
    cout <<     "\n\n        Printing teacher     :: " << id << endl;
    cout <<     "            name             :: " << name << endl;
    cout <<     "            preferences      :: ";
    for(int preference : preferences)
        cout << preference << ",";
    cout << endl;
}

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
