#include "Event.h"

Event::Event(string _name,string _date,string _time,string _location,string _host):name(_name),date(_date),
																				   time(_time),location(_location),
																				   host(_host){}

void Event::printEventInfo()
{
	cout<<"Event:"<<name<<endl
		<<"Date:"<<date<<", time:"<<time<<endl
		<<"Location:"<<location<<endl
		<<"Host of event:"<<host<<endl;
	if (willAttend.size())
	{
		cout<<"Guests till now:"<<endl;
		for (int i = 0; i < willAttend.size(); ++i)
		{
			cout<<willAttend[i]<<endl;
		}
	}
}

void Event::addGuest(string guestName)
{
	willAttend.push_back(guestName);
	for (int i = 0; i < invited.size(); ++i)
	{
		if (invited[i]==guestName)	
		{
			invited.erase(invited.begin()+i);
			break;
		}
	}
}

void Event::addInvitation(string guestName)
{
	invited.push_back(guestName);
}


bool Event::checkIfGuestWillAttend(string guest)
{
	for (int i = 0; i < willAttend.size(); ++i)
	{
		if (willAttend[i]==guest)
		{
			return true;
		}
	}
	return false;
}

