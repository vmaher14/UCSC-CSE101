//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa6
// CruzID - Vmaher
//------------------------------------------------------------------------------
#include "List.h"
#include<iostream>
#include<string>
#include<stdexcept>

using namespace std;
// Private Constructor

List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List() {
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    pos_cursor = 0;    
    num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    pos_cursor = 0;    
    num_elements = 0;
    Node *N = L.frontDummy->next;
    while (N != L.backDummy) {
        insertBefore(N->data);
        N = N->next;
    }
    //for concat
    moveFront();
}

// Destructor
List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if (length() <= 0) {
        throw std::length_error("List Error: Calling front() on empty list\n");
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if (length() <= 0) {
        throw std::length_error("List Error: Calling back() on empty list\n");
    }
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if (position() >= length()) {
        throw std::range_error("List Error: Calling peekNext() with position() > length()\n");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if (position() <= 0) {
        throw std::range_error("List Error: Calling peekPrev() with position() < 0\n");
    }
    return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    moveFront();
    while (length() > 0) {
        eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = num_elements;

}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
    if (position() >= length()) {
        throw std::range_error("List Error: Calling moveNext() with position() > length()\n");
    }
    ListElement d = afterCursor->data;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor += 1;
    return d;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
    if (position() <= 0) {
        throw std::range_error("List Error: Calling movePrev() with position() < 0\n");
    }
    ListElement d = beforeCursor->data;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor -= 1;
    return d;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    Node *N = new Node(x);
    afterCursor->prev = N;
    beforeCursor->next = N;
    N->prev = beforeCursor;
    N->next = afterCursor;
    afterCursor = N;
    num_elements += 1;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    Node *N = new Node(x);
    afterCursor->prev = N;
    beforeCursor->next = N;
    N->prev = beforeCursor;
    N->next = afterCursor;
    beforeCursor = N;
    num_elements += 1;
    pos_cursor += 1;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    if (position() > length()) {
        throw std::range_error("List Error: Calling setAfter() with position() > length()\n");
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    if (position() <= 0) {
        throw std::range_error("List Error: Calling setBefore() with position() < 0\n");
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    if (position() >= length()) {
        throw std::range_error("List Error: Calling eraseAfter() with position() > length()\n");
    }
    Node *N = afterCursor;
    afterCursor = afterCursor->next;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    num_elements -= 1;
    delete N;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    if (position() <= 0) {
        throw std::range_error("List Error: Calling eraseAfter() with position() > length()\n");
    }
    Node *N = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    num_elements -= 1;
    pos_cursor -= 1;
    delete N;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
    while (position() < length()) {
        ListElement n = moveNext();
        if (n == x) {
            return position();
        }
    }
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    while (position() > 0) {
        ListElement n = movePrev();
        if (n == x) {
            return position();
        }
    }
    return -1;

}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    //keep track of cursor
    Node *N = beforeCursor;
    moveFront();
    while (position() < length()) {
        ListElement d = moveNext();
        while (findNext(d) != -1) {
            if (N == beforeCursor) {
                N = N->prev;
            }
            eraseBefore();
        }
        moveFront();
        findNext(d);
    }
    moveFront();
    if (N != frontDummy) {
        findNext(N->data);
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List C = List(L);
    Node *N = frontDummy->next;
    while (N != backDummy) {
        C.insertBefore(N->data);
        N = N->next;
    }
    C.moveFront();
    return C;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    Node *N = nullptr;
    std::string s = "(";

    for (N = frontDummy->next; N != backDummy; N = N->next) {
        s += std::to_string(N->data);
        if (N != backDummy->prev) {
            s += ", ";
        }
    }
    s += ")";
    return s;

}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    bool eq = false;
    Node *N = nullptr;
    Node *M = nullptr;

    eq = (length() == R.length());
    N = frontDummy;
    M = R.frontDummy;
    while (eq && N != nullptr) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
    if (this != &L) {
        List tmp = L;

        std::swap(frontDummy, tmp.frontDummy);
        std::swap(backDummy, tmp.backDummy);
        std::swap(beforeCursor, tmp.beforeCursor);
        std::swap(afterCursor, tmp.afterCursor);
        std::swap(pos_cursor, tmp.pos_cursor);
        std::swap(num_elements, tmp.num_elements);
    }
    return *this;
}