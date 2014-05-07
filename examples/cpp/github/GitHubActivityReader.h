/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * An abstract class for reading a single click at a time
 * from a source of 1.USA.gov clicks
 *
 */

#ifndef USAGOVCLICKREADER_H_
#define USAGOVCLICKREADER_H_

#include"GitHubActivityEvent.h"
#include<exception>

class USAGovClickReader {

public:
	// Constructor
	USAGovClickReader();

	// Destructor
	virtual ~USAGovClickReader();

	// This method must return true once the reader has no
	// more clicks to provide
	virtual bool done() = 0;

	// Returns the next click in the source. This method
	// may block if the source still has more clicks, but
	// not when the next() method is called.
	virtual USAGovClick next() = 0;
};

// Exception class to be thrown whenever there is
// an error reading from a 1.usa.gov source
class USAGovClickReaderException: public std::exception
{
	// Error description
	const char *reason;

public:
	// Constructor
	USAGovClickReaderException(const char* reason) throw();
	// Returns the reason for the error
	const char* what() const throw();
};

#endif /* USAGOVCLICKREADER_H_ */
