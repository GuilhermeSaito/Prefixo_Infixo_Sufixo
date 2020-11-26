#include "Stack.h"
#include <string.h>

Stack *createStack(int tam)
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->tamanho = tam;
    s->topo = 0;
    s->vec = (char *)malloc(sizeof(char) * tam);
    return s;
}

void push(Stack *s, char elem)
{
    if (full(s))
    {
        printf("Stack Full!\n");
        return;
    }
    s->vec[s->topo] = elem;
    s->topo++;
}

char pop(Stack *s)
{
    if (empty(s))
    {
        printf("Stack Empty!!\n");
        return -1;
    }
    s->topo--;
    return s->vec[s->topo];
}

int full(Stack *s)
{
    return (s->topo == s->tamanho);
}

int empty(Stack *s)
{
    return (s->topo == 0);
}

void printElements(Stack *s)
{
    for (int i = 0; i < s->topo; i++)
        printf("Element: %c\n", s->vec[i]);
}

void liberarStack(Stack *s)
{
    free(s->vec);
    free(s);
}

// SE QUISER TER A SEQUENCIA CERTINHO, SIMPLESMENTE ARMAZENA EM UMA LISTA OU EM UM VETOR DE CHAR COM O MESMO TAMANHO.
// SO IR COLOCANDO NOS LOCAIS QUE TEM O PRINTF
void infixo_To_sufixo(char *str)
{
    // Essa pilha vai armazenar SOMENTE OS OPERADORES E ABERTURA DE CHAVE
    // FECHADURA DE CHAVE nao sera armazenado em local nenhum
    Stack *s = createStack(strlen(str));
    int i = 0;
    // Aux = valores dos char do str, temp eh quando faz um pop
    char aux, temp;

    while (str[i] != '\0')
    {
        aux = str[i];
        switch (aux)
        {
        // Se for uma ABERTURA DE CHAVE, simplesmente coloca na pilha
        case '(':
            push(s, aux);
            break;
        // FECHADURA DE CHAVE retira um operador, se o TOPO da pilha nao for ( printar e continuar a retirar
        // Ele vai retirar a ABERTURA DE CHAVE.
        case ')':
            temp = pop(s);
            while ((temp != '(') && (!empty(s)))
            {
                printf("%c ", temp);
                temp = pop(s);
            }
            break;
        // Nao tem prioridade, portanto, se aparecer e o anterior nao for (, simplesmente printa
        case '+':
        case '-':
            temp = pop(s);
            if (temp == '(')
                push(s, temp);
            else
            {
                // Como ele vai retirar 1 pop a mais, coloca ele de volta
                while ((!empty(s)) && temp != '(')
                {
                    printf("%c ", temp);
                    temp = pop(s);
                }
                push(s, temp);
            }
            push(s, aux);
            break;
        // Como * e / tem prioridades perante a + e -, ele sao colocados por ultimo, LIFO (Last In First Out)
        case '*':
        case '/':
            temp = pop(s);
            if ((temp == '(') || (temp == '+') || (temp == '-'))
                push(s, temp);
            else
            {
                // Como ele vai retirar um pop a mais, coloca de volta
                while ((!empty(s)) && (temp != '(') && (temp != '+') && (temp != '-'))
                {
                    printf("%c ", temp);
                    temp = pop(s);
                }
                push(s, temp);
            }
            push(s, aux);
            break;

        // Encontrou um numero, simplesmente printa
        default:
            if (aux != ' ')
                printf("%c ", aux);
            break;
        }
        i++;
    }
    // Printando os operadores que restaram na pilha
    while (!empty(s))
    {
        temp = pop(s);
        printf("\nTEMP: %c\n", temp);
        if (temp != '(')
            printf("%c ", temp);
    }
    printf("\n");

    liberarStack(s);
}

void sufixo_To_Infixo(char *str)
{
}

int calculoSufixo_To_Infixo(char *str)
{
}