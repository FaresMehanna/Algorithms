#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "heapsort.h"

/** 
 * Type: heap
 * ---------------
 * Defines the struct needed for the heap
 *
 * array : points to the array of elements the client provide
 * elemsize : store the client-supplied size of each element in the array of data
 * CmpFN : points to the function Which will be called to compare any two elements
 */
typedef struct {
	void  *array;
	int elemsize;
	int len;
	CompareFunction CmpFN;
}heap;


static void swap(void* f1 , void* f2 , int elemsize){

	//make temp with the same size of every element
	void* temp = malloc(elemsize);

	//swap the elements
	memcpy(temp,f1,elemsize);
	memcpy(f1,f2,elemsize);
	memcpy(f2,temp,elemsize);

	//free temp
	free(temp);
}

//return the parent of a node
static void* GetParent(heap* h, int i){
	return (char *) h->array + (i/2) * h->elemsize;
}

//return a node
static void* Node(heap* h, int i){
	return (char *) h->array + i * h->elemsize;
}

static void Heapify(heap* h, int i){

	int left = 2*i + 1;
	int right = 2*i + 2;
	int largest = i;

	if(left < h->len && h->CmpFN(Node(h,left), Node(h,i)))
		largest = left;
	
	if(right < h->len && h->CmpFN(Node(h,right), Node(h,largest)))
		largest = right;

	if(largest != i){
		swap(Node(h,i),Node(h,largest),h->elemsize);
		Heapify(h,largest);
	}
}

static void InitializeHeap(heap *h, void* array, int elemsize, int len, CompareFunction CmpFN){

	//set the data
	h->array = array;
	h->elemsize = elemsize;
	h->CmpFN = CmpFN;
	h->len = len;
}

static void SortByExtracting(heap* h){

	while(h->len != 1){
		h->len--;
		swap((char *)h->array,(char *)h->array + h->elemsize * h->len,h->elemsize);
		//fix the tree
		Heapify(h,0);
	}

}

void Heapsort(void* array, int elemsize, int len, CompareFunction CmpFN){
	
	//the heap
	heap h;

	//initialize the heap
	InitializeHeap(&h,array,elemsize,len,CmpFN);
	
	//Fix the order from the bottom up
	for(int i=len/2;i!=-1;i--)
		Heapify(&h,i);

	//do sorting by extracting
	SortByExtracting(&h);
}