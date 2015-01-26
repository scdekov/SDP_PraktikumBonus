#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <string>
#include <vector>
#include "Message.h"
#include "Server.h"


class Client
{
private:
	Server* server;
	string name;
	vector<Message*> Messages;
public:
	Client(string _name, Server* _server);
	void printAllMessages();
	void printUnreadedMessages();
	bool sendMessage(string, string);
	void reciveMessage(Message*);
	string getName();
};

#endif