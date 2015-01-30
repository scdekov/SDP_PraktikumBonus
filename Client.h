#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include "Message.h"
#include "Server.h"

class Server;


class Client
{
private:
	Server* server;
	string name;
	vector<Message*> messages;
	vector<string> friends;
	queue<string> friendRequests;
	stack<string> invitationsForEvents;

	void encryptMessage(string&);
	void decryptMessage(string&);
public:
	Client(string, Server*);
	string getName();
	void printAllMessages();
	void printUnreadMessages();
	bool sendMessage(string, string);
	void receiveMessage(Message*);
	void printClientsInServer();
	void printMyFriends();
	void printAndProceedFriendRequests();
	void sendFriendRequest(string);
	void receiveFriendRequest(string);
	void hostEvent(string,string,string,string);
	void printAllEvents();
	void inviteForEvent(string,string);
	void printAndProceeInvitationsForEvents();
	void receiveInvitationForEvent(string);
};

#endif
	