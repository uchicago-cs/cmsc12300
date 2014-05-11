/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2014
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
#include <json/json.h>

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

protected:

    std::string created_at;
    std::string type;
    std::string actor;
    std::string repository;
    std::string repository_owner;

public:
    // Default constructor
    GitHubActivityEvent();

    // Constructor. Takes the JSON representation of the event.
	GitHubActivityEvent(Json::Value &event);

    std::string getRepositoryFullName();

    virtual std::string repr() = 0;

	// Destructor
	virtual ~GitHubActivityEvent();

};



class GitHubCommitCommentEvent : public GitHubActivityEvent {

    std::string commit;

public:

    GitHubCommitCommentEvent(Json::Value &event);
    std::string repr();
    ~GitHubCommitCommentEvent();

};


class GitHubCreateEvent : public GitHubActivityEvent {

    std::string ref_type;
    std::string ref;

public:

    GitHubCreateEvent(Json::Value &event);
    std::string repr();
    ~GitHubCreateEvent();

};


class GitHubDeleteEvent : public GitHubActivityEvent {

public:

    GitHubDeleteEvent(Json::Value &event);
    std::string repr();
    ~GitHubDeleteEvent();

};


class GitHubDeploymentEvent : public GitHubActivityEvent {

public:

    GitHubDeploymentEvent(Json::Value &event);
    std::string repr();
    ~GitHubDeploymentEvent();

};


class GitHubDeploymentStatusEvent : public GitHubActivityEvent {

public:

    GitHubDeploymentStatusEvent(Json::Value &event);
    std::string repr();
    ~GitHubDeploymentStatusEvent();

};


class GitHubDownloadEvent : public GitHubActivityEvent {

public:

    GitHubDownloadEvent(Json::Value &event);
    std::string repr();
    ~GitHubDownloadEvent();

};


class GitHubFollowEvent : public GitHubActivityEvent {

public:

    GitHubFollowEvent(Json::Value &event);
    std::string repr();
    ~GitHubFollowEvent();

};


class GitHubForkEvent : public GitHubActivityEvent {

public:

    GitHubForkEvent(Json::Value &event);
    std::string repr();
    ~GitHubForkEvent();

};


class GitHubForkApplyEvent : public GitHubActivityEvent {

public:

    GitHubForkApplyEvent(Json::Value &event);
    std::string repr();
    ~GitHubForkApplyEvent();

};


class GitHubGistEvent : public GitHubActivityEvent {

public:

    GitHubGistEvent(Json::Value &event);
    std::string repr();
    ~GitHubGistEvent();

};


class GitHubGollumEvent : public GitHubActivityEvent {

public:

    GitHubGollumEvent(Json::Value &event);
    std::string repr();
    ~GitHubGollumEvent();

};


class GitHubIssueCommentEvent : public GitHubActivityEvent {

    unsigned int issue_id;

public:

    GitHubIssueCommentEvent(Json::Value &event);
    std::string repr();
    ~GitHubIssueCommentEvent();

};


class GitHubIssuesEvent : public GitHubActivityEvent {

    std::string action;
    unsigned int number;

public:

    GitHubIssuesEvent(Json::Value &event);
    std::string repr();
    ~GitHubIssuesEvent();

};


class GitHubMemberEvent : public GitHubActivityEvent {

public:

    GitHubMemberEvent(Json::Value &event);
    std::string repr();
    ~GitHubMemberEvent();

};


class GitHubPageBuildEvent : public GitHubActivityEvent {

public:

    GitHubPageBuildEvent(Json::Value &event);
    std::string repr();
    ~GitHubPageBuildEvent();

};


class GitHubPublicEvent : public GitHubActivityEvent {

public:

    GitHubPublicEvent(Json::Value &event);
    std::string repr();
    ~GitHubPublicEvent();

};


class GitHubPullRequestEvent : public GitHubActivityEvent {

    std::string action;
    unsigned int number;

public:

    GitHubPullRequestEvent(Json::Value &event);
    std::string repr();
    ~GitHubPullRequestEvent();

};


class GitHubPullRequestReviewCommentEvent : public GitHubActivityEvent {

public:

    GitHubPullRequestReviewCommentEvent(Json::Value &event);
    std::string repr();
    ~GitHubPullRequestReviewCommentEvent();

};


class GitHubPushEvent : public GitHubActivityEvent {

    std::string ref;
    unsigned int size;

public:

    GitHubPushEvent(Json::Value &event);
    std::string repr();
    ~GitHubPushEvent();

};


class GitHubReleaseEvent : public GitHubActivityEvent {

public:

    GitHubReleaseEvent(Json::Value &event);
    std::string repr();
    ~GitHubReleaseEvent();

};


class GitHubStatusEvent : public GitHubActivityEvent {

public:

    GitHubStatusEvent(Json::Value &event);
    std::string repr();
    ~GitHubStatusEvent();

};


class GitHubTeamAddEvent : public GitHubActivityEvent {

public:

    GitHubTeamAddEvent(Json::Value &event);
    std::string repr();
    ~GitHubTeamAddEvent();

};


class GitHubWatchEvent : public GitHubActivityEvent {

    std::string action;

public:

    GitHubWatchEvent(Json::Value &event);
    std::string repr();
    ~GitHubWatchEvent();

};



#endif /* GITHUBACTIVITYEVENT_H_ */
