#ifndef INPUTSORT_H
#define INPUTSORT_H

#include <vector>
#include <deque>
#include <map>

using namespace std;

class InputSort
{
    bool debug;
    struct Teacher
    {
        string name;
        int n_courses;
        vector<string> courses;
        vector<int> preferences;
        Teacher(string input_name) { name = input_name; }
        void print()
        {
            cout << "name :: " << name << endl;
            cout << "courses\n{ ";
            for(auto e : courses)
                cout << e << " ";
            cout << "}" << endl;
            cout << "preferences\n{ ";
            int day = 0;
            int c = 8;
            for(auto e : preferences)
            {
                if(!(c % 8))
                {
                    cout << "\nDay (" << day << ") ";
                    day++;
                }
                c++;
                cout << e << " ";
            }
            cout << "\n}\n" << endl;
        }
    };
    //
    struct Course
    {
        string name;
        vector<int> n_teachers;
        vector<string> teachers;
        Course(string input_name) { name = input_name; }

        void print()
        {cout << "name :: " << name << endl;
        cout << "teachers\n{ ";
        for(auto e : teachers)
            cout << e << " ";
        cout << "}\n" << endl;}
    };


    int rooms;
    int n_courses;
    int n_teachers;
    vector<int> hours;
    vector<Course> courses;
    vector<Teacher> teachers;
    // deque<Teacher*> teachers;
    // deque<Course*> courses;
    // map<string, vector<Teacher>> teachers; //key is teacher name, value is the courses taught by teacher

    deque<string> * raw_input;

    void set_raw_input(char const * file_name)
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

        raw_input = input_lines;
        return;
    }
    vector<int> csv_binary_to_int_vector(string csv, string separator)
    {
        if(debug) cout << "InputSort Construction :: csv_binary_to_int_vector ( " << separator << " | " << csv << ")" << endl;
        // if(csv.front() != '0' || csv.front() != '1') { cout << "FATAL -> csv_to_int_vector (with separator '" << separator << "') with incorrect string" << endl; exit(1); }
        vector<int> ints = {};
        string temp = "";
        while(csv.size() > 0)
        {
            temp += csv.front();
            csv.erase(0, 1);
            ints.push_back(stoi(temp));
            temp = "";
            if(csv.size() <= 0) break;
            for(int i = 0; i < separator.size(); i++) csv.erase(0, 1);
        }

        if(debug)
        {
            cout << "    Made vector { ";
            for(auto integer : ints)
                cout << "'" << integer << "' ";
            cout << "}" << endl;
        }

        return ints;
    }
    vector<int> csv_to_int_vector(string csv)
    {
        if(debug) cout << "InputSort Construction :: csv_to_int_vector      :: (" << csv << ")" << endl;
        vector<int> hour_times = {};
        string number;
        while(!isdigit(csv.front())) csv.erase(csv.begin() + 0);
        while(!isdigit(csv.back()))  csv.erase(csv.size() -1);
        while(csv.size() > 0)
        {
            while(isdigit(csv.front()))
            {
                number = number + csv.front();
                csv.erase(csv.begin() + 0);
            }
            hour_times.push_back(stoi(number));
            number = "";
            if(csv.size() <= 0) break;
            if(csv.front() != ',') { cout << "FATAL -> csv_to_int_vector " << endl; exit(1); } csv.erase(csv.begin() + 0);
            if(csv.front() != ' ') { cout << "FATAL -> csv_to_int_vector " << endl; exit(1); } csv.erase(csv.begin() + 0);
        }

        if(debug)
        {
            cout << "    Made vector { ";
            for(auto hour : hour_times)
                cout << "'" << hour << "' ";
            cout << "}" << endl;
        }
        return hour_times;
    }
    vector<string> csv_to_string_vector(string csv)
    {
        if(debug) cout << "InputSort Construction :: csv_to_string_vector   :: (" << csv << ")" << endl;
        vector<string> names = {};
        string name;
        //Erase whitespace if exists
        while(csv.front() == ' ') csv.erase(0);
        while(csv.back() ==  ' ') csv.erase(csv.size() -1);
        //Exit if illegal front detected
        if(!isalpha(csv.front())) { cout << "FATAL -> csv_to_string_vector " << endl; exit(1); }

        while(csv.size() > 0)
        {
            while(isalpha(csv.front()))
            {
                name = name + csv.front();
                csv.erase(0, 1);
            }
            names.push_back(name);
            name = "";
            if(csv.size() <= 0) break;
            if(csv.front() != ',') { cout << "FATAL -> csv_to_string_vector " << endl; exit(1); } csv.erase(csv.begin() + 0);
            if(csv.front() != ' ') { cout << "FATAL -> csv_to_string_vector " << endl; exit(1); } csv.erase(csv.begin() + 0);
        }

        if(debug)
        {
            cout << "    Made vector { ";
            for(auto name : names)
                cout << "'" << name << "' ";
            cout << "}" << endl;
        }
        return names;
    }


public:
    void print_teachers()
    {
        if(debug) cout << "\n\nInputSort print_teachers :: printing teachers\n" << endl;
        for(auto teacher : teachers) if(debug) teacher.print();
    }
    void print_courses()
    {
        if(debug) cout << "\n\nInputSort print_courses :: printing courses\n" << endl;
        for(auto course : courses) if(debug) course.print();
    }
    InputSort(bool d, char const * file_name)
    {

        string * string_buffer = new string;
        vector<string> * strings_buffer = new vector<string>;
        vector<int> * ints_buffer = new vector<int>;
        vector<string> * teacher_names = new vector<string>;

        debug = d;
        //Open file and set raw_input
        set_raw_input(file_name);

        //ROOMS
        if(debug) cout << "InputSort Construction :: setting rooms          :: (" << raw_input->front().back() << ")" << endl;
        rooms = raw_input->front().back() - '0';            raw_input->pop_front();
        //n_courses
        if(debug) cout << "InputSort Construction :: setting n_courses      :: (" << raw_input->front().back() << ")" << endl;
        n_courses = raw_input->front().back() - '0';          raw_input->pop_front();

        //HOURS
        *string_buffer = raw_input->front();   raw_input->pop_front();
        if(string_buffer->substr(0, 12) != "Hours       ") { if(debug) cout << "FATAL -> Hours input sorting failed" << endl; exit(1); }
        if(debug) cout << "erasing (" << string_buffer->substr(0, 12) << ")" << endl;
        string_buffer->erase(0, 12);
        if(debug) cout << "InputSort Construction :: setting hours          :: (" << *string_buffer << ")" << endl;
        hours = csv_to_int_vector(*string_buffer);

        //COURSES
        *string_buffer = raw_input->front(); raw_input->pop_front();
        if(string_buffer->substr(0, 5) != "Names") { if(debug) cout << "FATAL -> Names input sorting failed" << endl; exit(1); }
        if(debug) cout << "erasing (" << string_buffer->substr(0, 12) << ")" << endl;
        string_buffer->erase(0, 12);
        if(debug) cout << "InputSort Construction :: setting names          :: (" << *string_buffer << ")" << endl;
        *strings_buffer = csv_to_string_vector(*string_buffer);
        for(auto course_name : *strings_buffer)
            courses.push_back(Course(course_name));


        //N_TEACHERS
        if(debug) cout << "InputSort Construction :: setting n_teachers     :: (" << raw_input->front().back() << ")" << endl;
        n_teachers = raw_input->front().back() - '0';       raw_input->pop_front();

        //TEACHERS
        *string_buffer = raw_input->front();                raw_input->pop_front();
        if(debug) cout << "InputSort Construction :: setting Teachers       :: (" << *string_buffer << ")" << endl;
        *strings_buffer = csv_to_string_vector(*string_buffer);
        for(int i = 0; i < strings_buffer->size(); i++)
            teachers.push_back(Teacher(strings_buffer->at(i)));

        //TEACHER SUBJECTS INPUTTING
        *string_buffer = raw_input->front();                raw_input->pop_front();
        if(string_buffer->substr(0, 3) != "%TL") { cout << "FATAL -> TL courses teacher matrix out of sync" << endl; exit(1); }
        for(int i = 0; i < n_courses; i++)
        {
            *string_buffer = raw_input->front();                raw_input->pop_front();
            *ints_buffer = csv_binary_to_int_vector(*string_buffer, ",");

            for(int j = 0; j < n_teachers; j++)
                if(ints_buffer->at(j) == 1)
                {
                    courses.at(i).teachers.push_back(teachers.at(j).name);
                    teachers.at(j).courses.push_back(courses.at(i).name);
                }

        }

        //TEACHER PREFERENCES INPUTTING
        *string_buffer = raw_input->front();                raw_input->pop_front();
        if(string_buffer->substr(0, 3) != "%LP") { cout << "FATAL -> LP preferences out of sync" << endl; exit(1); }
        for(int i = 0; i < n_teachers; i++)
        {
            *string_buffer = raw_input->front();            raw_input->pop_front();
            *ints_buffer = csv_binary_to_int_vector(*string_buffer, ",");
            teachers.at(i).preferences = *ints_buffer;
        }

        print_teachers();
        print_courses();


        // while(!strings_buffer->empty())
        // {
        //     teachers.push_back(Teacher(strings_buffer->front()));
        //     strings_buffer->pop_front()
        // }

        delete string_buffer;
        delete strings_buffer;
        delete ints_buffer;
        delete teacher_names;


    }

    ~InputSort()
    {

        delete raw_input;
    }
};

#endif
