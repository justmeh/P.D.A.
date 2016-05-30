#include "inOut.h"
#include "list.h"
#include "polish.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


    int isoperator(char e){
        if(e == '+' || e == '-' || e == '*' || e == '/' || e == '^')
            return 1;
        return 0;
    }

    int priority(char e){
        int pri = 0;

        if(e == '*' || e == '/' || e =='^')
            pri = 2;
        else
        {
            if(e == '+' || e == '-')
                pri = 1;
        }
        return pri;
    }

    void infix2postfix(char* infix, char * postfix, int space){
        char *i,*p;
        struct stack X;
        char n1;
        emptystack(&X);
        i = &infix[0];
        p = &postfix[0];

        while(*i!='\0')
        {
            if( isdigit(*i) || isalpha(*i) )
            {
                while( isdigit(*i) || isalpha(*i))
                {
                    *p = *i;
                    p++;
                    i++;
                }
                if(space)
                {
                    *p = ' ';
                    p++;
                }
            }
            else if( isoperator(*i) )
            {
                if(*i=='-' && isoperator(*(i-1)) && (isdigit(*(i+1))))
                {
                    *p = *i;
                    p++;
                    i++;
                    while( isdigit(*i) || isalpha(*i))
                    {
                        *p = *i;
                        p++;
                        i++;
                    }
                    if(space)
                    {
                        *p = ' ';
                        p++;
                    }
                }
                else if(*i=='-' && isoperator(*(i-1)) && (isalpha(*(i+1))))
                {
                    *p = *i;
                    p++;
                    int w=VAR[*(i+1)-'a'];
                    i+=2;
                    if(w<0){
                        p--;
                        w=-w;
                    }
                    char aux[10];
                    int nrc=0;
                    while(w)
                    {
                        aux[nrc++]=(char)('0'+w%10);
                        w/=10;
                    }
                    aux[nrc]='\0';
                    for(w=nrc-1;w>=0;--w)
                    {
                        *p=aux[w];
                        p++;
                    }
                    if(space)
                    {
                        *p = ' ';
                        p++;
                    }
                }
                else
                {
                    if(isempty(&X))
                        push(&X,*i);
                    else
                    {
                        n1 = pop(&X);
                        while(priority(n1) >= priority(*i))
                        {
                            *p = n1;
                            p++;
                            if(space)
                            {
                                *p = ' ';
                                p++;
                            }
                            n1 = pop(&X);
                        }
                        push(&X,n1);
                        push(&X,*i);
                    }
                    i++;
                }
            }
        }
        while(!isempty(&X))
        {
            n1 = pop(&X);
            *p = n1;
            p++;
            if(space)
            {
                *p = ' ';
                p++;
            }
        }
        *p = '\0';
    }
