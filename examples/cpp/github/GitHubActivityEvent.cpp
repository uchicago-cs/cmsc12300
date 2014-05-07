/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Provides the USAGovClick class, which represents a single click
 * on 1.usa.gov as specified in http://www.usa.gov/About/developer-resources/1usagov.shtml
 *
 * See USAGovClick.h for details.
 */

#include "GitHubActivityEvent.h"
#include <string>
#include "string.h"
#include <json/json.h>
using namespace std;

USAGovJSONException::USAGovJSONException(const char* reason) throw()
{

	this->reason = strdup(reason);
}


const char* USAGovJSONException::what() const throw()
{
	return reason;
}

USAGovClick::USAGovClick() {

}


USAGovClick::USAGovClick(string json) {
	// Create a JSON reader
	Json::Reader reader;
	Json::Value root;

	// Parse the JSON
	if (!reader.parse(json, root))
	{
		throw USAGovJSONException(("Failed to parse JSON: " + reader.getFormattedErrorMessages()).c_str());
	}

	// The 1.usa.gov stream sometimes returns heartbeat messages.
	// We can filter them simply by checking whether any of the
	// attributes is present (arbitrarily, we choose "a")
	if(!root.isMember("a"))
		throw USAGovJSONException("Does not have 'a'");

	// Retrieve the values from the click JSON object
    userAgent = root.get("a", Json::Value::null).asString();
    countryCode = root.get("c", Json::Value::null).asString();
    known = root.get("cy", Json::Value::null).asBool();
    globalBitlyHash = root.get("g", Json::Value::null).asString();
    encodingUserBitlyHash = root.get("h", Json::Value::null).asString();
    encodingUserLogin = root.get("l", Json::Value::null).asString();
    shortURLcname = root.get("hh", Json::Value::null).asString();
    referringURL = root.get("r", Json::Value::null).asString();
    longURL = root.get("u", Json::Value::null).asString();
    timestamp = root.get("t", Json::Value::null).asLargestUInt();
    geoRegion = root.get("gr", Json::Value::null).asString();
    latitude = root.get("ll", Json::Value::null)[0].asFloat();
    longitude = root.get("ll", Json::Value::null)[1].asFloat();
    geoCityName = root.get("cy", Json::Value::null).asString();
    timezone = root.get("tz", Json::Value::null).asString();
    hashTimestamp = root.get("hc", Json::Value::null).asLargestUInt();
    acceptLanguage = root.get("al", Json::Value::null).asString();
}


USAGovClick::~USAGovClick() {

}
