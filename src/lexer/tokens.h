#ifndef TOKENS_H
#define TOKENS_H

#include <stdlib.h>

char WHITESPACES[4];
char DIGITS[11];

enum token_type
{
    NUMBER = 1,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN
};

typedef struct token_t
{
    enum token_type type;
    int value;
} token_t;

typedef struct token_list_t
{
    token_t *arr;
    size_t size;
    size_t capacity;
} token_list_t;

#endif // TOKENS_H
