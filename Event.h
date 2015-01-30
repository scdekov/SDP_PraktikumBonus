#ifndef EVENT_H_
#define EVENT_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Event
{
	string name,date,time,location,host;
	vector<string> invited;
	vector<string> willAttend;
	Event(string,string,string,string,string);
	void printEventInfo();
	void addGuest(string);
	void RemoveInvitation(string);
	void addInvitation(string);
};

#endif