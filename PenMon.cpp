#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <thread>
#include <chrono>

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
    string source(argv[1]);
    string response(argv[2]);
    cout << "When " << source << " changes I will do this: " << response << endl;
    int interval = 300;
    if(argc>3 && argv[3][0] == '-')
    {
        switch(argv[3][1]){
            case 'u':
                stringstream(argv[4]) >> interval;
                break;
        }
    }
//Store original value
    string answer = command((char*)source.c_str());
    cout << "starting value is: \n" << answer << endl;
    cout << "I will check every " << interval <<" seconds" << endl;
//Main checking loop
    while(answer==command((char*)source.c_str()))
    {
    //Wait desired amount
        this_thread::sleep_for(chrono::seconds(interval));
    }
//Respong accordingly
    cout << command((char*)response.c_str()) << endl;
   
    return 0;
}
