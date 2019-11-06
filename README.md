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

**28/10/19 -> Jason

I have adapted our program to run two different ways now: left to right and right to left.  To avoid writing separate loops in the assigner function, I realised that the only thing my assigner truly needs to care about is the hour it's looking at. So I just made some new functions to manipulate the hour based on a version number which is passed to the assigner.

I also had to edit the Eval program to flush its static containers when new input came along and only collect input if new input is coming. It was initially reading the input every loop and doubling up all the lecturers/courses/etc. Now it will only read an input file when told (which will be good for performance too).

There is one new bug I'll be fixing next, which is the lecturers can be assigned to do >2 hours in a row if they teach different courses (2 on one course, then 1 or more on another immediately after). My functions only make sure they can't do more than 2 hours for one course at a time, so this will need to change so we can never have >2 hours without a break.

///////////////////////////////////////////////////////////

**31/10/2019 -> TommyG

I've been a bit sparse on my reporting here so this will be bit of a dump. Anyway, here goes . . .

As Jason mentioned above we were keen to experiment "...with writing...permutations to separate external files." This is so significant changes needn't be made to how our program reads files, minimizing the amount of code we'll write that will essentially be accomplishing the exact same thing.

I opted for this job because I had already written the initiall input ripping class and so was familiar with the code I could copy for this task. I started by examining my InputSort class and then essentially stripped out the functioning parts and tried to improve the jankier bits. For example, the initial input sorting where the file is read failed to nicely compartmentalise the data previously because I was attempting to read it into heap memory and delete along the way. I decided that for simplicity I would rely on the compiler. Also, I mostly read through the entire file before splitting the data into separate structures.

Next up was writing to a file with correct formatting. This task was new to me but actually quite easy!
(1) create a fostream object
(2) insert strings with the << operator
(3) then close the object
This meant reading through the member data in the correct order and specifying a file name.

I then took this function (write_to_file(..)) and overloaded it with an int array. The array is meant to specify the order of access and so can manipulate the order of file content. This is designed to be uber-flexible -> if we want different kinds of permutations we have to write code that saves the permutation order into an array (which is the argument for our file writing code).

The first permutation order we've tried is a cyclic one -> {a,b,c} :: {b,c,a} :: {c,a,b}. The classes are arranged in a cyclic way. In future we are hoping to implement many more permutations. The key is not creating too many because permutations are in the order of factorial magnitude, which gets crazy big crazy fast (e.g. having ten classes == 10! > 3 million!!!).

///////////////////////////////////////////////////////////

**31/10/19 -> Jason

Fixed the bug that was complaining about >2 hour assignments without a break. Unfortunately, the eval program still calls it out. Not sure if this is a bug in the eval program or if I just don't understand what constitutes a 'break' in this assignment. I have made a discussion post about this which will hopefully help sort it out.

The assigner now creates 2 timetables for any input: one from left to right and another from right to left. The timetables are compared and the one with the best fitness value is returned. This timetable will be the one that will undergo iterative improvement. Once Tom's input permuter is working and we integrate it into the program, we can get stuck into this.

///////////////////////////////////////////////////////////

**31/10/19 -> TommyG

Having problems with the input permutation in that file writing appears to be stored in a buffer and then on termination of the program these buffered writes are flushed to files. This means that we'll have to handle data permutation internally and begin recoding sections of the input sorting class.

We are seriously considering abandoning this route as it is a decent amount of code to walk through and adapt. If I were to have a go I would definitely want to use the original input sorting class as a reference only. However, any changes (at all!) to the original input sorting code could adversely affect code that generates timetables, so this makes generating inspired code difficult to fit with the rest of the program as it is now.

As it stands, we are hoping to implement basic permutations of the input in the initial assigning algorithm.

///////////////////////////////////////////////////////////

**31/10/19 -> Jason

We have started looking at how we can iteratively improve our timetables. We have decided on a few simple rules to help us get started:
- We will only try and improve a restricted number of iterations (there could be infinite steps to take otherwise)
- An improvement is made if:
    - we move a higher value LP pref to a lower value one (small gain)
    - we are able to allocate a previously unallocated hour (large gain)
    
Given that allocating more hours is more desireable, we will focus on this first. We will need to establish some sort of heuristic, or some identifiable pattern that allows us to manipulate the time table and introduce a new hour. We can start doing this by just inspecting our outputs and messing with them on paper. If we can produce an algorithm that moves hours and assigns new ones, we will have made a big improvement to our program.

///////////////////////////////////////////////////////////

**4/11/19 -> Jason

Our first hour improver is simple. It looks through the timetable row of the courses with outstanding hours and finds single hour assignments. It then checks the surrounding assignments, room constraints, hour constraints, etc. If it passes all tests, it will assign the same lecturer an extra hour, turning it from a 1 hour session into a two hour. This has gained us fitness increases of .5 in some cases, which is pretty good!

Tom is still working on the input permuter. It is looking like we may still be able to use it, which is really cool because that will give us a lot more to work with; It has a good chance of finding good results.

Next we will try to find another case in which extra hours can be reliably assigned. I think this will really be our main focus, since changes like upgrading an LP2 assignment to an LP1 only yields minor fitness gains. Other cases where it is likely we can manipulate the table to assign hours will be things like:
 - when a course has no assignments for a given day
 - when an alternative lecturer for a course can be used to assign a 2 hour session for some 1 hour session (some of the permutations may find some of these)
 
///////////////////////////////////////////////////////////

**5/11/19 -> Tommy G

Building from my last thoughts about adapting the code to work on internal data rather than generate files to later read:
 - I adapted InputSort to accept a list of strings as an input rather than a file,
 - which allowed multiple InputSort objects to be generated from the intial input file,
 - which meant that the Assigner code and eval code could be left untouched,
 - except for reassembling the time_table generated from each input object in the original order of the courses.
 - Additionally, the work done to permute the original inputs into readable files was canibalised;
 - It generates the lists of strings that InputSort objects were converted to take as inputs.

Essentially, overall code changes were about as minimal as possible and considering the timeframe we are currently operating on this was the only feasible option.
That being said I am uneasy with the current state of the code. The original ideas and resulting classes, structures and functions that were generated are all stretched to the limit of their original intentions. Everything that I have worked on is strung together by the tiniest threads and feels unstable. If time was on my side I would take big step back and produce new code from the old with the main goal of taking the core parts that work and building more robust objects with less interoperability.

Still I am really relieved to have gotten some form of permutation working as I have spent an entire week on it at least. It would be particularly soul crushing if I did not achieve the amount that I have so far.

///////////////////////////////////////////////////////////

**5/11/19 -> TommyG

Changed the eval code ~line 300 to 'int courses = ProblemUCS::mC;' as otherwise for small inputs you get seg faults. Added to the discussion forum so other people could potentially benefit from this insight.

///////////////////////////////////////////////////////////

**6/11/19 -> TommyG

Commentary on general state of the code, thoughts and feelings on the assignment :

 - Overall the problem is interesting in that it is an optimisation problem that relates to a real world scenarios. My brother is a teacher and even expressed interest in having a copy of my code for helping timetable in his school.
 - Teacher handling of the resources applied stress to our time management. The extra week given was nice, however, it also puts stress on exam revision. It felt like an exercise in faith to plough on with our side of the code (writing input collection, permutation, optimisation) without knowing precisely how timetables would be evaluated, which was not fun.
 - It's interesting that once we got hold of the eval program we weren't out of the woods; the initial code given didn't compile and once it was compiling it was not instantly intergratable. We had some fun converting it to run on string streams instead, allowing it to evaluate data internally rather than external process text files.
 - Super satisfied with where we ended up finishing. We coded ourselves down many wrong paths but managed to either backtrack (re-code sections) or find a way to jump onto a better path (cannibalise/re-jig IO to allow communication between different classes and functions).
 - Further on coding ourselves down wrong paths (C.S. Lewis "We all want progress, but if you're on the wrong road, progress means doing an about-turn and walking back to the right road; in that case, the man who turns back soonest is the most progressive"). We had the option about halfway through to take a step back and re-assess the data structures we were using. We opted to continue as we were because of time restrictions. However, we possibly would have saved time overall by adapting the input sorting and input permuting classes into one class. As is often the case, attempting something for the first time leaves you at the mercy of learning through mistake-making. If I were to write a scheduler for my brother for example, I would use this code as a reference and attempt to avoid the tight coupling that occured.
 
///////////////////////////////////////////////////////////

**6/11/19 -> Jason & TommyG

Uploaded what will be our final version of the program. The due date is close but so are exams, so we need to finish up with this and get more study done.

Our final version has been adapted to compile with a makefile and produce an output.txt file that testers can read into the Eval program.

On all of our test cases, we managed very good scores. Typically less than 1.6 or so which is pretty good. For simple cases, it often found timetables with scores of 1 nice and fast. We had larger test cases (ones with 16 or so courses) that run for around 30 seconds but also produce scores of around 1.2.

Our assignment algorithm is doing most of the work in our program. We have created a fairly sophisticated system which has integrated the eval program into our own, and runs over hundreds, potentially thousands, of permutations of the original input file. Each timetable produced from each permutation is checked against the current best and stored if it is better. This means we get the best possible timetable our algorithm produces from a huge set of possible timetables. Each timetable is also run through our basic iterative improver which seeks to allocate any hours that were not allocated in the original assignment as this produces the greatest changes to our final score.

As mentioned in earlier logbook entries, the input permutation idea was meant to produce a solid starting point for improvement. But, we realised that our simple improvements could be run on all the permutations without a major performance cost, and so we were likely to find a perfect solution or at very least, a solution with score < 2. The improver was considered simple and efficient because it didn't have to run the evaluation function after every iteration.

So in sum, we are running our entire process on thousands of permutations of the original input to produce a solid timetable.
