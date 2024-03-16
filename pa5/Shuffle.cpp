//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa5
// CruzID - Vmaher
//------------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include <iomanip>
#include"List.h"
using namespace std;


//function to shuffle list
void shuffle(List& D) {
    int s = D.length();
    List A = List();
    List B = List();
    D.moveFront();
    while (D.position() < s) {
        int n = D.position();
        ListElement d = D.moveNext();
        if (n < (s / 2)) {
            A.insertBefore(d);
        } else {
            B.insertBefore(d);
        }
    }
    D.clear();
    A.moveFront();
    B.moveFront();
    for (int i = 1; i <= s; i += 1) {
        if (i % 2 == 0) {
            ListElement e = A.moveNext();
            D.insertBefore(e);
        } else {
            ListElement e = B.moveNext();
            D.insertBefore(e);
        }
    }
}

//helper function to keep track of number of shuffles
int numShuff(List& D) {
    List C = D;
    int cnt = 1;
    shuffle(C);
    while (!(C == D)) {
        shuffle(C);
        cnt += 1;
    }
    return cnt;
}

int main(int argc, char * argv[]) {
    int n;

    // check command line for correct number of arguments
   if( argc != 2 ){
      cerr << "Usage: " << argv[0] << " <Argument> " << endl;
      return(EXIT_FAILURE);
   }

   n = atoi(argv[1]);
   if (n < 0) {
       cerr << "invalid argument, must be > 0" << endl;
       return(EXIT_FAILURE);
   }

   cout << "deck size       shuffle count" << endl;
   cout << "------------------------------" << endl;
   for (int i = 1; i <= n; i += 1) {
       List O = List();
       for (int j = 0; j < i; j += 1) {
           O.insertBefore(j);
       }
       int shuff = numShuff(O);
       cout << left << setw(1) << ' ' << left << setw(16) << i << left << shuff << endl;
   }

}


