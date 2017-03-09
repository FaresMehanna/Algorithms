#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "selectionsort.h"

/** 
 * Type: toCompare
 * ---------------
 * Defines the struct needed for the Selectionsort to work
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


void Selectionsort(void* array, int elemsize, int len, CompareFunction CmpFN){
	
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
		target = (char*)array + i * x.elemsize;	//the Min/Max element

		for(int j=i+1;j<len;j++){
			if(x.CmpFN(target, (char*)array + j * x.elemsize)){	//compare the target to the new elemen
				flip = 1;	//if there is new target set flip to one
				target =  (char*)array + j * x.elemsize;	//put the new target
			}
		}

		if(flip)
			swap(target,(char*)array + i * x.elemsize, x.elemsize);
	}
}