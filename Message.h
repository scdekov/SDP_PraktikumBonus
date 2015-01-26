#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <iostream>
using namespace std;

struct Message
{
	string sender;
	string recipient;
	string data;
	bool isRead;

	Message(string,string,string);
	void markAsReaded();
	void printMessage();
};

#endif