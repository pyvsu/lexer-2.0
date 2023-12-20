#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "path/to/balik.h"

// Token types
enum {
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SEMICOLON,
    TOKEN_STRING,
    TOKEN_SINGLECOMMENTLINE,
    TOKEN_KEYWORD,
    TOKEN_RESERVED_WORD,
    TOKEN_EOF
};

const char* keywords[] = {"balik", "ipakita", "kundi", "pangungusap",
                          "para",  "pasok",   "tigil", "walangbalik"};

const char* reserved_words[] = {"bool",      "des",    "int",
                                "kar",       "mali",   "magpatuloy",
                                "pumuntasa", "simula", "tama"};

// Token structure
typedef struct {
    int type;
    char* value;
} Token;

// Lexer structure
typedef struct {
    FILE* inputFile;
    FILE* outputFile;
} Lexer;

// TODO: For checking purposes, delete later
int is_keyword(const char* str) { return 0; }

int is_reserved_word(const char* str) {
    int len = sizeof(reserved_words) / sizeof(reserved_words[0]);

    for (int i = 0; i < len; ++i) {
        if (strcmp(str, reserved_words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to create a token
Token* create_token(int type, char* value) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->value = strdup(value);
    return token;
}

// Function to free memory used by tokens
void free_token(Token* token) {
    free(token->value);
    free(token);
}

// Function to tokenize input string
Token** tokenize(const char* input) {
    int len = strlen(input);
    int idx = 0;
    Token** tokens =
        (Token**)malloc((len + 1) * sizeof(Token*));  // Add one for EOF token
    int tokens_count = 0;

    while (idx < len) {
        char current_char = input[idx];

        // Skipping spaces and tabs
        if (current_char == ' ' || current_char == '\t') {
            idx++;
            continue;
        }

        if (current_char == '^') {
            int start = idx;
            while (input[idx] != '\0' && input[idx] != '\n') {
                idx++;
            }
            char* value = (char*)malloc((idx - start + 1) * sizeof(char));
            strncpy(value, input + start, idx - start);
            value[idx - start] = '\0';

            // Check if it's the first occurrence of the comment
            if (tokens_count == 0 ||
                tokens[tokens_count - 1]->type != TOKEN_SINGLECOMMENTLINE) {
                tokens[tokens_count++] =
                    create_token(TOKEN_SINGLECOMMENTLINE, value);
            }
            continue;
        }

        // Tokenizing numbers
        if (isdigit(current_char)) {
            int start = idx;
            while (isdigit(input[idx]) || input[idx] == '.') {
                idx++;
            }
            char* value = (char*)malloc((idx - start + 1) * sizeof(char));
            strncpy(value, input + start, idx - start);
            value[idx - start] = '\0';

            if (strchr(value, '.') != NULL) {
                tokens[tokens_count++] = create_token(TOKEN_FLOAT, value);
            } else {
                tokens[tokens_count++] = create_token(TOKEN_INT, value);
            }
            continue;
        }

        // Classify if lexeme is reserved word, keyword, or identifier
        if (isalpha(current_char)) {
            int start = idx;

            while (isalnum(input[idx])) {
                idx++;
            }

            char* value = (char*)malloc((idx - start + 1) * sizeof(char));
            strncpy(value, input + start, idx - start);
            value[idx - start] = '\0';

            if (is_reserved_word(value)) {
                tokens[tokens_count++] =
                    create_token(TOKEN_RESERVED_WORD, value);
                continue;
            } else if (checkBalik(value)) {
                tokens[tokens_count++] = create_token(TOKEN_KEYWORD, value);
                continue;
            } else {
                tokens[tokens_count++] = create_token(TOKEN_IDENTIFIER, value);
                continue;
            }
        }

        // Tokenizing strings
        if (current_char == '"') {
            int start = ++idx;  // Skip the opening quote
            while (input[idx] != '\0' && input[idx] != '"') {
                idx++;
            }

            if (input[idx] == '\0') {
                printf("Error: Unterminated string\n");
                exit(1);
            }

            char* value = (char*)malloc((idx - start + 1) * sizeof(char));
            strncpy(value, input + start, idx - start);
            value[idx - start] = '\0';
            tokens[tokens_count++] = create_token(TOKEN_STRING, value);
            idx++;  // Skip the closing quote
            continue;
        }

        // Tokenizing operators and delimiters
        switch (current_char) {
            case '+':
                tokens[tokens_count++] = create_token(TOKEN_PLUS, "+");
                break;
            case '-':
                tokens[tokens_count++] = create_token(TOKEN_MINUS, "-");
                break;
            case '*':
                tokens[tokens_count++] = create_token(TOKEN_MULTIPLY, "*");
                break;
            case '/':
                tokens[tokens_count++] = create_token(TOKEN_DIVIDE, "/");
                break;
            case '(':
                tokens[tokens_count++] = create_token(TOKEN_LPAREN, "(");
                break;
            case ')':
                tokens[tokens_count++] = create_token(TOKEN_RPAREN, ")");
                break;
            case ';':
                tokens[tokens_count++] = create_token(TOKEN_SEMICOLON, ";");
                break;
            default:
                printf("Invalid character: %c\n", current_char);
                break;
        }

        idx++;
    }

    tokens[tokens_count] = create_token(TOKEN_EOF, "EOF");
    return tokens;
}

// Function to read input from file
char* read_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(file_size + 1);
    if (!buffer) {
        fclose(file);
        printf("Memory allocation failed.\n");
        exit(1);
    }

    fread(buffer, 1, file_size, file);
    fclose(file);
    buffer[file_size] = '\0';
    return buffer;
}

void process_file(const char* inputFileName) {
    Lexer lexer;

    if (strlen(inputFileName) <= 3 ||
        strcmp(inputFileName + strlen(inputFileName) - 3, ".ms") != 0) {
        fprintf(stderr, "Error: Input file must have the '.ms' extension.\n");
        exit(1);
    }

    lexer.inputFile = fopen(inputFileName, "r");
    lexer.outputFile = fopen("symbol_table.txt", "w");

    if (lexer.inputFile == NULL || lexer.outputFile == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fprintf(lexer.outputFile, "Lexemes\t\tTokens\n");  // Headers

    int idx = 0;
    char* inputBuffer = read_from_file(inputFileName);
    Token** tokens = tokenize(inputBuffer);

    while (tokens[idx]->type != TOKEN_EOF) {
        const char* type_name;
        switch (tokens[idx]->type) {
            case TOKEN_INT:
                type_name = "INTEGER";
                break;
            case TOKEN_FLOAT:
                type_name = "FLOAT";
                break;
            case TOKEN_RESERVED_WORD:
                type_name = "RESERVED WORD";
                break;
            case TOKEN_KEYWORD:
                type_name = "KEYWORD";
                break;
            case TOKEN_IDENTIFIER:
                type_name = "IDENTIFIER";
                break;
            case TOKEN_PLUS:
                type_name = "PLUS";
                break;
            case TOKEN_MINUS:
                type_name = "MINUS";
                break;
            case TOKEN_MULTIPLY:
                type_name = "MULTIPLY";
                break;
            case TOKEN_DIVIDE:
                type_name = "DIVIDE";
                break;
            case TOKEN_LPAREN:
                type_name = "LPAREN";
                break;
            case TOKEN_RPAREN:
                type_name = "RPAREN";
                break;
            case TOKEN_SEMICOLON:
                type_name = "SEMICOLON";
                break;
            case TOKEN_STRING:
                type_name = "STRING";
                fprintf(lexer.outputFile, "\"%s\"\t\t%s\n", tokens[idx]->value,
                        type_name);
                break;
            case TOKEN_SINGLECOMMENTLINE:
                type_name = "SINGLE COMMENT LINE";
                fprintf(lexer.outputFile, "%s\t\t%s\n", tokens[idx]->value,
                        type_name);
                break;
            default:
                type_name = "INVALID";
                break;
        }

        if (tokens[idx]->type != TOKEN_STRING &&
            tokens[idx]->type != TOKEN_SINGLECOMMENTLINE) {
            fprintf(lexer.outputFile, "%s\t\t\t%s\n", tokens[idx]->value,
                    type_name);
        }

        idx++;
    }

    fclose(lexer.inputFile);
    fclose(lexer.outputFile);

    // Free allocated memory
    free(inputBuffer);
    idx = 0;
    while (tokens[idx]->type != TOKEN_EOF) {
        free_token(tokens[idx]);
        idx++;
    }
    free(tokens);
}

// Main function
int main() {
    const char* filename = "test.ms";
    process_file(filename);

    return 0;
}
