#include "Client.h"


Client::Client(string _name, Server* _server):name(_name),server(_server){}

void Client::printAllMessages()
{
	for (int i = 0; i < Messages.size(); ++i)
	{
		Messages[i]->printMessage();
		Messages[i]->markAsRead();
		cout<<endl;
	}
}

void Client::printUnreadMessages()
{
	for (int i = Messages.size()-1; i >= 0; i--)
	{
		if (Messages[i]->isRead)
		{
			return;
		}else
		{
			Messages[i]->printMessage();
			cout<<endl;
			Messages[i]->markAsRead();
		}
	}
}

bool Client::sendMessage(string recipient, string message)
{
	Message* msg = new Message(this->name,recipient, message);
	return server->sendMessage(msg);
}

void Client::receiveMessage(Message* msg)
{
	Messages.push_back(msg);
}

string Client::getName()
{
	return name;
}
