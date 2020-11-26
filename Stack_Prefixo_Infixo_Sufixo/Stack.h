#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct Pilha
{
    int topo;
    int tamanho;
    char *vec;
} Stack;

Stack *createStack(int tam);
void push(Stack *s, char elem);
char pop(Stack *s);
int full(Stack *s);
int empty(Stack *s);
void printElements(Stack *s);
void liberarStack(Stack *s);

void infixo_To_sufixo(char *str);
void sufixo_To_Infixo(char *str);
int calculoSufixo_To_Infixo(char *str);