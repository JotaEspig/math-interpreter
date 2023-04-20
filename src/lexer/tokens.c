#include "tokens.h"

#include <stdio.h>
#include <stdlib.h>

const char WHITESPACES[4] = " \n\t";
const char DIGITS[11] = "0123456789";
const char MINUS_CHAR = '-';

token_list_t *new_token_list()
{
    token_list_t *tokens = (token_list_t *)malloc(sizeof(token_list_t));
    if (tokens == NULL)
        return NULL;

    tokens->arr = (token_t *)calloc(START_LIST_SIZE, sizeof(token_t));
    tokens->capacity = 5;
    tokens->size = 0;
    return tokens;
}

token_list_t *token_list_append_token(token_list_t *tokens, token_t new_token)
{
    // increases the capacity if it's already full
    if (tokens->size == tokens->capacity)
    {
        size_t new_capacity = tokens->capacity * 2;
        token_t *new_arr = (token_t *)
            realloc(tokens->arr, sizeof(token_t) * new_capacity);
        if (new_arr == NULL)
            return NULL;

        tokens->arr = new_arr;
        tokens->capacity = new_capacity;
    }

    tokens->arr[tokens->size] = new_token;
    tokens->size++;
    return tokens;
}

void token_list_print(token_list_t *tokens)
{
    printf("Capacity: %ld, Size: %ld\n", tokens->capacity, tokens->size);
    for (size_t i = 0; i < tokens->size; i++)
    {
        token_t token = tokens->arr[i];
        printf("TYPE: %d -> NUMBER: %d\n", token.type, token.value);
    }
}

void delete_token_list(token_list_t *tokens)
{
    free(tokens->arr);
    free(tokens);
}
