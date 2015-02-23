#include "Client.h"


Client::Client(string _name, string _password,string _email, Server* _server):name(_name),password(_password)
																			,server(_server),email(_email){}

void Client::printAllMessages()
{
	if (messages.size()==0)
	{
		cout<<"Empty"<<endl;
		return;
	}
	for (int i = 0; i < messages.size(); ++i)
	{
		messages[i]->printMessage();
		messages[i]->markAsRead();
		cout<<endl;
	}
}

void Client::printUnreadMessages()
{
	if (messages.size()==0)
	{
		cout<<"Empty"<<endl;
		return;
	}
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
	if (friendRequests.size()==0)
	{
		cout<<"Empty"<<endl;
		return;
	}
	while(friendRequests.size())
	{
		cout<<"Frined request["<<friendRequests.size()<<"] from:"<<friendRequests.back()<<endl;
		cout<<"What you want to do accept/decline?>";
		string decision;
		cin>>decision;
		if (decision=="accept")
		{
			friends.push_back(friendRequests.back());
			server->clients[friendRequests.back()]->friends.push_back(name);
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
	server->receiveFriendRequest(this->name,to);
}

void Client::receiveFriendRequest(string from)
{
	friendRequests.push(from);
}

void Client::hostEvent(string _name, string date, string time, string location)
{
	Event* event = new Event(_name,date,time,location,this->name);
	server->addEvent(event);
}

void Client::printAllEvents()
{
	server->printEvents();
}

void Client::printAndProceeInvitationsForEvents()
{
	if (invitationsForEvents.size()==0)	
	{
		cout<<"Empty"<<endl;
		return;
	}
	while(invitationsForEvents.size())
	{
		cout<<"You are invited for event:";
		server->printEventInfo(invitationsForEvents.top());
		cout<<"Do you wan't to attend this event y/n?>";
		string choice;
		cin>>choice;
		if (choice=="y")
		{
			server->addGuestToEvent(this->name,invitationsForEvents.top());
			invitationsForEvents.pop();
		}else if(choice=="n")
		{
			invitationsForEvents.pop();
		}else
		{
			cout<<"Wrong comand!"<<endl;
		}
	}
}

void Client::inviteForEvent(string eventName,string guestName)
{	
	server->inviteForEvent(eventName,guestName);
}

void Client::receiveInvitationForEvent(string eventName)
{
	invitationsForEvents.push(eventName);
}

bool Client::login(string _password)
{
	return _password==password;
}

void Client::gen_random(string& s) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < s.length(); ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
}


void Client::forgottenPassword()
{
	string newPassword = "00000000";
	gen_random(newPassword);
	string message = "Your new password is :"+newPassword;
	sendEmail(message);
}

void Client::sendEmail(string message)
{
	return;
}


bool Client::checkEmail(string _email)
{
	return _email==email;
}


void Client::printPotentialFriends()
{
	server->printPotentialFriendsOf(name);
}

bool Client::checkForFriendshipWith(string fr)
{
	for (int i = 0; i < friends.size(); ++i)
	{
		if (friends[i]==fr)
		{
			return true;
		}
	}
	return false;
}


bool Client::checkForMutturalFriend(string fr)
{
	if (checkForFriendshipWith(fr))
	{
		return false;
	}
	for (int i = 0; i < friends.size(); ++i)
	{
		if (server->clients[friends[i]]->checkForFriendshipWith(fr))
		{
			return true;
		}
	}
	return false;
}

void Client::printPotentialEvents()
{
	server->printPotentialEvents(name,friends);
}

void Client::changePassword(string newPassword)
{
	password=newPassword;
}
