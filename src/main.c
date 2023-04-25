#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer/tokens.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/ast.h"
#include "evaluator/evaluator.h"

int main()
{
    lexer_text_t buff = (lexer_text_t)malloc(sizeof(char) * 128);
    token_list_t *tokens;
    parser_t *parser;
    ast_node_t *ast;
    int result;

    printf("MATH INTERPRETER\n"
           "by: JotaEspig\n"
           "Version: v0.1\n"
           "----\n"
           "type \"exit\" or \"q\" to exit the program\n"
           "======================================\n");
    while (1)
    {
        printf("> ");
        if (!fgets(buff, 128, stdin))
            exit(1);

        buff[strcspn(buff, "\n")] = 0; // removes \n
        if (strcmp(buff, "q") == 0 || strcmp(buff, "exit") == 0)
            exit(0);

        if (strcmp(buff, "") == 0)
        {
            printf("Invalid input\n");
            continue;
        }

        // TODO Prevent memory leaks
        tokens = generate_tokens(buff);
        //printf("TOKENS:\n");
        //token_list_print(tokens);
        //printf("\n");

        parser = new_parser(tokens);
        ast = parser_generate_ast(parser);
        if (ast != NULL)
        {
            result = evaluate_ast(ast);
            printf("= %d\n", result);
        }
        else
        {
            printf("Invalid syntax\n");
        }

        if (tokens != NULL)
            delete_token_list(tokens);
        if (parser != NULL)
            delete_parser(parser);
        if (ast != NULL)
            delete_ast(ast);
    }

    // Memory leak still occurs caused by some thing inside parser
    // Example: "- (00" causes memory leak
    free(buff);
    return 0;
}
