/*
 * DocumentIndex.h
 *
 *  Created on: 18 Kas 2014
 *      Author: Mustafa ALP
 */

#ifndef DOCUMENTINDEX_H_
#define DOCUMENTINDEX_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>//size_t
#include "Word.h"//Word class



using namespace std;


namespace DocumentIndexNameSpace {


/**
 *
 *	DocumentIndex class prototype
 *
 *
 */
class DocumentIndex {
public:
	// constructors
	DocumentIndex();
	DocumentIndex(const string);
	DocumentIndex(const DocumentIndex&);
	//	destructor
	~DocumentIndex();

	//	member functions
	void erase(int);
	void putInIndexOrder();

	/**
	 *	operator over loads
	 *
	 */

	//	index operators
	const int* operator[](const string);
	const DocumentIndex operator[](int);
	string operator[](int)const;

	//	assignment and compound assignment operators
	const DocumentIndex operator=(const DocumentIndex&);
	friend const DocumentIndex operator+=(DocumentIndex&, const DocumentIndex&);
	friend const DocumentIndex operator+=(DocumentIndex&, const Word&);

	//	addition operators
	friend const DocumentIndex operator+(const DocumentIndex&, const DocumentIndex&);

	//	stream operators
	friend ostream& operator<<(ostream&, const DocumentIndex&);
	friend istream& operator>>(istream&, DocumentIndex&);


private:
	Word* indexSection;
	int capacity;
	int size;

	//	private member functions
	string strToLower(string)const;
	void fillDocumentIndex(string, int );
	void add(const Word&);
	void sort();
	void join();

};

} /* namespace DocumentIndexNameSpace */
#endif /* DOCUMENTINDEX_H_ */
