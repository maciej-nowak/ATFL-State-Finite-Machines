#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

using namespace std;

//VARIABLES DEFINITIONS-----------------------------------------------
int tab[5000][256];
int ending[5000];
int sentenceLength, state, state2, finish, index;
string sentence, word;
char letter;

void automat()
{
    //CLEARING TABLE--------------------------------------------------------------------------------
    for(int i=0; i<5000; i++)
    {
        ending[i] = -1;
        for(int j=0; j<256; j++) {tab[i][j] = - 1;}
    }

    index = 0;

    //GETTING TEXT LINE---------------------------------------------------------------------------
    while(getline(cin, sentence))
    {
        sentenceLength = 0, state = -1 , state2 = -1;

        //COMMENTARY AND FINAL STATES--------------------------------------------------------------
        if(sentence[0] == '#') continue;
        if(sentence.find(" ") == string::npos)
        {

            finish = atoi(sentence.c_str());
            ending[index] = finish;
            index++;
            continue;
        }
        sentenceLength = sentence.length();

        //CHECKING TEXT LINE----------------------------------------------------------------------
        for(int i = 0; i < sentenceLength; i++)
        {
            if(sentence[i] != ' ')
            {
                if(sentence[i] >= 48 && sentence[i] <= 57) word = word + sentence[i];
                else
                {
                    //PUSHING LINE TO TABLE--------------------------------------------------------
                    letter = sentence[i];
                    int liczba = (int)letter;
                    if(tab[state][liczba] == -1) tab[state][liczba] = state2;
                }
            }
            //MAKING NUMBERS AS STATES----------------------------------------------------------------
            else
            {
                if(word[0] >= 47 && word[0] <= 57)
                {
                    if(state == -1) state = atoi(word.c_str());
                    else state2 = atoi(word.c_str());
                }
                word = "";
            }
        }

    }
}

bool checkFinalState(int x)
{
    bool check = false;
    for(int i = 0; i < 5000; i++)
    {
        if(ending[i] == x)
        {
            check = true;
            break;
        }
    }
    return check;
}

void check(string text)
{
    int textLength = text.length();
    int actualState = 0;
    bool check = true;
    for(int i=0; i<textLength; i++)
    {
        char letter = text[i];
        int letterASCII = (int)letter;
        if(tab[actualState][letterASCII] != -1) actualState = tab[actualState][letterASCII];
        else
        {   check = false;
            break;
        }
    }
    if(check && checkFinalState(actualState)) cout<<"YES "<<text<<endl;
    else cout<<"NO "<<text<<endl;
}

int main(int argc, char*argv[])
{
    //READING FILE----------------------------------------------------------------------
    automat();
    string data;
    fstream fileArg;
    fileArg.open(argv[1], ios::in);

    while(!fileArg.eof())
    {
        getline(fileArg, data);
        if(data[0] >= 33)check(data);
    }

    fileArg.close();
    return 0;
    
}
