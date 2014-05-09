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
#include <sstream>
#include <iomanip>
#include "string.h"
#include <json/json.h>
using namespace std;

GitHubEventJSONException::GitHubEventJSONException(const char* reason) throw()
{

	this->reason = strdup(reason);
}


const char* GitHubEventJSONException::what() const throw()
{
	return reason;
}

GitHubActivityEvent::GitHubActivityEvent() {

}


GitHubActivityEvent::GitHubActivityEvent(Json::Value &event) {

    created_at = event["created_at"].asString();
    type = event["type"].asString();

}


GitHubActivityEvent::~GitHubActivityEvent() {

}

GitHubPushEvent::GitHubPushEvent(Json::Value &event):GitHubActivityEvent(event)
{
    ref = event["payload"]["ref"].asString();
}

GitHubPushEvent::~GitHubPushEvent()
{

}

string GitHubPushEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(10) << type << " -- ref:" << ref;

    return ss.str();    
}

