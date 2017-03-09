/** 
 * File: bubblesort.h
 * ---------------
 * Defines the interface for the bubblesort.
 *
 * Given an generic array this function will sort the given array using Bubble sort
 */

#ifndef _bubblesort_
#define _bubblesort_


/** 
 * Type: CompareFunction
 * ---------------
 * The function which will compare the array's elements
 *
 * CompareFunction is pointer to client-supplied function to compare elements, This function
 * will recieve two pointers to the element to compare and return the value 0 or 1 , 
 * by changing how it do the comparison you can sort ASC or DESC
 */
typedef int (*CompareFunction) (void*,void*);

/** 
 * Function: Bubblesort
 * ---------------
 * Sort given generic array
 *
 * accepts pointer to the array you want to sort
 * the number of byte for each element in the array
 * pointer to the compare function which will be used to compare the items in the array
 */
void Bubblesort(void* array, int elemsize, int len, CompareFunction);


#endif