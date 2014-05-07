/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Implementation of the USAGovClickReader abstract class
 * for click data stored in a text file.
 *
 * See USAGovClickFileReader.h for details
 *
 */

#include "GitHubActivityFileReader.h"
#include <iostream>
using namespace std;

USAGovClickFileReader::USAGovClickFileReader(istream &is):is(is) {


}

USAGovClickFileReader::~USAGovClickFileReader() {

}

bool USAGovClickFileReader::done()
{
	// If the EOF is reached, we have no more clicks.
	return is.eof();
}


USAGovClick USAGovClickFileReader::next()
{
	// Read in one line, and parse it (using the USAGovClick class)
	string line;
	getline(is, line);
	USAGovClick click;

	try
	{
		click = USAGovClick(line);
	} catch (USAGovJSONException &e)
	{
		throw USAGovClickReaderException(e.what());
	}

	return click;
}
