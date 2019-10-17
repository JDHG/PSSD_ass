#include <iostream>
#include <vector>
#include <deque>
#include "InputSort.cpp"
#include "Assigner.cpp"

using namespace std;

//Arguments to main are <debug> <file_name>

int main(int argc, char const * argv[]) {

    if(argc < 3) { cout << "FATAL -> not enough arguments on main call (" << argc << "arguments)" << endl; exit(1); }
    if(argc > 3) { cout <<   "FATAL -> too many arguments on main call (" << argc << "arguments)" << endl; exit(1); }

    bool debug = false;
    string * do_debug = new string; *do_debug = argv[1];
    if(*do_debug == "true") debug = true;
    delete do_debug;
    char const * file_name = argv[2];

    if(debug) cout << "Initiating timetable booking with input file :: '" << file_name << "'" << endl;
    if(debug) cout << "Debug is TRUE (" << debug << ")" << endl;

    InputSort input = InputSort(debug, file_name);
    input.print();

    Assigner assigner = Assigner();
    assigner.create_timetable(input);

    return 0;
}
