#include "CAM_Helper.h"

/*
	 * Checks if a given string contains another string
	 * @param s: The string to search in
	 * @param target: The string to search for
	 * @returns True or false if the target is found in s
	 */
bool CAM_Helper::stringContains(std::string s, std::string target)
{
	//Checks for out of bounds errors
	if (s.length() > target.length())
	{
		for (size_t i = 0; i < s.length() - target.length(); i++)	//Loops through the string
		{
			std::string ss = s.substr(i, target.length());			//Takes a substring the size of the target
			if (ss == target)
			{
				return true;	//The substring matches the target					
			}
		}
	}
	return false; //Did not find a match
}

/*
 * Sets the speed of CAM_print()
 * @param slow: Set the speed of printing to slow? Defaults to true
 */
void CAM_Helper::setSlow(bool slow)
{
	Fast = slow ? false : true;
}

/*
 * Indents the text based on the number of indents set in CAM_setIndent()
 */
void CAM_Helper::indent() const
{
	for (int i = 0; i < indents; i++)
	{
		std::cout << TAB;
	}
}

/*
 * Clears the screen and indents the cursor
 */
void CAM_Helper::newScreen() const
{
	std::cout << ICS_CLEAR_SCREEN;
	indent();
}

/*
 * Sets the indents of CAM_print()
 * @param numOfIndents: The number of indents to be added to each side of the text
 */
void CAM_Helper::setIndent(int numOfIndents)
{
	indents = numOfIndents;
	std::cout << std::endl;
	indent();
}

/*
 * Converts an entire string to all lowercase
 * 
 * @param input The string to be converted into lowercase
 * 
 * @returns The lowercase string
 */
std::string CAM_Helper::lowercase(std::string& input)
{
	for (unsigned int i = 0; i < input.length(); i++) //Loops for every character
	{
		if (islower(input[i]) == false)
		{
			input[i] = tolower(input[i]);
		}
	}
	return input;
}

/*
 * Prints text to the screen, and automatically checks if a word will get cut off when printed on the edge of the screen
 * and will make it go to a new line and indents the text on both sides
 * 
 * @param s: The string to be printed
 * @param newLine: Print a newline and indent after the string is finished printing? Defaults to true
 * @param fast: Print the text without delay in between characters? Defaults to false
 */
int CAM_Helper::print(std::string s, bool newLine, bool fast) const
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;	//Used for finding console width
	int consoleWidth = 0;				//Used to store console witdh
	bool hasSpace = false;				//Checks that the string has a space, to make sure it doesn't get cut off halfway on the edge of the window
	int printed = 0;					//How many charcters have been printed

	//Finds the console size, dont ask me how
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		// an error occourred
		std::cerr << "Cannot determine console size." << std::endl;
	}
	else
	{
		consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left - indents * 16;		//An indent is 8 characters long, so subtracting indents times 16 will indents both sides of the screen
	}

	for (size_t i = 0; i < s.length(); i++)		//Repeats for every character in the string and checks if they have a space in them.
	{
		if (s[i] == ' ')
		{
			hasSpace = true;
			i = s.length();
		}
	}

	int totalPrinted = 0;
	for (size_t i = 0; i < s.length(); i++)		//Repeats for every character in the string
	{
		if ((s[i] == ' ' or not hasSpace) and i > 0)	//If the character to be printed is a space, then it will check if the next word can fit on the rest of the line
		{
			//Tokenizes the next word in the string
			std::string holder = "";
			int spaceLeftInLine = consoleWidth - printed;		//Number of charcters keft in the console window
			std::stringstream ss;
			ss << s.substr((i + 1), (s.length() - 1));
			getline(ss, holder, ' ');

			if (holder.length() >= spaceLeftInLine)		//If there are more characters than space left, it will move the cursor to a new line
			{
				std::cout << std::endl;
				indent();
				s.erase(s.begin() + i);	//Erases the space so that it doesn't count as a printed character, because the newline replaces it
				printed = 0;
			}
		}
		std::cout << s[i];		//Prints the next character

		//Updates counts
		printed++;
		totalPrinted++;
		if (not fast and not Fast)	//If the delay is wanted
		{
			ICS_sleep(PRINTING_DELAY);
		}
	}
	if (newLine)	//after the string has been printed, move to a newline if wanted
	{
		std::cout << std::endl;
		indent();
	}
	return totalPrinted;		//return how many characters were printed
}

/*
 * Prints spaces to the screen to reach a certain point, used for constistent columns
 * 
 * @param printed:		How many characters have already been typed
 * @param total:		The total spacing required
 * @returns				The amount of spaces printed
 */
int CAM_Helper::printSpaces(int printed, int total) const
{
	int printedSpaces = 0;
	for (int i = 0; i < total - printed; i++)		//repeats for the difference between printed and total
	{
		printedSpaces += print(" ", false);		//prints a space
	}
	return printedSpaces;
}

/**
 * Waits for the user to press a key before continuing with the program, similar
 * to system("cls") in Windows, but this function should be platform independent
 *
 * Automatically moves the cursor to a new line, resets the colour, and indents based on CAM_setIndent()
 */
void CAM_Helper::pause() const
{
#ifdef _WIN32
	// on Windows, this will be exectuted
	print(NEWLINE);
	std::cout << WHITE_TEXT;
	system("pause");
	print("");
	indent();
#else
	// all other operating systems will execute this
	print(NEWLINE);
	std::cout << WHITE;
	std::cout << "Press any key to continue . . .";
	getchar();
	print("");
	indent();
#endif
}


/*
 * Capitalizes the first character in a string if it is a letter
 * 
 * @param input The string to be capitalized
 * @returns The capitalized string
 */
void CAM_Helper::capitalize(std::string& input)
{
	if (not isupper(input[0]))
	{
		input[0] = toupper(input[0]);
	}
}

/*
 * Truncates a string to a specified length
 * @param input: The string to be truncated
 * @param length: The length to be truncated to, defaults to MAX_STRING_LENGTH
 * @returns The capitalized string
 */
void CAM_Helper::truncateString(std::string& input, int length)
{
	if (input.length() > length)
	{
		input = input.substr(0, length);
	}
}

/*
 * Deletes any spaces at the beginning of a string
 *
 * @param s: The string to be stripped of spaces
 */
void CAM_Helper::stripSpaces(std::string& s)
{
	bool hasContent = false;
	for (unsigned int i = 0; i < (int)s.length(); i++)		//Checks that the string is not entirely spaces
	{
		if (s[i] != ' ')
		{
			hasContent = true;
			i = (int)s.length();
		}
	}
	bool repeat = false;

	if (hasContent)		//If the string is not just spaces, the loop through deleting spaces until the first character is not a space
	{
		do
		{
			repeat = false;
			if (s.length() > 2 and s[0] == ' ')
			{
				s = s.substr(1, s.length() - 1);
				repeat = true;
			}
		} while (repeat);
	}
}

/*
 * Prompts the user repeatedly to enter an input, and explain what the valid commands are if a wrong input is given. Will only exit after the player enters a valid command
 *
 * @param commands[]: The valid commads
 * @param question: The prompt to ask the user
 * @param input: To read the user input value after exiting the function
 * @param num: The number of valid commands
 * @param commandColour: The colour that the commands should be printed in to make it easier for the user to understand
 * @param lowercase: Should the input be converted to lowercase before checking for macthes with valid commands? Defaults to true
 * @returns The capitalized string
 */
void CAM_Helper::handleInput(std::string commands[], std::string question, std::string& input, int num, std::string commandColour, bool _lowercase)
{
	bool wrongInput = false;
	do
	{
		wrongInput = false;	//Resets
		print(question);//Prompts

		//Lists the valid commands
		setSlow(false);
		print("(", false);
		for (int i = 0; i < num; i++)
		{
			print(commandColour + commands[i] + WHITE_TEXT, false);
			if (i != num - 1)
			{
				print(", ", false);
			}
			else
			{
				print(")");
			}
		}
		setSlow();
		getline(std::cin, input);	//Takes input
		print("");
		stripSpaces(input);		//Strips spaces from beginning
		if (_lowercase)
		{
			lowercase(input);	//Lowercase if needed
		}
		for (int i = 0; i < num; i++)//Repeats for each command, and checks if it equals input, if it does it exits the loop, if not, sets wrongInput to true
		{
			if (input != commands[i])
			{
				wrongInput = true;
			}
			else
			{
				wrongInput = false;
				i = num;
			}
		}

		if (wrongInput)	//If the user didn't enter a valid command, print out their options, and loop back to the start
		{
			setSlow(false);
			print("");
			print("\"" + input + "\" is not a valid command. The valid commands are: ", false);
			for (int i = 0; i < num; i++)
			{
				//Grammar checking and formatting
				if (i == num - 1)
				{
					print("or ", false);
				}
				print(commandColour + commands[i] + WHITE_TEXT, false);
				if (i < num - 1)
				{
					print(", ", false);
				}
				else
				{
					print("");
				}
			}
			print("");
			setSlow();
		}
	} while (wrongInput);
}

/*
 * Centres a given text in a given space
 *
 * @param text: The text to be printed
 * @param totalSpace: The space for the text to be centred in
 * @param colour: The colour of the text
 */
void CAM_Helper::centreText(std::string text, int totalSpace, std::string colour) const
{
	totalSpace -= (int)text.length();
	int firstSpacing = totalSpace / 2;

	for (int i = 0; i < firstSpacing; i++)
	{
		std::cout << " ";
	}

	print(colour + text + WHITE_TEXT, false);


	int spaceLeft = totalSpace - firstSpacing;
	for (int i = 0; i < spaceLeft; i++)
	{
		std::cout << " ";
	}
}