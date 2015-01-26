#include "Server.h"



bool Server::checkIfClientExist(string name)
{
	if(clients.find(name)!=clients.end())
	{
		return true;
	}else
	{
		return false;
	}

}

Server::Server(){}

bool Server::sendMessage(string to,Message* msg)
{
	if (!checkIfClientExist(to))
	{
		return false;
	}else
	{
		clients[to]->reciveMessage(msg);
		return true;
	}
}

void Server::addClient(Client* toBeAdded)
{
	clients[toBeAdded->getName()]=toBeAdded;
}

void Server::printAllClients()
{
	for (map<string,Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		cout<<it->first<<endl;
	}
}


