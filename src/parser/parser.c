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

ast_node_t *parser_parse_expr(parser_t *parser)
{
    ast_node_t *result = parser_parse_term(parser);
    if (result == NULL)
        return NULL;

    while (parser->current_token.type != INVALID &&
           (parser->current_token.type == PLUS ||
            parser->current_token.type == MINUS))
    {
        if (parser->current_token.type == PLUS)
        {
            next(parser);
            ast_node_t *right = parser_parse_term(parser);
            if (right == NULL)
                return NULL;

            result = new_plus_node(result, right);
        }
        else if (parser->current_token.type == MINUS)
        {
            next(parser);
            ast_node_t *right = parser_parse_term(parser);
            if (right == NULL)
                return NULL;

            result = new_minus_node(result, right);
        }
    }

    return result;
}

ast_node_t *parser_parse_term(parser_t *parser)
{
    ast_node_t *result = parser_parse_factor(parser);
    if (result == NULL)
        return NULL;

    while (parser->current_token.type != INVALID &&
           (parser->current_token.type == MULTIPLY ||
            parser->current_token.type == DIVIDE))
    {
        if (parser->current_token.type == MULTIPLY)
        {
            next(parser);
            ast_node_t *right = parser_parse_factor(parser);
            if (right == NULL)
                return NULL;

            result = new_multiply_node(result, right);
        }
        else if (parser->current_token.type == DIVIDE)
        {
            next(parser);
            ast_node_t *right = parser_parse_factor(parser);
            if (right == NULL)
                return NULL;

            result = new_divide_node(result, right);
        }
    }

    return result;
}

ast_node_t *parser_parse_factor(parser_t *parser)
{
    ast_node_t *result = NULL;
    if (parser->current_token.type == INVALID)
        return NULL;

    if (parser->current_token.type == LPAREN)
    {
        next(parser);
        result = parser_parse_expr(parser);
        if (parser->current_token.type != RPAREN)
            return NULL;

        next(parser);
        return result;
    }

    if (parser->current_token.type == PLUS)
    {
        next(parser);
        ast_node_t *child = parser_parse_factor(parser);
        if (child == NULL)
            return NULL;

        result = new_positive_node(child);
        return result;
    }
    if (parser->current_token.type == MINUS)
    {
        next(parser);
        ast_node_t *child = parser_parse_factor(parser);
        if (child == NULL)
            return NULL;

        result = new_negative_node(child);
        return result;
    }

    if (parser->current_token.type != NUMBER)
        return NULL;

    result = new_number_node(parser->current_token);
    next(parser);
    return result;
}
