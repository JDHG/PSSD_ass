#include "Assigner.h"

using namespace std;

vector<vector<int> > Assigner::initialise_empty_timetable(int n_courses, int n_days, int n_hours)
{
    if(db) cout << "Assigner :: initialise_empty_timetable" << endl;
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

bool Assigner::room_available(int n_rooms, int current_hour, int incoming_teacher_id, vector<vector<int> > time_table)
{
    if(db) cout << "Assigner :: room_available" << endl;
    unsigned short rooms_in_use = 0;
    for(int i = 0; i < time_table.size(); i++)
    {
        int target_hour = time_table.at(i).at(current_hour);
        if(target_hour >= 0) rooms_in_use++;
        if(rooms_in_use >= n_rooms || target_hour == incoming_teacher_id) return false;
    }
    return true;
}

bool Assigner::day_available(int hours_per_day, std::vector<int> tt_slot, int current_hour)
{
    if(db) cout << "Assigner :: day_available" << endl;
    //get hour boundaries of day containing 'current_hour'
    int day_start = (current_hour / hours_per_day) * hours_per_day;
    int day_end = day_start + hours_per_day;

    for(int i = day_start; i < day_end; i++)
        if(tt_slot.at(i) >= 0)
        {
            // if(++i < tt_slot.size())
            // {
                if(tt_slot.at(++i) < 0 && i == current_hour) return true; //allow 2-hour session assignment
                else return false; //day has a session allocated already
            // }
        }
    return true; //all hours are available for this course on this day
}

bool Assigner::permitted(int preference_val, vector<int> permitted_LP_values)
{
    if(db) cout << "Assigner :: permitted" << endl;
    for(int p : permitted_LP_values) if(preference_val == p) return true;
    return false;
}

void Assigner::basic_assign(InputSort input, vector<vector<int> > * time_table, int n_rooms, vector<int> permitted_LP_values, int hours_per_day)
{
    if(db) cout << "Assigner :: basic_assign" << endl;
    for(int i = 0; i < input.courses.size(); i++) //for each course
    {
        Course c = input.courses.at(i);
        int hours_to_assign = c.hours;

        for(int j = 0; j < c.teachers.size(); j++) //for each assigned course teacher
        {
            Teacher t = c.teachers.at(j);
            for(int k = 0; k < t.preferences.size(); k++) //for each hour in teacher's preferences
            {
                if(day_available(hours_per_day, time_table->at(i), k))
                {
                    vector<int> p = t.preferences;
                    if(permitted(p.at(k), permitted_LP_values) && hours_to_assign > 0)
                    {
                        if(room_available(input.n_rooms, k, t.id, *time_table))
                        {
                            time_table->at(i).at(k) = t.id; //write teacher's id to time_table[i][k]
                            hours_to_assign--;
                            if(hours_to_assign == 0) break;
                        }
                    }
                }
                else while(k%hours_per_day != hours_per_day-1) k++; //proceed to next day if unavailable
            }
        }
    }
}

//debug printer formatting
void Assigner::print_time_table_debug(vector<int> v, char neg_replace, int hours_per_day)
{
    // if(db) cout << "Assigner :: print_time_table_debug" << endl;
    cout << "[ ";
    for(int i = 0; i < v.size()-1; i++)
    {
        if(i>0 && i%hours_per_day==0) cout << " | ";
        if(v.at(i) < 0) cout << neg_replace << ", ";
        else cout << v.at(i) << ", ";

    }
    if(v.back() < 0) cout << neg_replace << " ]" << endl;
    else cout << v.back() << " ]" << endl;
}
void Assigner::print_twin_vec_debug(vector<vector<int> > v, vector<Course> courses, int hours_per_day)
{
    if(db) cout << "Assigner :: print_twin_vec_debug" << endl;
    for(int i = 0; i < v.size(); i++)
    {
        cout << courses.at(i).name << "\t: ";
        print_time_table_debug(v.at(i), '~', hours_per_day);
    }
    cout << endl;
}

void Assigner::fatal(string error_message)
{
    cout << "Assigner :: fatal() -> " << error_message << endl;
    exit(1);
}

bool Assigner::is_complete(std::vector<vector<int> > time_table, std::vector<Course> courses)
{
    if(db) cout << "Assigner :: is_complete" << endl;
    if(time_table.size() != courses.size()) return false;
    for(int i = 0; i < time_table.size(); i++)
    {
        int hours_required = courses.at(i).hours;
        int hours_assigned = 0;
        for(int j = 0; j < time_table.at(i).size(); j++)
            if(time_table.at(i).at(j) >= 0) hours_assigned++;
        if(hours_assigned < hours_required) return false;
    }
    return true;
}

vector<vector<int> > Assigner::create_timetable(InputSort input, int hours_per_day)
{
    if(db) cout << "Assigner :: create_timetable" << endl;
    vector<vector<int> > time_table = initialise_empty_timetable(input.n_courses, 5, hours_per_day);

    //assign earliest valid time_table slots
    basic_assign(input, &time_table, input.n_rooms, {1}, hours_per_day);
    if(!is_complete(time_table, input.courses))
        basic_assign(input, &time_table, input.n_rooms, {1, 2}, hours_per_day);
    if(!is_complete(time_table, input.courses))
        basic_assign(input, &time_table, input.n_rooms, {1, 2, 5}, hours_per_day);

    //display results if debug enabled
    if(input.debug && !is_complete(time_table, input.courses))
        cout << "* * * INCOMPLETE SOLUTION -> some course hours were not assigned * * *" << endl;
    if(input.debug) print_twin_vec_debug(time_table, input.courses, hours_per_day);

    return time_table;
}

//output printer formatting
void Assigner::print_vec(vector<int> v)
{
    for(int i = 0; i < v.size()-1; i++)
        cout << v.at(i) << ", ";
    cout << v.back() << endl;
}
void Assigner::print_twin_vec(vector<vector<int> > v)
{
    if(db) cout << "Assigner :: print_twin_vec" << endl;
    for(int i = 0; i < v.size(); i++)
        print_vec(v.at(i));
}
