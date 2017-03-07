/** 
 * File: heaps1.h
 * ---------------
 * Defines the interface for the heaps.
 *
 * This version of the heap allows the user to add generic item related
 * with float weight, it's implement both Max and Min heaps and allow
 * the user to build the heap from array and insert more element to it 
 * or just use insertion, the heap has no upper bound for it's size 
 * The client specifies the size (in bytes) of the elements that will be
 * stored in the heap when it is created.  Thereafter the client and 
 * the heap can refer to elements via (void *) ptrs. and the client must
 * iclude the Free function if the client malloc-ed the elements before the
 * insertion.
 */

#ifndef _heapsort_
#define _heapsort_


/** 
 * Type: CompareFunction
 * ---------------
 * Defines the interface for the heaps.
 *
 * CompareFunction is pointer to lient-supplied function to compare elements, This function
 * will recieve two pointers to the element the heap wants to compare and return the value
 * 0 or 1 , by changing how it do the comparison you can sort ASC or DESC
 */
typedef int (*CompareFunction) (void*,void*);

/** 
 * Function: Heapsort
 * ---------------
 * Sort given generic array
 *
 * accepts pointer to the array you want to sort
 * the number of byte for each element in the array
 * pointer to the compare function which will be used to compare the items in the array
 */
void Heapsort(void* array, int elemsize, int len, CompareFunction);


#endif