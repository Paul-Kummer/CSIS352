// File: README.txt
// Name: Paul Kummer
// Class: CSIS 352
//Program: prog8
//Modified: 03/03/21


	-[Description]-
Program 8 will allow a user to go over terms and their corresponding definitions of a specified file
in a variety of ways. The user can choose to lookup a term and get its defintion if it exists in the
file chosen. The user may also choose to go over all the terms and definitions one by one from the file.
Furthermore, the user can choose to have definitions shown to them, and they must provide the corresponding
term to the definition to progress to the next term. They will also have the option to reveal the answer or
skip the term if they do not know the answer. Then when the user wants to quit, they can enter 0 or ctrl+D
to exit the portion of the program that they are in. The use of ctrl+d is exit is limited to the trivia or
term read-off portions of the program.


	-[Inputs]- (input method : input type : description)
1.) keyboard : int/string : values interpreted as commands or answers to prompts.
2.) test.txt : text file : a text file can be input as a command line argument. This file should hold
							operation commands and values for operations that require additonal input


	-[Outputs]- (output method : output type : description)
1.) display : string : text displayed on monitor showing what operations are doing or requesting


	-[Design]-
The program will begin by providing the user with a list of options to choose from. When an option is selected
the operations function is called to try to perform the selected function. The user may choose to change the 
input file, get a definition of a term, match terms to defintions, go over all the term defintion pairs, or
exit the program.

Initially the program will populate a map with key value pairs from a default file called "studyTerms". In any
term-definition file the term will be all the characters on each line up until the character ":" is encountered.
After the colon ":", all the characters until the charcter "#" is reached will be stored as the terms definiton.

	(Term & Definition Example)
	This is a term: The term stopped at the colon character. This is now the definition and the
								definition will end after the character of the last word of this senctence#

When the user chooses a differnt file to get term defintion values from, the program will attempt to open the
new file. If it successfully opens the new file. The defMap will be cleared and populated with new terms and
definitions. If the file unsucessfully opens, the map will remain unchanged.

Programatic errors will be handled with try catch statments, and the program will continue running if an error
occurs that is capable of being handled. When errors occur from users enter invalid commands, the program will
notify the user that it could not read their command, and will request them to ener a new command.

While going over terms and definitions in either a readout or an answer request, the user will have a pause
between outputs to allow them to review the term and definition. Without this pause, the console window gets
flooded with output, making it hard to focus on each new term. When the user uses a test file, there are no
pauses and all commands are executed until the end of the file. This is primarily used for testing purposes.



	-[Files] (file : function : description)-
main.cpp : main : executes the main line of logic, allowing the user to input operations

prototypes.h : declaration : declares the selectOperation function and other functions

operations.cpp : definition : defines the function selectOperation, which interprets users commands

functions.cpp : definition : defines functions used in operations

makefile : compilation & linking : creates and executable of prog8

README.txt : information : gives detailed information about prog8

test.txt : test user input : creates user input from a text file

studyTerms.txt : term/definitions text : small realistic example of term and definition values

testDef.txt : term/definitions text : larger unrealistic example of potential user inputs in differnt formats


	-[Testing]-
The program has be tested with invalid and valid files to ensure it doesn't crash. Also, the term/defintion files
have been tested with characters from many different languages. The program hasn't been tested with very large files.
There is potentially an error that could occur from using to much memory, but it will probably be caught by the default
exception handler.


	-[Bugs]-
1) when using, I believe to be true, Hebrew characters, there are special characters that cause the text to be alligned
	strangely. I think it is because the language is written from right to left, or the computer misinterprets some of
	the characters. I get a warning loading the text file into Visual Studio Code about the file have characters that
	can cause problems. However, the program still runs and outputs to the best of its ability.

2) there were bugs of the user having to it enter multiple times to progress through terms, but I think they are resolved
	through strategically placed cin.ignore(100, '/n');