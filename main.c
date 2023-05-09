#include <toPostfix.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "varibleManager.h"

int main(int argc, char* argv[])
{
    int mode;  // 0 for release, 1 for debug
    if (argc!= 2)
    {
        printf("Error: You should use exactly 1 of the following flags: -release or -debug\n");
        return -1;
    }
    if (strcmp(argv[1], "-release") == 0)
    {
        mode = 0;
    }
    else if (strcmp(argv[1], "-debug") == 0)
    {
        mode = 1;
    }
    else
    {
        printf("Error: Unknown flag: %s\n", argv[1]);
        return -2;
    }


    if (mode == 0)
    {
        //
        // Put release code here
        //
        greeting();
        Variable variable_pool[MAX_VARIABLE_POOL_SIZE];
        char infix[100],postfix[100];
        while (1)
        {
            ret_arrow();
            gets(infix);
            infix_to_postfix(infix,postfix);
            printf("%s\n",postfix);
        }
    }
    else
    {
        //
        // Put debug code here
        //
        ret_arrow();
        Variable variable_pool[MAX_VARIABLE_POOL_SIZE];
        char infix[100],postfix[100];
        Variable a = {"a1", "1 2 /"};
        Variable b = {"b1", "a1 3 *"};
        Variable c = create_variable("c", "15 2 +")
        variable_pool[0] = a;
        variable_pool[1] = b;
        eval(&b, 2, variable_pool);


        return 0;
    }
}
