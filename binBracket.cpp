#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm> 
#include <tgmath.h>
using namespace std;

class binBracket
{
	public:
		vector<bool> data;
		int dataToIndex() 
		{
			int ret = 0;
			int size = this->data.size();
			for (int k = 0; k < size; ++k)
			{	
				ret = ret + this->data[k] * pow(2,(size-k)-1);
			}
			return ret;
		}
		static vector<bool> valueToData(int value, bool isCommand)
		{
			vector<bool> outputVec;
			int nval = value;
			int iterations = 0;
			while (nval > 0)
			{
				int mod = nval%2;
				if (mod == 0)
				{
					outputVec.push_back(false);
				}
				if (mod == 1)
				{
					outputVec.push_back(true);
				}
				nval = nval / 2;
				++iterations;
			}
			if (isCommand)
			{
				outputVec.push_back(false);
			}
			std::reverse(outputVec.begin(),outputVec.end()); 
			return outputVec;
		}
};

int main(int argc, char** argv)
{
	//system("clear"); //Clear text. Removed for now.
	cout << "\n\nbinBracket v0.15";
	vector<binBracket> binBrackets;
	if (argc < 2)
	{
		cout << "\nPlease enter binBracket code to run it, or use \"--help\" (without quotes) as the first argument to see commands.";
		return -1;
	}
	if (argv[1] == "--help")
	{
		cout << "\nTo run this program, enter one of these arguments before typing in your code:\n\n--run-binary-verbose\nAccepts a raw binary string\n\n--run-separated-verbose\nAccepts commands and data separated by spaces";
	}
	if (argc == 2)
	{
		char argument[65536];
		strcpy(argument, argv[1]);
		cout << "\nInput:\n";
		vector<bool> binary;
		int i = 0;
		const int max = strlen(argv[1]);
		while (i < max)
		{
			char thisChar = argument[i];
			cout << thisChar;
			if (thisChar == '0')
			{
				binary.push_back(false);
			}
			if (thisChar == '1')
			{
				binary.push_back(true);
			}
			++i;
		}
		cout << "\nBinary size:" << binary.size();
		//now that we have loaded it into a binary vector, we can convert it to a vector of vectors (e.g. groups of binary data)
		
		bool bracketSignifier = false;
		binBracket currentBracket = binBracket();
		const int max2 = binary.size();
		i = 0;
		while (i < max2)
		{
			bool thisThingymabob = binary[i];
			if (bracketSignifier)
			{
				if (!thisThingymabob) //basically this indicates a closed bracket
				{
					binBrackets.push_back(currentBracket);
					currentBracket = binBracket();
				}
			}
			else
			{
				currentBracket.data.push_back(binary[i]);
			}
			++i;
			bracketSignifier = !bracketSignifier;
		}
	}
	if (argc > 2)
	{
		for (int I = 1; I < argc; I++)
		{
			char argument[65536];
			strcpy(argument, argv[I]);
			vector<bool> binary;
			int i = 0;
			int max = strlen(argv[I]);
			while (i < max)
			{
				char thisChar = argument[i];
				cout << thisChar;
				if (thisChar == '0')
				{
					binary.push_back(false);
				}
				if (thisChar == '1')
				{
					binary.push_back(true);
				}
				++i;
			}
			binBracket currentBracket = binBracket();
			int max2 = binary.size();
			i = 0;
			while (i < max2)
			{
				bool thisThingymabob = binary[i];
				currentBracket.data.push_back(binary[i]);
				++i;
			}
			binBrackets.push_back(currentBracket);
		}
	}
	cout << "\nNumber of bin brackets:\n" << binBrackets.size();
	cout << "\nHere are each bin bracket:\n";
	const int max3 = binBrackets.size();
	int i = 0;
	while (i < max3)
	{
		for (int j = 0; j < binBrackets[i].data.size(); j++)
		{
			cout << binBrackets[i].data[j];
		}
		++i;
		cout << "\n";
		}
	int binCount = binBrackets.size();
	const int origBinCount = binCount;
	int index = 0;
	int ops = 0;
	while (index < binCount && ops < pow(origBinCount,3) + binCount) //for now, this should do
	{
		vector<bool> thisOperation = binBrackets[index].data;
		int opLength = thisOperation.size();
		bool advance = true;
		++ops;
		
		string opCode = "";
		for (int j = 0; j < opLength; j++)
		{
			if (thisOperation[j] == 0)
			{
				opCode = opCode + "0";
			}
			if (thisOperation[j] == 1)
			{
				opCode = opCode + "1";
			}
		}
		cout << "\n" << index << " OpCode " + opCode;
		cout << " " << binBrackets[index].dataToIndex();
		if (opLength >= 4)
		{
			if (opCode == "0100") //Set
			{
				cout << " Set Command found";
				if (index + 2 < binCount) //is it safe to advance?
				{
					int pos1 = binBrackets[index+1].dataToIndex();
					int pos2 = binBrackets[index+2].dataToIndex();
					if (pos1 < binCount && pos2 < binCount)
					{
						cout << " Command executed";
						binBrackets[pos1].data = binBrackets[pos2].data;
					}
				}
			}
			if (opCode == "0101") //Branch
			{
				cout << " Branch Command found";
				if (index + 3 < binCount) //is it safe to advance?
				{
					int pos1 = binBrackets[index+1].dataToIndex();
					int pos2 = binBrackets[index+2].dataToIndex();
					int gotoPos = binBrackets[index+3].dataToIndex();
					if (pos1 < binCount && pos2 < binCount && gotoPos < binCount)
					{
						if (binBrackets[pos1].dataToIndex() > binBrackets[pos2].dataToIndex())
						{
							cout << " Command executed, greater ";
							cout << binBrackets[pos1].dataToIndex() << " > " << binBrackets[pos2].dataToIndex();
							index = gotoPos;
							advance = false;
						}
						else
						{
							cout << " Command executed, not greater ";
							cout << binBrackets[pos1].dataToIndex() << " <= " << binBrackets[pos2].dataToIndex();
							index = index + 3;
						}
					}
				}
			}
			if (opCode == "0110") //Destroy
			{
				cout << " Destroy Command found";
				if (index + 1 < binCount)
				{
					int pos = binBrackets[index+1].dataToIndex();
					if (pos < binCount)
					{
						cout << " Command executed";
						binBrackets.erase(binBrackets.begin() + pos);
						if (pos <= index)
						{
							--index;
						}
					}
				}
			}
			if (opCode == "0111") //Declare
			{
				cout << " Declare Command found";
				if (index + 2 < binCount) //is it safe to advance?
				{
					int pos = binBrackets[index+1].dataToIndex();
					int pos2 = binBrackets[index+2].dataToIndex();
					if (pos < binCount && pos2 < binCount)
					{
						cout << " Command executed ";
						binBracket newBin = binBracket();
						newBin.data = binBrackets[pos2].data;
						cout << "Inserted data to " << pos;
						binBrackets.insert(binBrackets.begin() + pos, 1, newBin);
						if (pos <= index)
						{
							++index;
						}
					}
				}
			}
		}
		else if (opLength >= 3)
		{
			if (opCode == "010") //Subtract
			{
				cout << " Subtract Command found";
				if (index + 2 < binCount) //is it safe to advance?
				{
					int pos1 = binBrackets[index+1].dataToIndex();
					int pos2 = binBrackets[index+2].dataToIndex();
					if (pos1 < binCount && pos2 < binCount)
					{
						int result = binBrackets[pos1].dataToIndex()-binBrackets[pos2].dataToIndex();
						if (result < 0)
						{
							result = 0;
						}
						cout << " Command executed with result ";
						cout << result;
						bool isCommand = (binBrackets[index+1].data[0] == false);
						binBrackets[pos1].data = binBracket::valueToData(result,isCommand);
					}
				}
			}
			if (opCode == "011") //Add
			{
				cout << " Add Command found";
				if (index + 2 < binCount) //is it safe to advance?
				{
					int pos1 = binBrackets[index+1].dataToIndex();
					int pos2 = binBrackets[index+2].dataToIndex();
					if (pos1 < binCount && pos2 < binCount)
					{
						int result = binBrackets[pos1].dataToIndex()+binBrackets[pos2].dataToIndex();
						cout << " Command executed with result ";
						cout << result;
						bool isCommand = (binBrackets[index+1].data[0] == false);
						binBrackets[pos1].data = binBracket::valueToData(result,isCommand);
					}
				}
			}
		}
		else if (opLength >= 2)
		{
			if (opCode == "00") //Pos
			{
				cout << " Pos Command found";
				if (index + 1 < binCount) //is it safe to advance?
				{
					int pos = binBrackets[index+1].dataToIndex();
					if (pos < binCount)
					{
						cout << " Command executed";
						bool isCommand = (binBrackets[pos].data[0] == false);
						binBrackets[pos].data = binBracket::valueToData(index,isCommand);
					}
				}
			}
			if (opCode == "01") //Goto
			{
				cout << " Goto Command found";
				if (index + 1 < binCount) //is it safe to advance?
				{
					int pos = binBrackets[index+1].dataToIndex();
					if (pos < binCount)
					{
						cout << " Command executed";
						index = pos;
						advance = false;
					}
				}
			}
		}
		if (advance)
		{
			index = index + 1;
		}
		binCount = binBrackets.size();
	}
	cout << "\nOutputted binary:\n";
	string outbin = "";
	for (int j = 0; j < binBrackets.size(); j++)
	{
		for (int k = 0; k < binBrackets[j].data.size(); k++)
		{
			if (binBrackets[j].data[k] == false)
			{
				outbin = outbin + "0";
			}
			if (binBrackets[j].data[k] == true)
			{
				outbin = outbin + "1";
			}
			if (k < binBrackets[j].data.size() - 1)
			{
				outbin = outbin + "1";
			}
			else
			{
				outbin = outbin + "0";
			}
		}	
	}
	cout << outbin;
	outbin = "";
	cout << "\nBinary converted to bracket notation:\n";
	for (int j = 0; j < binBrackets.size(); j++)
	{
		outbin = outbin + "{";
		for (int k = 0; k < binBrackets[j].data.size(); k++)
		{
			if (binBrackets[j].data[k] == false)
			{
				outbin = outbin + "0";
			}
			if (binBrackets[j].data[k] == true)
			{
				outbin = outbin + "1";
			}
		}
		outbin = outbin + "} ";	
	}
	cout << outbin << "\n";
	return 0;
}
