Coding done by: Tom Galindo a1720286, Jason de Groot a1740630

Arguments to main are <debug> <file_name>

      Hello! Welcome to our timetabler!
      To run this script use the makefile (make)
      Then give required arguments -> ./schedule <debug> <file_name> (<target_score float>) :
          -   <debug> is expected to be 'true' or 'false'
          -   <file_name> is the input file's name
          -   (<target_score float>) optional float value (1.0 or greater) to stop assigner if target score is produced - defaults to 1.0 if not specified
          -   e.g. './schedule false input.txt'  ::  is valid
	  -        './schedule false input.txt 1.4'  ::  is valid
	  -        './schedule false input.txt notcorrect'  ::  is valid but target score will default to 1.0
          -        './schedule input.txt'        ::  is invalid -> requires the debug to be specified
      You almost assuredly want to run the program with debug set to 'false'
      
      Please make use of the <target_score> argument if you wish to save time :)