/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2014
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
#include <json/json.h>
#include <iostream>
#include <string>
using namespace std;


GitHubActivityReader::GitHubActivityReader() {
}

GitHubActivityReader::~GitHubActivityReader() {
}


GitHubActivityEvent* GitHubActivityReader::createEvent(string jsonstr)
{
	// Create a JSON reader
	Json::Reader reader;
	Json::Value root;
    GitHubActivityEvent* event = NULL;

	// Parse the JSON
	if (!reader.parse(jsonstr, root))
	{
		throw GitHubEventJSONException(("Failed to parse JSON: " + reader.getFormattedErrorMessages()).c_str());
	}

    string type;

    type = root.get("type", Json::Value::null).asString();

    if (type == "CommitCommentEvent")
    {
        event = new GitHubCommitCommentEvent(root);
    }
    else if (type == "CreateEvent")
    {
        event = new GitHubCreateEvent(root);
    }
    else if (type == "DeleteEvent")
    {
        event = new GitHubDeleteEvent(root);
    }
    else if (type == "DeploymentEvent")
    {
        event = new GitHubDeploymentEvent(root);
    }
    else if (type == "DeploymentStatusEvent")
    {
        event = new GitHubDeploymentStatusEvent(root);
    }
    else if (type == "DownloadEvent")
    {
        event = new GitHubDownloadEvent(root);
    }
    else if (type == "FollowEvent")
    {
        event = new GitHubFollowEvent(root);
    }
    else if (type == "ForkEvent")
    {
        event = new GitHubForkEvent(root);
    }
    else if (type == "ForkApplyEvent")
    {
        event = new GitHubForkApplyEvent(root);
    }
    else if (type == "GistEvent")
    {
        event = new GitHubGistEvent(root);
    }
    else if (type == "GollumEvent")
    {
        event = new GitHubGollumEvent(root);
    }
    else if (type == "IssueCommentEvent")
    {
        event = new GitHubIssueCommentEvent(root);
    }
    else if (type == "IssuesEvent")
    {
        event = new GitHubIssuesEvent(root);
    }
    else if (type == "MemberEvent")
    {
        event = new GitHubMemberEvent(root);
    }
    else if (type == "PageBuildEvent")
    {
        event = new GitHubPageBuildEvent(root);
    }
    else if (type == "PublicEvent")
    {
        event = new GitHubPublicEvent(root);
    }
    else if (type == "PullRequestEvent")
    {
        event = new GitHubPullRequestEvent(root);
    }
    else if (type == "PullRequestReviewCommentEvent")
    {
        event = new GitHubPullRequestReviewCommentEvent(root);
    }
    else if (type == "PushEvent")
    {
        event = new GitHubPushEvent(root);
    }
    else if (type == "ReleaseEvent")
    {
        event = new GitHubReleaseEvent(root);
    }
    else if (type == "StatusEvent")
    {
        event = new GitHubStatusEvent(root);
    }
    else if (type == "TeamAddEvent")
    {
        event = new GitHubTeamAddEvent(root);
    }
    else if (type == "WatchEvent")
    {
        event = new GitHubWatchEvent(root);
    }

    return event;
}

GitHubActivityReaderException::GitHubActivityReaderException(const char* reason) throw()
{
	this->reason = strdup(reason);
}

const char* GitHubActivityReaderException::what() const throw()
{
	return reason;
}


