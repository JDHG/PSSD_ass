#include "Assigner.h"
using namespace std;

bool Assigner::not_complete = true;

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

bool Assigner::two_hour_max(int current_hour, int incoming_teacher_id, vector<vector<int> > time_table, int hours_per_day)
{
    if(db) cout << "Assigner :: two_hour_max" << endl;
    int day_start = (current_hour / hours_per_day) * hours_per_day;
    int day_end = day_start + hours_per_day;

    if(day_end > 39) day_end = 39;

    int consec_hours = 0;

    if(current_hour-1 >= day_start)
        for(int i = 0; i < time_table.size(); i++)
            if(time_table.at(i).at(current_hour-1) == incoming_teacher_id) consec_hours++;

    if(current_hour-2 >= day_start)
        for(int i = 0; i < time_table.size(); i++)
            if(time_table.at(i).at(current_hour-2) == incoming_teacher_id) consec_hours++;

    if(current_hour+1 <= day_end)
        for(int i = 0; i < time_table.size(); i++)
            if(time_table.at(i).at(current_hour+1) == incoming_teacher_id) consec_hours++;

    if(current_hour+2 <= day_end)
        for(int i = 0; i < time_table.size(); i++)
            if(time_table.at(i).at(current_hour+2) == incoming_teacher_id) consec_hours++;

    if(consec_hours >= 2) return false;
    else return true;
}

bool Assigner::room_available(int n_rooms, int current_hour, int incoming_teacher_id, vector<vector<int> > time_table)
{
    if(db) cout << "Assigner :: room_available" << endl;
    unsigned short rooms_in_use = 0;
    for(int i = 0; i < time_table.size(); i++)
    {
        int target_hour = time_table.at(i).at(current_hour);
        if(target_hour >= 0) rooms_in_use++;
        if(rooms_in_use >= n_rooms || target_hour == incoming_teacher_id) return false; //rooms all used || teacher being double booked

    }
    return true;
}

bool Assigner::day_available(int hours_per_day, std::vector<int> tt_slot, int current_hour, int version)
{
    if(db) cout << "Assigner :: day_available" << endl;
    //get hour boundaries of day containing 'current_hour'
    int day_start = (current_hour / hours_per_day) * hours_per_day;
    int day_end = day_start + hours_per_day;

    for(int i = day_start; i < day_end; i++)
        if(tt_slot.at(i) >= 0)
        {
            if(version < 1 && i < day_end-1)
                if(tt_slot.at(++i) < 0 && i == current_hour) return true; //allow 2-hour session assignment

            if(version == 1 && i > day_start+1)
                if(tt_slot.at(--i) < 0 && i == current_hour) return true; //allow 2-hour session assignment

            return false; //day has a session allocated already
        }
    return true; //all hours are available for this course on this day
}

bool Assigner::permitted(int preference_val, vector<int> permitted_LP_values)
{
    if(db) cout << "Assigner :: permitted" << endl;
    for(int p : permitted_LP_values) if(preference_val == p) return true;
    return false;
}

int Assigner::get_hour(int current_hour, int hour_limit, int version)
{
    if(db) cout << "Assigner :: get_hour" << endl;
    switch(version)
    {
        case  1: { current_hour--; break; }
        default: current_hour++;
    }
    if(current_hour < 0 || current_hour >= hour_limit) return -2;
    else return current_hour;
}

int Assigner::advance_day(int k, int hours_per_day, int version)
{
    if(db) cout << "Assigner :: advance_day" << endl;
    if(k == -2 || k < 0 || k >= 40) return -2;
    switch(version)
    {
        case  1: { if(k == 0) return -2; while(k % hours_per_day != 1) k--; return k; }       //previous day
        default: { while(k % hours_per_day != hours_per_day-1) k++; }   //next day
    }
    return k;
}

void Assigner::basic_assign(InputSort input, vector<Course> courses, vector<vector<int> > * time_table, int n_rooms, vector<int> permitted_LP_values, int hours_per_day, int run, int version)
{
    if(db || input.debug) cout << "Assigner :: basic_assign :: version ("<<version<<") :: run number ("<<run<<")" << endl;
    if(run > 2) return; //run number is recursive depth -> forces return after 3 runs which goes through all permitted_LP_values vectors

    for(int i = 0; i < courses.size(); i++) //for each course
    {
        Course * c = &courses.at(i);
        for(int j = 0; j < c->teachers.size(); j++) //for each assigned course teacher
        {
            Teacher t = c->teachers.at(j);
            int LP_size = t.preferences.size();

            //assign starting hour to k based on version behaviour
            int k;
            switch(version)
            {
                case  1: { k = LP_size-1; break; }  //right to left greedy
                default: { k = 0; }                 //left to right greedy
            }

            while(k != -2) //k = -2 when get_hour() determines we are finished based on version
            {
                if(db) cout << "hour:" << k << ' ';
                if(k >= 0)
                {
                    if(c->hours > 0 && day_available(hours_per_day, time_table->at(i), k, version))
                    {
                        vector<int> p = t.preferences;
                        if  (    permitted(p.at(k), permitted_LP_values)
                              && room_available(input.n_rooms, k, t.id, *time_table)
                              && two_hour_max(k, t.id, *time_table, hours_per_day)
                            )
                        {
                            time_table->at(i).at(k) = t.id; //write teacher's id to time_table[i][k]
                            if(db || input.debug) cout << "    add " << t.id << ':' << t.name << " LP(" << p.at(k) << ") @ course[hour] " << c->name << '['<<k<<']' << endl;
                            c->hours--;
                            if(c->hours == 0) break;
                        }
                    }
                    else k = advance_day(k, hours_per_day, version); //proceed to next day if unavailable
                }
                k = get_hour(k, LP_size, version); //get next hour based on version
            }
        }
    }
    //if incomplete, run again allowing assignment on LP = {1 || 2}
    if(run == 0 && !is_complete(*time_table, courses, input.debug))
        basic_assign(input, courses, time_table, input.n_rooms, {1, 2}, hours_per_day, ++run, version);

    //if still incomplete, run again allowing assignment on LP = {1 || 2 || 5}
    else if(run == 1 && !is_complete(*time_table, courses, input.debug))
        basic_assign(input, courses, time_table, input.n_rooms, {1, 2, 5}, hours_per_day, ++run, version);

    else if(input.debug && !is_complete(*time_table, courses, input.debug))
        cout << "* * * INCOMPLETE SOLUTION -> some course hours were not assigned * * *" << endl;
}

bool Assigner::is_complete(std::vector<vector<int> > time_table, std::vector<Course> courses, bool input_debug)
{
    if(db) cout << "Assigner :: is_complete" << endl;
    bool complete = true;
    for(Course c : courses)
    {
        if(db || input_debug) cout << c.name << "\t: hours left = " << c.hours << endl;
        if(c.hours > 0) complete = false;
    }
    if(db || input_debug) cout << endl;
    return complete;
}

vector<int> Assigner::get_remaining_hours(vector<vector<int> > time_table, vector<Course> courses)
{
    vector<int> incomplete_courses;
    for(int i = 0; i < time_table.size(); i++)
    {
        int hours = courses.at(i).hours;
        for(int j = 0; j < time_table.at(i).size(); j++)
        {
            if(time_table.at(i).at(j) >= 0) hours--;
        }
        if(hours > 0) incomplete_courses.push_back(i);
    }
    return incomplete_courses;
}

vector<vector<int> > Assigner::improve(vector<vector<int> > time_table, InputSort input, vector<int> ic)
{
    //ic = vector of incomplete course indexes
    for(int i = 0; i < ic.size(); i++)
    {
        for(int j = 0; j < time_table.at(ic.at(i)).size(); j++)
        {
            int teacher_id = time_table.at(ic.at(i)).at(j);

            //find assigned single hours
            if(teacher_id > -1)
            {
                int day_start = (j / 8) * 8;
                int day_end = day_start + 8;

                if(j+1 < day_end)
                {
                    if(input.get_teacher_by_id(teacher_id).preferences.at(j+1) > 0)
                    {
                        if(room_available(input.n_rooms, j+1, teacher_id, time_table))
                        {
                            if(two_hour_max(j+1, teacher_id, time_table, 8))
                            {
                                time_table.at(ic.at(i)).at(j+1) = teacher_id;
                                if(db || input.debug) cout << "    add " << teacher_id << " @ course[hour] " << input.courses.at(ic.at(i)).name << '['<<j+1<<']' << endl;
                                return time_table;
                            }
                        }
                    }
                }
                if(j-1 > day_start)
                {
                    if(input.get_teacher_by_id(teacher_id).preferences.at(j-1) > 0)
                    {
                        if(room_available(input.n_rooms, j-1, teacher_id, time_table))
                        {
                            if(two_hour_max(j-1, teacher_id, time_table, 8))
                            {
                                time_table.at(ic.at(i)).at(j-1) = teacher_id;
                                if(db || input.debug) cout << "    add " << teacher_id << " @ course[hour] " << input.courses.at(ic.at(i)).name << '['<<j-1<<']' << endl;
                                return time_table;
                            }
                        }
                    }
                }
            }
        }
    }

    return time_table;
}


//debug printer formatting
void Assigner::print_time_table_debug(vector<int> v, char neg_replace, int hours_per_day)
{
    cout << "[ ";
    for(int i = 0; i < v.size()-1; i++)
    {
        if(i>0 && i%hours_per_day==0) cout << "| ";
        if(i%8 == 3) cout << "L, ";
        else if(v.at(i) < 0) cout << neg_replace << ", ";
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
{ cout << "Assigner :: fatal() -> " << error_message << endl; exit(1); }


//********************************************************************************************************************//

vector<vector<int> > Assigner::create_timetable(InputSort input, int hours_per_day, int version)
{
    if(db) cout << "Assigner :: create_timetable" << endl;
    vector<vector<int> > time_table = initialise_empty_timetable(input.n_courses, 5, hours_per_day);

    //populate time table -> allowing worse LP selections if returned time_table is incomplete (course hours outstanding)
    basic_assign(input, input.courses, &time_table, input.n_rooms, {1}, hours_per_day, 0, version);

    //display results if debug enabled
    // if(input.debug) print_twin_vec_debug(time_table, input.courses, hours_per_day);
    not_complete = false; //ends program in main

    vector<vector<int>> time_table_reordered = {};

    //Reorder time_table to match input course order
    for(int i = 0; i < input.n_courses; i++)
        for(int j = 0; j < input.n_courses; j++)
            if(input.courses.at(j).name == original_order.at(i))
            {
                time_table_reordered.push_back(time_table.at(j)); break;
            }
    if(input.debug) print_twin_vec_debug(time_table_reordered, original_order, hours_per_day);
    return time_table_reordered;
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
void Assigner::set_original_order(InputSort original_input)
{
    for(Course c : original_input.courses)
        original_order.push_back(c.name);
    return;
}
void Assigner::print_twin_vec_debug(vector<vector<int> > v, vector<string> courses, int hours_per_day)
{
    if(db) cout << "Assigner :: print_twin_vec_debug (string not Course)" << endl;
    for(int i = 0; i < v.size(); i++)
    {
        cout << courses.at(i) << "\t: ";
        print_time_table_debug(v.at(i), '~', hours_per_day);
    }
    cout << endl;
}
