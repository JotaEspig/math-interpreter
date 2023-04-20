#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static token_t generate_number(lexer_text_t *text);

// next takes a pointer to a pointer and increments it, so when you use *text
// (out of the function) it access the next character
static void next(lexer_text_t *text)
{
    (*text)++;
}

token_list_t *generate_tokens(lexer_text_t text)
{
    token_t token;
    // initialize list of tokens
    token_list_t *tokens = new_token_list();
    if (tokens == NULL)
        return NULL;

    char current_char[] = {*text};
    while (*current_char != 0)
    {
        // if char is a whitespace do nothing
        if (strstr(WHITESPACES, current_char) != NULL)
        {
            goto next_char;
        }
        else if (strstr(DIGITS, current_char) != NULL ||
                 *current_char == MINUS_CHAR)
        {
            token = generate_number(&text);
        }

        tokens = token_list_append_token(tokens, token);
        if (tokens == NULL)
            return NULL;

    next_char:
        next(&text);
        *current_char = *text;
    }

    return tokens;
}

static token_t generate_number(lexer_text_t *text)
{
    char *buff = (char *)calloc(128, sizeof(char));

    char current_char[] = {**text};

    *buff = *current_char;

    next(text);
    *current_char = **text;
    while (*current_char != 0 && strstr(DIGITS, current_char))
    {
        buff[strlen(buff)] = *current_char;
        next(text);
        *current_char = **text;
    }
    if (*current_char == MINUS_CHAR)
    {
        printf("Invalid Sintax: %s\n"
               ".................▲\n",
               --(*text));
        exit(1);
    }

    token_t token;
    token.type = NUMBER;
    token.value = atoi(buff);
    free(buff);
    return token;
}
