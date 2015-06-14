/**
 *	file:	driver.cpp
 *	author:	Mustafa ALP
 *
 */
#include <iostream>
#include "Word.h"
#include "DocumentIndex.h"

using namespace DocumentIndexNameSpace;

void testDocumentIndexClass();
void wait();

int main(int argc, char **argv) {

	testDocumentIndexClass();


	return 0;
}

/**
 *	wait:	waits for any entry from standard output
 *
 */
void wait(){

	cout << "\n\n\n\n\n press ENTER for next step  ";

	    char enter;

	    do {
	        cin.get(enter);
	    } while ( enter != '\n' );

	    cout << "\n\n\n";
}

/**
 * testDocumentIndexClass:	tests DocumentIndex Class's functions
 */
void testDocumentIndexClass(){
	cout<<"\n\n\t tests of DocumentIndex class\n\n\n";


	/*	input file: marix.txt
	 *	output file out_matrix.txt
	 *
	 *	test: index operators
	 *
	 */
	DocumentIndex matrix("input/matrix.txt");

	cout 	<< "\n\n input file: matrix.txt\n\n "
			<< "object name: matrix\n\n"
			<< matrix;

	fstream out;
	out.open("out_matrix.txt", ios::out);

	out << matrix;
	out.close();


	cout 	<< "\n\n\n\n\n\n\n"
			<< "------------------------------------"
			<< "--------------------------\n"
			<< "\t index operators's test\n"
			<< "------------------------------------"
			<< "--------------------------\n\n\n";

	cout << " index operator which takes a string:\n\n";


	cout << "\n marix[\"trinity\"] : ";

	const int* indexes = matrix["trinity"];


	for (int i = 0; indexes[i] != -1 ; ++i) {
		cout<<indexes[i] <<  " ";
	}

	cout << "\n\n\n\n\n index operator which takes an int:\n\n";

	cout<<" matrix[177] :\t";

	int line = 177;
	for (int i = 0; matrix[line][i].size() != 0; ++i) {
		cout << matrix[line][i] << "\t";
	}

	wait();

	/*	input file: starWars_aNewHope.txt
	 *	output file out_starWars_aNewHope.txt
	 *
	 *	test: stream extraction operator
	 *
	 */
	cout 	<< "\n\n\n\n\n\n\n\n\n\n\n\n"
			<< "------------------------------------"
			<< "--------------------------\n"
			<< "\t stream extraction operator's test\n"
			<< "------------------------------------"
			<< "--------------------------\n\n\n\n\n";


	DocumentIndex starWars;

	fstream inp;
	inp.open("input/starWars_aNewHope.txt", ios::in);
	inp >> starWars;
	inp.close();

	cout 	<< " inp.open(\"starWars_aNewHope.txt\", ios::in)\n"
			<< " inp >> starWars\n\n"
			<< starWars;



	out.open("out_starWars.txt", ios::out);
	out << starWars;
	out.close();


	wait();

	/*	input file: lordOfTheRings.txt
	 *	output file out_lordOfTheRings.txt
	 *
	 *	test: stream extraction operator
	 *
	 */
	cout 	<< "\n\n\n\n\n\n\n\n\n\n\n\n"
			<< "------------------------------------"
			<< "--------------------------\n"
			<< "\t assignment operators's test\n"
			<< "------------------------------------"
			<< "--------------------------\n\n\n\n\n";

	DocumentIndex temp;

	cout <<" object: temp\n";
	cout << temp;


	DocumentIndex lordOfTheRings("input/lordOfTheRings.txt");

	cout <<"\n\n\n object: lordOfTheRings\n";
	cout << lordOfTheRings;

	out.open("out_lordOfTheRings.txt", ios::out);
	out << lordOfTheRings;
	out.close();


	cout << "\n\n\n temp = lordOfTheRings;\n\n";

	temp = lordOfTheRings;
	cout <<" object: temp\n";
	cout << temp;


	wait();

	cout << "\n\n\n\n\n\n temp += matrix;\n temp += starWars;\n\n";
	temp += matrix;
	temp += starWars;

	cout <<" object: temp\n";
	cout << temp;


	wait();

	cout 	<< "\n\n\n\n\n\n\n\n\n\n\n\n"
			<< "------------------------------------"
			<< "--------------------------\n"
			<< "\t addition operator's test\n"
			<< "------------------------------------"
			<< "--------------------------\n\n\n\n\n";
	cout << " cout << matrix + starWars;\n\n";
	cout << matrix + starWars;


	out.open("out_matrix+starWars.txt", ios::out);
	out << matrix + starWars;
	out.close();

}
