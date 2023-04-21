#include "parser.h"

#include "ast.h"
#include "../lexer/tokens.h"

parser_t *new_parser(token_list_t *tokens)
{
    if (tokens == NULL || tokens->size < 1)
        return NULL;

    parser_t *parser = (parser_t *)malloc(sizeof(parser_t));
    parser->tokens = tokens;
    parser->current_token = *parser->tokens->arr;
    return parser;
}

static void next(parser_t *parser)
{
    parser->tokens->arr++;
    parser->current_token = *parser->tokens->arr;
}

ast_node_t *parser_generate_ast(parser_t *parser)
{
    ast_node_t *result = parser_parse_expr(parser);
    return result;
}
