#include <stdio.h>
#include <stdlib.h>
#include "shallow_and_deep_copy.h"

int main(int argc, char *argv[]){

	//initialize and print variable a1 and its properties
	struct Double_Array *a1 = doubleArray(6,9);
	randomizeArray(a1, 0.0, 10.0);
 	printf("The address of a1 is %p\n", (void *)&a1);
	printf("The structure pointed to by a1 is:\n");
	char *str = "Double_Array";
	printStruct(a1, str);

	//initialize and print variable a2 and its properties
	struct Double_Array *a2 = a1;
	printf("The address of a2 is %p\n", (void *)&a2);
	printf("The structure pointed to by a2 is:\n");
	printStruct(a2, str);

	//shallow copy of a1, address print, and structure print
	struct Double_Array *a_shallow = shallowCopy(a1);
	printf("The address of a_shallow is %p\n", (void *)&a_shallow);
	printf("The structure pointed to by a_shallow is:\n");
	printStruct(a_shallow, str);

	//deep copy of a1, address print, and structure print
	struct Double_Array *a_deep = deepCopy(a1);
	printf("The address of a_deep is %p\n", (void *)&a_deep);
	printf("The structure pointed to by a_deep is:\n");
	printStruct(a_deep, str);
	printf("\n\n\n");

	//setting elements in arrays to values given in the assignment
	a1 -> array[0][1] = 100.0;
	a2 -> array[1][2] = 200.0;
	a_shallow -> array[2][3] = 300.0;
	a_deep -> array[3][4] = 400.0;
	printf("Array a1:\n");
	printArray(a1);
	printf("\n\n");
	printf("Array a2:\n");
	printArray(a2);
	printf("\n\n");
	printf("Array a_shallow:\n");
	printArray(a_shallow);
	printf("\n\n");
	printf("Array a_deep:\n");
	printArray(a_deep);
	printf("\n\n\n");

	struct Double_Array *b1 = doubleArray(6,9);
		randomizeArray(b1, 10.0, 20.0);

	for(int i = 0; i < a2 -> rowsize; i++){
		for(int j = 0; j < a2 -> colsize; j++){
			a2 -> array[i][j] = b1 -> array[i][j];
		}
	}

	//prints out a1, a2, a_shallow, a_deep, b1
	printf("Printing the first set of arrays:\n\n");
	printf("Array a1:\n");
	printArray(a1);
	printf("\n\n");
	printf("Array a2:\n");
	printArray(a2);
	printf("\n\n");
	printf("Array a_shallow:\n");
	printArray(a_shallow);
	printf("\n\n");
	printf("Array a_deep:\n");
	printArray(a_deep);
	printf("\n\n");
	printf("Array b1:\n");
	printArray(b1);
	printf("\n\n\n");

	//initializes values in the arrays
	a1 -> array[0][1] = 5000.0;
	a2 -> array[1][2] = 6000.0;
	a_shallow -> array[2][3] = 700.0;
	a_deep -> array[3][4] = 8000.0;
	b1 -> array[4][5] = 9000.0;

	//prints each array again
	printf("Printing the second set of arrays with values changed\n\n");
	printf("Array a1:\n");
	printArray(a1);
	printf("\n\n");
	printf("Array a2:\n");
	printArray(a2);
	printf("\n\n");
	printf("Array a_shallow:\n");
	printArray(a_shallow);
	printf("\n\n");
	printf("Array a_deep:\n");
	printArray(a_deep);
	printf("\n\n");
	printf("Array b1:\n");
	printArray(b1);
	printf("\n\n\n");

	//frees all of the malloc'd pointers
	freeArray(a_deep);
	freeArray(a1);
	freeArray(b1);

	return 0;
}

//returns copy od Double_Array struct and holds the same content but any chnages to interior of one struct will not be reflected in the other
struct Double_Array * deepCopy(struct Double_Array *myArray){

	//allocate new memory so that changes are reflected only in one struct
	struct Double_Array *deepCopy = malloc(sizeof(struct Double_Array));

	//copy the contents of the original struct into the newly allocated struct
	deepCopy -> rowsize = myArray -> rowsize;
	deepCopy -> colsize = myArray -> colsize;

        deepCopy -> array = malloc (deepCopy -> rowsize * sizeof(double*));
        for (int i = 0; i < deepCopy -> rowsize; i++){
                deepCopy -> array[i] = malloc (deepCopy -> colsize* sizeof(double));
        }

	for (int j = 0; j < deepCopy -> rowsize; j++){
		for (int k= 0; k < deepCopy -> colsize; k++){
			deepCopy -> array[j][k] = myArray -> array[j][k];
		}
	}

	return deepCopy;
}

void printStruct(struct Double_Array *myArray, char *str){

	//prints the criteria given in question #3
	printf("%s\n", str);
	printf("struct address = %p\n", (void *)&myArray);
	printf("row_size = %d, col_size = %d\n", myArray -> rowsize, myArray -> colsize);
	printf("array address = %p, with contents:\n\n", (void *)&myArray -> array);
	printArray(myArray);
	printf("\n\n");
	return;
}

//takes in the Double_Array struct and an upper and lower bound numbers to initialize the elements inside the struct array
struct Double_Array *randomizeArray(struct Double_Array *myArray, double a, double b){

	//initializes elements in the array to random values between the lower and upper bounds
	for (int i = 0; i < myArray -> rowsize; i++){
		for (int j = 0; j < myArray -> colsize; j++){
			myArray -> array[i][j] = ((double) rand() / (double) RAND_MAX) * (b - a) +a;
		}
	}
	return myArray;
}

struct Double_Array * shallowCopy (struct Double_Array *myArray){

	//returns a copy of Double_Array struct but holds the same content, chnages to either the new or old struct is reflected automatically
	struct Double_Array *shallowCopy = myArray;
	shallowCopy -> rowsize = myArray -> rowsize;
	shallowCopy -> colsize = myArray -> colsize;

	return shallowCopy;
}

//takes in Double_Array struct pointer and frees struct as well as the array in it
void freeArray(struct Double_Array *myArray){

	//frees each element in the struct array
	for (int i = 0; i < myArray -> rowsize; i++){
		free(myArray -> array[i]);
	}

	//frees the array then the struct pointer
	free(myArray -> array);
	free(myArray);
}

//returns a pointer to a struct given the input for num rows and num columns
struct Double_Array *doubleArray(int row, int col){

	//allocates memory for the struct pointer
	struct Double_Array *myArray = malloc(sizeof(struct Double_Array));

	//sets row and col size of the struct
	myArray -> rowsize = row;
	myArray -> colsize = col;

	//allocates memory for the 2D array row elements
 	myArray -> array = malloc (row * sizeof(double*));

	//allocates memory for the 2D array column elements
	for (int i = 0; i < row; i++){
		myArray -> array[i] = malloc (col* sizeof(double));
	}
 
	return myArray;
}

//takes Double_Array struct pointer and prints the array with each element to 1 decimal place
void printArray(struct Double_Array *myArray){

    for (int i = 0; i < myArray -> rowsize; i++){
        for (int j = 0; j < myArray -> colsize; j++){
            printf("%0.1f ", myArray -> array[i][j]);
        }
        printf("\n");
    }
	return;
}