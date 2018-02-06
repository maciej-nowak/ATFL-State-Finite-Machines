#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

using namespace std;

//VARIABLES DEFINITIONS-----------------------------------------------
string automat[5000][256];
int ending[5000];
int sentenceLength, state, finish, index;
string sentence, word, state2;
char letter;

int finalAutomat[5000][256];
string newStates[5000];
int statesNumber = 0;
int finalEnding[5000];

void automatNoDeterministic()
{
    for(int i=0; i<5000; i++)
    {
        ending[i] = -1;
        for(int j=0; j<256; j++) {automat[i][j] = "";}
    }

    index = 0;

    //GETTING TEXT LINE---------------------------------------------------------------------------
    while(getline(cin, sentence))
    {
        sentenceLength = 0, state = -1 , state2 = "";

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
                if(sentence[i] >= 47 && sentence[i] <= 57) word = word + sentence[i];
                else
                {
                    //PUSHING LINE TO TABLE--------------------------------------------------------
                    letter = sentence[i];
                    int number = (int)letter;
                    automat[state][number] = automat[state][number] + state2;
                }
            }
            //MAKING NUMBERS AS STATES----------------------------------------------------------------
            else
            {
                if(word[0] >= 47 && word[0] <= 57)
                {
                    if(state == -1) state = atoi(word.c_str());
                    else state2 = word + ";";
                }
                word = "";
            }
        }

    }
}

//ADDING NEW STATE AS A NUMBER e.g. 0;2;1 -> 2
void addNewStates(string text)
{
    for(int i=0; i<=statesNumber; i++)
    {
        if(newStates[i] == text) return;
    }
    statesNumber = statesNumber + 1;
    newStates[statesNumber] = text;
}

//GETTING STATE NUMBER
int getStateNumber(string text)
{
    for(int i=0; i<=statesNumber; i++)
    {
        if(newStates[i] == text) return i;
    }

}

//MAKING AUTOMAT DETERMINISTIC
void automatDeterministic()
{
    //CLEARING TABLE
    for(int i=0; i<5000; i++)
    {
        for(int j=0; j<256; j++) {finalAutomat[i][j] = -1;}
    }

    //SOME VARIABLES
    int currentState = 0;
    string stringValue;
    int value;
    newStates[0] = "0;";
    string content = "", currentStateValues = "";

    //MAIN LOOP
    while(true)
    {
        if(newStates[currentState] == "") break;
        currentStateValues = newStates[currentState];
        stringValue = "";

        //LOOP FOR GETTING THE STRING OF STATES LIKE 0;2;1 (FOR EVERY LETTER)
        for(int i=97; i<=122; i++)
        {

            //LOOP FOR CHECKING ALL STRING OF STATES LIKE 0;2;1 -> 0  2   1
            for(int j=0; j<currentStateValues.length(); j++)
            {
                if(currentStateValues[j] != ';')
                {
                    stringValue = stringValue + currentStateValues[j];
                }
                else
                {
                    value = atoi(stringValue.c_str());
                    stringValue = "";
                    if(automat[value][i] != "") content = content + automat[value][i];
                }
            }
            //ADDING NEW STATES (OR NOT) AND PUTTING NEW STATE INTO FINAL AUTOMAT
            if(content != "")
            {
                addNewStates(content);
                finalAutomat[currentState][i] = getStateNumber(content);
            }
            content = "";
        }
        currentState = currentState + 1;
    }
}

//MAKING ENDING KEYS FOR DETERMINISTIC AUTOMAT
void keysDeterministic()
{
    //CLEARING TABLE
    for(int i=0; i<5000; i++) finalEnding[i] = -1;
    int keysCounter = 0;
    int value;

    //LOOP FOR GETTING OLD KEYS
    for(int i=0; i<5000; i++)
    {
        if(ending[i] == -1) break;
        else
        {
            //LOOP FOR GETTING NEW KEYS FROM OLD KEY
            for(int j=0; j<5000; j++)
            {
                if(newStates[j] == "") break;
                string currentStateValues = newStates[j];
                string stringValue = "";

                //GETTING A NUMBER LIKE 1 OR 24 ETC
                for(int k=0; k<currentStateValues.length(); k++)
                {
                    if(currentStateValues[k] != ';')
                    {
                        stringValue = stringValue + currentStateValues[k];
                    }
                    else
                    {
                        value = atoi(stringValue.c_str());
                        stringValue = "";
                    }

                    //PUTTING NEW FINAL KEYS
                    if(ending[i] == value)
                    {
                        bool checkKey = true;
                        for(int k=0; k<=keysCounter; k++)
                        {
                            if(finalEnding[k] == j) checkKey = false;
                        }
                        if(checkKey)
                        {
                            finalEnding[keysCounter] = j;
                            keysCounter++;
                            break;
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char*argv[])
{
    automatNoDeterministic();
    automatDeterministic();
    keysDeterministic();

    for(int i=0; i<5000; i++)
    {
        for(int j=97; j<122; j++)
        {
            if(finalAutomat[i][j] != -1) cout<<i<<" "<<finalAutomat[i][j]<<" "<<(char)j<<endl;
        }
    }

    for(int i=0; i<5000; i++)
    {
        if(finalEnding[i] == -1) break;
        else cout<<finalEnding[i]<<endl;
    }

    return 0;
}
