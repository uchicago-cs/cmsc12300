/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2014
 *
 * Provides the GitHubActivityEvent class, which represents a single
 * GitHub activity event as described in
 * https://developer.github.com/v3/activity/events/types/
 *
 * See GitHubActivityEvent.h for details.
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
    actor = event["actor"].asString();
    repository = event["repository"]["name"].asString();
    repository_owner = event["repository"]["owner"].asString();

}


GitHubActivityEvent::~GitHubActivityEvent() {

}


std::string GitHubActivityEvent::getRepositoryFullName()
{
    return repository_owner + "/" + repository;
}


GitHubCommitCommentEvent::GitHubCommitCommentEvent(Json::Value &event):GitHubActivityEvent(event)
{
    commit = event["payload"]["commit"].asString();
}

GitHubCommitCommentEvent::~GitHubCommitCommentEvent()
{

}

string GitHubCommitCommentEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- " << actor << " added a comment to commit " << commit;


    return ss.str();    
}



GitHubCreateEvent::GitHubCreateEvent(Json::Value &event):GitHubActivityEvent(event)
{
    ref_type = event["payload"]["ref_type"].asString();
    ref = event["payload"]["ref"].asString();
}

GitHubCreateEvent::~GitHubCreateEvent()
{

}

string GitHubCreateEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- " << actor << " created a " << ref_type << ": ";

    if (ref_type == "repository")
        ss << getRepositoryFullName();
    else
        ss << ref << " in " << getRepositoryFullName();

    return ss.str();    
}



GitHubDeleteEvent::GitHubDeleteEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubDeleteEvent::~GitHubDeleteEvent()
{

}

string GitHubDeleteEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubDeploymentEvent::GitHubDeploymentEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubDeploymentEvent::~GitHubDeploymentEvent()
{

}

string GitHubDeploymentEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubDeploymentStatusEvent::GitHubDeploymentStatusEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubDeploymentStatusEvent::~GitHubDeploymentStatusEvent()
{

}

string GitHubDeploymentStatusEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubDownloadEvent::GitHubDownloadEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubDownloadEvent::~GitHubDownloadEvent()
{

}

string GitHubDownloadEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubFollowEvent::GitHubFollowEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubFollowEvent::~GitHubFollowEvent()
{

}

string GitHubFollowEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubForkEvent::GitHubForkEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubForkEvent::~GitHubForkEvent()
{

}

string GitHubForkEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- " << actor << " forked " << getRepositoryFullName();

    return ss.str();    
}



GitHubForkApplyEvent::GitHubForkApplyEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubForkApplyEvent::~GitHubForkApplyEvent()
{

}

string GitHubForkApplyEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubGistEvent::GitHubGistEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubGistEvent::~GitHubGistEvent()
{

}

string GitHubGistEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubGollumEvent::GitHubGollumEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubGollumEvent::~GitHubGollumEvent()
{

}

string GitHubGollumEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubIssueCommentEvent::GitHubIssueCommentEvent(Json::Value &event):GitHubActivityEvent(event)
{
    issue_id = event["payload"]["issue_id"].asLargestUInt();
}

GitHubIssueCommentEvent::~GitHubIssueCommentEvent()
{

}

string GitHubIssueCommentEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- " << actor << " commented on ";
    ss << "an issue (id=" << issue_id << ") in repository " << getRepositoryFullName();

    return ss.str();    
}



GitHubIssuesEvent::GitHubIssuesEvent(Json::Value &event):GitHubActivityEvent(event)
{
    action = event["payload"]["action"].asString();
    number = event["payload"]["number"].asLargestUInt();
}

GitHubIssuesEvent::~GitHubIssuesEvent()
{

}

string GitHubIssuesEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- " << actor << " " << action << " ";
    ss << "issue #" << number << " in repository " << getRepositoryFullName();

    return ss.str();    
}



GitHubMemberEvent::GitHubMemberEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubMemberEvent::~GitHubMemberEvent()
{

}

string GitHubMemberEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubPageBuildEvent::GitHubPageBuildEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubPageBuildEvent::~GitHubPageBuildEvent()
{

}

string GitHubPageBuildEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubPublicEvent::GitHubPublicEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubPublicEvent::~GitHubPublicEvent()
{

}

string GitHubPublicEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubPullRequestEvent::GitHubPullRequestEvent(Json::Value &event):GitHubActivityEvent(event)
{
    action = event["payload"]["action"].asString();
    number = event["payload"]["number"].asLargestUInt();
}

GitHubPullRequestEvent::~GitHubPullRequestEvent()
{

}

string GitHubPullRequestEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- " << actor << " " << action << " ";
    ss << "pull request #" << number << " in repository " << getRepositoryFullName();

    return ss.str();    
}



GitHubPullRequestReviewCommentEvent::GitHubPullRequestReviewCommentEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubPullRequestReviewCommentEvent::~GitHubPullRequestReviewCommentEvent()
{

}

string GitHubPullRequestReviewCommentEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubPushEvent::GitHubPushEvent(Json::Value &event):GitHubActivityEvent(event)
{
    ref = event["payload"]["ref"].asString();
    size = event["payload"]["size"].asLargestUInt();
}

GitHubPushEvent::~GitHubPushEvent()
{

}

string GitHubPushEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- " << actor << " pushed " << size << (size==1?" commit":" commits") << " to " << getRepositoryFullName();

    return ss.str();    
}



GitHubReleaseEvent::GitHubReleaseEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubReleaseEvent::~GitHubReleaseEvent()
{

}

string GitHubReleaseEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubStatusEvent::GitHubStatusEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubStatusEvent::~GitHubStatusEvent()
{

}

string GitHubStatusEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubTeamAddEvent::GitHubTeamAddEvent(Json::Value &event):GitHubActivityEvent(event)
{

}

GitHubTeamAddEvent::~GitHubTeamAddEvent()
{

}

string GitHubTeamAddEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- ";

    return ss.str();    
}



GitHubWatchEvent::GitHubWatchEvent(Json::Value &event):GitHubActivityEvent(event)
{
    action = event["payload"]["action"].asString();
}

GitHubWatchEvent::~GitHubWatchEvent()
{

}

string GitHubWatchEvent::repr()
{
    stringstream ss;

    ss << created_at << setw(31) << type << " -- " << actor << " " << action << " watching repository " << getRepositoryFullName();

    return ss.str();    
}





