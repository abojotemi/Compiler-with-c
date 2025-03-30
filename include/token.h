#ifndef TOKEN_DEF
#define TOKEN_DEF
#include "lexer.h"
#include "binary_tree.h"

typedef enum
{
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_STR,
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_PAREN_OPEN,
    TOKEN_PAREN_CLOSE,
    TOKEN_BRACE_OPEN,
    TOKEN_BRACE_CLOSE,
    TOKEN_COMMA,
    TOKEN_ARROW,
    TOKEN_COLON,
    TOKEN_EOF,
    TOKEN_INVALID
} TokenType;

typedef struct
{
    TokenType type; 
    char *lexeme;   
    int line;       
    int column;     
} Token;
Token* get_next_token(Lexer *lexer, Node *node);
void free_token(Token *token);
#endif
