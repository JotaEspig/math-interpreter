#include "evaluator.h"

#include "../parser/ast.h"
#include "../lexer/tokens.h"

int evaluate_ast(ast_node_t *node)
{
    if (node == NULL)
        return 0;

    int divisor;
    switch (node->token.type)
    {
    case NUMBER:
        return node->token.value;

    case PLUS:
        return evaluate_ast(node->left) + (unsigned)evaluate_ast(node->right);

    case MINUS:
        return evaluate_ast(node->left) - (unsigned)evaluate_ast(node->right);

    case MULTIPLY:
        return evaluate_ast(node->left) * (unsigned)evaluate_ast(node->right);

    case DIVIDE:
        divisor = evaluate_ast(node->right);
        return divisor ? evaluate_ast(node->left) / divisor : 0;

    default:
        return 0;
    }
}
