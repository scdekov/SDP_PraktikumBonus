#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include "Message.h"
#include "Server.h"
#include "CommandParser.h"
#include <stdio.h>
#include <sqlite3.h> 

class Server;


class Client
{
private:
	Server* server;
	string name;
	string password;
	string email;
	vector<Message*> messages;
	vector<string> friends;
	queue<string> friendRequests;
	stack<string> invitationsForEvents;

	void encryptMessage(string&);
	void decryptMessage(string&);
public:
	Client(string, string, string,Server*);
	string getName();
	bool login(string);
	void forgottenPassword();
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
	bool checkEmail(string);
	void printPotentialFriends();
	bool checkForMutturalFriend(string);
	bool checkForFriendshipWith(string);
	void printPotentialEvents();
	void changePassword(string);
	void gen_random(string&);
	void sendEmail(string);

};

#endif
	