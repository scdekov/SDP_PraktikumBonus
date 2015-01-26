#ifndef SERVER_H_
#define SERVER_H_

#include "Client.h"
#include "Message.h"
#include <string>
#include <map>


class Server
{
private:
	map<string,Client*> clients;
	bool checkIfClientExist(string name);
public:
	Server();
	bool sendMessage(string,Message*);
	void addClient(Client* toBeAdded);
	void printAllClients();
};

#endif