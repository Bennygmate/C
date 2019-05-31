//
//  COMP1927 Assignment 1 - Vlad: the memory allocator
//  allocator.c ... implementation
//
//  Created by Liam O'Connor on 18/07/12.
//  Modified by John Shepherd in August 2014, August 2015
//  Copyright (c) 2012-2015 UNSW. All rights reserved.
//

#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define FREE_HEADER_SIZE  sizeof(struct free_list_header)  
#define ALLOC_HEADER_SIZE sizeof(struct alloc_block_header)  
#define MAGIC_FREE     0xDEADBEEF
#define MAGIC_ALLOC    0xBEEFDEAD

#define BEST_FIT       1
#define WORST_FIT      2
#define RANDOM_FIT     3

#define TRUE 1

typedef unsigned char byte;
typedef u_int32_t vsize_t;
typedef u_int32_t vlink_t;
typedef u_int32_t vaddr_t;

typedef struct free_list_header {
   u_int32_t magic;  // ought to contain MAGIC_FREE
   vsize_t size;     // # bytes in this block (including header)
   vlink_t next;     // memory[] index of next free block
   vlink_t prev;     // memory[] index of previous free block
} free_header_t;

typedef struct alloc_block_header {
   u_int32_t magic;  // ought to contain MAGIC_ALLOC
   vsize_t size;     // # bytes in this block (including header)
} alloc_header_t;

// Global data

static byte *memory = NULL;   // pointer to start of allocator memory
static vaddr_t free_list_ptr; // index in memory[] of first block in free list
static vsize_t memory_size;   // number of bytes malloc'd in memory[]
static u_int32_t strategy;    // allocation strategy (by default BEST_FIT)

static void vlad_merge();


// Private functions

//static void vlad_merge();


// Input: size - number of bytes to make available to the allocator
// Output: none              
// Precondition: Size >= 1024
// Postcondition: `size` bytes are now available to the allocator
// 
// (If the allocator is already initialised, this function does nothing,
//  even if it was initialised with different size)

void vlad_init(u_int32_t size)
{
    // Milestone 1
    // Make bytes power of two and allocate to memory 
    vsize_t memoryPowTwo = 1;
    while (memoryPowTwo < size) {
        memoryPowTwo = memoryPowTwo * 2;
    }
    vsize_t minimum = 1024;
    if (memoryPowTwo < minimum) {
        memoryPowTwo = minimum;
    }
    memory = (byte*) malloc(memoryPowTwo);

    // If malloc fails 
    if (memory == NULL) { // Malloc failed
        fprintf(stderr, "vlad_init: Insufficient memory\n");
        exit (EXIT_FAILURE);
    }
    //Index block to 0, memory_size should be number of bytes allocated CHECK
    free_list_ptr = (vaddr_t)0; 
    memory_size = memoryPowTwo; 
    strategy = BEST_FIT;
    //Set list headers
    free_header_t *first_list = (free_header_t *) ((void*)memory + free_list_ptr);
    first_list->magic = MAGIC_FREE;
    first_list->size = memoryPowTwo; // + sizeof (free_header_t);
    printf ("%d\n", first_list->size);
    first_list->next = free_list_ptr;
    first_list->prev = free_list_ptr;
    //Set block headers 
    //alloc_header_t *first_block = (alloc_header_t *) memory;
    //first_block->magic = MAGIC_ALLOC;
    //first_block->size = sizeof(alloc_header_t);
}


// Input: n - number of bytes requested
// Output: p - a pointer, or NULL
// Precondition: n < size of largest available free block
// Postcondition: If a region of size n or greater cannot be found, p = NULL 
//                Else, p points to a location immediately after a header block
//                      for a newly-allocated region of some size >= 
//                      n + header size.

void *vlad_malloc(u_int32_t n)
{
    // TODO for Milestone 2
    // Make sure client request at least 8 and is multiple of 4 or next highest
    if (n < 8) {
        n = 8;
    }
    if ((n % 4) != 0) {
        n = n + (4 - (n % 4));
    }  
	printf (" Client request %d---", n);

    // All pointers & size counters
    free_header_t *chosen_list = NULL;
    free_header_t *curr_list = (free_header_t *)((void*)memory+free_list_ptr);
    free_header_t *next_list = (free_header_t *)((void*)memory+curr_list->next);
    vsize_t finish = 0;
    vsize_t smallest_size = 0;

    // Smallest Size --> chosen_list
    while (finish <= memory_size){
	if (curr_list->magic != MAGIC_FREE || next_list->magic != MAGIC_FREE) {
		fprintf (stderr, "vlad_alloc: Memory corruption\n");
		exit (EXIT_FAILURE);
	}
        if (curr_list->size >= (ALLOC_HEADER_SIZE + n)){
            if (chosen_list == NULL) {
                chosen_list = curr_list;
                smallest_size = chosen_list->size;
            }
            if (next_list->size < curr_list->size && next_list->size >= (ALLOC_HEADER_SIZE + n)){ 
                chosen_list = next_list;
                smallest_size = chosen_list->size;
            } else if (chosen_list->size > curr_list->size){
                chosen_list = curr_list;
                smallest_size = chosen_list->size;
            }
        }
        if (next_list == (free_header_t *)((void*)memory + free_list_ptr) && chosen_list == NULL) {
            fprintf(stderr, "free_header_t: Insufficient memory to allocate\n");
            return NULL;
        }
        finish = finish + curr_list->size;
        curr_list = (free_header_t *)((void*)memory + curr_list->next);
        next_list = (free_header_t *)((void*)memory + next_list->next);
    }

    //Splitting block
    vsize_t threshold = ALLOC_HEADER_SIZE + n + 2*FREE_HEADER_SIZE;
    if (smallest_size < threshold) {
	    if (chosen_list == next_list) { //CHECK
        printf("here");
	        alloc_header_t *new_block = (alloc_header_t *) ((void*)memory + curr_list->prev);
            new_block->magic = MAGIC_ALLOC;
            new_block->size = ALLOC_HEADER_SIZE + smallest_size;
            free_header_t *new_list = (free_header_t *) ((void*)memory + curr_list->prev + new_block->size);
            new_list->magic = MAGIC_FREE;
            new_list->size = memory_size - ((void*)new_list - (void*)memory);
            new_list->next = ((void*)new_list - (void*)memory);
            new_list->prev = ((void*)new_list - (void*)memory);
	        free_list_ptr = ((void*)new_list - (void*)memory);
            printf ("%d",new_list->size);
	        if (new_list->size * -1 < 8) {
                fprintf(stderr, "vlad_malloc: Insufficient memory to allocate\n");
                return NULL;
            }
	    } else {
            alloc_header_t *new_block = (alloc_header_t *) ((void*)memory + curr_list->prev);
            new_block->magic = MAGIC_ALLOC;
            new_block->size = ALLOC_HEADER_SIZE + smallest_size;
            free_header_t *prev_list = (free_header_t *) ((void*)memory + chosen_list->prev);
            prev_list->next = ((void*)curr_list - (void*)memory);  
            curr_list->prev =((void*)prev_list - (void*)memory); 
	    free_list_ptr = ((void*)curr_list - (void*)memory);
	    }
    } else if (smallest_size >= threshold) {
	    if (chosen_list == next_list) { // GOOD
            printf ("HERE");
	        alloc_header_t *new_block = (alloc_header_t *) ((void*)memory + curr_list->prev);
            new_block->magic = MAGIC_ALLOC;
            new_block->size = ALLOC_HEADER_SIZE + n; 
            free_header_t *new_list = (free_header_t *) ((void*)memory + curr_list->prev + new_block->size);
            new_list->magic = MAGIC_FREE;
            new_list->size = memory_size - ((void*)new_list - (void*)memory);
            new_list->next = ((void*)new_list - (void*)memory);
            new_list->prev = ((void*)new_list - (void*)memory);
	        free_list_ptr = ((void*)new_list - (void*)memory);
	    } else {
            alloc_header_t *new_block = (alloc_header_t *) ((void*)memory + curr_list->prev);
            new_block->magic = MAGIC_ALLOC;
            new_block->size = ALLOC_HEADER_SIZE + n;
            free_header_t *new_list = (free_header_t *) ((void*)memory + curr_list->prev + new_block->size);
            free_header_t *prev_list = (free_header_t *) ((void*)memory + chosen_list->prev);
            new_list->magic = MAGIC_FREE;
            new_list->size = chosen_list->size - new_block->size;
            new_list->next = ((void*)curr_list - (void*)memory);
            new_list->prev = ((void*)prev_list - (void*)memory);
            prev_list->next = ((void*)new_list - (void*)memory);
            curr_list->prev = ((void*)new_list - (void*)memory);
	        free_list_ptr = ((void*)new_list - (void*)memory);
	    }
   }

   //Adjust free list ptr 
    free_header_t *chosen_ptr = (free_header_t *) ((void*)memory + free_list_ptr);

   return((void *)chosen_ptr + ALLOC_HEADER_SIZE);
}


// Input: object, a pointer.
// Output: none
// Precondition: object points to a location immediately after a header block
//               within the allocator's memory.
// Postcondition: The region pointed to by object has been placed in the free
//                list, and merged with any adjacent free blocks; the memory
//                space can be re-allocated by vlad_malloc

void vlad_free(void *object)
{
   // TODO for Milestone 3
/*
    if (object > 
    free_header_t *object_block = (free_header_t *) ((void*)object - FREE_HEADER_SIZE);
    free_header_t *curr_list = (free_header_t *) ((void*)memory + free_list_ptr);
    free_header_t *next_list = (free_header_t *) ((void*)memory + curr_list->next);
    free_header_t *prev_list = (free_header_t *) ((void*)memory + curr_list->prev);
    vlink_t object_offset = ((void*)object_block-(void*)memory);
*/

   vlad_merge();
}

// Input: current state of the memory[]
// Output: new state, where any adjacent blocks in the free list
//            have been combined into a single larger block; after this,
//            there should be no region in the free list whose next
//            reference is to a location just past the end of the region

static void vlad_merge()
{
	// TODO for Milestone 4
}

// Stop the allocator, so that it can be init'ed again:
// Precondition: allocator memory was once allocated by vlad_init()
// Postcondition: allocator is unusable until vlad_int() executed again

void vlad_end(void)
{
   // TODO for Milestone 1
   //free 
    free (memory);
}


// Precondition: allocator has been vlad_init()'d
// Postcondition: allocator stats displayed on stdout

void vlad_stats(void)
{
   // TODO
   // put whatever code you think will help you
   // understand Vlad's current state in this function
   // REMOVE all of these statements when your vlad_malloc() is done
   printf("vlad_stats() won't work until vlad_malloc() works\n");
   return;
}

