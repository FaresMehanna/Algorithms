#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "bubblesort.h"

/** 
 * Type: toCompare
 * ---------------
 * Defines the struct needed for the Bubblesort to work
 *
 * array : points to the array of elements the client provide
 * elemsize : store the client-supplied size of each element in the array of data
 * len : store the client-supplied length of the array
 * CmpFN : points to the function Which will be called to compare any two elements
 */
typedef struct {
	void  *array;
	int elemsize;
	int len;
	CompareFunction CmpFN;
}toCompare;

static void swap(void* f1 , void* f2 , int elemsize){

	//make temp with the same size of every element
	void* temp = malloc(elemsize);
	assert(temp != NULL);

	//swap the elements
	memcpy(temp,f1,elemsize);
	memcpy(f1,f2,elemsize);
	memcpy(f2,temp,elemsize);

	//free temp
	free(temp);
}


void Bubblesort(void* array, int elemsize, int len, CompareFunction CmpFN){
	
	//the struct to hold the data for the merge sort
	toCompare x;
	x.array = array;
	x.elemsize = elemsize;
	x.len = len;
	x.CmpFN = CmpFN;

	int flip;
	void* target;

	//loop through the array
	for(int i=0;i<len;i++){
		flip = 0;	//flag to check if there is new target
		for(int j=0;j<len-i-1;j++){
			if(x.CmpFN((char*)array + (j+1) * x.elemsize, (char*)array + j * x.elemsize)){	//compare the target to the new elemen
				flip = 1;	//if there is new target set flip to one
				swap((char*)array + (j+1) * x.elemsize,(char*)array + j * x.elemsize, x.elemsize);
			}
		}

		if(!flip)
			break;
	}
}