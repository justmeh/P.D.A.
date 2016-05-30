#include "inOut.h"
#include "list.h"
#include "polish.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

    void make_tree(char* postfix, struct node **root){
        struct stack X;
        struct node *newnode,*op1,*op2;
        char numberextract[100];
        char *p;

        emptystack(&X);
        p = &postfix[0];
        strcpy(numberextract,"");
        while(*p)
        {
            while(*p == ' ')
            {
                p++;
            }

            if(isdigit(*p))
            {
                while(isdigit(*p))
                {
                    strcat(numberextract,p);
                    p++;
                }
                newnode = malloc(sizeof(struct node));
                newnode->kind = 'N';
                newnode->number = atoi(numberextract);
                newnode->left = NULL;
                newnode->right = NULL;
                push(&X,newnode);
                strcpy(numberextract,"");
            }
            else if(!isoperator(*p))
            {
                newnode = malloc(sizeof(struct node));
                newnode->kind = 'N';
                newnode->number = VAR[*p-'a'];
                newnode->left = NULL;
                newnode->right = NULL;
                push(&X,newnode);
            }
            else
            {
                if(*p=='-' && isdigit(*(p+1)))
                {
                    strcat(numberextract,p);
                    p++;
                    while(isdigit(*p))
                    {
                        strcat(numberextract,p);
                        p++;
                    }
                    newnode = malloc(sizeof(struct node));
                    newnode->kind = 'N';
                    newnode->number = atoi(numberextract);
                    newnode->left = NULL;
                    newnode->right = NULL;
                    push(&X,newnode);
                    strcpy(numberextract,"");
                }
                else if(*p=='-' && isalpha(*(p+1)))
                {
                    newnode = malloc(sizeof(struct node));
                    newnode->kind = 'N';
                    newnode->number = -VAR[*p-'a'];
                    newnode->left = NULL;
                    newnode->right = NULL;
                    push(&X,newnode);
                }
                else
                {
                    op1 = pop(&X);
                    op2 = pop(&X);
                    newnode = malloc(sizeof(struct node));
                    newnode->kind = 'O';
                    newnode->op = *p;
                    newnode->left = op2;
                    newnode->right = op1;
                    push(&X,newnode);
                }
            }
            p++;
        }
        *root = pop(&X);
    }

    long long evaluatetree(struct node *x){
        if( x->kind == 'O' )
        {
            long long ans;
            long long op1 = evaluatetree( x->left );
            long long op2 = evaluatetree( x->right );
            switch ( x->op )
            {
                case '+':   return op1 + op2;
                case '-':   return op1 - op2;
                case '*':   return op1 * op2;
                case '/':   return op1 / op2;
                case '^':   ans = pow(op1,op2);
                            return ans;

                default:   return 0;
            }
        }
        else
            return x->number;
    }
