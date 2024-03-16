//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa6
// CruzID - Vmaher
//------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  BigIntegerTest.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main() {
    string s = "46548465432135485468462168513521651654";
    string s2 = "+89874984524165132135135135185184846";
    string s3 = "-6546548468465468546846486846846546846";

    BigInteger A = BigInteger(s);
    BigInteger B = BigInteger(s2);
    BigInteger C = BigInteger(s3);
    BigInteger D = A;

    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl;
    cout << "D = " << D << endl << endl;

    cout << "C.sign() = " << C.sign() << endl;
    C.negate();
    cout << "C negated sign = " << C.sign() << endl << endl;
    
    cout << "(A < B)  = " << ((A<B)? "True":"False") << endl;
    cout << "(B < C) = " << ((B<C)?"True":"False") << endl;
    cout << "(A == D)  = " << ((A==D)? "True":"False") << endl << endl;

    BigInteger E = A + B;
    BigInteger F = A - B;
    BigInteger G = A * B;
    BigInteger H = D - A;
    C += C;

    cout << "A + B = " << E << endl;
    cout << "A - B = " << F << endl;
    cout << "A * B = " << G << endl;
    cout << "D - A = " << H << endl;
    cout << "C += C = " << C << endl << endl;

    A.makeZero();
    cout << "A.makeZero() = " << A << endl << endl;

    


    






   

    






}