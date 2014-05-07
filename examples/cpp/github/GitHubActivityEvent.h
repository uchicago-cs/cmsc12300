/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Provides the USAGovClick class, which represents a single click
 * on 1.usa.gov as specified in http://www.usa.gov/About/developer-resources/1usagov.shtml
 *
 */

#ifndef USAGOVCLICK_H_
#define USAGOVCLICK_H_

#include<string>
#include<exception>

// Exception class to be thrown whenever there is
// an error in the 1.USA.gov JSON
class USAGovJSONException: public std::exception
{
	// Error description
	const char *reason;

public:
	// Constructor
	USAGovJSONException(const char* reason) throw();
	// Returns the reason for the error
	const char* what() const throw();
};

// A single click
class USAGovClick {

    std::string userAgent;             // "a": USER_AGENT,
    std::string countryCode;           // "c": COUNTRY_CODE, # 2-character iso code
    bool known;                       // "nk": KNOWN_USER,  # 1 or 0. 0=this is the first time we've seen this browser
    std::string globalBitlyHash;       // "g": GLOBAL_BITLY_HASH,
    std::string encodingUserBitlyHash; // "h": ENCODING_USER_BITLY_HASH,
    std::string encodingUserLogin;     // "l": ENCODING_USER_LOGIN,
    std::string shortURLcname;         // "hh": SHORT_URL_CNAME,
    std::string referringURL;          // "r": REFERRING_URL,
    std::string longURL;               // "u": LONG_URL,
    time_t timestamp;                  // "t": TIMESTAMP,
    std::string geoRegion;             // "gr": GEO_REGION,
    float latitude, longitude;        // "ll": [LATITUDE, LONGITUDE],
    std::string geoCityName;           // "cy": GEO_CITY_NAME,
    std::string timezone;              // "tz": TIMEZONE # in http://en.wikipedia.org/wiki/Zoneinfo format
    time_t hashTimestamp;              // "hc": TIMESTAMP OF TIME HASH WAS CREATED,
    std::string acceptLanguage;        // "al": ACCEPT_LANGUAGE http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.4


public:
    // Default constructor
    USAGovClick();

    // Constructor. Takes the JSON representation of the click.
	USAGovClick(std::string json);

	// Destructor
	virtual ~USAGovClick();

	// GETTERS

	std::string getAcceptLanguage() const
	{
		return acceptLanguage;
	}

	std::string getCountryCode() const
	{
		return countryCode;
	}

	std::string getEncodingUserBitlyHash() const
	{
		return encodingUserBitlyHash;
	}

	std::string getEncodingUserLogin() const
	{
		return encodingUserLogin;
	}

	std::string getGeoCityName() const
	{
		return geoCityName;
	}

	std::string getGeoRegion() const
	{
		return geoRegion;
	}

	std::string getGlobalBitlyHash() const
	{
		return globalBitlyHash;
	}

	time_t getHashTimestamp() const
	{
		return hashTimestamp;
	}

	bool isKnown() const
	{
		return known;
	}

	float getLatitude() const
	{
		return latitude;
	}

	std::string getLongUrl() const
	{
		return longURL;
	}

	std::string getReferringUrl() const
	{
		return referringURL;
	}

	std::string getShortUrLcname() const
	{
		return shortURLcname;
	}

	time_t getTimestamp() const
	{
		return timestamp;
	}

	std::string getTimezone() const
	{
		return timezone;
	}

	std::string getUserAgent() const
	{
		return userAgent;
	}

};

#endif /* USAGOVCLICK_H_ */
