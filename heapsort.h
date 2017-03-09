/** 
 * File: heapsort.h
 * ---------------
 * Defines the interface for the heapsort.
 *
 * Given an array this function will sort the given array in place
 * using heaps
 */

#ifndef _heapsort_
#define _heapsort_


/** 
 * Type: CompareFunction
 * ---------------
 * The function which will compare the array's elements
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