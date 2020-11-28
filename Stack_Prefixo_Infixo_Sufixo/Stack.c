#include "Stack.h"

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

// Stack Int
StackInt *createStackInt(int tam)
{
    StackInt *s = (StackInt *)malloc(sizeof(StackInt));
    s->tamanho = tam;
    s->topo = 0;
    s->vec = (int *)malloc(sizeof(int) * tam);
    return s;
}

void pushInt(StackInt *s, int elem)
{
    if (fullInt(s))
    {
        printf("Stack Full!\n");
        return;
    }
    s->vec[s->topo] = elem;
    s->topo++;
}

int popInt(StackInt *s)
{
    if (emptyInt(s))
    {
        printf("Stack Empty!!\n");
        return -1;
    }
    s->topo--;
    return s->vec[s->topo];
}

int fullInt(StackInt *s)
{
    return (s->topo == s->tamanho);
}

int emptyInt(StackInt *s)
{
    return (s->topo == 0);
}

void printElementsInt(StackInt *s)
{
    for (int i = 0; i < s->topo; i++)
        printf("Element: %d\n", s->vec[i]);
}

void liberarStackInt(StackInt *s)
{
    free(s->vec);
    free(s);
}

// SE QUISER TER A SEQUENCIA CERTINHO, SIMPLESMENTE ARMAZENA EM UMA LISTA OU EM UM VETOR DE CHAR COM O MESMO TAMANHO.
// SO IR COLOCANDO NOS LOCAIS QUE TEM O PRINTF
char *infixo_To_sufixo(char *str)
{
    // Essa pilha vai armazenar SOMENTE OS OPERADORES E ABERTURA DE CHAVE
    // FECHADURA DE CHAVE nao sera armazenado em local nenhum
    Stack *s = createStack(strlen(str));
    char *posFix = (char *)malloc(sizeof(char) * strlen(str));
    int i = 0, j = 0;
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
                posFix[j++] = temp;
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
                    posFix[j++] = temp;
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
                    posFix[j++] = temp;
                    temp = pop(s);
                }
                push(s, temp);
            }
            push(s, aux);
            break;

        // Encontrou um numero, simplesmente printa
        default:
            if (aux != ' ')
            {
                printf("%c ", aux);
                posFix[j++] = aux;
            }
            break;
        }
        i++;
    }
    // Printando os operadores que restaram na pilha
    while (!empty(s))
    {
        temp = pop(s);
        if (temp != '(')
        {
            printf("%c ", temp);
            posFix[j++] = temp;
        }
    }
    printf("\n");

    posFix[j] = '\0';

    liberarStack(s);

    return posFix;
}

void sufixo_To_infixo(char *str)
{
}

// 9 0 1 + 2 3 * * +
// 9 + (0 + 1) * (2 * 3)
int calculoSufixo_To_Infixo(char *str)
{
    StackInt *s = createStackInt(strlen(str));
    int i = 0;
    int total = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
            pushInt(s, str[i] - 48);
        else
        {
            switch (str[i])
            {
            case '/':
                total = popInt(s) / popInt(s);
                pushInt(s, total);
                break;
            case '*':
                total = popInt(s) * popInt(s);
                pushInt(s, total);
                break;
            case '-':
                total = popInt(s) - popInt(s);
                pushInt(s, total);
                break;
            case '+':
                total = popInt(s) + popInt(s);
                pushInt(s, total);
                break;

            default:
                printf("Algo de errado nao esta certo.\n");
                break;
            }
        }
        i++;
    }
    return total;
}