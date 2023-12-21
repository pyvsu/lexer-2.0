#include <stdio.h>

enum STATE { START, M, MA, MAL, MALI };
enum STATE state = START;

enum STATE Start(int c);
enum STATE m(int c);
enum STATE ma(int c);
enum STATE mal(int c);
enum STATE mali(int c);

int checkMali(const char* str);

enum STATE Start(int c) {
    enum STATE state;
    if ((char)c == 'm')
        state = M;
    else
        state = START;
    return state;
}

enum STATE m(int c) {
    enum STATE state = M;
    if ((char)c == 'a')
        state = MA;
    else
        state = START;
    return state;
}

enum STATE ma(int c) {
    enum STATE state = MA;
    if ((char)c == 'l')
        state = MAL;
    else
        state = START;
    return state;
}

enum STATE mal(int c) {
    enum STATE state = MAL;
    if ((char)c == 'i')
        state = MALI;
    else
        state = START;
    return state;
}

enum STATE mali(int c) {
    enum STATE state = MAL;
    return state;
}

int checkBool(const char* str) {
    enum STATE state = START;

    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        if (state == START) {
            state = Start(str[i]);
        }

        else if (state == M) {
            state = m(str[i]);
        } else if (state == MA) {
            state = ma(str[i]);
        } else if (state == MAL) {
            state = mal(str[i]);
        } else if (state == MALI) {
            return 1;
        }
    }
    return 0;
}