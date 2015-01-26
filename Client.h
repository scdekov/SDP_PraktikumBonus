#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <string>
#include <vector>
#include "Message.h"
#include "Server.h"

class Server;


class Client
{
private:
	Server* server;
	string name;
	vector<Message*> Messages;
public:
	Client(string _name, Server* _server);
	void printAllMessages();
	void printUnreadMessages();
	bool sendMessage(string, string);
	void receiveMessage(Message*);
	string getName();
};

#endif
