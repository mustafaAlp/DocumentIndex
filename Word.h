/*
 * Word.h
 *
 *  Created on: 18 Kas 2014
 *      Author: Mustafa ALP
 */

#ifndef WORD_H_
#define WORD_H_

#include <iostream>
#include <string>

using namespace std;


namespace DocumentIndexNameSpace {

// const macro represents last element of int* index
#define END_OF_INDEX -1

class Word {
public:
	//constructors
	Word();
	Word(const string, int);
	Word(const string, const int*, int);
	Word(const Word&);
	//destructor
	~Word();

	//mutator
	void set(const string, const int*, int);
	void set(const string, int);

	//accessor
	const int* getLineNumbers()const;
	string getWord()const;

	//	member function
	bool isInThisLine(int)const;
	bool isAlphabetic()const;

	//operator overloads
	friend const Word operator+=(Word&, const int*);

	friend ostream& operator<<(ostream&, const Word&);
	int operator==(const Word& )const;
	const Word operator=(const Word&);

private:
	string word;
	int* lineNumbers;//last element should be -1
	int capacity;
	int size;

};

} /* namespace DocumentIndexNameSpace */
#endif /* WORD_H_ */
