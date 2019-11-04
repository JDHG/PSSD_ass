#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <vector>


struct Teacher
{
    std::string name;
    std::vector<int> preferences;
    Teacher(std::vector<int>, std::string);
    void print();
};
struct Course
{
    int hours;
    std::string name;
    std::vector<Teacher> teachers;
    Course(int, std::string);
    void print();
};

#endif
