#include "ast.h"

#include <stdlib.h>

#include "../lexer/tokens.h"

ast_node_t *new_number_node(token_t token)
{
    ast_node_t *node = (ast_node_t *)malloc(sizeof(ast_node_t));
    node->token = token;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ast_node_t *new_plus_node(ast_node_t *left, ast_node_t *right)
{
    token_t token;
    token.type = PLUS;
    token.value = 0;

    ast_node_t *node = (ast_node_t *)malloc(sizeof(ast_node_t));
    node->token = token;
    node->left = left;
    node->right = right;
    return node;
}

ast_node_t *new_minus_node(ast_node_t *left, ast_node_t *right)
{
    token_t token;
    token.type = MINUS;
    token.value = 0;

    ast_node_t *node = (ast_node_t *)malloc(sizeof(ast_node_t));
    node->token = token;
    node->left = left;
    node->right = right;
    return node;
}

ast_node_t *new_multiply_node(ast_node_t *left, ast_node_t *right)
{
    token_t token;
    token.type = MULTIPLY;
    token.value = 0;

    ast_node_t *node = (ast_node_t *)malloc(sizeof(ast_node_t));
    node->token = token;
    node->left = left;
    node->right = right;
    return node;
}

ast_node_t *new_divide_node(ast_node_t *left, ast_node_t *right)
{
    token_t token;
    token.type = DIVIDE;
    token.value = 0;

    ast_node_t *node = (ast_node_t *)malloc(sizeof(ast_node_t));
    node->token = token;
    node->left = left;
    node->right = right;
    return node;
}

void delete_ast(ast_node_t *node)
{
    if (node == NULL)
        return;

    delete_ast(node->left);
    delete_ast(node->right);
    free(node);
}
