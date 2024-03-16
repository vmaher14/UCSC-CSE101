//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa5
// CruzID - Vmaher
//------------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main() {
    List V, I, C;

    for (int i = 1; i <= 14; i += 1) {
        V.insertBefore(i);
        I.insertAfter(i);
        C = V.concat(I);
    }

    cout << endl;
    cout << "V = " << V << endl;
    cout << "I = " << I << endl;
    cout << "C = " << C << endl;
    cout << endl << "V.position() = " << V.position() << endl;
    cout << endl << "I.position() = " << I.position() << endl;
    cout << endl;

    V.moveFront();
    I.moveBack();

    cout << endl << "V.position() = " << V.position() << endl;
    cout << endl << "I.position() = " << I.position() << endl;
    cout << endl;

    C.moveFront();
    cout << "C.findNext(7) = " << C.findNext(7) << endl;
    cout << "C = " << C << endl;
    C.eraseBefore();
    C.eraseAfter();
    cout << "C = " << C << endl;

}  