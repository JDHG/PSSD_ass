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

/////////////////////////////////////////////////////
