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
	//sv->printClientsInServer();
	sv->sendFriendRequest("pesho");
	pesho->printAndProceedFriendRequests();
	cout<<"=========================="<<endl;
	pesho->printMyFriends();
	
	
	return 0;
}