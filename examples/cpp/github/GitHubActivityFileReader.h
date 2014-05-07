/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Implementation of the USAGovClickReader abstract class
 * for click data stored in a text file.
 *
 */

#ifndef USAGOVCLICKFILEREADER_H_
#define USAGOVCLICKFILEREADER_H_

#include "GitHubActivityReader.h"
#include <iostream>

class USAGovClickFileReader: public USAGovClickReader {
	// Input stream. Reading one line
	// from this stream yields one click
	// (in JSON)
	std::istream &is;

public:
	// Constructor
	// Parameter: The input stream with the click data.
	USAGovClickFileReader(std::istream &is);

	// Destructor
	virtual ~USAGovClickFileReader();

	// Implementation of USAGovClickReader abstract methods.
	// See USAGovClickReader.h for details.
	bool done();
	USAGovClick next();
};

#endif /* USAGOVCLICKFILEREADER_H_ */
