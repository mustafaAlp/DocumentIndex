/*
 * DocumentIndex.cpp
 *
 *  Created on: 18 Kas 2014
 *      Author: Mustafa ALP
 */

#include "DocumentIndex.h"

namespace DocumentIndexNameSpace {

/**
 *	no parameter constructor
 *
 */
DocumentIndex::DocumentIndex()
	:capacity(10),size(0)
{
	indexSection = new Word [capacity];
}

/**
 * one parameter constructor:	takes a string named fileName
 * 				reads the file , fill the object and orders the object
 *
 *
 */
DocumentIndex::DocumentIndex(const string fileName)
	:capacity(5), size(0)
{

	indexSection = new Word[capacity];

	fstream inp;
	inp.open(fileName.c_str());

	string line;

	for (int i = 1; getline(inp, line) ; ++i) {
		fillDocumentIndex(line, i);
	}

	putInIndexOrder();

	inp.close();
}

/**
 * copy constructor:	uses deep copy
 *
 */
DocumentIndex::DocumentIndex(const DocumentIndex& copy)
	:capacity(copy.capacity), size(copy.size)
{
	indexSection = new Word[capacity];

	for (int i = 0; i < size; ++i) {
		indexSection[i] = copy.indexSection[i];
	}
}

/**
 *	Destructor:	frees the allocated memory
 *
 */
DocumentIndex::~DocumentIndex() {
	if (indexSection != NULL )
		delete[]indexSection;
}


/**
 *	operator+=():	compound assignment operator takes two DocumentIndex operator
 *					adds members of right object to the left object
 *					returns a copy of left object
 *
 */
const DocumentIndex operator+=(DocumentIndex& left, const DocumentIndex& right){

	for (int i = 0; i < right.size; ++i) {
		left += right.indexSection[i];
	}

	left.putInIndexOrder();

	return left;
}

/**
 *	operator+():	addition operator takes two DocumentIndex operator
 *					returns a new DocumentIndex object which includes
 *					both left and right objects's members
 *
 */
const DocumentIndex operator+(const DocumentIndex& left, const DocumentIndex& right){
	DocumentIndex temp(left);

	for (int i = 0; i < right.size; ++i) {
		temp += right.indexSection[i];
	}

	temp.putInIndexOrder();

	return temp;
}

/**
 *	operator+=():	compound assignment operator which takes a DocumentIndex object and a Word object
 *					adds word object to DocumentIndex object and
 *					returns a copy of the DocumentIndex object
 */
const DocumentIndex operator+=(DocumentIndex& doc, const Word& newElement){
	if (doc.size +1 == doc.capacity) {
		doc.capacity *= 2;
		Word* temp = new Word[doc.capacity];

		for (int i = 0; i < doc.size; ++i) {
			temp[i] = doc.indexSection[i];
		}
		delete[]doc.indexSection;

		doc.indexSection = temp;
	}

	doc.indexSection[doc.size] = newElement;
	doc.size++;

	return doc;
}

/**
 *	operator[]():	index operator which takes a string named input
 *					if object includes an element has same word
 *					value with the input  returns the int* index
 *					else returns NULL
 *
 *					last element of the int* index is -1
 */
const int* DocumentIndex::operator[](const string input){
	Word temp(input, 0);
	for (int i = 0; i < size; ++i) {
		if ( (indexSection[i] == temp) == 0) {
			return indexSection[i].getLineNumbers();
		}
	}

	return NULL;
}

/**
 *	operator[]():	index operator which takes a int named line
 *					creates a new DocumentIndex object named temp
 *					if an element's lineNumbers includes argument line
 *					adds this elements to object temp
 *					and return object temp
 *
 *
 *
 */
const DocumentIndex DocumentIndex::operator[](int line){
	DocumentIndex temp;

	for (int i = 0; i < size; ++i) {
		if(indexSection[i].isInThisLine(line))
			temp += indexSection[i];
	}

	return temp;
}

/**
 *	operator[]():	takes an int. works on const DocumentIndex objects
 *					if i in the range of dynamic array indexSection's index
 *					returns array's i indexed element's member word
 *					else returns an empty string
 *
 */
string DocumentIndex::operator[](int i)const{
	if(i >= 0 && i < size)
		return indexSection[i].getWord();
	else
		return string();
}



/**
 *	operator>>():	stream extraction operator
 *					fills object with input from inp stream
 *
 */
istream& operator>>(istream&inp, DocumentIndex& doc){

	if (doc.indexSection != NULL) {
		delete[] doc.indexSection;
	}

	doc.capacity = 5;
	doc.size = 0;

	doc.indexSection = new Word[doc.capacity];
	string line;

	for (int i = 1; getline(inp, line); ++i) {
		doc.fillDocumentIndex(line, i);
	}

	doc.putInIndexOrder();

	return inp;
}

/**
 * operator<<():	stream insertion operator implementation
 * 					writes object to out stream
 *
 */
ostream& operator<<(ostream& out, const DocumentIndex& doc){
	char temp = ' ';
	out <<"\n\t INDEX\n";

	for (int i = 0; i < doc.size; ++i) {
		if (temp != doc.indexSection[i].getWord()[0]) {//writes head char of words
			temp = doc.indexSection[i].getWord()[0];
			out << "\n\n\n" << (char) toupper(temp) << endl;
		}
		out << doc.indexSection[i];
	}

	return out;
}

/**
 *	operator=():	assignment operator implementation.
 *					copies right object to other object by using deep copy
 *
 */
const DocumentIndex DocumentIndex::operator=(const DocumentIndex& rigth){
	capacity = rigth.capacity;
	size = rigth.size;

	if(indexSection != NULL){
		delete[] indexSection;
		indexSection = new Word[capacity];
	}

	for (int i = 0; i < size; ++i) {
		indexSection[i] = rigth.indexSection[i];
	}

	putInIndexOrder();

	return *this;
}



/**
 *	strToLower:	takes a string. creates a second string named temp
 *				adds all characters of line string to temp as 'lower case'
 *				returns string temp
 *
 *				note that: it only applies to ascii characters
 *
 */
string DocumentIndex::strToLower(string line)const{
	string temp;

	for (unsigned int i = 0; i < line.size(); ++i) {
		temp += tolower(line[i]);
	}
	return temp;
}

/**
 *	fillDocumentIndex:	takes a string and an int.
 *						divides string to parts
 *						creates Word objects from this parts and
 *						lineNumber.
 *						characters which among elements of char* charSet
 *						but not a member of charSet, becomes parts.
 *
 *
 */
void DocumentIndex::fillDocumentIndex(string line, int lineNumber){
	line = strToLower(line);
	string temp;

	const char* charSet = ", .();:-\t\n" ;
	size_t	start = -1,
			end;

	while( end != std::string::npos ){
		end = line.find_first_of(charSet, start + 1);

		if((end - start) > 1 ){
			temp = line.substr(start + 1 , end - start - 1 );
			add(Word(temp, lineNumber));
		}
		start = end;
	}
}

/**
 *	add:	takes a const Word object reference
 *			add this object to dynamic Word array indexSection
 *
 */
void DocumentIndex::add(const Word& inp){
	if(inp.isAlphabetic()){
		if (size == capacity) {
			capacity *= 2;
			Word* temp = new Word[capacity];

			for (int i = 0; i < size; ++i) {
				temp[i] = indexSection[i];
			}
			delete[]indexSection;

			indexSection = temp;
		}

		indexSection[size] = inp;
		size++;
	}
}


/**
*	sort:	takes no argument.
*			puts in dynamic array indexSection alphabetic order
 *
 */
void DocumentIndex::sort(){

	Word swap;

	for (int i = 0; i < size-1; ++i) {
		for (int j = 0; j < size-i-1 ; ++j) {
			if ((indexSection[j] == indexSection[j+1]) > 0  ) {
				swap = indexSection[j];
				indexSection[j] = indexSection[j+1];
				indexSection[j+1] = swap;
			}
		}
	}
}

/**
 *	join:	takes no argument.
 *			merges object's members int* index which are
 *			belongs objects with equal member string word values
 *			and erase the object which is stays in the bigger index
 *
 *
 *
 */
void DocumentIndex::join(){

	for (int i = 0; i < size; ++i) {
		while((indexSection[i] == indexSection[i+1]) == 0 ){
			indexSection[i] += indexSection[i+1].getLineNumbers();
			erase(i+1);
		}
	}
}

/**
 *	erase:	takes an int named i which keeps info of
 *			an index from dynamic array indexSection
 *			function deletes this element of array
 *			and decreases the size
 *
 */
void DocumentIndex::erase(int i){
	for (; i < size; ++i) {
		indexSection[i] = indexSection[i+1];
	}

	--size;
}

/**
 *	putInIndexOrder:	orders dynamic array and erase words repeated
 *
 */
void DocumentIndex::putInIndexOrder(){
	sort();
	join();
}


} /* namespace DocumentIndexNameSpace */
