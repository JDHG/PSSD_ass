# PSSD_ass
PSSD scheduling assignment 2019 s2

LOGBOOK COPY/DUMP inbetween websub commits

***Entries should be dated!!***


/////////////////////////////////////////////////////
**9/10/19

Formed group for the assignment: Jason de Groot - a1740630,  Tom Galindo - a1720286 (Temporary Australians)

Initial problem discussion and plan:

Some initial thoughts on the problem:
- This is an optimisation problem
- There are too many possible solutions to be bruteforced; the potential solution space is very large
- Need to work out an efficient way to find a good solution (chances are it will be suboptimal)

We will start by having a read of the linked resources, just so we don't go too astray too early.
When we start designing, we will start by creating the easiest, most tractable solution that conforms to all constraints. This is so we can get on the scoreboard and have a solid/robust foundational algorithm and program.

We have around 3 weeks to complete this assignment. There are also a few other large assignments for other subjects all due at around the same time, so we are going to have to be quite smart with our time for this one because it seems complicated.
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
**17/10/2019 -> TommyG

At this stage we have made our first major merge into the master file.
The functionality being implemented was the input collector and sorter.

This functionality was implemented with the class InputSort. InputSort can take the raw input form and convert it into structures:

Course  -> A course has       : name, hours and list of Teacher (teachers)
Teacher -> A Teacher has      : name and a list of preferences

This is probably not that difficult to implement. However, my first attempt the day before today was not particularly successful. The problems I had were:

  (1) Thinking I needed to sort the input lines into something as soon as I encountered them
  (2) Writing too many small non-flexible functions
  
(1) ruined the flow of information into containers. For example, the binary matrix indicating which teachers taught which courses came between the names of the lecturers and lecturer preferences. Because I was inputting information into the appropriate containers as they came, I ended up with structures that pointed to each other, which was a confusing hierarchy. I realised that  storing the names of the teachers and then getting the prefferences later would allow me to create teachers, which where then stored in courses
This creates a clear hierarchy of containers.

(2) this was a basic mistake to make at this point as I have had a decent amount of experience producing larger programs. Still, on my second attempt at implementation of a input sorter, these functions were good reference points for larger, more flexible functions.

Overall I like the code I wrote because it is concise and tractable. The only improvement left to make is to make better use of pointers. As it stands, each course contains a copy of a teacher. This means that teachers involved with multiple courses have separate, identical copies. This is a waste of space and makes maintaining any changes to teachers harder to implement.

/////////////////////////////////////////////////////

**19/10/19 -> Jason

Implemented a very basic version of the assignment algorithm. It produces the simplest possible form of a legal timetable.
- assigns first available teacher's 1st preference to first course in line
- prevents over allocating rooms
- does not assign on lunchbreaks or assign more than 2 hours in a row

Essentially, the algorithm assigns the absolute earliest legal position available in the timetable to the earliest available teacher. This is hopefully going to provide a template which we can expand on and optimise as we develop our program.

I still need to allow preferences lower than 1 to be assigned; Currently if the all courses could not be assigned on available first preferences, it would be incomplete. Now that I write this, I realsie I should probably implement a check to our debug setup that notifies us if the timetable was unable to be completed. I feel that the safest way to do this would be to count the non-negative values in the course's timetable slot and compare to its expected hours. Should be simple enough, and will save us from missing things in the future.

/////////////////////////////////////////////////////////

**19/10/19 -> Jason

Basic assignment algorithm has been tidied up quite a lot. A few logic bugs were fixed and some out of bounds exceptions fixed too. We should now be in possession of a fairly robust starting platform to start optmising. It is very modular and I beleive that will come in very handy when we start optimising selections it makes (I hope so anyway).

The output timetables produced should now match the expected output and conform to all constraints imposed by the assignment. It might be wise to create the makefile next and submit a working version to see what's going on in the marking domain. After that, we can get the 'goodness' calculator up and running so we can start optimising the algorithm.

///////////////////////////////////////////////////////////

**23/10/19 -> Jason

Got ahold of the EvalUCS program yesterday. Didn't work at first. Sent it back to Cruz for some tweaking and got it back today. It still didn't work on my laptop because of the reading of getline() into a bool (not entirely sure how that works at her end. different c++ version maybe?). Had to change all getline() statements to be standalone so the return wasn't used. It works now but hopefully that doesn't break anything down the line.

Next problem: The Eval program simply prints info to the console, as it would of course, but we want to be able to probe its return value and use it to find better solutions. This means we will need to integrate it with our program so at the end of each loop in our timetable generator, we can read the fitness value and change behaviour based on what we see. If we get a fitness value of 1, we can stop because the solution is optimal. If >1, we can try different algorithm behaviours to try and produce better results. This also allows us to keep a copy of the timetable with the lowest fitness value so at the end, when all avenues have been exhausted, we get back the best solution we found and write it to output.

I will attempt to convert this Eval program into something we can call in our program. I'm sure there are ways we can do this using BASH commands or other external software/commands but I don't know how to do that yet, so I'll just stick with what I know for now.

///////////////////////////////////////////////////////////
