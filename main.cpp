#include <iostream>
#include <string>
#include "Client.h"
#include "Server.h"
#include "Message.h"
using namespace std;


int main()
{
	string svetlio="svetlio";
	string pes="pesho";
	Server* srv = new Server();
	Client* sv = new Client(svetlio,srv);
	Client* pesho = new Client(pes,srv);
	srv->addClient(sv);
	srv->addClient(pesho);
	sv->sendMessage("pesho","mara");
	sv->sendMessage("pesho","mara2");
	sv->sendMessage("pesho","mara3");
	sv->sendMessage("pesho","mara4");
	
	pesho->printAllMessages();

	sv->sendMessage("pesho","mara0");
	sv->sendMessage("pesho","mara40");

	pesho->printUnreadMessages();
	cout<<endl;

	srv->printAllClients();
	
	
	return 0;
}