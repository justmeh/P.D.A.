#ifndef list
#define list

#define MAX 100
#define EMPTY -1

    struct node{
        char kind;
        char op;
        long long number;
        struct node *left,*right;
    };

    struct stack{
        struct node *data[MAX];
        int top;
    };

    int isempty(struct stack *s);
    void emptystack(struct stack* s);
    void push(struct stack* s, struct node *item);
    struct node* pop(struct stack* s);

#endif
