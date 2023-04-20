#ifndef LEXER_H
#define LEXER_H

#include "tokens.h"

#define START_LIST_SIZE 5

typedef char *lexer_text_t;

token_list_t *generate_tokens(lexer_text_t text);

#endif // LEXER_H
