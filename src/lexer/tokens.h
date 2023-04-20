#ifndef TOKENS_H
#define TOKENS_H

#include <stdlib.h>

#define START_LIST_SIZE 5

extern const char WHITESPACES[4];
extern const char DIGITS[11];
extern const char MINUS_CHAR;

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

token_list_t *new_token_list();

token_list_t *token_list_append_token(token_list_t *tokens, token_t new_token);

void token_list_print(token_list_t *tokens);

void delete_token_list(token_list_t *tokens);

#endif // TOKENS_H
