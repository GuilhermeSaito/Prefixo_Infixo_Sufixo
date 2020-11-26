#include "Stack.h"

#define TAM 10

int main()
{
    char *str = "(5 / (5 + 9 - 9 / 8) + 5 * 8 + (8 / 5) * (5 / 8) * 1)";
    printf("%s\n", str);

    infixo_To_sufixo(str);

    return 0;
}