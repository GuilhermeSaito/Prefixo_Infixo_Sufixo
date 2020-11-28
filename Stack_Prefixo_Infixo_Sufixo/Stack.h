#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Stack de Int
typedef struct PilhaInt
{
    int topo;
    int tamanho;
    int *vec;
} StackInt;

StackInt *createStackInt(int tam);
void pushInt(StackInt *s, int elem);
int popInt(StackInt *s);
int fullInt(StackInt *s);
int emptyInt(StackInt *s);
void printElementsInt(StackInt *s);
void liberarStackInt(StackInt *s);

char *infixo_To_sufixo(char *str);
void sufixo_To_infixo(char *str);
int calculoSufixo_To_Infixo(char *str);