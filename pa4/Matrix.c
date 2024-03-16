//------------------------------------------------------------------------------
// Victor Maher - CSE 101 pa4
// CruzID - Vmaher
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"

//private inner struct for entries that contains colum number and value
typedef struct EntryObj* Entry;

typedef struct EntryObj {
    int col;        //colum number
    double val;     //values in an entry
} EntryObj;
    
typedef struct MatrixObj {
    List *entries;  //list of entries in a given row
    int nonz;       //number of nonzero entries
    int size;       //size of matrix
} MatrixObj;

//constructor for entry struct
Entry newEntry(int c, double v) {
    Entry E = malloc(sizeof(EntryObj));
    E->col = c;
    E->val = v;
    return E;
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->entries = calloc(n+1, sizeof(List));
    for (int i = 1; i <= n; i += 1) {
        M->entries[i] = newList();
    }
    M->nonz = 0;
    M->size = n;
    return M;
}

//destructor for entry struct
void freeEntry(Entry* pE) {
    if (pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        makeZero(*pM);
        for (int i = 1; i <= (*pM)->size; i += 1) {
            freeList(&((*pM)->entries[i]));
        }
        free((*pM)->entries);
        free(*pM);
        *pM = NULL;
    }
}


// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
    if (M == NULL) {
        printf("Matrix error: calling size() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    return M->size;
}


// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
    if (M == NULL) {
        printf("Matrix error: calling NNZ() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    return M->nonz;
}


// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
      printf("Matrix error: calling equals() on NULL Matrix\n");
      exit(EXIT_FAILURE);
   }
   if (size(A) != size(B)) {
      return 0;
   }
   for (int i = 1; i <= size(A); i += 1) {
       moveFront(A->entries[i]);
       moveFront(B->entries[i]);
       if (length(A->entries[i]) != length(B->entries[i])) {
           return 0;
       }
       while (index(A->entries[i]) >= 0) {
           Entry a = (Entry)get(A->entries[i]);
           Entry b = (Entry)get(B->entries[i]);
           if (a->val != b->val || a->col != b->col) {
               return 0;
           }
           moveNext(A->entries[i]);
           moveNext(B->entries[i]);          
       }
   }
   return 1;

}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    if (M == NULL) {
        printf("Matrix error: calling makeZero() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= size(M); i += 1) {
        moveFront(M->entries[i]);
        while (index(M->entries[i]) >= 0) {
            Entry entry = (Entry)get(M->entries[i]);
            freeEntry(&entry);
            moveNext(M->entries[i]);
            deleteFront(M->entries[i]);
        }
    }
    M->nonz = 0;
}


// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        printf("Matrix error: calling changeEntry() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    if (i < 1 || i > size(M) || j < 1 || j > size(M)) {
        printf("Matrix error: calling changeEntry() with i or j out of range\n");
        exit(EXIT_FAILURE);
    }
    List r = M->entries[i];
    moveFront(r);
    while (index(r) >= 0) {
        Entry entry = (Entry)get(r);
        if (j == entry->col) {
            if (x == 0) {
                freeEntry(&entry);
                delete(r);
                M->nonz -= 1;
            } else {
                entry->val = x;
            }
            return;
        } else if (j < entry->col) {
            if (x != 0) {
                Entry n = newEntry(j, x);
                insertBefore(r, n);
                M->nonz += 1;
            }
            return;
        }
        moveNext(r);
    }
    if (x != 0) {
        Entry n = newEntry(j, x);
        append(r, n);
        M->nonz += 1;
    }
}


// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    if (A == NULL) {
        printf("Matrix error: calling copy() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    Matrix C = newMatrix(size(A));
    for (int i = 1; i <= size(A); i += 1) {
        moveFront(A->entries[i]);
        while (index(A->entries[i]) >= 0) {
            Entry entry = (Entry)get(A->entries[i]);
            changeEntry(C, i, entry->col, entry->val);
            moveNext(A->entries[i]);
        }
    }
    return C;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
    if (A == NULL) {
        printf("Matrix error: calling transpose() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    Matrix T = newMatrix(size(A));
    for (int i = 1; i <= size(A); i += 1) {
        moveFront(A->entries[i]);
        while (index(A->entries[i]) >= 0) {
            Entry entry = (Entry)get(A->entries[i]);
            changeEntry(T, entry->col, i, entry->val);
            moveNext(A->entries[i]);
        }
    }
    return T;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) {
        printf("Matrix error: calling scalarMult() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    Matrix SM = copy(A);
    for (int i = 1; i <= size(A); i += 1) {
        moveFront(SM->entries[i]);
        while (index(SM->entries[i]) >= 0) {
            Entry entry = (Entry)get(SM->entries[i]);
            entry->val *= x;
            moveNext(SM->entries[i]);
        }
    }
    return SM;
}

//dot()
//helder function
double vectorDot(List P, List Q) {
    //sum of dot product
    double s = 0;
    moveFront(P);
    moveFront(Q);
    while (index(P) >= 0 && index(Q) >= 0) {
        Entry pe = (Entry)get(P);
        Entry qe = (Entry)get(Q);
        if (pe->col == qe->col) {
            s += (pe->val * qe->val);
            moveNext(P);
            moveNext(Q);
        } else if (pe->col < qe->col) {
            moveNext(P);
        } else {
            moveNext(Q);
        }
    }
    return s;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        printf("Matrix error: calling sum() on NULL matrices\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        printf("Matrix error: calling sum() on different sized Matrices\n");
        exit(EXIT_FAILURE);
    }
    Matrix S = copy(A);
    for (int i = 1; i <= size(A); i += 1) {
        moveFront(S->entries[i]);
        moveFront(B->entries[i]);
        while (index(S->entries[i]) >= 0 || index(B->entries[i]) >= 0) {
            if (index(S->entries[i]) >= 0 && index(B->entries[i]) >= 0) {
                Entry sy = (Entry)get(S->entries[i]);
                Entry by = (Entry)get(B->entries[i]);
                if (sy->col == by->col) {
                    changeEntry(S, i, sy->col, sy->val + by->val);
                    moveNext(S->entries[i]);
                    moveNext(B->entries[i]);
                } else if (sy->col < by->col) {
                    moveNext(S->entries[i]);
                } else {
                    changeEntry(S, i, by->col, by->val);
                    moveNext(B->entries[i]);
                }
            }
            else if (index(B->entries[i]) >= 0) {
                Entry by = (Entry)get(B->entries[i]);
                changeEntry(S, i, by->col, by->val);
                moveNext(B->entries[i]);
            }
            else {
                break;
            }
        }
    }
    return S;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        printf("Matrix error: calling diff() on NULL matrices\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        printf("Matrix error: calling diff() on different sized Matrices\n");
        exit(EXIT_FAILURE);
    }
    Matrix D = copy(A);
    if (equals(D, B) == 1) {
        makeZero(D);
        return D;
    }
    for (int i = 1; i <= size(A); i += 1) {
        moveFront(D->entries[i]);
        moveFront(B->entries[i]);
        while (index(D->entries[i]) >= 0 || index(B->entries[i]) >= 0) {
            if (index(D->entries[i]) >= 0 && index(B->entries[i]) >= 0) {
                Entry dy = (Entry)get(D->entries[i]);
                Entry by = (Entry)get(B->entries[i]);
                if (dy->col == by->col) {
                    changeEntry(D, i, by->col, dy->val - by->val);
                    moveNext(D->entries[i]);
                    moveNext(B->entries[i]);
                } else if (dy->col < by->col) {
                    moveNext(D->entries[i]);
                } else {
                    changeEntry(D, i, by->col, -by->val);
                    moveNext(B->entries[i]);
                }
            } 
            else if (index(B->entries[i]) >= 0) {
                Entry by = (Entry)get(B->entries[i]);
                changeEntry(D, i, by->col, -by->val);
                moveNext(B->entries[i]);
            }
            else {
                break;
            }
        }
    }
    return D;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        printf("Matrix error: calling product() on NULL matrices\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        printf("Matrix error: calling product() on different sized Matrices\n");
        exit(EXIT_FAILURE);
    }
    Matrix P = newMatrix(size(A));
    Matrix T = transpose(B);
    for (int i = 1; i <= size(A); i += 1) {
        if (length(A->entries[i]) > 0) {
            for (int j = 1; j <= size(A); j += 1) {
                double num = vectorDot(A->entries[i], T->entries[j]);
                if (num != 0) {
                    changeEntry(P, i, j, num);
                }
            }
        }
    }
    freeMatrix(&T);
    return P;

}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    if (M == NULL) {
        printf("Matrix error: calling printMatrix() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= size(M); i += 1) {
        if (length(M->entries[i]) > 0) {
            fprintf(out, "%d: ", i);
            moveFront(M->entries[i]);
            while (index(M->entries[i]) >= 0) {
                Entry entry = (Entry)get(M->entries[i]);
                fprintf(out, "(%d, %.1f) ", entry->col, entry->val);
                moveNext(M->entries[i]);
            }
            fprintf(out, "\n");
        }
    }
}


