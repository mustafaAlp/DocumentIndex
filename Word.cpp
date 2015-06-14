/*
 * Word.cpp
 *
 *  Created on: 18 Kas 2014
 *      Author: Mustafa ALP
 */

#include "Word.h"

namespace DocumentIndexNameSpace {

/**
 * no parameter constructor
 *
 */
Word::Word()
	:capacity(5), size(0)
{
	lineNumbers = new int[capacity];

	lineNumbers[size] = END_OF_INDEX;
}

/**
 * two parameter constructor
 *
 *		input:		string which keeps input for member string word
 *		inpLinex:	int which keeps an input for member int* lineNumbers
 */
Word::Word(const string input, int inpLine)
	:word(input), capacity(5), size(0)
{
	lineNumbers = new int[capacity];

	lineNumbers[size] = inpLine;

	++size;

	lineNumbers[size] = END_OF_INDEX;
}

/**
 * three parameter constructor
 *
 *		input:		string which keeps input for member string word
 *		inplinet:	int* which keeps input for member int* lineNumbers
 *		arraySize:	int which keeps input for member int size
 */
Word::Word(const string input, const int* inpLine, int arraySize )
	:word(input), capacity(arraySize * 2), size(arraySize)
{
	lineNumbers = new int [capacity];

	for (int i = 0; i < size; ++i) {
		lineNumbers[i] = inpLine[i];
	}

	lineNumbers[size] = END_OF_INDEX;
}

/**
 * copy constructor:	uses deep copy
 *
 *
 */
Word::Word(const Word& copy)
	:word(copy.word), capacity(copy.capacity), size(copy.size)
{
	lineNumbers = new int [capacity];

	for (int i = 0; i <= size; ++i) {
		lineNumbers[i] = copy.lineNumbers[i];
	}
}

/**
 *	Destructor:	frees allocated memory
 *
 */
Word::~Word() {
	if (lineNumbers != NULL) {
		delete[] lineNumbers;
	}
}

/**
 *	set:	mutator function which takes a string, an int* and an int
 *
 *
 *		inpWord:	string which keeps input for member string word
 *		inpLine:	int* which keeps input for member int* lineNumbers
 *		inpSize:	int which keeps input for member int size
 */
void Word::set(const string inpWord, const int*inpLine, int inpSize){
	word = inpWord;
	capacity *= inpSize;
	size = inpSize;

	if (lineNumbers != NULL) {
		delete[] lineNumbers;
	}

	lineNumbers = new int [capacity];

	for (int i = 0; i < size; ++i) {
		lineNumbers[i] = inpLine[i];
	}

	lineNumbers[size] = END_OF_INDEX;
}

/**
 *	set:	mutator function which takes a string and an int
 *
 *		input:		string which keeps input for member string word
 *		inpLine:	int which keeps an input for member int* lineNumbers
 *
 */
void Word::set(const string inpWord, int inpLine){
	word = inpWord;

	//does reallocation when its needed
	if (size + 1 == capacity ) {
		capacity *= 2;
		int* temp = new int[capacity];

		for (int i = 0; i < size; ++i) {
			temp[i] = lineNumbers[i];
		}

		delete[] lineNumbers;

		lineNumbers = temp;
	}

	lineNumbers[size] = inpLine;
	++size;

	lineNumbers[size] = END_OF_INDEX;
}


/**
 *	getIndex:	accessor function which returns index info of the object
 *
 *		returns an int* which its last element is -1
 */
const int* Word::getLineNumbers()const{
	return lineNumbers;
}

/**
 *	getWord:	accessor function which returns member string word
 *
 */
string Word::getWord()const{
	return word;
}


/**
 *	isInThisLine:	member function which takes an int as argument
 *					if objects int* has an element equal to checkLine returns true
 *					else returns false
 *
 */
bool Word::isInThisLine(int checkLine)const{
	for (int i = 0; i < size; ++i) {
		if (lineNumbers[i] == checkLine) {
			return true;
		}
	}
	return false;
}

/**
 *	isAlphabetic:	if all characters of member string word are alphabetic returns true
 *					else returns false
 *
 */
bool Word::isAlphabetic()const{

	if (word.size() == 0)
		return false;

	for (int i = 0; i < (int)word.size(); ++i) {
		if ( (tolower(word[i]) < (int)'a') || (tolower(word[i]) > (int)'z') ){
			return false;
		}
	}

	return true;
}


/**
 *	operator+():	addition operator takes a Word reference and int*
 *					adds int* newLine's elements to member int* lineNumbers
 *					if member int* lineNumbers has already have an element of newLine
 *					operator doesn't add this particular element of newLine
 *
 *					makes reallocation when its needed
 *
 */
const Word operator+=(Word& arg, const int* newLine){

	for (int j = 0; newLine[j] != -1 ; ++j ) {
		if (arg.size + 2 == arg.capacity) {
			arg.capacity *= 2;
			int* temp = new int [arg.capacity];

			for (int i = 0; i < arg.size; ++i) {
				temp[i] = arg.lineNumbers[i];
			}
			arg.lineNumbers = temp;
		}
		if (!arg.isInThisLine(newLine[j])) {
			arg.lineNumbers[arg.size] = newLine[j];
			++arg.size;
		}
	}

	arg.lineNumbers[arg.size] = -1;

	return arg;
}


/**
 *	operator==():	takes two const Word reference and compares member strings of them
 *			if string members are equal returns 0
 *			if right object's string's alphabetically priority is higher return an int greater than 0
 *			if left object's string's alphabetically priority is higher return an int lesser than 0
 *
 *
 */
int Word::operator==(const Word& right )const{
	return word.compare(right.word);
}


/**
 *	operator<<():	stream insertion operator
 *					writes object to standard output
 *
 */
ostream& operator<<(ostream& out, const Word& arg){
	out.width(15);
	out <<  arg.word << "\t:";
	out.width(7);

	for (int i = 0; i < arg.size; ++i) {
		out << arg.lineNumbers[i] << " ";
	}
	out << endl;

	return out;
}

/**
 *	operator=():	assignment operator copies right object's members
 *					to the left object's members by using deep copy
 *					makes reallocation when its needed
 *
 */
const Word Word::operator=(const Word& right){
	word = right.word;
	capacity = right.capacity;
	size = right.size;

	if(lineNumbers != NULL)
		delete[]lineNumbers;

	lineNumbers = new int [capacity];

	for (int i = 0; i <= size; ++i) {
		lineNumbers[i] = right.lineNumbers[i];
	}

	return *this;
}


} /* namespace DocumentIndexNameSpace */
