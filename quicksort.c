#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "quicksort.h"

/** 
 * Type: toCompare
 * ---------------
 * Defines the struct needed for the Quicksort to work
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

static int PartPoint(toCompare* x, int low, int high, void* pivot){
   int lowPointer = low;
   int highPointer = high;

   while(1){

   		while(lowPointer <= high  && x->CmpFN(pivot,(char*) x->array + lowPointer * x->elemsize))
   			lowPointer++;
   		
   		while(highPointer > -1 && ! x->CmpFN(pivot,(char*) x->array + highPointer * x->elemsize))
   			highPointer--;

		if(lowPointer >= highPointer)
			break;
		else
			swap((char*) x->array + highPointer * x->elemsize,(char*) x->array + lowPointer * x->elemsize, x->elemsize);
   }

	swap((char*) x->array + lowPointer * x->elemsize, (char*) x->array + (high+1) * x->elemsize, x->elemsize);	
	return lowPointer;
}

static void Sort(toCompare* x, int low, int high){

	if(low >= high)
		return;

	void *pivot = (char *)x->array + high * x->elemsize;
	int point = PartPoint(x,low,high-1,pivot);

	Sort(x,low,point-1);
	Sort(x,point+1,high);

}

static void SortV2(toCompare* x, int low, int high){

	if(low >= high)
		return;
	
	void* f1 = (char *)x->array;
	void* f2 = (char *)x->array + ((high-low)/2) * x->elemsize;
	void* f3 = (char *)x->array + high * x->elemsize;

	if((f1 >= f2 && f1 <= f3) || (f1 >= f3 && f1 <= f2))
		swap(f1,(char *)x->array + high * x->elemsize, x->elemsize);
	else if((f2 >= f1 && f2 <= f3) || (f2 >= f3 && f2 <= f1))
		swap(f2,(char *)x->array + high * x->elemsize, x->elemsize);
	else if((f3 >= f2 && f3 <= f1) || (f3 >= f1 && f3 <= f2))
		swap(f3,(char *)x->array + high * x->elemsize, x->elemsize);


	void *pivot = (char *)x->array + high * x->elemsize;

	int point = PartPoint(x,low,high-1,pivot);


	if(high-low < 1000){
		Sort(x,low,point-1);
		Sort(x,point+1,high);
		return;
	}

	SortV2(x,low,point-1);
	SortV2(x,point+1,high);
}


void Quicksort(void* array, int elemsize, int len, CompareFunction CmpFN){
	
	//the struct to hold the data for the merge sort
	toCompare x;
	x.array = array;
	x.elemsize = elemsize;
	x.len = len;
	x.CmpFN = CmpFN;

	SortV2(&x,0,len-1);
}