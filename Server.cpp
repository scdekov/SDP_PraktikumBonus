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

bool Server::sendMessage(Message* msg)
{
	if (!checkIfClientExist(msg->recipient))
	{
		return false;
	}else
	{
		clients[msg->recipient]->receiveMessage(msg);
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


void Server::receiveFriendRequest(string from, string to)
{
	if (clients.find(from)!=clients.end())
	{
		clients[to]->receiveFriendRequest(from);
	}
}


void Server::addEvent(Event* event)
{
	events[event->name]=event;
}


void Server::printEvents()
{
	for (map<string,Event*>::iterator i = events.begin(); i != events.end(); ++i)
	{
		i->second->printEventInfo();
	}
}

void Server::addGuestToEvent(string guestName, string eventName)
{
	if (events.find(eventName)!=events.end())
	{
		events[eventName]->addGuest(guestName);
	}
}

void Server::inviteForEvent(string eventName, string guestName)
{
	if (events.find(eventName)!=events.end())
	{
		events[eventName]->addInvitation(guestName);
		clients[guestName]->receiveInvitationForEvent(eventName);
	}
}

void Server::printEventInfo(string eventName)
{
	events[eventName]->printEventInfo();
}

