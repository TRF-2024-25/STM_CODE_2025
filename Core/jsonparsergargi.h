/*
 * jsonparsergargi.h
 *
 *  Created on: May 9, 2025
 *      Author: RISHI
 */

#ifndef JSONPARSERGARGI_H_
#define JSONPARSERGARGI_H_
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum {
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACKET,
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_NULL,
    TOKEN_TRUE,
    TOKEN_FALSE
} token_type;

typedef struct token {
    token_type type;
    char* value;
} token;

typedef struct value {
    union {
        double number;
        char* string;
        int boolean;
    } as_union;
    char* key;
} value;

value parse_value(token tok);
void parse_object(value* obj, token* tokens, int* token_index);
token* lexer(const char* input);

void append_token(token tokens[], int* token_count, token_type type, const char* value) {
    tokens[*token_count].type = type;
    tokens[*token_count].value = malloc(strlen(value) + 1);
    strcpy(tokens[*token_count].value, value);
    (*token_count)++;
}

int is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

int is_number(char c) {
    return c >= '0' && c <= '9';
}

token* lexer(const char* input) {
    int pos = 0;
    int token_count = 0;
    token* tokens = malloc(200 * sizeof(token));

    while (input[pos] != '*' && input[pos] != '\0') {
        char ch = input[pos];

        if (ch == '{') {
            append_token(tokens, &token_count, TOKEN_LEFT_BRACE, "{");
            pos++;
        } else if (ch == '}') {
            append_token(tokens, &token_count, TOKEN_RIGHT_BRACE, "}");
            pos++;
        } else if (ch == '[') {
            append_token(tokens, &token_count, TOKEN_LEFT_BRACKET, "[");
            pos++;
        } else if (ch == ']') {
            append_token(tokens, &token_count, TOKEN_RIGHT_BRACKET, "]");
            pos++;
        } else if (ch == ':') {
            append_token(tokens, &token_count, TOKEN_COLON, ":");
            pos++;
        } else if (ch == ',') {
            append_token(tokens, &token_count, TOKEN_COMMA, ",");
            pos++;
        } else if (ch == '"') {
            int start = ++pos;
            while (input[pos] != '"' && input[pos] != '' && input[pos] != '\0') { // Stop at ''
                pos++;
            }
            int len = pos - start;
            char* sval = malloc(len + 1);
            strncpy(sval, &input[start], len);
            sval[len] = '\0';
            append_token(tokens, &token_count, TOKEN_STRING, sval);
            free(sval);
            pos++;
        } else if (is_whitespace(ch)) {
            pos++;
        } else if (is_number(ch)) {
            int start = pos;
            while (is_number(input[pos])) {
                pos++;
            }
            int len = pos - start;
            char* numval = malloc(len + 1);
            strncpy(numval, &input[start], len);
            numval[len] = '\0';
            append_token(tokens, &token_count, TOKEN_NUMBER, numval);
            free(numval);
        } else if (strncmp(&input[pos], "true", 4) == 0) {
            append_token(tokens, &token_count, TOKEN_TRUE, "true");
            pos += 4;
        } else if (strncmp(&input[pos], "false", 5) == 0) {
            append_token(tokens, &token_count, TOKEN_FALSE, "false");
            pos += 5;
        } else if (strncmp(&input[pos], "null", 4) == 0) {
            append_token(tokens, &token_count, TOKEN_NULL, "null");
            pos += 4;
        } else {
            printf("Unknown character: %c\n", ch);
            exit(1);
        }
    }

    return tokens;
}

void parse_object(value* obj, token* tokens, int* token_index) {
    token tok = tokens[*token_index];

    if (tok.type != TOKEN_LEFT_BRACE) {
        printf("Syntax error: Expected opening brace\n");
        exit(1);
    }
    (*token_index)++;

    while (tokens[*token_index].type != TOKEN_RIGHT_BRACE) {
        token key_token = tokens[*token_index];
        if (key_token.type != TOKEN_STRING) {
            printf("Syntax error: Expected string key\n");
            exit(1);
        }

        obj->key = strdup(key_token.value);
        (*token_index)++;

        token colon_token = tokens[*token_index];
        if (colon_token.type != TOKEN_COLON) {
            printf("Syntax error: Expected colon\n");
            exit(1);
        }
        (*token_index)++;

        token value_token = tokens[*token_index];
        value parsed_value = parse_value(value_token);
        obj->as_union = parsed_value.as_union;
        (*token_index)++;

        token next_token = tokens[*token_index];
        if (next_token.type == TOKEN_COMMA) {
            (*token_index)++;
        } else if (next_token.type != TOKEN_RIGHT_BRACE) {
            printf("Syntax error: Expected comma or closing brace\n");
            exit(1);
        }
    }
    (*token_index)++;
}

value parse_value(token tok) {
    switch (tok.type) {
        case TOKEN_STRING:
            return (value){.as_union.string = strdup(tok.value)};
        case TOKEN_NUMBER:
            return (value){.as_union.number = atof(tok.value)};
        case TOKEN_TRUE:
            return (value){.as_union.boolean = 1};
        case TOKEN_FALSE:
            return (value){.as_union.boolean = 0};
        case TOKEN_NULL:
            return (value){.as_union.boolean = 0};
        default:
            printf("Unexpected token %d\n", tok.type);
            exit(1);
    }
}

value parse_json(const char* json_string) {
    token* tokens = lexer(json_string);
    int token_index = 0;

    value root = {0};
    parse_object(&root, tokens, &token_index);

    free(tokens);
    return root;
}


#endif /* JSONPARSERGARGI_H_ */
