#include<iostream>
#include<cstdlib>
#include<string>

using namespace std;

int main()
{
    string linia;
    int licznik = 0;

    while(getline(cin, linia))
    {
        if(linia[0]=='#') continue;
        if(linia.find(" ") == string::npos) continue;
        else licznik++;
    }
    cout<<licznik<<endl;

    return 0;
}
