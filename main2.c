#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: For checking only, delete later
const char *keywords[] = {"balik", "ipakita", "kundi", "pangungusap",
                          "para",  "pasok",   "tigil", "walangbalik"};

const char *reserved_words[] = {"bool",      "des",    "int",
                                "kar",       "mali",   "magpatuloy",
                                "pumuntasa", "simula", "tama"};

int is_keyword(const char *str) {
    int len = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < len; ++i) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_reserved_word(const char *str) {
    int len = sizeof(reserved_words) / sizeof(reserved_words[0]);

    for (int i = 0; i < len; ++i) {
        if (strcmp(str, reserved_words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
// DELETE UP TIL HERE

enum {
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_ASSIGN,
    TOKEN_ADD_ASSIGN,
    TOKEN_SUB_ASSIGN,
    TOKEN_MUL_ASSIGN,
    TOKEN_DIV_ASSIGN,
    TOKEN_INCREMENT,
    TOKEN_DECREMENT,
    TOKEN_EQUAL,
    TOKEN_LESS_THAN,
    TOKEN_GREATER_THAN,
    TOKEN_LESS_THAN_EQUAL,
    TOKEN_GREATER_THAN_EQUAL,
    TOKEN_NOT_EQUAL,
    TOKEN_MODULUS,
    TOKEN_MODULUS_ASSIGN,
    TOKEN_EXPONENT,
    TOKEN_OPEN_CURLY_BRACE,
    TOKEN_CLOSE_CURLY_BRACE,
    TOKEN_OPEN_PARENTHESIS,
    TOKEN_CLOSE_PARENTHESIS,
    TOKEN_OPEN_SQUARE_BRACKET,
    TOKEN_CLOSE_SQUARE_BRACKET,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    TOKEN_SEMICOLON,
    TOKEN_EOF
};

typedef struct {
    FILE *inputFile;
    FILE *outputFile;
    char current_char;
    char next_char;
} Lexer;

Lexer *create_lexer(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (strlen(filename) <= 3 ||
        strcmp(filename + strlen(filename) - 3, ".ms") != 0) {
        fprintf(stderr, "Error: Input file must have the '.ms' extension.\n");
        exit(1);
    }

    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
    lexer->inputFile = file;
    lexer->outputFile = fopen("symbol_table.txt", "w");
    lexer->current_char = fgetc(file);
    lexer->next_char = fgetc(file);

    return lexer;
}

char get_current_char(Lexer *lexer) { return lexer->current_char; }

char get_next_char(Lexer *lexer) { return lexer->next_char; }

void move_to_next(Lexer *lexer) {
    lexer->current_char = lexer->next_char;
    lexer->next_char = fgetc(lexer->inputFile);
}

void close_lexer(Lexer *lexer) {
    fclose(lexer->inputFile);
    fclose(lexer->outputFile);
    free(lexer);
}

void process_file(Lexer *lexer) {
    while (lexer->current_char != EOF) {
        if (lexer->current_char == '^') {
            char comment[1000];
            int idx = 0;
            comment[idx++] = lexer->current_char;
            move_to_next(lexer);

            while (lexer->current_char != '\n' && lexer->current_char != EOF) {
                comment[idx++] = lexer->current_char;
                move_to_next(lexer);
            }
            comment[idx] = '\0';

            fprintf(lexer->outputFile, "%-20s%s\n", comment,
                    "SINGLE LINE COMMENT");
            continue;
        }

        // Check if word is resword, keyword, or identifier
        if (isalpha(lexer->current_char)) {
            char value[100];
            int idx = 0;
            while (isalnum(lexer->current_char) || lexer->current_char == '_' ||
                   lexer->current_char == '.') {
                value[idx++] = lexer->current_char;
                move_to_next(lexer);
            }
            value[idx] = '\0';

            if (idx > 0 &&
                (isalpha(value[idx - 1]) || isdigit(value[idx - 1]))) {
                if (is_reserved_word(value)) {
                    fprintf(lexer->outputFile, "%-20sRESERVED WORD\n", value);
                } else if (is_keyword(value)) {
                    fprintf(lexer->outputFile, "%-20sKEYWORD\n", value);
                } else {
                    fprintf(lexer->outputFile, "%-20sIDENTIFIER\n", value);
                }
            } else {
                printf("Invalid identifier: %s\n", value);
            }
            continue;
        }

        // Check if digit is int or float
        if (isdigit(lexer->current_char) || lexer->current_char == '.') {
            char value[100];
            int idx = 0;
            int dotCount = 0;

            while (isdigit(lexer->current_char) || lexer->current_char == '.') {
                if (lexer->current_char == '.') {
                    dotCount++;
                }
                if (dotCount > 1) {
                    break;
                }
                value[idx++] = lexer->current_char;
                move_to_next(lexer);
            }
            value[idx] = '\0';

            if (dotCount == 1 &&
                ((isdigit(value[idx - 1]) && isdigit(value[0])) ||
                 (value[idx - 1] == '.' && isdigit(value[0])))) {
                fprintf(lexer->outputFile, "%-20sFLOAT\n", value);
            } else if (dotCount == 0 &&
                       (isalpha(value[idx - 1]) || isdigit(value[idx - 1]))) {
                fprintf(lexer->outputFile, "%-20sINTEGER\n", value);
            } else {
                printf("Invalid number: %s\n", value);
            }
            continue;
        }

        // operators
        switch (lexer->current_char) {
            case '+':
                if (lexer->next_char == '=') {
                    fprintf(lexer->outputFile, "%-20sADD_ASSIGN\n", "+=");
                    move_to_next(lexer);
                } else if (lexer->next_char == '+') {
                    fprintf(lexer->outputFile, "%-20sINCREMENT\n", "++");
                    move_to_next(lexer);
                } else {
                    fprintf(lexer->outputFile, "%-20sPLUS\n", "+");
                }
                break;
            case '-':
                if (lexer->next_char == '=') {
                    fprintf(lexer->outputFile, "%-20sSUB_ASSIGN\n", "-=");
                    move_to_next(lexer);
                } else if (lexer->next_char == '-') {
                    fprintf(lexer->outputFile, "%-20sDECREMENT\n", "--");
                    move_to_next(lexer);
                } else {
                    fprintf(lexer->outputFile, "%-20sMINUS\n", "-");
                }
                break;
            case '*':
                if (lexer->next_char == '=') {
                    fprintf(lexer->outputFile, "%-20sMUL_ASSIGN\n", "*=");
                    move_to_next(lexer);
                } else {
                    fprintf(lexer->outputFile, "%-20sMULTIPLY\n", "*");
                }
                break;
            case '/':
                if (lexer->next_char == '=') {
                    fprintf(lexer->outputFile, "%-20sDIV_ASSIGN\n", "/=");
                    move_to_next(lexer);
                } else {
                    fprintf(lexer->outputFile, "%-20sDIVIDE\n", "/");
                }
                break;
            case '=':
                if (lexer->next_char == '=') {
                    fprintf(lexer->outputFile, "%-20sEQUAL\n", "==");
                    move_to_next(lexer);
                } else {
                    fprintf(lexer->outputFile, "%-20sASSIGN\n", "=");
                }
                break;
            case '<':
                if (lexer->next_char == '=') {
                    fprintf(lexer->outputFile, "%-20sLESS_THAN_EQUAL\n", "<=");
                    move_to_next(lexer);
                } else {
                    fprintf(lexer->outputFile, "%-20sLESS_THAN\n", "<");
                }
                break;
            case '>':
                if (lexer->next_char == '=') {
                    fprintf(lexer->outputFile, "%-20sGREATER_THAN_EQUAL\n",
                            ">=");
                    move_to_next(lexer);
                } else {
                    fprintf(lexer->outputFile, "%-20sGREATER_THAN\n", ">");
                }
                break;
            case '!':
                if (lexer->next_char == '=') {
                    fprintf(lexer->outputFile, "%-20sNOT_EQUAL\n", "!=");
                    move_to_next(lexer);
                } else {
                    printf("Invalid character: %c\n", lexer->current_char);
                }
                break;
            case '%':
                if (lexer->next_char == '=') {
                    fprintf(lexer->outputFile, "%-20sMODULUS_ASSIGN\n", "%=");
                    move_to_next(lexer);
                } else {
                    fprintf(lexer->outputFile, "%-20sMODULUS\n", "%");
                }
                break;
            case ':':
                fprintf(lexer->outputFile, "%-20sEXPONENT\n", ":");
                break;
            case '{':
                fprintf(lexer->outputFile, "%-20sOPEN_CURLY_BRACE\n", "{");
                break;
            case '}':
                fprintf(lexer->outputFile, "%-20sCLOSE_CURLY_BRACE\n", "}");
                break;
            case '(':
                fprintf(lexer->outputFile, "%-20sOPEN_PARENTHESIS\n", "(");
                break;
            case ')':
                fprintf(lexer->outputFile, "%-20sCLOSE_PARENTHESIS\n", ")");
                break;
            case '[':
                fprintf(lexer->outputFile, "%-20sOPEN_SQUARE_BRACKET\n", "[");
                break;
            case ']':
                fprintf(lexer->outputFile, "%-20sCLOSE_SQUARE_BRACKET\n", "]");
                break;
            case '|':
                fprintf(lexer->outputFile, "%-20sOR\n", "|");
                break;

            case '@':
                fprintf(lexer->outputFile, "%-20sAND\n", "@");
                break;
            case '~':
                fprintf(lexer->outputFile, "%-20sNOT\n", "~");
                break;
            case ';':
                fprintf(lexer->outputFile, "%-20sSEMICOLON\n", ";");
                break;
            default:
                printf("Invalid character: %c\n", lexer->current_char);
                break;
        }
        move_to_next(lexer);
    }
    fprintf(lexer->outputFile, "%-20sEOF\n", "EOF");
}

int main() {
    const char *filename = "test.ms";
    Lexer *lexer = create_lexer(filename);
    if (!lexer) {
        return 1;
    }

    process_file(lexer);

    close_lexer(lexer);

    return 0;
}
