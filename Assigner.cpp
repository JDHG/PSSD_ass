#include "Assigner.h"

using namespace std;

vector<vector<int> > Assigner::initialise_empty_timetable(int n_courses, int n_days, int n_hours)
{
    vector<vector<int> > tt;
    for(int i = 0; i < n_courses; i++)
    {
        vector<int> v;
        tt.push_back(v);
        for(int j = 0; j < n_days*n_hours; j++)
            tt.at(i).push_back(-1);
    }
    return tt;
}

void Assigner::basic_assign(InputSort input, vector<vector<int> > * time_table)
{
    for(int i = 0; i < input.courses.size(); i++) //for each course
    {
        Course c = input.courses.at(i);
        int hours_to_assign = c.hours;
        for(int j = 0; j < c.teachers.size(); j++) //for each assigned course teacher
        {
            Teacher t = c.teachers.at(j);
            for(int k = 0; k < t.preferences.size(); k++) //for each hour in teacher's preferences
            {
                vector<int> p = t.preferences;
                if(p.at(k) == 1 && hours_to_assign > 0)
                {
                    // i relative to courses[i]
                    time_table->at(i).at(k) = t.id;
                    hours_to_assign--;
                    if(hours_to_assign == 0) break;
                }
            }
        }
    }

    //cannot do more than 2 in a row

    //need to check room numbers

    //if unable to get hours with 1's - assign on 2's and then 5's


}

void Assigner::print_vec(std::vector<int> v)
{
    cout << "[ ";
    for(int i = 0; i < v.size()-1; i++)
        cout << v.at(i) << ", ";
    cout << v.back() << " ]" << endl;
}
void Assigner::print_twin_vec(std::vector<vector<int> > v)
{
    for(int i = 0; i < v.size(); i++)
        print_vec(v.at(i));
    cout << endl;
}

void Assigner::fatal(string error_message)
{
    cout << "Assigner :: fatal() -> " << error_message << endl;
    exit(1);
}

vector<vector<int> > Assigner::create_timetable(InputSort input)
{
    vector<vector<int> > time_table = initialise_empty_timetable(input.n_courses, 5, 8);

    //assign earliest valid timetable slots
    basic_assign(input, &time_table);

    if(input.debug) print_twin_vec(time_table);

    return time_table;
}
