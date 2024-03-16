//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa4
// CruzID - Vmaher
//------------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   void *data;
   Node next;
   Node prev;
} NodeObj;

// private QueueObj type
typedef struct ListObj{
   Node front;
   Node back;
   int length;
   Node cursor;
   int idx;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(void *x) {
   Node N = malloc(sizeof(NodeObj));
   N->data = x;
   N->next = N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ) {
      free(*pN);
      *pN = NULL;
   }
}

// Creates and returns a new empty List.
List newList(void) {
   List L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->idx = -1;
   return L;
}

// Frees all heap memory associated with *pL, and sets
 // *pL to NULL.
void freeList(List* pL) {
   if (pL != NULL && *pL != NULL) {
      clear(*pL);
      free(*pL);
      *pL = NULL;
   }
   return;
}

// Access functions -----------------------------------------------------------
 // Returns the number of elements in L.
int length(List L) {
   if (L == NULL) {
      printf("List error: calling length() on empty list\n");
      exit(EXIT_FAILURE);
   }
   return L->length;
}
 // Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
   if (L == NULL) {
      printf("List error: calling index() on empty list\n");
      exit(EXIT_FAILURE);
   }
   return L->idx;
}

// Returns front element of L. Pre: length()>0
void* front(List L) {
   if (L == NULL) {
      printf("List error: calling front() on empty list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      printf("List Error: calling front() on list with length() < 0\n");
      exit(EXIT_FAILURE);
   
   }
   return L->front->data;
}

 // Returns back element of L. Pre: length()>0
void* back(List L) {
   if (L == NULL) {
      printf("List error: calling back() on empty list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      printf("List Error: calling back() on list with length() < 0\n");
      exit(EXIT_FAILURE);
   }
   return L->back->data;
}

 // Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L) {
   if (L == NULL) {
      printf("List error: calling get() on empty list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      printf("List Error: calling get() on list with length() <= 0\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      printf("List Error: calling get() on list with index() < 0\n");
      exit(EXIT_FAILURE);
   }
   
   return L->cursor->data;
}

// Manipulation procedures ----------------------------------------------------
 // Resets L to its original empty state.
void clear(List L) {
   if (L == NULL) {
      printf("List error: calling clear() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   Node N = NULL;
   while (L->front != NULL) {
      N = L->front;
      L->front = L->front->next;
      freeNode(&N);
   }
   L->idx = -1;
   L->length = 0;
}

 // Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0
void set(List L, void *x) {
   if (L == NULL) {
      printf("List error: calling set() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      printf("List error: calling length() on empty list\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      printf("List error: calling length() with idx < 0\n");
      exit(EXIT_FAILURE);
   }
   L->cursor->data = x;
}

 // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveFront(List L) {
   if (L == NULL) {
      printf("List error: calling mvoeFront() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) > 0) {
      L->cursor = L->front;
      L->idx = 0;
   }
}

 // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void moveBack(List L) {
   if (L == NULL) {
      printf("List error: calling mvoeBack() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) > 0) {
      L->cursor = L->back;
      L->idx = length(L) - 1;
   }
}

 // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void movePrev(List L) {
   if (L == NULL) {
      printf("List error: calling movePrev() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor != NULL) {
      L->cursor = L->cursor->prev;
      L->idx -= 1;
   }
}

// If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L) {
   if (L == NULL) {
      printf("List error: calling moveNext() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor != NULL) {
      L->cursor = L->cursor->next;
      L->idx += 1;
      if (L->idx == length(L)) {
         L->cursor = NULL;
         L->idx = -1;
      }  
   }
}

// Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void prepend(List L, void *x) {
   if (L == NULL) {
      printf("List error: calling prepend() on NULL list\n");
      exit(EXIT_FAILURE);
   }

   Node N = newNode(x);
   if (length(L) == 0) {
      L->front = L->back = N;
      L->length += 1;
   } else {
      if (L->idx >= 0) {
         L->idx += 1;
      }
      N->next = L->front;
      L->front->prev = N;
      L->front = N;
      L->length += 1;      
   }
}

// Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void append(List L, void *x) {
   if (L == NULL) {
      printf("List error: calling append() on NULL list\n");
      exit(EXIT_FAILURE);
   }

   Node N = newNode(x);
   if (length(L) == 0) {
      L->back = L->front = N;
      L->length += 1;
   } else {
      N->prev = L->back;
      L->back->next = N;
      L->back = N;
      L->length += 1;
   }
}

// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, void *x) {
   if (L == NULL) {
      printf("List error: calling insertBefore() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      printf("List error: calling insertBefore() on empty list\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      printf("List error: calling insertBefore() with idx < 0\n");
      exit(EXIT_FAILURE);
   }

   Node N = newNode(x);
   if (L->cursor == L->front) {
      L->front = N;
   }
   if (L->cursor->prev != NULL) {
      L->cursor->prev->next = N;
      N->prev = L->cursor->prev;
   }
   L->cursor->prev = N;
   N->next = L->cursor;
   L->length += 1;
   L->idx += 1;
}

// Insert new element after cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, void *x) {
   if (L == NULL) {
      printf("List error: calling insertAfter() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) < 0) {
      printf("List error: calling insertBefore() on empty list\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      printf("List error: calling insertBefore() with idx < 0\n");
      exit(EXIT_FAILURE);
   }

   Node N = newNode(x);
   if (L->cursor == L->back) {
      L->back = N;
   }
   if (L->cursor->next != NULL) {
      L->cursor->next->prev = N;
      N->next = L->cursor->next;
   }
   L->cursor->next = N;
   N->prev = L->cursor;
   L->length += 1;
   
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
   if (L == NULL) {
      printf("List error: calling deleteFront() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      printf("List error: calling deleteFront() on empty list\n");
      exit(EXIT_FAILURE);
   }
   
   Node N = L->front;
   if (L->cursor == L->front) {
      L->cursor = NULL;
      L->idx = -1;
   }   
   if (length(L) > 1) {
      L->front = L->front->next;
      L->front->prev = NULL;
   } else {
      L->front = L->back = NULL;
   }
   if (L->idx >= 0) {
      L->idx -= 1;
   }
   L->length -= 1;
   
   freeNode(&N);
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
   if (L == NULL) {
      printf("List error: calling deleteBack() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      printf("List error: calling insertBefore() on empty list\n");
      exit(EXIT_FAILURE);
   }
   
   Node N = L->back;
   if (L->cursor == L->back) {
      L->cursor = NULL;
      L->idx = -1;
   }
   if (length(L) > 1) {
      L->back = L->back->prev;
      L->back->next = NULL;
   } else {
      L->back = L->front = NULL;
   }
   L->length -= 1;
   freeNode(&N);
}

// Delete cursor element, making cursor undefined.
void delete(List L) {
   if (L == NULL) {
      printf("List error: calling delete() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) < 0) {
      printf("List error: calling insertBefore() on empty list\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      printf("List error: calling insertBefore() with idx < 0\n");
      exit(EXIT_FAILURE);
   }

   Node N = L->cursor;
   if (length(L) == 1) {
      L->front = L->back = NULL;
   } else if (L->cursor == L->front) {
      L->front = L->front->next;
      L->front->prev = NULL;
   } else if (L->cursor == L->back) {
      L->back = L->back->prev;
      L->back->next = NULL;
   } else {
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
   }
   L->cursor = NULL;
   L->idx = -1;
   L->length -= 1;
   freeNode(&N);
}

// Pre: length()>0, index()>=0
// Other operations -----------------------------------------------------------

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L) {
   if (L == NULL) {
      printf("List error: calling printList() on NULL list\n");
      exit(EXIT_FAILURE);
   }
   if (out == NULL) {
      printf("List error: calling printList on NULL outfile");
      exit(EXIT_FAILURE);
   }

   Node N = L->front;
   while (N != NULL) {
      fprintf(out, "%d ", *(int*)(N->data));
      N = N->next;
   }
   fprintf(out, "\n");
}

// Returns a new List which is the concatenation of
 // A and B. The cursor in the new List is undefined,
 // regardless of the states of the cursors in A and B.
 // The states of A and B are unchanged.
List concatList(List A, List B) {
   List C = newList();
   Node N = A->front;
   Node M = B->front;
   while (N != NULL) {
      append(C, N->data);
      N = N->next;
   }
   while (M != NULL) {
      append(C, M->data);
      M = M->next;
   }
   C->cursor = NULL;
   C->idx = -1;
   return C;
}



