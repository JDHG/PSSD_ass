#ifndef ASSIGN_H
#define ASSIGN_H

#include "structs.h"
#include "InputSort.h"
#include <vector>

class Assigner
{
    //set lunchbreak LP hours to 0 - LB hour is index of LunchBreak hour in an hours array for 1 day -> day[LB_hour]
    void nullify_lunchbreaks(std::vector<int> * preferences, int LB_hour, int n_hours);

    //create return vector of -1's
    std::vector<int> initialise_empty_timetable(int n_courses, int n_days, int n_hours);

    void print_v(std::vector<int> v);
public:
    std::vector<int> basic_timetable(std::vector<Course> courses);
};
#endif
