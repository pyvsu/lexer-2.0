#include <stdio.h>

enum STATE { START, T, TA, TAM, TAMA };
enum STATE state = START;

enum STATE Start(int c);
enum STATE t(int c);
enum STATE ta(int c);
enum STATE tam(int c);
enum STATE tama(int c);

int checkTama(const char* str);

enum STATE Start(int c) {
    enum STATE state;
    if ((char)c == 't')
        state = T;
    else
        state = START;
    return state;
}

enum STATE t(int c) {
    enum STATE state = T;
    if ((char)c == 'a')
        state = TA;
    else
        state = START;
    return state;
}

enum STATE ta(int c) {
    enum STATE state = TA;
    if ((char)c == 'm')
        state = TAM;
    else
        state = START;
    return state;
}

enum STATE tam(int c) {
    enum STATE state = TAM;
    if ((char)c == 'a')
        state = TAMA;
    else
        state = START;
    return state;
}

enum STATE tama(int c) {
    enum STATE state = TAM;
    return state;
}

int checkTama(const char* str) {
    enum STATE state = START;

    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        if (state == START) {
            state = Start(str[i]);
        }

        else if (state == T) {
            state = t(str[i]);
        } else if (state == TA) {
            state = ta(str[i]);
        } else if (state == TAM) {
            state = tam(str[i]);
        } else if (state == TAMA) {
            return 1;
        }
    }
    return 0;
}