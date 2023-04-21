#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "../lexer/tokens.h"

typedef struct parser_t
{
    token_list_t *tokens;
    token_t current_token;
} parser_t;

parser_t *new_parser(token_list_t *tokens);

ast_node_t *parser_generate_ast(parser_t *parser);

ast_node_t *parser_parse_expr(parser_t *parser);

ast_node_t *parser_parse_term(parser_t *parser);

ast_node_t *parser_parse_factor(parser_t *parser);

#endif // PARSER_H
