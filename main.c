#include <toPostfix.h>
#include <stdio.h>

int main(){
    char infix[100],postfix[100];
    gets(infix);
    infix_to_postfix(infix,postfix);
    printf("%s",postfix);
    return 0;
}
