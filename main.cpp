#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <iterator>
#include "InputSort.cpp"
#include "Assigner.cpp"

#include "EvalUCS_v2.cpp"
extern double Eval(string input_file, string time_table, bool debug);

string twinvec_to_string(vector<vector<int> > tv);

using namespace std;

//Arguments to main are <debug> <file_name>

int main(int argc, char const * argv[]) {

    const unsigned short HOURS_PER_DAY = 8;

    if(argc < 3) { cout << "FATAL -> not enough arguments on main call (" << argc << "arguments)" << endl; exit(1); }
    if(argc > 3) { cout <<   "FATAL -> too many arguments on main call (" << argc << "arguments)" << endl; exit(1); }

    bool debug = false;
    string * do_debug = new string; *do_debug = argv[1];
    if(*do_debug == "true") debug = true;
    delete do_debug;
    char const * file_name = argv[2];

    if(debug) cout << "Initiating timetable booking with input file :: '" << file_name << "'" << endl;
    if(debug) cout << "Debug is TRUE (" << debug << ")" << endl;

    //create set of input permutations

    InputSort input = InputSort(debug, file_name);
    if(debug) input.print();

    //create a string of the input permutation to give to Eval

    Assigner assigner = Assigner();
    vector<vector<int> > TT; //stores resulting time_table
    vector<vector<int> > best_TT;
    double current_eval_score = 99999;
    int assigner_version_number = 0;
    unsigned long n_timetables_created = 0;
    bool new_file = true;

    //PROGRAM LOOP - attempt to create best starting timetable
    while(current_eval_score > 1 && assigner_version_number < 2) //assigner_version_number stop is temporary -> will be stopping after all input permutations have been tried or score of 1 is reached
    {
        //set new_file bool to true when a new permutation file is opened

        //create_timetable needs a variable to determine its behaviour (what algorithm it tries)
        TT = assigner.create_timetable(input, HOURS_PER_DAY, assigner_version_number);

        //convert TT to string so it can be read by Eval()
        string time_table_csv = twinvec_to_string(TT);

        //get fitness value from Eval program
        double eval_score = Eval(file_name, time_table_csv, new_file, debug);

        //update return timetable if a better solution was found
        if(eval_score < current_eval_score)
        {
            best_TT = TT;
            current_eval_score = eval_score;
        }

        //run next assigner algorithm on next loop
        assigner_version_number++;
        n_timetables_created++;
        new_file = false;
    }
    if(debug) cout << "number of timetables created = " << n_timetables_created << endl;
    if(debug) cout << "fitness of final time_table  = " << current_eval_score << endl;
    assigner.print_twin_vec(best_TT); //output generation


    // while()
    // assigner.improve()


    return 0;
}

string twinvec_to_string(vector<vector<int> > tv)
{
    string s = "";
    ostringstream vts;
    for(int i = 0; i < tv.size(); i++)
    {
        copy(tv.at(i).begin(), tv.at(i).end()-1, ostream_iterator<int>(vts, ", "));
        vts << tv.at(i).back() << '\n';
    }
    return vts.str();
}
