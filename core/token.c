#include "token.h"
#include "config.h"
#include <string.h>

void InitializeToken(Token *token)
{
    for (int i = 0; i < MAX_TOKEN_TYPE_LEN; i++)
    {
        token->value[i] = '\0';
    }
    for (int i = 0; i < MAX_TOKEN_VALUE_LEN; i++)
    {
        token->type[i] = '\0';
    }

}

Token CreateToken(char *type, char *value)
{
    Token token;
    InitializeToken(&token);
    strcpy(token.type, type);
    strcpy(token.value, value);
    return token;
}