#include "InputSort.h"

using namespace std;

void check_string(string s)
{
    cout << "\n\nchecking string    ::    '" << s << "'    ::    \n\n" << endl;
    return;
}

//Take raw input and put into a deque of strings
void InputSort::set_raw_input(char const * file_name)
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

        raw_input = *input_lines;
        // delete input_lines;
        return;
    }

string InputSort::pop_input()
{
    string temp = raw_input.front(); raw_input.pop_front();
    return temp;
}

void InputSort::clean_line(string * line, string front)
{
    //erase front off of line
    if(line->substr(0, front.size()) == front) line->erase(0, front.size());
    else { cout << "clean_line :: Called with incorrect front" << endl; return;}

    //clean whitespace either end
    while(line->front() == ' ') line->erase(0, 1);
    while(line->back()  == ' ') line->pop_back();
    return;
}

string InputSort::pop_input(string front)
{
    string line = pop_input();
    clean_line(&line, front);
    return line;
}

void InputSort::print()
{
    cout << "\n\nPrinting input     ::" << endl;
    cout << "    n_rooms        :: '" << n_rooms << "'" << endl;
    cout << "    n_courses      :: '" << n_courses << "'" << endl;
    cout << "    n_teachers     :: '" << n_teachers << "'" << endl;
    cout << "    Printing courses     ::" << endl;
    //COURSES printing
    for(auto course : courses)
        course.print();
    // cout
}

vector<int> InputSort::stoi_vector(string s, string separator)
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

vector<string> InputSort::sto_vector(string s, string separator)
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

InputSort::InputSort(bool b, char const * file_name)
{
    debug = b;
    set_raw_input(file_name);

    if(debug) cout << "\n\nPrinting raw_input :\n" << endl;
    if(debug) for(auto line : raw_input)
        cout << "    [" << line << "]" << endl;

    //Get n_rooms | n_courses
    n_rooms = stoi(pop_input("Rooms"));
    n_courses = stoi(pop_input("Courses"));

    //Get hours and names for courses
    string line = pop_input("Hours");
    vector<int> * course_hours = new vector<int>;
    *course_hours = stoi_vector(line, ", ");
    vector<string> * course_names = new vector<string>;
    line        = pop_input("Names");
    *course_names = sto_vector(line, ", ");

    vector<string>::iterator a_name = course_names->begin();
    vector<int>   ::iterator a_hour = course_hours->begin();

    //Push names | hours into courses as Course objects
    while(a_name < course_names->end())
    {
        courses.push_back(Course(*a_hour, *a_name));
        a_name++; a_hour++;
    }

    delete course_hours;
    delete course_names;

    //Get n_teachers
    n_teachers = stoi(pop_input("Lecturers"));

    //Get teacher names
    line = pop_input();
    vector<string> * teacher_names = new vector<string>;
    *teacher_names = sto_vector(line, ", ");

    //Pop %TL - binary mapping
    pop_input();

    //Get teacher_lecturer matrix (TL)
    vector<vector<int>> * teacher_lecturer_matrix = new vector<vector<int>>;
    for(int i = 0; i < n_courses; i++)
    {
        line = pop_input();
        teacher_lecturer_matrix->push_back(stoi_vector(line, ","));
    }

    //Pop %LP preferences
    pop_input();

    //Get teachers
    vector<int> preferences;
    vector<Teacher> * teachers = new vector<Teacher>;
    for(int i = 0; i < n_teachers; i++)
    {
        line = pop_input();
        preferences = stoi_vector(line, ",");
        //nullify_lunchbreaks
        for(int j = 3; j < preferences.size(); j+=8)
            preferences.at(j) = -1;
        teachers->push_back(Teacher(preferences, teacher_names->at(i), i));
    }

    for(int course_i = 0; course_i < n_courses; course_i++)
        for(int teacher_i = 0; teacher_i < n_teachers; teacher_i++)
        {
            if(teacher_lecturer_matrix->at(course_i).at(teacher_i) == 1) /*HIT*/
                courses.at(course_i).teachers.push_back(teachers->at(teacher_i));
        }

    delete teachers;
    delete teacher_names;
    delete teacher_lecturer_matrix;
}
