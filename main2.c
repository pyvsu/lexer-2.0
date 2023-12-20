#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
                fprintf(lexer->outputFile, "%-20sIDENTIFIER\n", value);
            } else {
                printf("Invalid identifier: %s\n", value);
            }
            continue;
        }

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
                } else if (lexer->next_char == '/') {
                    fprintf(lexer->outputFile, "%-20sOR\n", "//");
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
                fprintf(lexer->outputFile, "%-20sMODULUS\n", "%");
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
    const char *filename =  "test.ms";
    Lexer *lexer = create_lexer(filename);
    if (!lexer) {
        return 1;
    }

    process_file(lexer);

    close_lexer(lexer);

    return 0;
}
