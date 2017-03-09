#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "insertionsort.h"

/** 
 * Type: toCompare
 * ---------------
 * Defines the struct needed for the Insertionsort to work
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


void Insertionsort(void* array, int elemsize, int len, CompareFunction CmpFN){
	
	//the struct to hold the data for the merge sort
	toCompare x;
	x.array = array;
	x.elemsize = elemsize;
	x.len = len;
	x.CmpFN = CmpFN;

	int flip;
	void* target;

	//loop through the array
	for(int i=1;i<len;i++){
		flip = 0;	//flag to check if there is new target
		
		void* temp = malloc(x.elemsize);
		memcpy(temp,(char *)x.array + i * x.elemsize,x.elemsize);

		int j;
		for(j=i-1;j>-1;j--){

			if(x.CmpFN(temp, (char *)x.array + j * x.elemsize)){
				memcpy((char *)x.array + (j+1) * x.elemsize,(char *)x.array + j * x.elemsize, x.elemsize);
				flip = 1;
			}else
				break;
		}

		if(flip)
			memcpy((char *)x.array + (j+1) * x.elemsize,temp,x.elemsize);

		free(temp);
	}
}