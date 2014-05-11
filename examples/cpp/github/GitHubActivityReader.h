/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2014
 *
 * An abstract class for reading a single event from
 * a GitHub activity source.
 *
 */

#ifndef GITHUBACTIVITYREADER_H_
#define GITHUBACTIVITYREADER_H_

#include"GitHubActivityEvent.h"
#include<exception>
#include<string>

class GitHubActivityReader {

public:
	// Constructor
	GitHubActivityReader();

	// Destructor
	virtual ~GitHubActivityReader();

	// This method must return true once the reader has no
	// more events to provide
	virtual bool done() = 0;

	// Returns the next event in the source. This method
	// may block if the source still has more events, but
	// not when the next() method is called.
	virtual GitHubActivityEvent* next() = 0;

	// Create an event object from a JSON string
	GitHubActivityEvent* createEvent(std::string jsonstr);
};

// Exception class to be thrown whenever there is
// an error reading from a GitHub activity source
class GitHubActivityReaderException: public std::exception
{
	// Error description
	const char *reason;

public:
	// Constructor
	GitHubActivityReaderException(const char* reason) throw();
	// Returns the reason for the error
	const char* what() const throw();
};

#endif /* GITHUBACTIVITYREADER_H_ */
