//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa6
// CruzID - Vmaher
//------------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

uint power = 9;
long base = 1000000000;

// Exported type  -------------------------------------------------------------

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
    List digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    if (s == "") {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    if ((s[0] != '+' && s[0] != '-') && (isdigit(s[0]) == false)) {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    //if front character in string is + or -
    if (s[0] == '+') {
        signum = 1;
        s = s.substr(1);
    } else if (s[0] == '-') {
        signum = -1;
        s = s.substr(1);
    } else {
        signum = 1;
    }
    for (uint i = 0; i < s.length(); i += 1) {
        if (isdigit(s[i]) == false) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    } 
    //start from back of list and if reach the power, add everything to list
    long l = s.length() - 1;
    std::string tmp = "";
    while (l >= 0) {
        if (tmp.length() == power) {
            digits.insertAfter(std::stol(tmp));
            tmp = "";
        }
        tmp = s[l] + tmp;
        l -= 1;
    }
    //if string does not evenly divided by power
    if (tmp != "") {
        while (tmp.length() < power) {
            tmp = "0" + tmp;
        }
        digits.insertAfter(std::stol(tmp));
    }
    



}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    signum = N.signum;
    digits = List(N.digits);
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();

// Helper functions --------------------------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L) {
    L.moveFront();
    while (L.position() < L.length()) {
        ListElement n = L.moveNext();
        L.setBefore(n * -1);
    }
}
// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn) {
    if (sgn == -1) {
        negateList(B);
    }
    S.clear();
    A.moveBack();
    B.moveBack();
    while (A.position() > 0 && B.position() > 0) {
        ListElement a = A.movePrev();
        ListElement b = B.movePrev();
        S.insertAfter(a + b);
    }
    //remaining digits in list A or B
    while (B.position() > 0) {
        ListElement b = B.movePrev();
        S.insertAfter(b);
    }
    while (A.position() > 0) {
        ListElement a = A.movePrev();
        S.insertAfter(a);
    }
}
// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L) {
    int sgn;
    if (L.length() == 0) {
        return 0;
    }
    //remove 0s
    L.moveFront();  
    while (L.front() == 0) {
        L.eraseAfter();
    }
    //sets sgn for whether integer is positive or negative
    if (L.front() < 0) {
        sgn = -1;
    } else if (L.front() > 0) {
        sgn = 1;
    }
    //normalize and keep track of carry
    long carry = 0;
    L.moveBack();
    while (L.position() > 0) {
        //keep track of current value with carry
        ListElement cnt = L.movePrev() + carry;
        //reset carry
        carry = 0;
        //if cnt >= base
        if (cnt >= base) {
            carry = cnt / base;
            cnt = cnt % base;
        }
        //if cnt < 0 and integer is positive
        if (cnt < 0 && sgn == 1) {
            carry -= 1;
            cnt += base;
        }
        //if cnt > 0 and integer is negative
        if (cnt > 0 && sgn == -1) {
            carry += 1;
            cnt -= base;
        }
        L.setAfter(cnt);
    }
    //if there is a carry
    if (carry != 0) {
        L.insertAfter(carry);
    }
    //if there are any leftover 0s
    L.moveFront();
    while (L.front() == 0) {
        L.eraseAfter();
    }
    //if integer is negative, turn positive
    if (sgn == -1) {
        negateList(L);
    }
    return sgn;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p) {
    L.moveBack();
    for (int i = 0; i < p; i += 1) {
        L.insertBefore(0);
    }
}
// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m) {
    L.moveFront();
    while (L.position() < L.length()) {
        ListElement n = L.moveNext();
        L.setBefore(n * m);
    }
}


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
    if (signum == -1) {
        return -1;
    } else if (signum == 1) {
        return 1;
    } else {
        return 0;
    }
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    if (signum < N.signum) {
        return 1;
    }
    if (signum > N.signum) {
        return -1;
    }
    if (digits.length() > N.digits.length()) {
        return 1;
    } 
    if (digits.length() < N.digits.length()) {
        return -1;
    }
    List ci = digits;
    List di = N.digits;
    //integers must be of same length
    ci.moveFront();
    di.moveFront();
    while (ci.position() < ci.length()) {
        ListElement c = ci.moveNext();
        ListElement d = di.moveNext();
        if (c < d) {
            return -1;
        }
        if (c > d) {
            return 1;
        }
    }
    //integers are equal
    return 0;
}   



// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    digits.clear();
    signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    if (digits.length() > 0) {
        if (signum == 1) {
            signum = -1;
        } else {
            signum = 1;
        }
    }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    //converts lists to positive if they are negative
    if (signum == 1 && N.signum == -1) {
        BigInteger No = N;
        No.negate();
        return sub(No);
    } else if (signum == -1 && N.signum == 1) {
        BigInteger T = *this;
        T.negate();
        T = N.sub(T);
        return T;
    } else if (signum == -1 && N.signum == -1) {
        BigInteger No = N;
        BigInteger T = *this;
        No.negate();
        T.negate();
        No = T.add(No);
        No.negate();
        return No;
    }
    //perform addition
    BigInteger B = BigInteger();
    sumList(B.digits, digits, N.digits, 1);
    B.signum = normalizeList(B.digits);
    return B;

}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    //if lists are both equal
    if (compare(N) == 0) {
        BigInteger O = BigInteger();
        return O;
    }
     //converts lists to positive if they are negative
    if (signum == 1 && N.signum == -1) {
        BigInteger No = N;
        No.negate();
        return add(No);
    } else if (signum == -1 && N.signum == 1) {
        BigInteger T = *this;
        T.negate();
        T = N.add(T);
        T.negate();
        return T;
    } else if (signum == -1 && N.signum == -1) {
        BigInteger No = N;
        BigInteger T = *this;
        No.negate();
        T.negate();
        T = T.sub(No);
        T.negate(); 
        return T;
    }
    //perform subtraction
    BigInteger S = BigInteger();
    sumList(S.digits, digits, N.digits, -1);
    S.signum = normalizeList(S.digits);
    return S;
   
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    //uses shift and scalar and normalize
    if (digits.length() == 0 || N.digits.length() == 0) {
        BigInteger O = BigInteger();
        return O;
    }
    BigInteger M = BigInteger();
    List C = List(N.digits);
    C.moveBack();
    int count = 0;
    while (C.position() > 0) {
        //store value currently on
        BigInteger S = BigInteger(*this);
        ListElement n = C.movePrev();
        shiftList(S.digits, count);
        scalarMultList(S.digits, n);
        sumList(M.digits, S.digits, M.digits, 1);
        normalizeList(M.digits);
        count += 1;
    }
    M.signum = normalizeList(M.digits);
    
    if ((signum == 1 && N.signum == -1) || (signum == -1 && N.signum == 1)) {
        M.signum = -1;
    } else {
        M.signum = 1;
    }
    return M;
    
}

// Returns true if BigIntegers are equal
bool BigInteger::equals(const BigInteger& R) const {
    BigInteger Di = BigInteger(*this);
    BigInteger Ri = BigInteger(R);
    if (Di.digits.length() != Ri.digits.length()) {
        return false;
    }
    if (Di.signum != Ri.signum) {
        return false;
    }
    if (Di.signum == -1) {
        Di.negate();
        Ri.negate();
    }
    Di.digits = List(digits);
    Ri.digits = List(R.digits);
    Di.digits.moveFront();
    Ri.digits.moveFront();
    while (Di.digits.position() < Di.digits.length()) {
        ListElement d = Di.digits.moveNext();
        ListElement r = Ri.digits.moveNext();
        if (d != r) {
            return false;
        }
    }
    return true;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    std::string s = "";
    if (digits.length() == 0) {
        s += '0';
        return s;
    }
    if (signum == -1) {
        s += '-';
    } 
    digits.moveFront();
    while (digits.front() == 0) {
        digits.eraseAfter();
    }
    while (digits.position() < digits.length()) {
        std::string n = std::to_string(digits.moveNext());
        if (digits.position() > 1) {
            std::string z(power - n.length(), '0');
            s += z;
        }
        s += n;
        
    }
    return s;

}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}
    
// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::compare(B) == 0;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == -1) {
        return true;
    } else {
        return false;
    }
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == -1 || A.BigInteger::compare(B) == 0) {
        return true;
    } else {
        return false;
    }
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == 1) {
        return true;
    } else {
        return false;
    }
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == 1 || A.BigInteger::compare(B) == 0) {
        return true;
    } else {
        return false;
    }
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.BigInteger::add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.BigInteger::sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.BigInteger::mult(B);
    return A;
}




