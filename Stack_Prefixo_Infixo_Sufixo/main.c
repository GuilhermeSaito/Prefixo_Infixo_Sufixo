#include "Stack.h"

#define TAM 10

int main()
{
    // (5 / (5 + 9 - 9 / 8) + 5 * 8 + (8 / 5) * (5 / 8) * 1)
    char *str = "(1+(2/2*1)*9+(9*8*6)+9)";
    printf("%s\n", str);

    printf("Soma: %d\n", calculoSufixo_To_Infixo(infixo_To_sufixo(str)));
    return 0;
}