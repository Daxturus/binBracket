# binBracket
The binBracket language is an esolang somewhat similar to Brainf---, containing a very small instruction set. However, unlike Brainf--- or many other conventional esolangs I know of, both a binBracket program's memory AND instructions are stored on a single tape. This means that the instructions executed by a program can be manipulated during runtime by the program itself, which can allow for incredibly complex behaviors. Also, unlike Brainf---, binBracket's instructions are far more parameter-based, relying on information contained within other conceptual memory cells ("brackets") to perform tasks. For instance, a memory cell-bracket containing the binary representation of an addition function would look to the next two cells as pointers, adding the number at the location of the second pointer, to the number at the location of the first pointer.

Each cell contains a raw binary string which can be used to represent the program's memory and instructions. Under the hood, memory and instructions are stored as a vector containing boolean data.

The current implementation I've made of binBracket in C++ is probably horribly cursed, as this is my first go at a C++ program. I wrote the entire first working draft of this language in just about six hours.

Brackets are (currently) represented within input data using every second inputted bit, in the format dBdBdBdB... where d represents data and B represents bracketing bits. A bracketing bit of zero essentially acts as a closing bracket; all data bits after the last zero bracketing bit, and before the latest bracketing bit, are conceptually placed within the same bracket/memory cell/binary string/boolean vector... thingy. Everything is still in early stages of development. I don't quite have names for everything yet.


Here are the eight currently-implemented commands:
(You do not really need more than these)

00: pos ($)

	Sets the contents of a bracket at a certain position to the next position index after pos and its bracket.
	
	{0}pos{0} yields {100}pos{0}.
	{0}{0}pos{0} yields {101}pos{0}.

01: goto (*)

	Moves the current position index to a certain index. 
	
	goto{0} infinitely loops.
	
010: subtract (-)

	Reduces the number within a bracket by a value at a certain position.
	Adding to a bracket with a 0 at the front keeps the 0 at the front; this constitutes changing a value to a different command.
  	{100}{}subtract{0}{1} yields {11}subtract{0}{1}
	
011: add (+)

	Increases the number within a bracket by a value at a certain position.
  	Adding to a bracket with a 0 at the front keeps the 0 at the front; this constitutes changing a value to a different command.
	{100}add{0}{1} yields {101}add{0}{1}
	
0100: set (=)

	Sets a number at a certain position to a value from another position.
	{1}{1000}set{1}{0} yields {1}{1}set{1}{0}
	
0101: branch (%)
	
	Goes to a certain position if a number at a position is greater than the other at a different position.
	{1}{10}branch{0}{1}{1001}subtract{0}{1}add{0}{1} yields {10}{10}branch{0}{1}{1001}subtract{0}{1}add{0}{1} (Note how the subtract function is skipped due to branch)

0110: destroy (#)

	Removes the bracket at a certain positional index.
	{1}destroy{0} yields destroy{0}
	
0111: declare (!)

	Creates a bracket BEFORE a certain position with the declared value.
	declare{0}{1} yields {1}declare{0}{1}
	declare{1}{10} yields declare{10}{1}{10}

Here is an example program which loops 8 times, with each example less abstract than the last.

{0}; {1}; {1000}; branch({0}, {10}, {1100}); add({0},{1}); goto({0}); {0} 

{0}; {1}; {1000}; %({0}, {10}, {1100}); +({0}, {1}); *({0}); {0} 

{0}{1}{1000}%{0}{10}{1100}+{0}{1}*{0}{0}

{0}{1}{1000}{0101}{0}{10}{1100}{011}{0}{1}{01}{0}{0}

0 1 1000 0101 0 10 1100 011 0 1 01 0 0 

0010110101000111011000110011110100011110001001100000  (Entering this into the V0.1 compiler will run the program, outputting a new but similar binary string.)
