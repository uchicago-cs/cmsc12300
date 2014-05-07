/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * An abstract class for reading a single click at a time
 * from a source of 1.USA.gov clicks
 *
 * See USAGovClickReader.h for details
 *
 */

#include "GitHubActivityEvent.h"
#include "GitHubActivityReader.h"
#include "string.h"
#include <iostream>
using namespace std;


USAGovClickReader::USAGovClickReader() {
}

USAGovClickReader::~USAGovClickReader() {
}

USAGovClickReaderException::USAGovClickReaderException(const char* reason) throw()
{
	this->reason = strdup(reason);
}

const char* USAGovClickReaderException::what() const throw()
{
	return reason;
}
