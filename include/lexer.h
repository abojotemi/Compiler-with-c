#ifndef LEXER_DEF
#define LEXER_DEF
#include "util.h"
typedef struct {
    char *source;  
    unsigned int pos;
    unsigned int line;
    unsigned int column;
    unsigned int size;
} Lexer;
char peek(Lexer *lexer);
char advance(Lexer *lexer);
// void lexer_error(Lexer *lexer, const char *message);
Lexer *init_lexer(const char *filename);
void free_lexer(Lexer *lexer);
#endif