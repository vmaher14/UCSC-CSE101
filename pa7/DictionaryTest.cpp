//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa7
// CruzID - Vmaher
//------------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main() {

    Dictionary A;
    Dictionary B;
    Dictionary C;
    Dictionary D;
    string s[] = {"bruh", "chicken", "cheese", "short", "banana", "gym", "zebra", "deltoid", "mario", "victor"};

  
    for (int i = 0; i < 10; i += 1) {
      A.setValue(s[i], i + 2);
    }
    for (int i = 9; i >= 0; i -= 1) {
      B.setValue(s[i], i + 2);
    }

    C = A;

    cout << "A.size() = " << A.size() << endl << A << endl;
    cout << "B.size() = " << B.size() << endl << B << endl;
    cout << "C.size() = " << C.size() << endl << C << endl;

    B.setValue("gym", 14);
    C.setValue("cheese", 21);
    
    cout << "B.size() = " << B.size() << endl << B << endl;
    cout << "C.size() = " << C.size() << endl << C << endl;

    cout << "A.getValue(chicken) = " << A.getValue("chicken") << endl;
    A.remove("short");
    A.remove("zebra");
    cout << A << endl;

    B.begin();
    C.begin();

    cout << "B.currentVal() = " << B.currentVal() << endl;
    cout << "C.currentVal() = " << C.currentVal() << endl << endl;

    B.end();
    C.end();

    string v = B.currentKey();
    string m = C.currentKey();

    cout << "B.currentKey() = " << v << endl;
    cout << "C.currentKey() = " << m << endl << endl;

    cout << "A==B is " << (A==B?"true":"false") << endl;
    cout << "B==C is " << (B==C?"true":"false") << endl;
    cout << "C==A is " << (C==A?"true":"false") << endl << endl;

    A.clear();
    cout << "A.size() = " << A.size() << A << endl;




   


 
}
    

