#include "util.c"
#include "lexer.c"
#include "token.c"
#include "binary_tree.c"

int main()
{
    Lexer *lexer = init_lexer("../test.temi");
    Tree tree;
    tree.root = NULL;
    for (int i = 0; i < KW_SIZE; i++)
    {
        tree.root = insert_btree_node(tree.root, (char *)KEYWORDS[i]);
    }

    while (lexer->pos < lexer->size)
    {
        Token *token = get_next_token(lexer, tree.root);
        if (!token)
        {
            puts("Error generating next token");
            return 1;
        }
        if (token->type == TOKEN_INVALID)
        {
            printf("%s is an invalid token.\n", token->lexeme);
        }
        else
            printf("Next_token: %s\n", token->lexeme);
        free_token(token);
    }
    free_lexer(lexer);
    return 0;
}