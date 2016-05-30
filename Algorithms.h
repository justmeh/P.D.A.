#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include<stdio.h>

void swap(int *a, int *b);

//MERGESORT
	void mergesort(int *x, int s, int f);
	void interclasare(int *x, int *v, int sx, int fx, int sy, int fy);

//QUICKSORT
	void quicksort(int *v, int x, int y);

//HEAPSORT
	struct node_heap
	{
		int data;

		struct node_heap *l, *r;
	};

	typedef struct node_heap node_heap;

	void initialise_heap(node_heap **root, int data);


	void add_to_heap(node_heap *root, int data);

	void heap_sort(node_heap *root, int *vec, int *size);

//LIST / STACK

	struct node_list
	{
		int data;
		struct node_list *next;
	};

	typedef struct node_list node_list;

	void initialise_list(node_list **node);

	void add_to_list(node_list** node, int data);

	void remove_first_list(node_list **node);

	int get_first_elem_list(node_list **node);


//QUEUE

	void initialise_queue(int *sq, int *eq);

	void add_to_queue(int *queue, int *sq, int *eq, int MAX, int data);

	int is_empty_queue(int *sq, int *eq);

	void pop_queue(int *sq, int *eq, int MAX);

	int  queue_front(int *queue, int *sq);


	
//GRAPH

	void DFS(node_list *V[], int *viz, int t);

	void BFS(node_list *V[], int size, int *viz, int s);

	void sort_top(node_list *V[], int *viz, node_list **stk, int t);

//BACKTRACKING

	void init(int *st, int k);

	int succesor(int *st, int k, int N);

	int solutie(int *st, int k, int N);

	void tipar(int *st, int k);

	int valid(int *st, int k);

	void bkt(int *st, int k, int N);



#endif