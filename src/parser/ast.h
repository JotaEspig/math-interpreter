#ifndef AST_H
#define AST_H

#include "../lexer/tokens.h"

struct ast_node
{
    token_t token;
    struct ast_node *left;
    struct ast_node *right;
};
typedef struct ast_node ast_node_t;

ast_node_t *new_number_node(token_t token);

ast_node_t *new_plus_node(ast_node_t *left, ast_node_t *right);

ast_node_t *new_minus_node(ast_node_t *left, ast_node_t *right);

ast_node_t *new_multiply_node(ast_node_t *left, ast_node_t *right);

ast_node_t *new_divide_node(ast_node_t *left, ast_node_t *right);

void delete_ast(ast_node_t *node);

#endif // AST_H
