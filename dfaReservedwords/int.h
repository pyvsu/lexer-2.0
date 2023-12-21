#include <stdio.h>

enum STATE { START, I, IN, INT };
enum STATE state = START;

enum STATE Start(int c);
enum STATE i(int c);
enum STATE in(int c);
enum STATE intt(int c);
;
int checkInt(const char* str);

enum STATE Start(int c) {
    enum STATE state;
    if ((char)c == 'i')
        state = I;
    else
        state = START;
    return state;
}

enum STATE ii(int c) {
    enum STATE state = I;
    if ((char)c == 'n')
        state = IN;
    else
        state = START;
    return state;
}

enum STATE in(int c) {
    enum STATE state = IN;
    if ((char)c == 't')
        state = INT;
    else
        state = START;
    return state;
}

enum STATE intt(int c) {
    enum STATE state = IN;
    return state;
}

int checkInt(const char* str) {
    enum STATE state = START;

    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        if (state == START) {
            state = Start(str[i]);
        }

        else if (state == I) {
            state = ii(str[i]);
        } else if (state == IN) {
            state = in(str[i]);
        } else if (state == INT) {
            return 1;
        }
    }
    return 0;
}