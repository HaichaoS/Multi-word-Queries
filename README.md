# Multi-word Queries

Implement a small part of a text search engine: using an existing inverted file index for a multi-word query to nd the top-matching documents in a large document collection.

Task 1: Array-based accumulation approach
Implement the function print array results() defined in query.c. This function has three input parameters: index (an Index pointer) containing data for the query to perform; n results (an integer) describing the number of results to output; and n documents (another integer) containing the total number of documents in the collection to be queried. This function should find the top n results matching document ids and their associated total scores. The total score for a document is the sum of its score from each term in the query. For this function, use the following method to find these top-scoring documents:
1. Initialise an array of n documents floating-point numbers, all set to 0.0.
2. Iterate through each document list in the index. For each document in the list, add the document score to the corresponding position in the array (using the document id as an array index).
3. Use the priority queue-based top-k selection algorithm to nd the maximum n results total scores in the resulting array, and their associated document ids.

Task 2: Priority queue-based multi-way merge approach
Implement the function print merge results() dened in query.c. This function has two input parameters: index (an Index pointer) containing data for the query to perform; and n results (an integer) describing the number of results to output.
This function should also nd the top n results matching document ids and their associated total scores. For this function, use the following method to nd these top-scoring documents:
1. Use a priority queue-based multi-way merge algorithm to iterate through the n terms document lists concurrently:
  1.Initialise a priority queue to order the document lists based on the id of their first documents.
  2.Repeatedly retrieve a document from the document list at the front of the priority queue, and rearrange the priority queue so that this list is positioned according to the id of its next document (stepping through the list). Stop after processing all documents in all lists.
2. While iterating through the lists in this way, accumulate total scores for each document id. Use the priority queue-based top-k selection algorithm to find the maximum n results total scores and associated document ids.

Task 3: Analysis of algorithms
First, analyse the different approaches from task 1 and task 2 in terms of their asymptotic time complexity. Then, explore the effect that the various input parameters (such as the number and length of document lists in the query and the number of results requested) have on the time taken by your program to produce its results. Support your investigation with experimental evidence gathered by timing your program with various input configurations. Include a plot to visualise your experimental results in your report. To conclude, give a precise characterisation of the circumstances where we should prefer one approach over the other.
