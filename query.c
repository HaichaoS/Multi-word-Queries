/* Assignment 1: Multi-word Queries
 * task 1 using array to store scores for every id
 * then make min-heap according to the array and print max num_results terms
 * task 2 using min_heap to store document id for every term
 * then arrange the score for every id to anther heap according to the link structure
 * and print max num_results terms
 *
 * Solution written by Haichao Song 854035
 */

#include <stdio.h>
#include "query.h"
#include "list.h"
#include "heap.h"
#include "index.h"

/****************************************************************/

/* function prototypes */
void print_task(Heap *h, int a);

/****************************************************************/

/* using array to store scores for every document
 * then make min-heap according to the array
 */

void print_array_results(Index *index, int n_results, int n_documents) {
    
    /* n_results cannot be zero */
    if (!n_results) {
        return;
    }
    
    /* create an array to scores for every id and reset */
    float total[n_documents];
    for (int i = 0; i < n_documents; i++) {
       total[i] = 0.0;
    }
    
    /* for every term add scores of each id to the array */
    for (int j = 0; j < index->num_terms; j++) {
        for(Node* node = index->doclists[j]->head; node != NULL; node = node->next) {
            total[((Document*)(node->data))->id] += ((Document*)(node->data))->score;
        }
    }
    
    /* create min_heap of size n_results
     * if the heap is not full
     * or the score of new id is larger than the min score in heap, replace it
     * else go to the next id
     */
    Heap *heap = new_heap(n_results);
    for (int k = 0; k < n_documents; k++) {
        if (k < n_results) {
            heap_insert(heap, total[k], k);
        } else if (total[k] > heap_peek_key(heap)){
            heap_remove_min(heap);
            heap_insert(heap, total[k], k);
        }
    }
    
    /* print num_results terms of largest scores according to the heap */
    print_task(heap, n_results);
    
    /* free the heap */
    free_heap(heap);
}

/****************************************************************/

/*using min_heap to store document id for every term
 *then arrange the score for every id to anther heap according to the link structure
 *and print max num_results terms
 */

void print_merge_results(Index *index, int n_results) {
    
    /* n_results cannot be zero */
    if (!n_results) {
        return;
    }
    
    /* create two heaps
     * data has size num_terms to store the ids as keys
     * resu has size n_results to top scores for ids
     */
    Heap *data = new_heap(index->num_terms);
    Heap *resu = new_heap(n_results);
    
    /* create an array to store the node currently used */
    Node* node[index->num_terms];
    
    float id, score = 0.0;
    int term;
    
    /* reset the heap data point to the head of doclists */
    for (int i = 0; i < index->num_terms; i++) {
        node[i] = index->doclists[i]->head;
        heap_insert(data,(float)(((Document*)(node[i]->data))->id),i);
    }
    
    /* find the min id in the heap data and replace it by using the next node
     * if the min id in the heap data is still the same, add scores
     * else compare the score in the heap resu
     *     if heap resu is not full or the score is larger than the min in heap resu
     *     insert id and score or replace the min id and score
     */
    while (data->current_position != 0) {
        
        /* get the min id in the heap */
        id = heap_peek_key(data);
        
        /* if the min id in the heap data is still the same */
        while(heap_peek_key(data) == id) {
            
            term = heap_peek_min(data);
            /* remove the node and add the score */
            heap_remove_min(data);
            score += ((Document*)(node[term]->data))->score;
            
            /* put the next node into the heap data if it is not null */
            if(node[term]->next != NULL) {
                node[term] = node[term]->next;
                heap_insert(data, (float)(((Document*)(node[term]->data))->id), term);
            }
            
            /* stop after all node has been processed */
            if (data->current_position == 0){
                break;
            }
            
        }
        
        /* if heap resu is not full insert id and score into heap resu
         * else if the score is larger than the min in heap resu
         * replace the min id and score
         */
        if (resu->current_position < n_results){
            heap_insert(resu, score, (int)id);
        } else if(score > heap_peek_key(resu)) {
            heap_remove_min(resu);
            heap_insert(resu, score, (int)id);
        }
        
        /* reset the score */
        score = 0.0;

    }
    
    /* print num_results terms of largest scores according to the heap */
    print_task(resu, n_results);
    
    /* free the heaps */
    free_heap(data);
    free_heap(resu);
}

/****************************************************************/

/* print num_results terms of largest scores according to the heap */
void print_task(Heap *h, int a){
    
    /* remove everything in the heap
     * according to the heap_remove_min
     * everytime it puts the structure with min score to the last place
     * after this process the heap become max_heap
     */
    while(h->current_position != 0) {
        heap_remove_min(h);
    }
    
    /* print the top n_results ids and keys in the heap */
    for (int i = 0; i < a; i++) {
        if(h->items[i].key != 0) {
            printf("%6d %.6f\n", h->items[i].value, h->items[i].key);
        }
    }
}

