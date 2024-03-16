//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa6
// CruzID - Vmaher
//------------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include"BigInteger.h"

using namespace std;

int main(int argc, char * argv[]) {
    ifstream in;
    ofstream out;
    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }
    //initialize string variable
    std::string s;
    
    //read in first string and initialize first integer
    getline(in, s);
    BigInteger A = BigInteger(s);

    //read in past empty line and initialize second integer
    getline(in, s);
    getline(in, s);
    BigInteger B = BigInteger(s);

    //A
    out << A << endl;
    out << endl;

    //B
    out << B << endl;
    out << endl;

    //A + B
    BigInteger C = A + B;
    out << C << endl;
    out << endl;

    //A - B
    BigInteger D = A - B;
    out << D << endl;
    out << endl;

    //A - A
    BigInteger E = A - A;
    out << E << endl;
    out << endl;

    //3A - 2B;
    BigInteger three = BigInteger("3");
    BigInteger two = BigInteger("2");
    BigInteger F = (A * three) - (B * two);
    out << F << endl;
    out << endl;

    //AB
    BigInteger G = A * B;
    out << G << endl;
    out << endl;

    //A^2
    BigInteger H = A * A;
    out << H << endl;
    out << endl;

    //B^2
    BigInteger I = B * B;
    out << I << endl;
    out << endl;

    //9A^4 + 16B^5
    BigInteger nine = BigInteger("9");
    BigInteger st = BigInteger("16");
    BigInteger J = (nine * (A * A * A * A)) + (st * (B * B * B * B * B));
    out << J << endl;
    out << endl;


}

