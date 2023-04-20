#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer/lexer.h"

int main()
{
    lexer_text_t buff = (lexer_text_t)malloc(sizeof(char) * 128);
    fgets(buff, 128, stdin);
    buff[strcspn(buff, "\n")] = 0; // removes \n
    if (strcmp(buff, "") == 0)
    {
        printf("Invalid input\n");
        exit(1);
    }
    printf("%s\n", buff);
    token_list_t *tokens = generate_tokens(buff);
    token_list_print(tokens);
    delete_token_list(tokens);
    return 0;
}
