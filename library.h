#ifndef library
#define library

    typedef struct Nod{
        int data;
        struct Nod * next;
    }Nod;

    //Push functions for single-linked lists
    void print_list(Nod *head);
    void push_first(Nod *head, int value);
    void push_last(Nod *head, int value);
    void push_poz(Nod *head, int poz, int value);

    //Pop functions for single-linked lists
    int pop_first(Nod * head);
    int pop_last(Nod * head);
    int pop_poz(Nod *head, int poz);

    //Read/Print functions
    void printArray(int arr[], int n);
    void readArray(int arr[], int n);
    void readMat(int a[100][100], int n);

    //Heap sort funtions
    void heapify(int arr[], int n, int i);
    void heapSort(int arr[], int n);

    //Merge sort functions
    void mergeArray(int arr[], int l, int m, int r);
    void mergeSort(int arr[], int l, int r);

    //Quick sort functions
    void swapp(int* a, int* b);
    int partitionn(int arr[], int l, int h);
    void quickSort(int arr[], int l, int h);

    //Radix sort funtions
    int getMax(int arr[], int n);
    void countSort(int arr[], int n, int exp);
    void radixsort(int arr[], int n);

    //DFS function
    void dfs(int root, int a[100][100], int visited[], int n);

    //Backtracking standard functions
    int printSolution();
    int valid();
    void backtracking();

#endif
