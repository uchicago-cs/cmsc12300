/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2014
 *
 * Implementation of the GitHubActivityReader abstract class
 * for event data stored in a gzipped file, as downloaded
 * from http://www.githubarchive.org/
 *
 */

#ifndef GITHUBACTIVITYFILEREADER_H_
#define GITHUBACTIVITYFILEREADER_H_

#include "GitHubActivityReader.h"
#include <iostream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>


class GitHubActivityFileReader: public GitHubActivityReader {
	// Input stream.
	boost::iostreams::filtering_istream file;

public:
	// Constructor
	// Parameter: The input stream with the event data.
	GitHubActivityFileReader(std::istream &is);

	// Destructor
	virtual ~GitHubActivityFileReader();

	// Implementation of GitHubActivityReader abstract methods.
	// See GitHubActivityReader.h for details.
	bool done();
	GitHubActivityEvent* next();
};

#endif /* GITHUBACTIVITYFILEREADER_H_ */
