// //------------------------------------------------------------------------------
// // Victor Maher - CSE 101 pa8
// // CruzID - Vmaher
// //------------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

int main(int argc, char * argv[]) {
    ifstream in;
    ofstream out;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

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

    Dictionary A;
    string line;
    string token;
    size_t begin, end, len;
    int token_count;
    while (getline(in, line)) {
        len = line.length();
        
        // get tokens in this line
        token_count = 0;

        // get first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end   = min(line.find_first_of(delim, begin), len);
        
        // convert string to array of char
        char p[len];
        for (size_t i = 0; i < sizeof(p); i += 1) {
            p[i] = line[i];
        }

        // convert array to lowercase
        for (size_t i = 0; i < sizeof(p); i += 1) {
            p[i] = tolower(p[i]);
        }
        
        // put lowercase array back into string
        line = "";
        for (size_t i = 0; i < sizeof(p); i += 1) {
            line += p[i];
        }

        token = line.substr(begin, end-begin);
        if (token != "") {
            if (A.contains(token) == false) {
                A.setValue(token, 1);
            } else {
                int tkval = A.getValue(token);
                tkval += 1;
                A.setValue(token, tkval);
            }
        }
        while(token != "" ){  // we have a token
            // set token count to 1
            token_count = 1;

            // get next token
            begin = min(line.find_first_not_of(delim, end+1), len);
            end   = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);

            // if token not in dictionary
            if (token != "") {
                if (A.contains(token) == false) {
                    A.setValue(token, token_count);
                } else {
                    // if token is in dictionary increment value
                    int val = A.getValue(token);
                    val += 1;
                    A.setValue(token, val);
                }
            }
        }  
    }

    // print out dictionary
    out << A << endl;

    // close files
    in.close();
    out.close();
}