/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2014
 *
 * Implementation of the GitHubActivityReader abstract class
 * for event data stored in a gzipped file, as downloaded
 * from http://www.githubarchive.org/
 *
 * See GitHubActivityFileReader.h for details
 *
 */

#include "GitHubActivityFileReader.h"
#include <iostream>
using namespace std;

GitHubActivityFileReader::GitHubActivityFileReader(istream &is) {

    file.push(boost::iostreams::gzip_decompressor());
    file.push(is);

    // Fast-forward to first "{"
    char c;
    while ( (c = file.peek()) != '{' && !file.eof()) 
        file.get();
}

GitHubActivityFileReader::~GitHubActivityFileReader() {

}

bool GitHubActivityFileReader::done()
{
	return file.eof();
}


GitHubActivityEvent* GitHubActivityFileReader::next()
{
	GitHubActivityEvent* event;
    string jsonstr;
    int matching_braces;
    char c;
    bool escape = false;
    matching_braces = 0;
    bool instr = false;

    do
    {
        c = file.get();
        jsonstr += c;

        if (c == '"' && !escape)
            instr = !instr;

        if(!instr)
        {
            if (c == '{')
                matching_braces++;
            else if (c == '}')
                matching_braces--;    
        }

        if (!escape && c == '\\')
            escape = true;
        else if (escape)
            escape = false;

    } while (matching_braces > 0);


    if (file.eof() && matching_braces > 0)
        throw GitHubActivityReaderException("EOF reached while reading event");

    // Fast-forward to next "{"
    while ( (c = file.peek()) != '{' && !file.eof()) 
        file.get();

	try
	{
		event = createEvent(jsonstr);
	} catch (GitHubEventJSONException &e)
	{
		throw GitHubActivityReaderException(e.what());
	}

	return event;
}
