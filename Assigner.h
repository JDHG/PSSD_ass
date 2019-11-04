#ifndef ASSIGN_H
#define ASSIGN_H

#include "structs.h"
#include "InputSort.h"
#include <vector>
#include <iostream>

class Assigner
{
    bool db = false; //local assigner debug switch

    /* ASSIGNER CREATE TIMETABLE FUNCTIONALITY */

    std::vector<int> hours_assigned; //stores assigned hours of each copy of input.courses hours

    //create return vector-vector of -1's
    std::vector<vector<int> > initialise_empty_timetable(int n_courses, int n_days, int n_hours);

    //prevent lecturer from being assigned >2 hours in a row
    bool two_hour_max(int current_hour, int incoming_teacher_id, vector<vector<int> > time_table, int hours_per_day);

    //check if number of rooms has been exhausted and prevents double bookings of teachers
    bool room_available(int n_rooms, int current_hour, int incoming_teacher_id, vector<vector<int> > time_table);

    //check if day already has a course session assigned (strict one session per day)
    bool day_available(int hours_per_day, std::vector<int> tt_slot, int current_hour, int version);

    //return true if preference_val value is in permitted_LP_values
    bool permitted(int preference_val, std::vector<int> permitted_LP_values);

    //gets hour for basic_assign based on version behaviour specified
    int get_hour(int current_hour, int hour_limit, int version);

    //advance to next day to assign based on version behaviour
    int advance_day(int k, int hours_per_day, int version);

    //basic hour assigner - allocates earliest valid time_table slots
    //version 0 -> left to right greedy assignment
    //version 1 -> right to left greedy assignment
    void basic_assign(InputSort input, std::vector<Course> courses, vector<vector<int> > * time_table, int n_rooms, std::vector<int> permitted_LP_values, int hours_per_day, int run, int version);

    //return true if all course hours have been assigned
    bool is_complete(std::vector<vector<int> > time_table, std::vector<Course> courses, bool input_debug);

    //print time_table in readable debug format
    void print_time_table_debug(std::vector<int> v, char neg_replace, int hours_per_day); //print neg_replace instead of negative integers
    void print_twin_vec_debug(std::vector<vector<int> > v, std::vector<Course> courses, int hours_per_day);

    void fatal(std::string error_message);

public:
    static bool not_complete; //flag to set when solution searching is finished

    //TIMETABLE CREATION ALGORITHM
    std::vector<vector<int> > create_timetable(InputSort input, int hours_per_day, int version);

    /* ITERATIVE IMPROVEMENT FUNCTIONALITY */

    std::vector<int> get_remaining_hours(std::vector<std::vector<int> > time_table, std::vector<Course> courses);

    //returns a time table that has undergone one step of iterative improvement
    std::vector<std::vector<int> > improve(std::vector<std::vector<int> > time_table, InputSort input, vector<int> incomplete_courses);

    //print vectors in output format
    void print_vec(std::vector<int> v);
    void print_twin_vec(std::vector<vector<int> > v);
};
#endif
