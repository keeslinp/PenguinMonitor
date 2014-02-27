#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

string escape(string s)
{
    string buff;
    for(string::iterator i = s.begin();i<s.end();i++)
    {
        if(*i == '$')
        {
            buff += "\\";
        }
        buff += *i;
        cout << *i << i-s.begin() << endl;
    }
    return buff;
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
    string escaped = escape(source);
    cout << system((char*)escaped.c_str()) << endl;
    
        
    cout << "I will check every " << interval <<" seconds" << endl;
    
   
    return 0;
}
