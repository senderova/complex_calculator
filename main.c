#include <toPostfix.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "varibleManager.h"
#include <stdlib.h>


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

        // Parsing
        Variable variable_pool[MAX_VARIABLE_POOL_SIZE];
        Token token_pool[MAX_TOKEN_POOL_SIZE];
        int number_of_variables = 0;
        char infix[MAX_INFIX_SIZE],postfix[MAX_POSTFIX_SIZE];
        // clear zeros
        for (int i = 0; i < MAX_TOKEN_POOL_SIZE; i++)
        {
            token_pool[i].type[0] = '\0';
        }
        clear_string(infix, MAX_INFIX_SIZE); clear_string(postfix, MAX_POSTFIX_SIZE);
        // Tokenizer
        int token_pool_id = 0;
        // Misc
        Token pi = CreateToken("NUMBER", "3.141592653589793");
        Token e = CreateToken("NUMBER", "2.718281828459045");
        create_variable("pi", &pi, &number_of_variables, variable_pool);
        create_variable("e", &e, &number_of_variables, variable_pool);
        while (1) {
            ret_arrow();
            gets(infix);
            if (strcmp(infix, "exit") == 0)
            {
                break;
            }
            if  (strlen(infix) == 0)
            {
                continue;
            }

            infix_to_postfix(infix,postfix);
//            Print_Pool(number_of_variables, variable_pool);
//            printf("%s\n", postfix);

            // tokenizer
            char *tokenizer = strtok(postfix, " ");
            token_pool[token_pool_id] = CreateToken(GetType(tokenizer), tokenizer);
            token_pool_id++;
            while (tokenizer != NULL)
            {
                tokenizer = strtok(NULL, " ");
                if (tokenizer == NULL){ break;}
                token_pool[token_pool_id] = CreateToken(GetType(tokenizer), tokenizer);
                token_pool_id++;
            }
            // precalculate previous variables
            eval(token_pool, &number_of_variables, variable_pool);
            // empty cache
            for (int i = 0; i < MAX_INFIX_SIZE; i++)
            {infix[i] = '\0';}
            for (int i = 0; i < MAX_POSTFIX_SIZE; i++)
            {postfix[i] = '\0';}
            for (int i = 0; i < MAX_TOKEN_POOL_SIZE; i++)
            {
                for (int j = 0; j < MAX_TOKEN_TYPE_LEN; j++)
                {token_pool[i].type[j] = '\0';}
                for (int j = 0; j < MAX_TOKEN_VALUE_LEN; j++)
                {token_pool[i].value[j] = '\0';}
            }
            token_pool_id = 0;
        }
    }
    else
    {
        //
        // Put debug code here
        //
        char infix[100], postfix[100];
        gets(infix);
        infix_to_postfix(infix, postfix);
        printf("%s",postfix);
        printf("\n");
        return 0;
    }
}
