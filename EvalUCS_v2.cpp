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
double Eval(string input_file, string time_table, bool debug) {

  // if(argc !=3){
  //   cerr << "usage: ./Eval ucs_problem_filename   ucs_solution filename"
	//  << endl;
  //   exit(EXIT_FAILURE);
  // }

  // string ucsFileName=string(argv[1]);
  // string ucsSolnFileName=string(argv[2]);

  string ucsFileName = input_file;
  string ucsSolnFileName = time_table;

  ProblemUCS::readUCSInstance(ucsFileName);;
  double res ;   // place holder for result


    if(debug) cout << "calling readSolution " << endl;
  // if a feasible solution can be read
   if ( Solution::readSolution(ucsSolnFileName)) {


    Solution::printTimetable(Solution::Timetable, ProblemUCS::cNames, ProblemUCS::lNames);

    if(debug) cout << "calling constrains " << endl;
    int constrains = Solution::checkConstraints(Solution::Timetable, ProblemUCS::rooms, ProblemUCS::cHours, ProblemUCS::LP, ProblemUCS::cNames, ProblemUCS::lNames);
    if (constrains == 0)
         if(debug) cout << "your solution is feasible" << endl;
     else
         if(debug) cout << "your solution is not feasible" << endl;

      res =  Solution::getFitnessValue(Solution::Timetable, ProblemUCS::mC,ProblemUCS::LP,ProblemUCS::cHours,constrains);
      if(debug) cout << "Fitness value " <<  res << endl;
    }
    else {
          if(debug) cout << "Solution file is not readable " << endl;
    }

    return res;
}
