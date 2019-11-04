//InputPermute.cpp
#include "InputPermute.h"
#include "InputSort.cpp"

using namespace std;

string clean_line(string * line, string front)
{
    //erase front off of line
    if(line->substr(0, front.size()) == front) line->erase(0, front.size());
    else { cout << "clean_line :: Called with incorrect front (" << front << ")" << endl; exit(1);}

    //clean whitespace either end
    while(line->front() == ' ') line->erase(0, 1);
    while(line->back()  == ' ') line->pop_back();
    return * line;
}

string vector_to_s(vector<int> ints, string separator)
{
    string result = "";
    for(int n : ints)
        result = result + to_string(n) + separator;
    for(int i = 0; i < separator.size(); i++) result.pop_back();
    return result;
}

vector<string> s_to_s_vector(string s, string separator)
{
    clean_line(&s, "");
    s.push_back('*');

    string stringy = "";
    vector<string> strings = {};
    string digit = "";

    while(s.front() != '*')
    {
        while((s.front() >= 'a' && s.front() <= 'z') || (s.front() >= 'A' && s.front() <= 'Z'))
        {
            stringy = stringy + s.front();
            s.erase(0, 1);
        }
        strings.push_back(stringy); stringy = "";
        if(s.front() == '*') break;
        for(int i = 0; i < separator.size(); i++) s.erase(0, 1);
    }
    return strings;
}

vector<int> s_to_i_vector(string s, string separator)
{
    clean_line(&s, "");
    s.push_back('*');

    string number = "";
    vector<int> ints = {};
    string digit = "";

    while(s.front() != '*')
    {
        while(s.front() >= '0' && s.front() <= '9' )
        {
            number = number + s.front();
            s.erase(0, 1);
        }
        ints.push_back(stoi(number)); number = "";
        if(s.front() == '*') break;
        for(int i = 0; i < separator.size(); i++) s.erase(0, 1);
    }
    return ints;
}

InputPermute::InputPermute(string fnp, const char * file_name)
{
    file_name_prefix = fnp;
    set_input(file_name);
}
void InputPermute::set_raw_input(char const * file_name)
{
    //Open file
    freopen(file_name, "r", stdin);

    string input_line = "";
    deque<string> * input_lines;
    input_lines = new deque<string>;

    //Get all lines and stuff them into vector
    while(getline(cin, input_line))
    {
        if(input_line.back() == '\x0D')
        input_line.pop_back();
        input_lines->push_back(input_line);
    }
    fclose(stdin);

    input = *input_lines;
    delete input_lines;
    return;
}
//Push input file into class structure. Called by constructor
void InputPermute::set_input(const char * file_name)
{
    string line = "";
    set_raw_input(file_name);

    string Rooms        = "";
    string Courses      = "";
    string Hours        = ""; vector<int> Hours_v = {};
    string Names        = ""; vector<string> Names_v = {};
    string lecturers_   = "";
    vector<string> lecturer_names = {};
    vector<vector<int>> TL = {};
    vector<vector<int>> LP = {};
    string TL_line = "";
    string LP_line = "";

    cout << Rooms << endl;
    Rooms       = pop_input(); n_rooms = stoi(clean_line(&Rooms, "Rooms"));
    /*Courses */
    Courses     = pop_input(); n_courses = stoi(clean_line(&Courses, "Courses"));
    Hours       = pop_input(); Hours_v = s_to_i_vector(clean_line(&Hours, "Hours"), ", ");
    Names       = pop_input(); Names_v = s_to_s_vector(clean_line(&Names, "Names"), ", ");

    /*Lecturers */
    lecturers_  = pop_input(); n_lecturers = stoi(clean_line(&lecturers_, "Lecturers"));

    lecturer_names = s_to_s_vector(pop_input(), ", ");

    pop_input(); /* pop :: %TL - binary mapping  1 or 0 */

    /* Push class to classes */
    for(int i = 0; i < n_courses; i++)
    {
        TL_line = pop_input();
        classes.push_back(Class(Hours_v.at(i), Names_v.at(i), s_to_i_vector(clean_line(&TL_line, ""), ",")));
    }

    pop_input(); /* pop :: %LP preferences */

    /* Push lecturer to lecturers */
    for(int i = 0; i < n_lecturers; i++)
    {
        LP_line = pop_input();
        lecturers.push_back(Lecturer(lecturer_names.at(i), s_to_i_vector(clean_line(&LP_line, ""), ",")));
    }

    return;
}

//reading pop
string InputPermute::pop_input()
{
    string temp = input.front(); input.pop_front();
    return temp;
}

/* permute to next cycle */
vector<int> vector_starting_from(vector<int> input, int start)
{
    vector<int> temp = {}; int loops = 0; int c = start;
    while(true)
    {
        if(c == start) loops++;
        if(loops > 1) break;
        temp.push_back(input.at(c));
        c++;
        c = c % input.size();
    }
    return temp;
}
//Default permuter -> reads into files in cycle
vector<const char *> InputPermute::permute(unsigned int n_permutations)
{
    int file_number = 0; vector<int> access_order = {};
    vector<const char *> files = {};
    for(int i = 0; i < n_courses; i++)
    {
        access_order.push_back(i);
    }

    //Shuffle through classes -> A, b, c, d :: b, c, d, A :: c, d, A, b :: d, A, b, c
    n_permutations /= n_courses; n_permutations++;
    for(int i = 0; i < access_order.size(); i++)
        for(int j = 0; j < n_permutations; j++)
        {
            files.push_back(write_to_file(file_number, vector_starting_from(access_order, i)));
            next_permutation(access_order.begin(), access_order.end());
            file_number++;
        }

    return files;
}

deque<InputSort> InputPermute::permute(unsigned int n_permutations, char type)
{
    deque<InputSort> input_sorts = {}; vector<int> access_order = {};
    deque<deque<string>> inputs = {};
    for(int i = 0; i < n_courses; i++)
        access_order.push_back(i);

    n_permutations /= n_courses; n_permutations++;
    for(int i = 0; i < access_order.size(); i++)
        for(int j = 0; j < n_permutations; j++)
        {
            inputs.push_back(write_to_string_vector(vector_starting_from(access_order, i)));
            next_permutation(access_order.begin(), access_order.end());
        }

    for(deque<string> input : inputs)
        input_sorts.push_back(InputSort(true, input));

    for(InputSort input_sort : input_sorts)
        input_sort.print();

    return input_sorts;
}

/*Strip members into a vector */
deque<string> InputPermute::write_to_string_vector(vector<int> access_order)
{
    deque<string> input = {}; string line = "";
    input.push_back("Rooms       " + to_string(n_rooms));       //Get Rooms
    input.push_back("Courses     " + to_string(n_courses));     //Get Courses

    line = "Hours       "; int hours = 0;                    //Get Hours
    for(int index : access_order)
    {
        line.append(to_string(classes.at(index).hours));
        if(index != access_order.back()) line.append(", ");
    }
    input.push_back(line); line.clear();

    line = "Names       ";                                  //Get course_names
    for(int index : access_order)
    {
        line = line + classes.at(index).name;
        if(index != access_order.back()) line.append(", ");
    }
    input.push_back(line); line.clear();

    input.push_back("Lecturers   " + to_string(n_lecturers));             //Get Lecturers
    for(int i = 0; i < n_lecturers - 1; i++)
        line = line + lecturers.at(i).name + ", ";
    line = line + lecturers.back().name;
    input.push_back(line);

    input.push_back("%TL - binary mapping  1 or 0");
    for(int index : access_order)                           //Get TL
    {
        line = vector_to_s(classes.at(index).TL, ",");
        input.push_back(line);
    }   line.clear();

    input.push_back("%LP preferences\n");                   //Get LP
    for(Lecturer lecturer : lecturers)
    {
        line = vector_to_s(lecturer.LP, ",");
        input.push_back(line);
    }   line.clear();
    return input;

}

/* Strip members into a file */
const char * InputPermute::write_to_file(int file_number, vector<int> access_order)
{
    ofstream ofs; string file_name = file_name_prefix + to_string(file_number) + ".txt";
    ofs.open(file_name, ofstream::out | ofstream::trunc);

    ofs << "Rooms       " << n_rooms << endl;
    ofs << "Courses     " << n_courses << endl;

    ofs << "Hours       ";
    for(int index : access_order)
    {
        if(index == access_order.back()) break;
        ofs << classes.at(index).hours << ", ";
    }
    ofs << classes.at(access_order.back()).hours << endl;

    ofs << "Names       ";

    for(int index : access_order)
    {
        if(index == access_order.back()) break;
        ofs << classes.at(index).name << ", ";
    }
    ofs << classes.at(access_order.back()).name << endl;

    ofs << "Lecturers   " << n_lecturers << endl;
    for(int i = 0; i < n_lecturers - 1; i++)
        ofs << lecturers.at(i).name << ", ";
    ofs << lecturers.back().name << endl;

    ofs << "%TL - binary mapping  1 or 0" << endl;
    for(int index : access_order)
        ofs << vector_to_s(classes.at(index).TL, ",") << endl;

    ofs << "%LP preferences" << endl;
    for(Lecturer lecturer : lecturers)
        ofs << vector_to_s(lecturer.LP, ",") << endl;

    ofs.close();
    return file_name.c_str();
}
const char * InputPermute::write_to_file(int file_number)
{
    ofstream ofs; string file_name = file_name_prefix + to_string(file_number) + ".txt";
    ofs.open(file_name, ofstream::out | ofstream::trunc);

    ofs << "Rooms       " << n_rooms << endl;
    ofs << "Courses     " << n_courses << endl;

    ofs << "Hours       ";
    for(int i = 0; i < n_courses - 1; i++)
        ofs << classes.at(i).hours << ", ";
    ofs << classes.back().hours << endl;

    ofs << "Names       ";
    for(int i = 0; i < n_courses - 1; i++)
        ofs << classes.at(i).name << ", ";
    ofs << classes.back().name << endl;

    ofs << "Lecturers   " << n_lecturers << endl;
    for(int i = 0; i < n_lecturers - 1; i++)
        ofs << lecturers.at(i).name << ", ";
    ofs << lecturers.back().name << endl;

    ofs << "%TL - binary mapping  1 or 0" << endl;
    for(Class c : classes)
        ofs << vector_to_s(c.TL, ",") << endl;

    ofs << "%LP preferences" << endl;
    for(Lecturer lecturer : lecturers)
        ofs << vector_to_s(lecturer.LP, ",") << endl;

    ofs.close();
    return file_name.c_str();
}
