#include "CommandParser.h"
#include <ctime> 

CommandParser::CommandParser(Server* _server):server(_server){}

void CommandParser::gen_random(string& s) {
	srand((unsigned)time(0)); 

    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < s.length(); ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
}

bool CommandParser::isPasswordWeak(string password)
{
	return password.length()<6;
}

bool CommandParser::isEmailInvalid(string email)
{
	int counter = 0;
	for (int i = 0; i < email.length(); ++i)
	{
		if (email[i]=='@')
		{
			counter++;
		}
	}
	return counter != 1;
}





void CommandParser::mainMenu()
{

	cout<<"Hello to new social network, please select one of the options below(write the number of option):"<<endl
		<<"[1].Login."<<endl
		<<"[2].Register new user."<<endl
		<<"[3].Forgotten password."<<endl
		<<"[4].Quit."<<endl;
	int choice;
	cin>>choice;
	if (choice == 1)
	{
		system("clear");
		login();
	}
	else if(choice==2)
	{
		system("clear");
		registerNewUser();
	}
	else if(choice==3)
	{
		system("clear");
		forgottenPassword();
	}
	else if(choice==4)
	{
		cout<<"Bye!"<<endl;
		return;
	}
	else
	{
		system("clear");
		cout<<"Wrong command please select number between 1 and 4:"<<endl;
		mainMenu();
	}
	
} 



void CommandParser::login()
{
	string user,pass;
	cout<<endl<<"Please enter your username:";
	cin>>user;
	while(!server->checkIfClientExist(user))
	{
		cout<<"Wrong username, please enter your username again:";
		cin>>user;

	}
	
	cout<<"Please enter your password:";
	pass=getPass();	
	while(!server->logClient(user,pass))
	{
		cout<<"Wrong password, please enter your password again:"<<endl;
		pass=getPass();
	}

	system("clear");
	cout<<"You successfully logged as "<<user<<endl<<endl;
	loggedUserMenu(user);			
}

	
string CommandParser::getPass()
{
	termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    string s;
    getline(cin, s);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    cout<<endl;
    return s;
    	
}


void CommandParser::registerNewUser()
{
	system("clear");
	string user,pass,email;
	cout<<"Please enter username:";
	cin>>user;
	while(server->checkIfClientExist(user))
	{
		cout<<"This username is already taken please select new username:";
		cin>>user;
	}
	
	cout<<"Please enter password(minimum 6 symbols, pass will not appear on the screen beacause of the security):";
	pass=getPass();
	while(isPasswordWeak(pass))
	{
		cout<<"Password is weak please select new password:";
		pass=getPass();
	}

	cout<<"Please select email for contacts:";
	cin>>email;
	while(isEmailInvalid(email))
	{
		cout<<"Email is invalid please select new email(ex. \"example@newSocialNetwork.com\":";
		cin>>email;
	}
	
	string securityCode,securityCodeRight="00000";
	gen_random(securityCodeRight);
	server->send_email(email,"Your security code is >"+securityCodeRight);
	system("clear");
	cout<<endl;
	cout<<"On your email you recived new message with security code please enter it here:";
	cin>>securityCode;
	while(securityCodeRight!=securityCode)
	{
		cout<<"Wrong security code please enter it again:";
		cin>>securityCode;
	}

	Client* newUser = new Client(user,pass,email,server);
	server->addClient(newUser);
	system("clear");
	cout<<"Successful registration! You are now logged as:"<<user<<endl;
	loggedUserMenu(user);	
}

void CommandParser::forgottenPassword()
{
	string user,pass,email;
	cout<<"Please enter your username:";
	cin>>user;
	while(!server->checkIfClientExist(user))
	{
		cout<<"There is no user with this username, please enter username again:";
		cin>>user;
	}

	cout<<"Please enter your email:";
	cin>>email;
	while(!server->checkUserEmail(user,email))
	{
		cout<<"Wrong email ,please enter email again:";
		cin>>email;
	}
	server->clientForgottenPassword(user);
	system("clear");
	cout<<endl<<"The new password has been sent to your email"<<endl<<endl;
	mainMenu();
}


void CommandParser::accountOptions(string name)
{
	cout<<"Please select one of the options below:"<<endl
		<<"[1].Change Password."<<endl
		<<"[2].Back to main menu."<<endl;
	int choice;
	cin>>choice;
	if (choice==1)
	{
		cout<<"Please enter your current password:";
		string crrPass;
		cin>>crrPass;
		while(!server->clients[name]->login(crrPass))
		{
			cout<<"Password is incorrect please enter your current password:";
			cin>>crrPass;
		}
		
		string newPassword;
		cout<<"Please enter your new password:";
		cin>>newPassword;
		while(isPasswordWeak(newPassword))
		{
			cout<<"This password is weak please enter password with minimum 6 symbols:";
			cin>>newPassword;
		}

		server->clients[name]->changePassword(newPassword);
	}
	else if(choice==2)
	{
		loggedUserMenu(name);
	}
	else
	{
		cout<<"Wrong command please select number between 1 and 2:"<<endl;
	}
	system("clear");
	accountOptions(name);
}



void CommandParser::loggedUserMenu(string user)
{
	cout<<"Please select one of the options below:"<<endl
		<<"[1].Print unread messages."<<endl
		<<"[2].Print friend requests."<<endl
		<<"[3].Print invitations for events"<<endl
		<<"[4].Print all messages."<<endl
		<<"[5].Send new message."<<endl
		<<"[6].Send friend request."<<endl
		<<"[7].Print list of my friends."<<endl
		<<"[8].Host new event."<<endl
		<<"[9].Invite friends to event."<<endl
		<<"[10].Find new friends."<<endl
		<<"[11].Find new events."<<endl
		<<"[12].Account options."<<endl
		<<"[13].Logout."<<endl;
	int choice;
	cin>>choice;
	switch(choice)
	{
		case 1: system("clear");cout<<endl;server->clients[user]->printUnreadMessages();cout<<endl;loggedUserMenu(user);break;
		case 2: system("clear");cout<<endl;server->clients[user]->printAndProceedFriendRequests();cout<<endl;loggedUserMenu(user);break;
		case 3: system("clear");cout<<endl;server->clients[user]->printAndProceeInvitationsForEvents();cout<<endl;loggedUserMenu(user);break;
		case 4: system("clear");cout<<endl;server->clients[user]->printAllMessages();cout<<endl;loggedUserMenu(user);break;
		case 5: 
		{	
			system("clear");
			cout<<endl;
			string message,recipient;
			cout<<"New message to: ";
			cin>>recipient;
			cout<<"Enter the message: ";
			cin>>message;
			server->clients[user]->sendMessage(recipient,message);cout<<endl;
			loggedUserMenu(user);
			break;
		}
		case 6: 
		{	
			system("clear");
			cout<<endl;
			string to;
			cout<<"Please enter the name of person that you want to send friend request:";
			cin>>to;
			server->clients[user]->sendFriendRequest(to);cout<<endl;
			loggedUserMenu(user);
			break;
		}
		case 7: system("clear");cout<<endl;server->clients[user]->printMyFriends();cout<<endl;loggedUserMenu(user);break;
		case 8: 
		{
			system("clear");
			cout<<endl;
			string name,date,time,location;
			cout<<"Enter event name:";
			cin>>name;
			cout<<"Enter event date:";
			cin>>date;
			cout<<"Enter event time:";
			cin>>time;
			cout<<"Enter event location:";
			cin>>location;
			server->clients[user]->hostEvent(name,date,time,location);cout<<endl;loggedUserMenu(user);break;
		}
		case 9: 
		{
			system("clear");
			cout<<endl;
			string name,guest;
			cout<<"Enter name of event:";
			cin>>name;
			cout<<"Enter name of friend that you want to invite for this event:";
			cin>>guest;
			server->clients[user]->inviteForEvent(name,guest);cout<<endl;loggedUserMenu(user);break;
		}
		case 10: 
		{
			system("clear");
			cout<<endl;
			cout<<"Here is list with people you may know, you can ask any of them for friendship:"<<endl;
			server->clients[user]->printPotentialFriends();cout<<endl;loggedUserMenu(user);break;
		}
		case 11:
		{	
			system("clear");
			cout<<endl;
			cout<<"Here is list with events you may like, you can attend any of them by checking it in main menu."<<endl;
			server->clients[user]->printPotentialEvents();cout<<endl;loggedUserMenu(user);break;
		}
		case 12:system("clear");cout<<endl;accountOptions(user);cout<<endl;loggedUserMenu(user);break;
		case 13:system("clear");cout<<endl;mainMenu();cout<<endl;break;
		default:system("clear");cout<<endl<<"Wrong command please select number between 1 and 12!"<<endl;loggedUserMenu(user);
;break;
	}
}







