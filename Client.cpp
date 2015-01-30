#include "Client.h"


Client::Client(string _name, Server* _server):name(_name),server(_server){}

void Client::printAllMessages()
{
	for (int i = 0; i < messages.size(); ++i)
	{
		messages[i]->printMessage();
		messages[i]->markAsRead();
		cout<<endl;
	}
}

void Client::printUnreadMessages()
{
	for (int i = messages.size()-1; i >= 0; i--)
	{
		if (messages[i]->isRead)
		{
			return;
		}else
		{
			messages[i]->printMessage();
			cout<<endl;
			messages[i]->markAsRead();
		}
	}
}

bool Client::sendMessage(string recipient, string message)
{
	encryptMessage(message);
	Message* msg = new Message(this->name,recipient, message);
	return server->sendMessage(msg);
}

void Client::receiveMessage(Message* msg)
{
	decryptMessage(msg->data);
	messages.push_back(msg);
}

string Client::getName()
{
	return name;
}

void Client::encryptMessage(string& message)
{
	for (int i = 0; i < message.length(); ++i)
	{
		if (i%2==0)
		{
			message[i]+=2;
		}else
		{
			message[i]++;
		}
	}
}

void Client::decryptMessage(string& message)
{
	for (int i = 0; i < message.length(); ++i)
	{
		if (i%2==0)
		{
			message[i]-=2;
		}else
		{
			message[i]--;
		}
	}
}

void Client::printClientsInServer()
{
	server->printAllClients();
}

void Client::printMyFriends()
{	
	if(friends.size())
	{
		cout<<"List of your friends:"<<endl;
		for (int i = 0; i < friends.size(); ++i)
		{
			cout<<friends[i]<<endl;
		}
	}else
	{
		cout<<"You don't have any friends."<<endl;
	}
}

void Client::printAndProceedFriendRequests()
{
	while(friendRequests.size())
	{
		cout<<"Frined request["<<friendRequests.size()<<"] from:"<<friendRequests.back()<<endl;
		cout<<"What you want to do accept/decline?>";
		string decision;
		cin>>decision;
		if (decision=="accept")
		{
			friends.push_back(friendRequests.back());
			friendRequests.pop();
		}else if(decision=="decline")
		{
			friendRequests.pop();
		}else
		{
			cout<<"wrong command!"<<endl;
		}
	}
} 

void Client::sendFriendRequest(string to)
{
	server->putFriendRequestIn(this->name,to);
}

void Client::putFriendRequestIn(string from)
{
	friendRequests.push(from);
}