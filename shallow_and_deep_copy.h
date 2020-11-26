#ifndef _SHALLOW_AND_DEEP_COPY_H
#define _SHALLOW_AND_DEEP_COPY_H

//holds an uninitialized 2d array, the row size, and the column size
struct Double_Array{
	double **array;
	int rowsize;
	int colsize;
};

/* function prototypes */

struct Double_Array * deepCopy(struct Double_Array *myArray);

void printStruct(struct Double_Array *myArray, char *str);

struct Double_Array *randomizeArray(struct Double_Array *myArray, double a, double b);

struct Double_Array * shallowCopy (struct Double_Array *myArray);

void freeArray(struct Double_Array *myArray);

struct Double_Array *doubleArray(int row, int col);

void printArray(struct Double_Array *myArray);

#endif