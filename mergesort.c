#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "mergesort.h"

/** 
 * Type: toCompare
 * ---------------
 * Defines the struct needed for the Mergesort to work
 *
 * array : points to the array of elements the client provide
 * elemsize : store the client-supplied size of each element in the array of data
 * len : store the client-supplied length of the array
 * CmpFN : points to the function Which will be called to compare any two elements
 * left,mid,right : define the boundries of each two arrays whicl will be sent to Merge
 */
typedef struct {
	void  *array;
	int elemsize;
	int len;
	CompareFunction CmpFN;
	int left;
	int mid;
	int right;
}toCompare;

static int min(int x1, int x2){
	if(x1 < x2)
		return x1;
	return x2;
}

static void Merge(toCompare* x){
	int fSeg = x->mid - x->left + 1;
	int SSeg = x->right - x->mid;

	void* first = NULL;
	void* second = NULL;

	if(fSeg > 0){
		first = malloc(x->elemsize * fSeg);
		assert(first != NULL);
		memcpy(first,(char *)x->array + x->left * x->elemsize, x->elemsize * fSeg);
	}

	if(SSeg > 0){
		second = malloc(x->elemsize * SSeg);
		assert(second != NULL);
		memcpy(second,(char *)x->array + (x->mid+1) * x->elemsize, x->elemsize * SSeg);
	}

    /* Merge the temp arrays back into arr[l..r]*/
    int i = 0;
    int j = 0;
    int k = x->left;

    while (i < fSeg && j < SSeg)
    {
        if (x->CmpFN((char*)first + i * x->elemsize, (char*)second + j * x->elemsize))
        {
        	memcpy((char *) x->array + k * x->elemsize,(char*)first + i * x->elemsize,x->elemsize);
            i++;
        }
        else
        {
        	memcpy((char *) x->array + k * x->elemsize,(char*)second + j * x->elemsize,x->elemsize);
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < fSeg)
    {
        memcpy((char *) x->array + k * x->elemsize,(char*)first + i * x->elemsize,x->elemsize);
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < SSeg)
    {
        memcpy((char *) x->array + k * x->elemsize,(char*)second + j * x->elemsize,x->elemsize);
        j++;
        k++;
    }

    //free them all
	free(first);
	free(second);
}

void Mergesort(void* array, int elemsize, int len, CompareFunction CmpFN){
	
	//the struct to hold the data for the merge sort
	toCompare x;
	x.array = array;
	x.elemsize = elemsize;
	x.len = len;
	x.CmpFN = CmpFN;

	//loop in bottom up
	for(int size = 1; size <= (len-1); size = size * 2){
		for(x.left = 0;x.left < (len-1); x.left += size * 2){	//the left boundary
			x.mid = min(x.left + size - 1,len-1);	//the medile boundary
			x.right = min(x.left + size * 2 - 1,len-1);	//the right boundary

			Merge(&x);
		}
	}
}