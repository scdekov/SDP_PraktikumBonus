#include "Message.h"



Message::Message(string _sender, string _recipient, string _message):sender(_sender),
														    recipient(_recipient),
														    data(_message){}
void Message::markAsRead()
{
	isRead=true;
}		

void Message::printMessage()
{
	cout<<"From:"<<sender<<endl
		<<data;
}


