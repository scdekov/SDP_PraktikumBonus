#ifndef SERVER_H_
#define SERVER_H_

#include "Client.h"
#include "Message.h"
#include <string>
#include <map>
#include "Event.h"

class Client;


class Server
{
private:
	map<string,Client*> clients;
	map<string,Event*> events;

	bool checkIfClientExist(string name);
public:
	Server();
	bool sendMessage(Message*);
	void receiveFriendRequest(string,string);
	void addClient(Client*);
	void printAllClients();
	void addEvent(Event*);
	void printEvents();
	void addGuestToEvent(string,string);
	void inviteForEvent(string,string);
	void printEventInfo(string);
};

#endif
