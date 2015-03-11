#include "Server.h"
#include "email.cpp"


void Server::send_email(string email, string message)
{
	sendEmail(email,message);
}


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


bool Server::logClient(string name, string password)
{
	return clients[name]->login(password);
}

void Server::clientForgottenPassword(string name)
{
	clients[name]->forgottenPassword();
}

bool Server::checkUserEmail(string username, string email)
{
	return clients[username]->checkEmail(email);
}

void Server::printPotentialFriendsOf(string name)
{
	vector<string> potentialFriends;
	for (map<string,Client*>::iterator it = clients.begin(); it != clients.end()&&potentialFriends.size()<10; ++it)
	{
		if (it->first!=name)
		{
			if(it->second->checkForMutturalFriend(name)&&it->first!=name)
			{
				potentialFriends.push_back(it->first);
			}
		}
	}
	if(potentialFriends.size()<10)
	{
		for (map<string,Client*>::iterator it = clients.begin(); it != clients.end()&&potentialFriends.size()<10; ++it)
		{
			if (!it->second->checkForFriendshipWith(name)&&it->first!=name)
			{
				potentialFriends.push_back(it->first);
			}
		}
	}
	for (int i = 0; i < potentialFriends.size(); ++i)
	{
		cout<<potentialFriends[i]<<endl;
	}
	if (potentialFriends.size()==0)
	{
		cout<<"Empty"<<endl;
	}
}



void Server::printPotentialEvents(string name, vector<string> friends)
{
	vector<string> potentialEvents;
	for (map<string,Event*>::iterator it = events.begin(); it!=events.end()&&potentialEvents.size()<10; ++it)
	{
		if (!it->second->checkIfGuestWillAttend(name))
		{
			for (int i = 0; i < friends.size(); ++i)
			{
				if (!it->second->checkIfGuestWillAttend(friends[i]))
				{
					potentialEvents.push_back(it->first);
					break;
				}
			}
		}
	}

	if (potentialEvents.size()<10)
	{
		for (map<string,Event*>::iterator it = events.begin(); it!=events.end()&&potentialEvents.size()<10; ++it)
		{
			if (!it->second->checkIfGuestWillAttend(name))
			{
				potentialEvents.push_back(it->first);
			}
		}
	}

	for (int i = 0; i < potentialEvents.size(); ++i)
	{
		cout<<potentialEvents[i]<<endl;
	}
	if (potentialEvents.size()==0)
	{
		cout<<"Empty"<<endl;
	}
}


