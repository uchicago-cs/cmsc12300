/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Provides the GitHubActivityEvent class, which represents a single
 * GitHub activity event as described in
 * https://developer.github.com/v3/activity/events/types/
 *
 */

#ifndef GITHUBACTIVITYEVENT_H_
#define GITHUBACTIVITYEVENT_H_

#include<string>
#include<exception>

// Exception class to be thrown whenever there is
// an error in the GitHub Event JSON
class GitHubEventJSONException: public std::exception
{
	// Error description
	const char *reason;

public:
	// Constructor
	GitHubEventJSONException(const char* reason) throw();
	// Returns the reason for the error
	const char* what() const throw();
};

// A single event
class GitHubActivityEvent {

    int id;


public:
    // Default constructor
    GitHubActivityEvent();

    // Constructor. Takes the JSON representation of the click.
	GitHubActivityEvent(std::string json);

	// Destructor
	virtual ~GitHubActivityEvent();

};

#endif /* GITHUBACTIVITYEVENT_H_ */
