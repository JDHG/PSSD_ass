#ifndef INPUTSORTV2_H
#define INPUTSORTV2_H

#include <deque>
#include <vector>
#include <iostream>
#include "structs.cpp"

class InputSort
{


    int n_rooms;
    int n_courses;
    int n_teachers;
    bool debug;
    std::deque<std::string> raw_input;
    std::vector<Course> courses;

    void set_raw_input(char const *);
    std::string pop_input();
    std::string pop_input(std::string);
    void clean_line(std::string *, std::string);

    std::vector<int> stoi_vector(std::string, std::string);
    std::vector<std::string> sto_vector(std::string, std::string);
public:


    InputSort(bool, char const * );
    void print();
};

#endif
