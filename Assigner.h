#ifndef ASSIGN_H
#define ASSIGN_H

#include "structs.h"
#include "InputSort.h"
#include <vector>
#include <iostream>

class Assigner
{
    //create return vector of -1's
    std::vector<vector<int> > initialise_empty_timetable(int n_courses, int n_days, int n_hours);

    //check if number of rooms has been exhausted
    bool room_available(int n_rooms, int current_hour, vector<vector<int> > time_table);
    //check if day already has a course session assigned
    bool day_available(int hours_per_day, std::vector<int> tt_slot, int current_hour);
    //return true if preference_val value is in permitted_LP_values
    bool permitted(int preference_val, std::vector<int> permitted_LP_values);
    //basic hour assigner
    void basic_assign(InputSort input, vector<vector<int> > * time_table, int n_rooms, std::vector<int> permitted_LP_values, int hours_per_day);

    //print vectors in output format
    void print_vec(std::vector<int> v);
    void print_twin_vec(std::vector<vector<int> > v);

    //print time_table in readable debug format
    void print_time_table_debug(std::vector<int> v, char neg_replace, int hours_per_day); //print neg_replace instead of negative integers
    void print_twin_vec_debug(std::vector<vector<int> > v, std::vector<Course> courses, int hours_per_day);

    void fatal(std::string error_message);
    //return true if all course hours have been assigned
    bool is_complete(std::vector<vector<int> > time_table, std::vector<Course> courses);
public:
    //TIMETABLE CREATION ALGORITHM
    std::vector<vector<int> > create_timetable(InputSort input, int hours_per_day);
};
#endif
