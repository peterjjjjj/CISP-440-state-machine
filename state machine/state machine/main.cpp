/*
   Generates a state machine to find all occurances of an arbitrary string

   Dan Ross
   Original April 2013
   Improved Nov 2020
   Poked at somemore Oct 2023

*/
#include <iostream>
#include <fstream>
#pragma warning( disable : 4996)
#pragma warning( disable : 4244)
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

}; /*= {
//     a  b   //inputs
      1, 0,  //state 0
      1, 2,  //state 1
      3, 0,  //state 2
      1, 4,  //state 3
      3, 0,  //state 4
};
*/

char state = 0;
int Count = 0;

// hard code input string
char instr[80] = "cheese";   //"abbbbbbaaaaaba";

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


/*
Compares first n characters of str1,
with last n characters of str2.

Returns 0 (false) if they match

It would look like this if you called it with hard-coded values:
strncmp("abab", "a", 1) match, store this

Copyright (c) 1981 Dan Ross
*/
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

/*
Create a state table for a sequence detector
*/
void create_StateTable(const char* sequence)
{
    /////////////////  YOU WRITE THIS FUNCTION PLEASE  ////////////////

    /* you may need these things...
    char got[80];
    got[0] = 0;         // the null terminator
    strncpy(...);       // handy, but it doesn't do this: got[zeroSpot] = 0;
    strcat(...);        // for sticking on a's and b's
    strlen(...);        // is useful too
    strncmp_olap(..)    // an amazing function!  try it!

    some tricky s**t...
    char ch[2] = "a";
    ch[0]++; // increments the above string to the next character
    */
    int states = strlen(sequence) + 1;
    int lgot;
    char ch[4] = {'c', 'h', 'e', 's'};
    char got[80];
    got[0] = 0;
    int nextstate = 0;
    char temp[5] = {',', ',', ',', ',', ' '};
    ofstream out("temp.txt");
    if (!out) {
        cout << "Error opening file temp\n";
        return;
    }


    
    for(int s = 0; s < states; ++s) {
        printf("state %d ", s);
        
        out << "{";
        for(int i = 0; i <= 4; ++i) {
            strncpy(got, sequence, s);
            got[s] = ch[i];
            got[s + 1] = '\0';
            lgot = s + 1;
            printf("%s goto ", got);
            
            nextstate = 0;
            for (int j = s + 1; j > 0; --j) {
                if (strncmp(sequence, &got[s + 1 - j], j) == 0) {
                    nextstate = j;
                    break;
                }
            }
            printf(" %d ", nextstate);
            out << nextstate << temp[i];
        }
        printf("\n");
        out << "}," << endl;
    }
    

 }


int main()
{
    chdir("/Users/mengfeijin/desktop/xcodes/cisp 440/cisp 440 state table/cisp 440 state table");
    /// //////////////  CREATE THE STATE TABLE
    
    create_StateTable(instr);
    print_StateTable();

    ///////////////////    RUN THE STATE MACHINE

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
