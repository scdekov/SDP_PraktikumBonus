#ifndef COMANDPARSER_H_
#define COMANDPARSER_H_

#include <iostream>
#include "Server.h"
#include "Client.h"
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <sqlite3.h> 
#include <termios.h>
#include <unistd.h>
using namespace std;

class Server;


class CommandParser
{
private:
	Server* server;
public:
	CommandParser(Server*);
	void gen_random(string&);
	bool isPasswordWeak(string);
	bool isEmailInvalid(string);
	void mainMenu();
	void login();
	void registerNewUser();
	void forgottenPassword();
	void loggedUserMenu(string);
	void accountOptions(string);
	string getPass();

};

#endif