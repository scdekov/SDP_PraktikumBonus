#include <iostream>
#include <string>
#include "Client.h"
#include "Server.h"
#include "Message.h"
#include "Event.h"
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
	sv->hostEvent("football","vtornik","20:00","stadion Pleven");
	sv->inviteForEvent("football","pesho");
	pesho->printAndProceeInvitationsForEvents();
	srv->printEvents();

	
	return 0;
}