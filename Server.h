#ifndef SERVER_H_
#define SERVER_H_

#include "Client.h"
#include "Message.h"
#include <string>
#include <map>
#include "Event.h"
#include "CommandParser.h"

class Client;
class CommandParser;

class Server
{
private:
	map<string,Client*> clients;
	map<string,Event*> events;

public:
	friend class CommandParser;
	friend class Client;
	Server();
	bool checkIfClientExist(string name);
	bool sendMessage(Message*);
	void receiveFriendRequest(string,string);
	void addClient(Client*);
	void printAllClients();
	void addEvent(Event*);
	void printEvents();
	void addGuestToEvent(string,string);
	void inviteForEvent(string,string);
	void printEventInfo(string);
	bool logClient(string,string);
	void clientForgottenPassword(string);
	bool checkUserEmail(string, string);
	void printPotentialFriendsOf(string);
	void printPotentialEvents(string,vector<string>);
	void send_email(string,string);
};

#endif
