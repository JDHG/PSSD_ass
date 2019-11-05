#include "EvalUCS_v2.hpp"

// static variables.
// ***********************************
int ProblemUCS::rooms;                  // Teaching rooms
int ProblemUCS::mC;                     // Number of courses
vector<int> ProblemUCS::cHours;         // hours per course
vector<string> ProblemUCS::cNames;      // names of courses
int ProblemUCS::nL;                     // number of lecturers
vector<string> ProblemUCS::lNames;      // names of lecturers
IntMatrix ProblemUCS::TL;
IntMatrix ProblemUCS::LP;
IntMatrix Solution::Timetable;

// simple driver program
// double Eval(int argc, char* argv[]) {
double Eval(string input_file, string time_table, bool new_input, bool debug) {

  string ucsFileName = input_file;
  string ucsSolnFileName = time_table;

  if(new_input) ProblemUCS::readUCSInstance(ucsFileName);;
  double res ;   // place holder for result

    if(debug) cout << "calling readSolution " << endl;
  // if a feasible solution can be read
   if ( Solution::readSolution(ucsSolnFileName)) {

    Solution::printTimetable(Solution::Timetable, ProblemUCS::cNames, ProblemUCS::lNames);

    if(debug) cout << "calling constrains " << endl;
    int constrains = Solution::checkConstraints(Solution::Timetable, ProblemUCS::rooms, ProblemUCS::cHours, ProblemUCS::LP, ProblemUCS::cNames, ProblemUCS::lNames);
    if (constrains == 0)
         cout << "your solution is feasible" << endl;
     else
         cout << "your solution is not feasible" << endl;

      res =  Solution::getFitnessValue(Solution::Timetable, ProblemUCS::mC,ProblemUCS::LP,ProblemUCS::cHours,constrains);
      if(debug) cout << "Fitness value " <<  res << endl;
    }
    else {
          if(debug) cout << "Solution file is not readable " << endl;
    }

    return res;
}
