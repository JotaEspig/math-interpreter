#include "lexer.h"

#include <stdlib.h>
#include <string.h>

static token_t generate_number(lexer_text_t *text);

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

    while (*text != 0)
    {
        // TODO check if it's possible to omit 0 and use just *text
        char current_char[] = {*text, 0};
        // if char is a whitespace do nothing
        if (strstr(WHITESPACES, current_char) != NULL)
        {
            next(&text);
            continue;
        }
        else if (strstr(DIGITS, current_char) != NULL)
        {
            token = generate_number(&text);
        }

        tokens = token_list_append_token(tokens, token);
        if (tokens == NULL)
            return NULL;

        next(&text);
    }

    return tokens;
}

static token_t generate_number(lexer_text_t *text)
{
    char *buff = (char *)calloc(128, sizeof(char));

    char current_char[] = {**text, 0};
    buff[0] = current_char[0];
    next(text);

    current_char[0] = **text;
    while (current_char[0] != 0 && strstr(DIGITS, current_char))
    {
        buff[strlen(buff)] = **text;
        next(text);
        current_char[0] = **text;
    }

    token_t token;
    token.type = NUMBER;
    token.value = atoi(buff);
    free(buff);
    return token;
}
