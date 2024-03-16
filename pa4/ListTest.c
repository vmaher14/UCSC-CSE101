//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa4
// CruzID - Vmaher
//------------------------------------------------------------------------------
/*Test Client for List ADT*/

#include "List.h"
#include <stdio.h>


int main (int argc, char *argv[]) {

    List First = newList();
    List Second = newList();
    int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

    for (int i = 1; i <= 20; i += 1) {    
        append(First, &X[i]);
        prepend(Second, &X[i]); 
    }
    printList(stdout, First);
    printf("\n");
    printList(stdout, Second);
    printf("\n");
    printf("\n");
   
    printf("First List Index: %d\n", index(First));
    printf("First List Front: %d\n", *(int*)front(First));
    printf("First List Back: %d\n", *(int*)back(First));
    printf("First List Length: %d\n", length(First));
    printf("\n");
    printf("Second List Index: %d\n", index(Second));
    printf("Second List Front: %d\n", *(int*)front(Second));
    printf("Second List Back: %d\n", *(int*)back(Second));
    printf("Second List Length: %d\n", length(Second));
    printf("\n");

    moveFront(First);
    moveBack(Second);
    printf("Set cursor of First list to first element and cursor of second list to last element\n");
    printf("Cursor of First list: %d\n", *(int*)get(First));
    printf("Cursor of Second list: %d\n", *(int*)get(Second));
    int num1 = 14;
    int num2 = 7;
    set(First, &num1);
    set(Second, &num2);
    printf("Set cursor of First List to 14 and cursor of Second List to 7\n");
    printf("Cursor of First list: %d\n", *(int*)get(First));
    printf("Cursor of Second list: %d\n", *(int*)get(Second));
    moveNext(First);
    movePrev(Second);
    printf("Moved First List cursor to next idx and Second List cursor to prev idx\n");
    printf("Cursor of First list: %d\n", *(int*)get(First));
    printf("Cursor of Second list: %d\n", *(int*)get(Second));
    printf("\n");

    printf("Inserted 10 after First List cursor and 10 before Second List cursor\n");
    int num3 = 10;
    insertAfter(First, &num3);
    insertBefore(Second, &num3);
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
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 

20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1


First List Index: -1
First List Front: 1
First List Back: 20
First List Length: 20

Second List Index: -1
Second List Front: 20
Second List Back: 1
Second List Length: 20

Set cursor of First list to first element and cursor of second list to last element
Cursor of First list: 1
Cursor of Second list: 1
Set cursor of First List to 14 and cursor of Second List to 7
Cursor of First list: 14
Cursor of Second list: 7
Moved First List cursor to next idx and Second List cursor to prev idx
Cursor of First list: 2
Cursor of Second list: 2

Inserted 10 after First List cursor and 10 before Second List cursor
14 2 10 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 10 2 7


Deleted First element of First List and Last element of Second List
2 10 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 10 2


Deleted Cursor of First and Second List
10 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 10


Cleared First and Second List
Length of First List: 0
Length of Second List: 0
*/ 

