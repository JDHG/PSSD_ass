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

**28/10/19 -> Jason

Starting on our optimisation today.

We have a test case which produces a score of 3.36 which is good because we can now try to improve it. After a quick chat, the way we have decided to approach this first stage of optimisation is as follows:
- Create multiple permutations of the input so we have courses and teachers shuffled around.
- Run our basic assigner from from different starting days or go from right to left, etc.

Once we have some of this functionality, we will be able to take the best timetable produced through all this shuffling and start optimising it more specifically through hour reassignments or similar methods. By doing it this way, we will hopefully produce a more optimal starting point for our further optimisations. It is possible that a less optimal timetable would happen to produce a better result at the second optimisation step, so we may keep the top 3 timetables or something like that.

Because of how the Eval program has been integrated into our program, the input sorter now needs to:
- read the input file into objects
- create a set of shuffled parameter permutations
- for each shuffled parameter set, produce a matching string which acts as an input file which can be fed to Eval to produce a score
This will be a bit of work, but it will likely be worth it for an optimisation problem like this. We will be experimenting with writing the permutations to separate external files and then reading them in one at a time in our loop. If we can generate a bunch of files and keep all their names/directory locations in a string array, we can open each file into an ifstream one by one. This way we can avoid making significant changes to how the program reads input, while still creating multiple results in the one loop.

Changing the assignment algorithm will also be a bit challenging. I am thinking I will change the assigner function to take an integer input which tells it which behaviour pattern to implement. This way, we can run the assigner in different ways within loops easily.
As for changing how the hours are assigned, I suppose the easiest place to start will be to get it to assign from right to left instead of left to right. I will probably need to create switch statements with different loop structures within each. This may make the function a little less tractable. On the plus side, all the assignment validity checks (rooms, days, permissions) should work regardless of direction so I could just need to create a different set of for loops if I'm lucky.

///////////////////////////////////////////////////////////
