#include "Assigner.h"

using namespace std;

void Assigner::nullify_lunchbreaks(vector<int> * preferences, int LB_hour, int n_hours)
{
    for(int i = LB_hour; i < preferences->size(); i+=n_hours)
        preferences->at(i) = 0;
}

vector<int> Assigner::initialise_empty_timetable(int n_courses, int n_days, int n_hours)
{
    vector<int> tt;
    for(int i = 0; i < n_courses; i++)
        for(int j = 0; j < n_days*n_hours; j++)
            tt.at(i).at(j) = -1;
    return tt;
}

void Assigner::print_v(std::vector<int> v)
{
    for(int i = 0; i < v.size(); i++)
        cout << v.at(i) << ", ";
    cout << endl;
}

vector<int> Assigner::basic_timetable(InputSort input)
{
    vector<int> time_table = initialise_empty_timetable(input.n_courses, 5, 8);
    if(input.debug) print_v(time_table);

    
}
