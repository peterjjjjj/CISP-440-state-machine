#include <iostream>
#include <fstream>
using namespace std;
#include <unistd.h>
#include <string.h>


#define STATES 21
char nextState[STATES][5] {
    {1,0,0,0,0 },
    {1,2,0,0,0 },
    {1,0,3,0,0 },
    {1,0,4,0,0 },
    {1,0,0,5,0 },
    {1,0,6,0,0 },
    {1,0,0,0,0 },

}; 

char state = 0;
int Count = 0;

char instr[80] = "cheese";   

void process(char ch)
{
    // print current char
    //cout << ch;
    
    // move to next state
    state = nextState[state][ch - 'a'];

    // output count if we are back to initial state
    if (state == strlen(instr))
        cout << Count + 1 << ", ";

    Count++;  //another ch bites the dust!
}


void print_StateTable()
{
    cout << "\nComplete state table for " << instr << "...\n";
    cout << "s\tc\th\te\ts\t\n\n";

    int l = strlen(instr) + 1;
    for (int s = 0; s < l; s++) {
        cout << s << "\t";
        for (int ch = 0; ch < 4; ch++)
            cout << (int)nextState[s][ch] << "\t";
        cout << endl;
    }
}


int strncmp_olap(char* str1, char* str2, int n)
{
    int i, j;
    int l1 = strlen(str1);
    int l2 = strlen(str2);

    for (i = 0, j = l2 - n; i < n; i++, j++)
        if (str1[i] != str2[j])
            return true;

    return false;
}

void create_StateTable(const char* sequence)
{
    int states = strlen(sequence) + 1;
    int lgot;
    char ch[4] = {'c', 'h', 'e', 's'};
    char got[80];
    int nextstate = 0;
    for(int s = 0; s < states; ++s) {
        for(int c = 0; c < 4; ++c) {
            strncpy(got, sequence, s);
            got[s] = ch[c];
            got[s + 1] = '\0';
            lgot = s + 1;
            nextstate = 0;
            for (int x = 0; x < lgot &&  x < states; ++x) {
                if (!strncmp_olap(const_cast<char*>(sequence), got, x+1)) {
                    nextstate = x + 1;
                }
            }
            cout << nextstate;
        }
        cout << endl;
    }


}

int main()
{
    chdir("");
    
    create_StateTable(instr);
    print_StateTable();


    char ch;
    ifstream in("extra.txt");
    if (!in) {
        cout << "Error opening file\n";
        return 1;
    }
    


    cout << "\nThe string " << instr << " was found at locations: ";

    // read and process characters
    while (in) {
        in.get(ch);
        if (in)
            process(ch);
    }
    int i = strncmp_olap("abab", "bab", 1);
    
    return 0;
}
