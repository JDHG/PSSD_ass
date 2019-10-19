#ifndef STRUCTS_H
#define STRUCTS_H

struct Teacher
{
    int id;
    std::string name;
    std::vector<int> preferences;
    Teacher(std::vector<int>, std::string, int);
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
