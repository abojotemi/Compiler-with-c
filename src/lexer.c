#include "../include/lexer.h"

char peek(Lexer *lexer)
{
    return lexer->source[lexer->pos];
}

char advance(Lexer *lexer)
{
    lexer->pos++;
    lexer->column++;
    char current_char = peek(lexer);
    if (current_char == '\n')
    {
        lexer->line++;
        lexer->column = 0;
    }
    return current_char;
}

Lexer *init_lexer(const char *filename)
{
    int file_size;
    char *source = get_file(filename, &file_size);
    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
    if (!lexer)
    {
        puts("Lexer reallocation failed");
        exit(1);
    }
    lexer->source = source;
    lexer->pos = 0;
    lexer->column = 0;
    lexer->line = 0;
    lexer->size = file_size;
    return lexer;
}

void free_lexer(Lexer *lexer)
{
    free(lexer->source);
    free(lexer);
}