#include "inOut.h"
#include "list.h"
#include "polish.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

    int isempty(struct stack *s){
        return s->top == EMPTY;
    }

    void emptystack(struct stack* s){
        s->top=EMPTY;
    }

    void push(struct stack* s, struct node *item){
        if(s->top == (MAX-1))
        {
            printf("\nSTACK FULL");
        }
        else
        {
            ++s->top;
            s->data[s->top]=item;
        }
    }

    struct node* pop(struct stack* s){
        struct node *ret=NULL;
        if(!isempty(s))
        {
            ret = s->data[s->top];
            --s->top;
        }
        return ret;
    }
