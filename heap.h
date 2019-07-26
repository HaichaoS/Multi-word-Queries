/* * * * * * *
 * creating and manipulating binary min-heaps on integer indices
 *
 * created by Haichao Song 854035
 */

typedef struct heap Heap;

typedef struct{
    int value;     /* the data value of the heapitem */
    float key;     /* the key for deciding position in the heap */
} heapitem;

struct heap {
    heapitem *items;        /* the array of heapitems */
    int max_size;           /* the max size of the array */
    int current_position;   /* the number of items in the array */
};

/*create an empty Heap with capacity for max_size items */
Heap *new_heap(int max_size);

/* insert data into h with priority key */
void heap_insert(Heap *h, float key, int data);

/* remove and return the item with the smallest key in h */
int heap_remove_min(Heap *h);

/* return, but not remove, the item with the smallest key in h */
int heap_peek_min(Heap *h);

/* return the key of the item with the smallest key in h */
float heap_peek_key(Heap *h);

/* de-allocate all memory used by h */
void free_heap(Heap *h);

/* print the contents of a heap to stdout */
void print_heap(Heap *h);




