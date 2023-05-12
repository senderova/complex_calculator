#include "config.h"

#pragma once

typedef struct {
    char type[MAX_TOKEN_TYPE_LEN];
    char value[MAX_TOKEN_VALUE_LEN];
} Token;

void InitializeToken(Token *token);

Token CreateToken(char *type, char *value);

