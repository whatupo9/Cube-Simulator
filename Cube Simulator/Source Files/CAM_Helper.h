#ifndef CAM_HELPER_H
#define CAM_HELPER_H


#include <string>												//For string
#include <iostream>												//For cout, endl, getline, and cin
#include <sstream>												//For stringstream
#include <Windows.h>											//For finding console width in characters

#include "ICS_ConsoleHelper.h"									//For setting text colour and putting thread to sleep

const int PRINTING_DELAY = 1;									//Delays between printing characters using CAM_print() in milliseconds
const int MAX_STRING_LENGTH = 20;								//The default value that strings are truncated to in CAM_truncateString()

const std::string NEWLINE = "\n";								//Escape sequence for a new line for more oragnized code
const std::string TAB = "\t";									//Escape seqeunce for an indent for more organized code
const std::string WHITE_TEXT = ICS_textColor(255, 255, 255);	//The default colour of the console window

class CAM_Helper
{
	int indents = 0;											//The number of indents for printing 
	bool Fast = false;											//Skip the delay in between printing characters

public:

	/**
	 * Checks if a given string contains another string
	 * 
	 * @param s: The string to search in
	 * @param target: The string to search for
	 * @returns True or false if the target is found in s
	 */
	bool stringContains(std::string s, std::string target);

	/**
	 * Sets the speed of print()
	 * 
	 * @param slow: Set the speed of printing to slow? Defaults to true
	 */
	void setSlow(bool slow = true);

	/**
	 * Indents the text based on the number of indents set in setIndent()
	 */
	void indent() const;

	/**
	 * Clears the screen and indents the cursor
	 */
	void newScreen() const;

	/**
	 * Sets the indents of print()
	 * 
	 * @param numOfIndents: The number of indents to be added to each side of the text
	 */
	void setIndent(int numOfIndents);

	/**
	 * Converts an entire string to all lowercase
	 * 
	 * @param input The string to be converted into lowercase
	 * 
	 * @returns The lowercase string
	 */
	std::string lowercase(std::string& input);

	/**
	 * Prints text to the screen, and automatically checks if a word will get cut off when printed on the edge of the screen
	 * and will make it go to a new line and indents the text on both sides
	 * 
	 * @param s: The string to be printed
	 * @param newLine: Print a newline and indent after the string is finished printing? Defaults to true
	 * @param fast: Print the text without delay in between characters? Defaults to false
	 */
	int print(std::string s, bool newLine = true, bool fast = false) const;
	
	/**
	 * Prints spaces to the screen to reach a certain point, used for constistent columns
	 * 
	 * @param printed:		How many characters have already been typed
	 * @param total:		The total spacing required
	 * @returns				The amount of spaces printed
	 */
	int printSpaces(int printed, int total) const;

	/**
	 * Waits for the user to press a key before continuing with the program, similar
	 * to system("cls") in Windows, but this function should be platform independent
	 *
	 * Automatically moves the cursor to a new line, resets the colour, and indents based on setIndent()
	 */
	void pause() const;

	/**
	 * Capitalizes the first character in a string if it is a letter
	 * 
	 * @param input The string to be capitalized
	 * @returns The capitalized string
	 */
	void capitalize(std::string& input);

	/**
	 * Truncates a string to a specified length
	 * 
	 * @param input: The string to be truncated
	 * @param length: The length to be truncated to, defaults to MAX_STRING_LENGTH
	 * @returns The capitalized string
	 */
	void truncateString(std::string& input, int length = MAX_STRING_LENGTH);

	/**
	 * Deletes any spaces at the beginning of a string
	 *
	 * @param s: The string to be stripped of spaces
	 */
	void stripSpaces(std::string& s);

	/**
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
	void handleInput(std::string commands[], std::string question, std::string& input, int num, std::string commandColour, bool lowercase = true);

	/**
	 * Centres a given text in a given space
	 *
	 * @param text: The text to be printed
	 * @param totalSpace: The space for the text to be centred in
	 * @param colour: The colour of the text
	 */
	void centreText(std::string text, int totalSpace, std::string colour = "") const;
	
	/**
	 * Swaps two values
	 */
	template <typename T>
	void swap(T& x, T& y)
	{
		T temp = x;
		x = y;
		y = temp;
	}

	/**
	 * This converts the given value to ascii.
	 *
	 * @param value			The value to convert to a string.
	 * @returns				The string representation of the value.
	 */
	template <typename T>
	std::string vtoa(T value)
	{
		// write the data to a string stream
		std::stringstream ss;
		ss << value;

		// return the result
		return ss.str();
	}

	/**
	 * If value is less than min, it is set to min.
	 * If value is greater than max, it is set to max.
	 *
	 * @param value		The value to clamp.
	 * @param min		The minimum that value can be.
	 * @param max		The maximum that value can be.
	 */
	template <typename T>
	void clamp(T& value, T min, T max)
	{
		// make sure value is no less than min
		if (value < min)
		{
			value = min;
		}

		// make sure value is no more than max
		if (value > max)
		{
			value = max;
		}
	}

	/**
	 * Checks if a value is in an array
	 *
	 * @param arr[]:	The array of values to search in.
	 * @param text:		The value to search for.w
	 * @param n:		The size of arr[].
	 * @returns			The position of text in arr[], or -1 if arr[] did not contain c.
	 * @returns			Refernced int is assigned the index of the matching value, or 0 if the value was not contained.
	*/
	template <typename T>
	bool findArrayIndex(T arr[], T c, int& n)
	{
		for (int i = 0; i < n; i++)	//Loops for every value in the array
		{
			if (arr[i] == c)		//If it matches the c
			{
				n = i;				//Index of matching value
				return true;		//c is a value in arr[]
			}
		}

		n = 0;						//To avoid out of bounds errors
		return false;				//c is not a value in arr[]
	}

	/**
	 * Copies the values of a constant array into a different, non-const array
	 *
	 * @param arr1[]:	The const array of values to copy.
	 * @param arr2[]:	The array to be copied to.
	 * @param n:		The size of the smaller array.
	*/
	template <typename T>
	void copyConstArray(const T arr1[], T arr2[], int n)
	{
		for (int i = 0; i < n; i++)	//Loops for every value in the array
		{
			arr2[i] = arr1[i];
		}
	}

	/**
	 * Copies the values of one array into another
	 *
	 * @param arr1[]:	The const array of values to copy.
	 * @param arr2[]:	The array to be copied to.
	 * @param n:		The size of the smaller array.
	*/
	template <typename T>
	void copyArray(T arr1[], T arr2[], int n)
	{
		for (int i = 0; i < n; i++)	//Loops for every value in the array
		{
			arr2[i] = arr1[i];
		}
	}

	/**
	 * Copies the values of a pointer to an array into another array
	 *
	 * @param arr1[]:	The pointer array of values to copy.
	 * @param arr2[]:	The array to be copied to.
	 * @param n:		The size of the smaller array.
	*/
	template <typename T>
	void copyPointerArray(T* arr1, T arr2[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			arr2[i] = *(arr1 + i);
		}
	}

	/**
	 * Finds the absolute value of a number
	 *
	 * @param value:	The value to find
	*/
	template <typename T>
	T absolute(T value)
	{
		if (value < 0)
		{
			return -value;
		}
		return value;
	}
};


#endif // !CAM_HELPER_H