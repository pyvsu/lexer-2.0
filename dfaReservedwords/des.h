#include <stdio.h>

enum STATE { START, D, DE, DES };
enum STATE state = START;

enum STATE Start(int c);
enum STATE d(int c);
enum STATE de(int c);
enum STATE des(int c);
;
int checkDes(const char* str);

enum STATE Start(int c) {
    enum STATE state;
    if ((char)c == 'd')
        state = D;
    else
        state = START;
    return state;
}

enum STATE d(int c) {
    enum STATE state = D;
    if ((char)c == 'a')
        state = DE;
    else
        state = START;
    return state;
}

enum STATE de(int c) {
    enum STATE state = DE;
    if ((char)c == 'l')
        state = DES;
    else
        state = START;
    return state;
}

enum STATE des(int c) {
    enum STATE state = DE;
    return state;
}

int checkDes(const char* str) {
    enum STATE state = START;

    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        if (state == START) {
            state = Start(str[i]);
        }

        else if (state == D) {
            state = d(str[i]);
        } else if (state == DE) {
            state = de(str[i]);
        } else if (state == DES) {
            return 1;
        }
    }
    return 0;
}