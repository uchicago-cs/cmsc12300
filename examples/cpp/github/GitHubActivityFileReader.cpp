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

GitHubActivityFileReader::GitHubActivityFileReader(istream &is) {

        file.push(boost::iostreams::gzip_decompressor());
        file.push(is);

}

GitHubActivityFileReader::~GitHubActivityFileReader() {

}

bool GitHubActivityFileReader::done()
{
	// If the EOF is reached, we have no more clicks.
	//return is.eof();
    return true;
}


GitHubActivityEvent GitHubActivityFileReader::next()
{
	GitHubActivityEvent event;


    /*
	try
	{
		click = USAGovClick(line);
	} catch (USAGovJSONException &e)
	{
		throw USAGovClickReaderException(e.what());
	}
    */

	return event;
}
