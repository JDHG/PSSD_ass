#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <iterator>
#include "InputSort.cpp"
#include "Assigner.cpp"
#include "InputPermute.cpp"

#include "EvalUCS_v2.cpp"
extern double Eval(string input_file, string time_table, bool debug);
pair<vector<vector<int>>, double> generate_time_score_pair(InputSort input, int algorithm, int HOURS_PER_DAY, char const * file_name, bool new_file, bool debug, Assigner assigner);
bool update_best(vector<vector<int>> * best_TT, double * current_eval_score, pair<vector<vector<int>>, double> TT_eval_pair);
void check_csv(string);
string twinvec_to_string(vector<vector<int> > tv);
char get_spinner(int spin_counter);

using namespace std;



//Arguments to main are <debug> <file_name>

//      Hello! Welcome to our timetabler!
//      To run this script use the makefile (make)
//      Then give required arguments -> ./scheduler <debug> <file_name> :
//          -   <debug> is expected to be 'true' or 'false'
//          -   <file_name> is the input file's name
//          -   e.g. './scheduler false input.txt'  ::  is valid
//          -        './scheduler input.txt'        ::  is invalid -> requires the debug to be specified
//      You almost assuredly want to run the program with debug set to 'false'



int main(int argc, char const * argv[]) {

    const unsigned short HOURS_PER_DAY = 8;
    const int MAX_TIMETABLES = 10000;
    int n_permutations = 10000;
    int spin_speed = 35;

    if(argc < 3) { cout << "FATAL -> not enough arguments on main call (" << argc << " arguments) || expecting ./scheduler <debug> <file_name>" << endl; exit(1); }
    if(argc > 3) { cout <<   "FATAL -> too many arguments on main call (" << argc << " arguments) || expecting ./scheduler <debug> <file_name>" << endl; exit(1); }

    bool debug = false; bool print_permutations = false;
    string * do_debug = new string; *do_debug = argv[1];
    if(*do_debug == "true") debug = true;
    delete do_debug;
    char const * file_name = argv[2];

    if(debug) cout << "Initiating timetable booking with input file :: '" << file_name << "'" << endl;
    if(debug) cout << "Debug is TRUE (" << debug << ")" << endl;

    Assigner assigner = Assigner();
    vector<vector<int> > best_TT;
    double current_eval_score = 99999;
    unsigned long n_timetables_created = 0;
    bool new_file = true;

    pair<vector<vector<int>>, double> TT_eval_pair;
    InputPermute ip = InputPermute(file_name, print_permutations);              //Generates input permuting class
    deque<InputSort> starting_inputs = ip.permute(n_permutations, debug); InputSort input = starting_inputs.front();   //Strips input permuting class into InputSort classes
    if(debug) cout << "\nGENERATED " << starting_inputs.size() << " INPUTS" << endl << endl;
    assigner.set_original_order(starting_inputs.front());            //Roughly n_permutations amount of inputs are generated

    int spin_counter = 0;

    //PROGRAM LOOP - attempt to create best starting timetable
    while(current_eval_score > 1 && !starting_inputs.empty() && n_timetables_created <= MAX_TIMETABLES)
    {
        if(n_timetables_created % spin_speed == 0)
        {
            spin_counter++; spin_counter %= 4; char c = get_spinner(spin_counter);
            string status = "timetable (" + to_string(n_timetables_created) + ") " + c;
            for(int i = 0; i < status.size(); i++) { printf("\b"); fflush(stdout); } cout << status;
        }
        //Update best timetable left to right
        TT_eval_pair = generate_time_score_pair(starting_inputs.front(), 0, HOURS_PER_DAY, file_name, true, debug, assigner);
        update_best(&best_TT, &current_eval_score, TT_eval_pair);

        n_timetables_created += 1;
        starting_inputs.pop_front();
    }

    //create completed timetable file
    ofstream ofs;
    ofs.open("output.txt", ofstream::out | ofstream::trunc);
    ofs << twinvec_to_string(best_TT); //output generation
    ofs.close();

    cout << "number of timetables created = " << n_timetables_created << endl;
    cout << "fitness of final time_table  = " << current_eval_score << " -> Eval(" << Eval(file_name, twinvec_to_string(best_TT), true, debug) << ")" << endl;
    assigner.print_twin_vec_debug(best_TT, input.courses, 8);
    assigner.print_twin_vec(best_TT);
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

pair<vector<vector<int>>, double> generate_time_score_pair(InputSort input, int algorithm, int HOURS_PER_DAY, char const * file_name, bool new_file, bool debug, Assigner assigner)
{
    //create_timetable needs a variable to determine its behaviour (what algorithm it tries)
    vector<vector<int>> TT = assigner.create_timetable(input, HOURS_PER_DAY, algorithm);

    vector<int> UF = assigner.get_remaining_hours(TT, input.courses);
    //run improver on timetable
    bool improving = true;
    while(improving)
    {
        vector<vector<int> > current_TT = TT;
        TT = assigner.improve(TT, input, UF);
        if(current_TT == TT) improving = false;
    }

    //convert TT to string so it can be read by Eval()
    string time_table_csv = twinvec_to_string(TT);

    //get fitness value from Eval program
    double eval_score = Eval(file_name, time_table_csv, new_file, debug);

    //update return timetable if a better solution was found
    return make_pair(TT, eval_score);
}

bool update_best(vector<vector<int>> * best_TT, double * current_eval_score, pair<vector<vector<int>>, double> TT_eval_pair)
{
    if(TT_eval_pair.second < *current_eval_score)
    {
        *best_TT = TT_eval_pair.first;
        *current_eval_score = TT_eval_pair.second;
        return true;
    }
    return false;
}

char get_spinner(int spin_counter)
{
    switch(spin_counter)
    {
        case 0: return '|';
        case 1: return '/';
        case 2: return '-';
        case 3: return '\\';
        default: exit(1);
    }
}
