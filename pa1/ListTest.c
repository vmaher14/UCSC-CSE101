/*Test Client for List ADT*/

#include "List.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    List First = newList();
    List Second = newList();

    for (int i = 0; i <= 30; i += 1) {
        if (i % 2 == 0) {
            append(First, i);
        } else  {
            prepend(Second, i); 
        }
    }
    printList(stdout, First);
    printf("\n");
    printList(stdout, Second);
    printf("\n");
    printf("\n");
   
    printf("First List Index: %d\n", index(First));
    printf("First List Front: %d\n", front(First));
    printf("First List Back: %d\n", back(First));
    printf("First List Length: %d\n", length(First));
    printf("\n");
    printf("Second List Index: %d\n", index(Second));
    printf("Second List Front: %d\n", front(Second));
    printf("Second List Back: %d\n", back(Second));
    printf("Second List Length: %d\n", length(Second));
    printf("\n");

    printf("%s\n", equals(First, Second)?"true":"false");
    printf("\n");

    moveFront(First);
    moveBack(Second);
    printf("Set cursor of First list to first element and cursor of second list to last element\n");
    printf("Cursor of First list: %d\n", get(First));
    printf("Cursor of Second list: %d\n", get(Second));
    set(First, 14);
    set(Second, 7);
    printf("Set cursor of First List to 14 and cursor of Second List to 7\n");
    printf("Cursor of First list: %d\n", get(First));
    printf("Cursor of Second list: %d\n", get(Second));
    moveNext(First);
    movePrev(Second);
    printf("Moved First List cursor to next idx and Second List cursor to prev idx\n");
    printf("Cursor of First list: %d\n", get(First));
    printf("Cursor of Second list: %d\n", get(Second));
    printf("\n");

    printf("Inserted 10 after First List cursor and 10 before Second List cursor\n");
    insertAfter(First, 10);
    insertBefore(Second, 10);
    printList(stdout, First);
    printf("\n");
    printList(stdout, Second);
    printf("\n");
    printf("\n");

    printf("Deleted First element of First List and Last element of Second List\n");
    deleteFront(First);
    deleteBack(Second);
    printList(stdout, First);
    printf("\n");
    printList(stdout, Second);
    printf("\n");
    printf("\n");

    printf("Deleted Cursor of First and Second List\n");
    delete(First);
    delete(Second);
    printList(stdout, First);
    printf("\n");
    printList(stdout, Second);
    printf("\n");
    printf("\n");

    printf("Cleared First and Second List\n");
    clear(First);
    clear(Second);
    printf("Length of First List: %d\n", length(First));
    printf("Length of Second List: %d\n", length(Second));

    freeList(&First);
    freeList(&Second);

    return(0);
}

/*Output:
0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 
29 27 25 23 21 19 17 15 13 11 9 7 5 3 1

First List Index: -1
First List Front: 0
First List Back: 30
First List Length: 16

Second List Index: -1
Second List Front: 29
Second List Back: 1
Second List Length: 15

false

Set cursor of First list to first element and cursor of second list to last element
Cursor of First list: 0
Cursor of Second list: 1
Set cursor of First List to 14 and cursor of Second List to 7
Cursor of First list: 14
Cursor of Second list: 7
Moved First List cursor to next idx and Second List cursor to prev idx
Cursor of First list: 2
Cursor of Second list: 3

Inserted 10 after First List cursor and 10 before Second List cursor
14 2 10 4 6 8 10 12 14 16 18 20 22 24 26 28 30
29 27 25 23 21 19 17 15 13 11 9 7 5 10 3 7

Deleted First element of First List and Last element of Second List
2 10 4 6 8 10 12 14 16 18 20 22 24 26 28 30
29 27 25 23 21 19 17 15 13 11 9 7 5 10 3

Deleted Cursor of First and Second List
10 4 6 8 10 12 14 16 18 20 22 24 26 28 30
29 27 25 23 21 19 17 15 13 11 9 7 5 10

Cleared First and Second List
Length of First List: 0
Length of Second List: 0
*/ 

