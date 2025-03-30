#include "../include/token.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

static void skip_whitespace_and_comments(Lexer *lexer)
{
    char current = peek(lexer);
    while (isspace(current) || current == '#')
    {
        if (current == '#')
        {
            while (current != '\n' && current != '\0')
            {
                current = advance(lexer);
            }
        }
        else
        {
            current = advance(lexer);
        }
        current = peek(lexer);
    }
}

static int process_identifier(Token *token, Lexer *lexer, Node *node,
                              char **lexeme, int *idx, int *size, int growth)
{
    char current = peek(lexer);
    while (isalpha(current) || current == '_' || isdigit(current))
    {
        (*lexeme)[(*idx)++] = current;
        current = advance(lexer);
        if (*idx >= *size - 1)
        {
            *size += growth;
            *lexeme = (char *)realloc(*lexeme, *size);
            if (!*lexeme)
            {
                puts("Lexeme reallocation failed");
                return 0;
            }
        }
    }
    (*lexeme)[*idx] = '\0';
    if (find_node(node, *lexeme))
        token->type = TOKEN_KEYWORD;
    else
        token->type = TOKEN_IDENTIFIER;
    return 1;
}

static int process_number(Token *token, Lexer *lexer, char **lexeme,
                          int *idx, int *size, int growth)
{
    bool is_invalid = false;
    bool is_float = false;
    char current = peek(lexer);
    int dot_count = 0;
    while (isdigit(current) || current == '.')
    {
        if (current == '.')
        {
            dot_count++;
            if (dot_count > 1)
                is_invalid = true;
            is_float = true;
        }
        (*lexeme)[(*idx)++] = current;
        current = advance(lexer);
        if (*idx >= *size - 1)
        {
            *size += growth;
            *lexeme = (char *)realloc(*lexeme, *size);
            if (!*lexeme)
            {
                puts("Lexeme reallocation failed");
                return 0;
            }
        }
    }
    if (isalpha(current))
    {
        is_invalid = true;
        while(!isspace(current)){
            (*lexeme)[(*idx)++] = current;
        current = advance(lexer);
        if (*idx >= *size - 1)
        {
            *size += growth;
            *lexeme = (char *)realloc(*lexeme, *size);
            if (!*lexeme)
            {
                puts("Lexeme reallocation failed");
                return 0;
            }
        }
        }
    }

    if ((*lexeme)[0] == '.' || ((*idx) > 0 && (*lexeme)[*idx - 1] == '.'))
        is_invalid = true;
    (*lexeme)[*idx] = '\0';
    if (is_invalid)
        token->type = TOKEN_INVALID;
    else if (is_float)
        token->type = TOKEN_FLOAT;
    else
        token->type = TOKEN_INT;
    return 1;
}

static int process_operator(Token *token, Lexer *lexer, char **lexeme,
                            int *idx, int *size, int growth)
{
    (*lexeme)[*idx] = peek(lexer);
    char first = (*lexeme)[*idx];
    char current = advance(lexer);
    if (first == '-' && current == '>')
    {
        token->type = TOKEN_ARROW;
        if (*idx >= *size - 1)
        {
            *size += growth;
            *lexeme = (char *)realloc(*lexeme, *size);
            if (!*lexeme)
            {
                puts("Lexeme reallocation failed");
                return 0;
            }
        }
        (*lexeme)[++(*idx)] = current;
        advance(lexer);
    }
    else
    {
        token->type = TOKEN_OPERATOR;
    }
    (*lexeme)[*idx + 1] = '\0';
    return 1;
}

static int process_string(Token *token, Lexer *lexer, char **lexeme,
                          int *idx, int *size, int growth)
{
    char current = advance(lexer);
    while (current != '"' && current != '\0')
    {
        (*lexeme)[(*idx)++] = current;
        current = advance(lexer);
        if (*idx >= *size - 1)
        {
            *size += growth;
            *lexeme = (char *)realloc(*lexeme, *size);
            if (!*lexeme)
            {
                puts("Lexeme reallocation failed");
                return 0;
            }
        }
    }
    token->type = TOKEN_STR;
    (*lexeme)[*idx] = '\0';
    advance(lexer);
    return 1;
}

static void process_single_char(Token *token, Lexer *lexer, char **lexeme, int *idx)
{
    char current = peek(lexer);
    switch (current)
    {
    case '(':
        token->type = TOKEN_PAREN_OPEN;
        break;
    case ')':
        token->type = TOKEN_PAREN_CLOSE;
        break;
    case '{':
        token->type = TOKEN_BRACE_OPEN;
        break;
    case '}':
        token->type = TOKEN_BRACE_CLOSE;
        break;
    case ',':
        token->type = TOKEN_COMMA;
        break;
    case ':':
        token->type = TOKEN_COLON;
        break;
    default:
        token->type = TOKEN_INVALID;
        break;
    }
    (*lexeme)[(*idx)++] = current;
    (*lexeme)[*idx] = '\0';
    advance(lexer);
}

Token *get_next_token(Lexer *lexer, Node *node)
{
    Token *token = (Token *)malloc(sizeof(Token));
    if (!token)
    {
        puts("Token allocation failed");
        return NULL;
    }
    token->type = TOKEN_INVALID;

    int size = 2;
    int growth = 4;
    int idx = 0;
    char *lexeme = (char *)malloc(sizeof(char) * size);
    if (!lexeme)
    {
        puts("Lexeme Allocation failed");
        free(token);
        return NULL;
    }

    skip_whitespace_and_comments(lexer);
    char current = peek(lexer);
    bool is_kw_or_id = isalpha(current) || current == '_';

    if (current == '\0')
    {
        free(lexeme);
        return token;
    }

    if (is_kw_or_id)
    {
        if (!process_identifier(token, lexer, node, &lexeme, &idx, &size, growth))
            return NULL;
    }
    else if (isdigit(current))
    {
        if (!process_number(token, lexer, &lexeme, &idx, &size, growth))
            return NULL;
    }
    else if (current == '=' || current == '*' || current == '+' || current == '-' ||
             current == '<' || current == '>')
    {
        if (!process_operator(token, lexer, &lexeme, &idx, &size, growth))
            return NULL;
    }
    else if (current == '"')
    {
        if (!process_string(token, lexer, &lexeme, &idx, &size, growth))
            return NULL;
    }
    else
    {
        process_single_char(token, lexer, &lexeme, &idx);
    }

    token->lexeme = lexeme;
    token->column = lexer->column;
    token->line = lexer->line;
    return token;
}

void free_token(Token *token)
{
    free(token->lexeme);
    free(token);
}