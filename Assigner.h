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

    //basic hour assigner - non-optimal
    void basic_assign(InputSort input, vector<vector<int> > * time_table);

    void print_vec(std::vector<int> v);
    void print_twin_vec(std::vector<vector<int> > v);
    void fatal(std::string error_message);
public:
    //TIMETABLE CREATION ALGORITHM
    std::vector<vector<int> > create_timetable(InputSort input);
};
#endif
