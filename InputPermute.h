//InputPermute.h
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <fstream>
#include "InputSort.cpp"

/*  Writes a single input file into it's
    permutations */

class InputPermute
{
public:
    struct Class
    {
        int hours;
        std::string name;
        std::vector<int> TL;
        Class(int h, std::string n, std::vector<int> tl)
        {
            hours = h; name = n; TL = tl;
        }
    };

    struct Lecturer
    {
        std::string name;
        std::vector<int> LP;
        Lecturer(std::string n, std::vector<int> lp)
        {
            name = n; LP = lp;
        }
    };

    //Cror
    InputPermute(std::string, const char *);
    void set_raw_input(char const * file_name); /*Rip file into a string */
    void set_input(const char *);               /*Rip string into class members */

    //File reading functions
    std::string pop_input();


    //set input file to this deque of inputs
    std::deque<std::string> input;
    std::string file_name_prefix;

    int n_rooms;
    int n_courses;
    int n_lecturers;

    std::vector<Class> classes;
    std::vector<Lecturer> lecturers;

    //functions that drives input permutation
    std::vector<std::string> permute();
    std::string write_to_file(int);
    std::string write_to_file(int, std::vector<int>);
};
