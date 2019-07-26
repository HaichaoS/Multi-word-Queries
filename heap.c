/* * * * * * *
* Module for creating and manipulating binary min-heaps on integer indices
*
* created for Haichao Song 854035
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"

void siftup(Heap *h, int pos);
void siftdown(Heap *h, int pos);
void swap(heapitem *a, heapitem *b);
int min_child(Heap *h, int i);

/*create an empty Heap with capacity for max_size items */
Heap *new_heap(int max_size) {
    Heap *heap = malloc(sizeof(*heap));
    assert(heap);
    heap->max_size = max_size;
    heap->current_position = 0;
    heap->items = malloc(max_size * sizeof(*heap->items));
    assert(heap->items);
    return heap;
}

/* insert data into h with priority key */
void heap_insert(Heap *h, float key, int data) {
    assert(h);
    if (h->current_position < h->max_size) {
        h->items[h->current_position].value = data;
        h->items[h->current_position].key = key;
        siftup(h, h->current_position);
        h->current_position += 1;
    }
}

/* remove and return the item with the smallest key in h */
int heap_remove_min(Heap *h) {
    assert(h);
    swap(h->items, h->items + h->current_position - 1);
    h->current_position -= 1;
    siftdown(h, 0);
    return h->items[h->current_position + 1].value;
}

/* return, but not remove, the item with the smallest key in h */
int heap_peek_min(Heap *h) {
    assert(h);
    return h->items[0].value;
}

/* return the key of the item with the smallest key in h */
float heap_peek_key(Heap *h) {
    assert(h);
    return h->items[0].key;
}

/* de-allocate all memory used by h */
void free_heap(Heap *h) {
    assert(h);
    free(h->items);
    free(h);
}

/* print the contents of a heap to stdout */
void print_heap(Heap *h){
    for(int i = 0; i < h->current_position-1; i++) {
        printf("%d %f\n", h->items[i].value, h->items[i].key);
    }
}

/* swap item i up the heap into its rightful position */
void siftup(Heap *h, int pos) {
    assert(h);
    while (pos != 0) {
        if (h->items[pos].key >= h->items[(pos-1)/2].key) {
            break;
        }
        swap(h->items+pos, h->items+(pos-1)/2);
        pos = (pos-1)/2;
    }
}

/* swap item i up the heap into its rightful position */
void siftdown(Heap *h, int pos) {
    assert(h);
    int smaller_child = min_child(h, pos);;
    
    if (smaller_child == -1) {
        return;
    }
    if (2*pos + 1 == h->current_position - 1) {
        if (h->items[pos].key > h->items[2*pos + 1].key) {
            swap(h->items+pos, h->items+(2*pos + 1));
        }
    } else {
        if (h->items[pos].key > h->items[smaller_child].key) {
            swap(h->items+pos, h->items+smaller_child);
            siftdown(h, smaller_child);
        }
    }
}

/* find the index of the minimum-key child of item i */
int min_child(Heap *h, int i) {
    if((2*i + 1) >= h->current_position) {
        return -1;
    }
    if ((2*i + 2) == h->current_position) {
        return 2*i + 1;
    }
    if (h->items[2*i + 1].key < h->items[2*i + 2].key) {
        return 2*i + 1;
    } else {
        return 2*i + 2;
    }
}

/* swap two heap items */
void swap(heapitem *a, heapitem *b) {
    heapitem temp;
    temp = *a;
    *a = *b;
    *b = temp;
}



