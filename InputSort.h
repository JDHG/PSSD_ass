#ifndef INPUTSORT_H
#define INPUTSORT_H

#include <deque>
#include <vector>
#include <iostream>
// #include <map>
#include "structs.cpp"

class InputSort
{

public:
    int n_rooms;
    int n_courses;
    int n_teachers;
    bool debug;
    std::deque<std::string> raw_input;
    std::vector<Course> courses;
    // std::map<std::string, int> teacher_id;

    void set_raw_input(char const *);
    std::string pop_input();
    std::string pop_input(std::string);
    void clean_line(std::string *, std::string);

    std::vector<int> stoi_vector(std::string, std::string);
    std::vector<std::string> sto_vector(std::string, std::string);



    InputSort(bool, char const * );
    void print();
};

#endif
