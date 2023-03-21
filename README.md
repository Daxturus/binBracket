# binBracket
The binBracket language is an esolang somewhat similar to Brainf---, containing a very small instruction set. However, unlike Brainf--- or many other conventional esolangs I know of, both a binBracket program's memory AND instructions are stored on a single tape. This means that the instructions executed by a program can be manipulated during runtime by the program itself, which can allow for incredibly complex behaviors. binBracket's instructions use arguments, relying on information contained within other conceptual memory cells ("brackets") to perform tasks. For instance, a memory cell-bracket containing the binary representation of an addition function would look to the next two cells as pointers, adding the number at the location of the second pointer to the number at the location of the first pointer. These pointers themselves can be changed by instructions, alongside everything else.

Each cell contains a raw binary string which can be used to represent the program's memory and instructions. Under the hood, memory and instructions are stored as a vector of vectors containing boolean data.

The current implementation I've made of binBracket in C++ is probably horribly cursed, as this is my first go at a C++ program. I wrote the entire first working draft of this language in just about six hours.

Each cell is either a few bits of information represented by a symbol or function name, or raw data bits separated in code by brackets. Each cell is normally iterated in sequence, with program flow controlled by the position of this "iterator" (currently not a real C++ iterator, mind you). Each bracket can be read, re-read multiple times, or skipped entirely by changing the position of the "iterator" using branch or goto. Brackets/cells containing raw non-functional data are simply moved over by the iterator; these are mainly used to store information within the program.

Brackets are (currently) represented within input data using every second inputted bit, in the format dBdBdBdB... where d represents data and B represents bracketing bits. A bracketing bit of zero essentially acts as a closing bracket; all data bits after the last zero bracketing bit, and before the latest bracketing bit, are conceptually placed within the same bracket/memory cell/binary string/boolean vector... thingy. Everything is still in early stages of development. I don't quite have names for everything yet.


Here are the eight currently-implemented commands:
(You do not really need more than these)

00: pos ($)

	Sets the contents of a bracket at a certain position to the next position index after pos and its bracket.
	
	{0}pos{0} yields {11}pos{0}.
	{0}{0}pos{1} yields {0}{100}pos{1}.

01: goto (*)

	Moves the current position index to a certain index. 
	
	goto{0} infinitely loops.
	
010: subtract (-)

	Reduces the number within a bracket by a value at a certain position.
	Adding to a bracket with a 0 at the front keeps the 0 at the front; this constitutes changing a value to a different command.
  	{100}{1}subtract{0}{1} yields {11}{1}subtract{0}{1}
	
011: add (+)

	Increases the number within a bracket by a value at a certain position.
  	Adding to a bracket with a 0 at the front keeps the 0 at the front; this constitutes changing a value to a different command.
	{100}{1}add{0}{1} yields {101}{1}add{0}{1}
	
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
	declare{1}{10} yields declare{10}{1}{10} (performing this a second time will yield declare{10}{1}{1}{10})

Here is an example program which loops 8 times, with each example less abstract than the last.

{0}; {1}; {1000}; branch({0}, {10}, {1100}); add({0},{1}); goto({0}); {0} 

{0}; {1}; {1000}; %({0}, {10}, {1100}); +({0}, {1}); *({0}); {0} 

{0}{1}{1000}%{0}{10}{1100}+{0}{1}*{0}{0}

{0}{1}{1000}{0101}{0}{10}{1100}{011}{0}{1}{01}{0}{0}

0 1 1000 0101 0 10 1100 011 0 1 01 0 0 

0010110101000111011000110011110100011110001001100000  (Entering this into the V0.1 compiler will run the program, outputting a new but similar binary string.)



Ideas for the future:
Since the program's entire state is conveniently stored in a single binary string, binBracket can easily be loaded and saved to a file, or even run out of one. Though binBracket's current implementation is not optimized for speed, and is not in a parallelizeable state (making it bad for computational purposes), I can see it being used to compute tasks that would normally take a computer days to complete -- granted, binBracket wouldn't be the fastest solution, but a binBracket program backed up to files regularly would be highly resilient to unforseen events like power loss, compared to programs stored solely in RAM.
I plan on creating sample scripts to show off binBracket's capabilities, such as creating a custom functions system and a dynamically-sized vector, and computing the first N primes or so.
