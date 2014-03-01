#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <ctime>
#include <cerrno>
#include <syslog.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

//Function for easy interaction with terminal
string command(char c[])
{
	string answer("");
	char buff[256];
	FILE *fp = popen(c,"r");
	while ( fgets( buff, 256, fp ) != NULL ) {
		answer += buff;
	}
	pclose(fp);
	return answer;
}

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		cout << "You're missing some arguments.\nFor more information visit: github.com/h3ckboy/PenguinMonitor"<<endl;
		return EXIT_FAILURE;
	}
	string source(argv[1]);
	string response(argv[2]);
	cout << "When " << source << " changes I will do this: " << response << endl;
	int interval = 300;
	int repeat = 0;
//Parse Args
	int i = 3;
	while(argc>i && argv[i][0] == '-')
	{
	        switch(argv[i][1]){
		//Set update Interval
			case 'u':
				stringstream(argv[i+1]) >> interval;
				i+=2;
			break;
		//Set repeating
			case 'r':
				repeat = 1;
				i++;
			break;
		}
	}
//Store original value
	string answer = command((char*)source.c_str());
	cout << "starting value is: \n" << answer << endl;
	cout << "I will check every " << interval <<" seconds" << endl;
//Main checking loop
	pid_t pid, sid;
	pid = fork();
	if (pid < 0) {
		exit(EXIT_FAILURE);
	}
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}
	
	umask(0);

	sid = setsid();
	if(sid < 0){
		exit(EXIT_FAILURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	do{
		long double t = time(0);
		while(answer==command((char*)source.c_str()))
		{
		    //Wait desired amount
		        this_thread::sleep_for(chrono::seconds(interval-(int)(time(0)-t)));
			t = time(0);
		}
		answer = command((char*)source.c_str());
		command((char*)response.c_str());
	}while(repeat);
//Respond accordingly
	exit(EXIT_SUCCESS);
}
