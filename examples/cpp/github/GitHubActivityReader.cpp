/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * An abstract class for reading a single event from
 * a GitHub activity source.
 *
 * See GitHubActivityReader.h for details
 *
 */

#include "GitHubActivityEvent.h"
#include "GitHubActivityReader.h"
#include "string.h"
#include <iostream>
using namespace std;


GitHubActivityReader::GitHubActivityReader() {
}

GitHubActivityReader::~GitHubActivityReader() {
}

GitHubActivityReaderException::GitHubActivityReaderException(const char* reason) throw()
{
	this->reason = strdup(reason);
}

const char* GitHubActivityReaderException::what() const throw()
{
	return reason;
}
