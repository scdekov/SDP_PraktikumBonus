#include <iostream>
#include <string>
#include "Client.h"
#include "Server.h"
#include "Message.h"
#include "Event.h"
#include "CommandParser.h"
using namespace std;










int main(int argc, char* argv[])
{
	Server* srv = new Server();
	CommandParser parser(srv);
	system("clear");
	parser.mainMenu();

	
	return 0;
}