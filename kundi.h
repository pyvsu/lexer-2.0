#include <stdio.h>

enum STATE { START, K, KU, KUN, KUND, KUNDI };
enum STATE state = START;
enum STATE Start(int c);
enum STATE k(int c);
enum STATE ku(int c);
enum STATE kun(int c);
enum STATE kund(int c);
enum STATE kundi(int c);
int kundiDFA(const char* str);

enum STATE Start(int c) {
    enum STATE state;
    if ((char)c == 'k')
        state = K;
    else
        state = START;
    return state;
}

enum STATE k(int c) {
    enum STATE state;
    if ((char)c == 'ku')
        state = KU;
    else
        state = START;
    return state;
}

enum STATE ku(int c) {
    enum STATE state;
    if ((char)c == 'n')
        state = KUN;
    else
        state = START;
    return state;
}

enum STATE kun(int c) {
    enum STATE state;
    if ((char)c == 'd')
        state = KUND;
    else
        state = START;
    return state;
}

enum STATE kund(int c) {
    enum STATE state;
    if ((char)c == 'i')
        state = KUNDI;
    else
        state = START;
    return state;
}

enum STATE kundi(int c) {
    enum STATE state = KUNDI;
    return state;
}

int kundiDFA(const char* str) {
    enum STATE state = START;

    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        if (state == START) {
            state = Start(str[i]);
        }

        else if (state == K) {
            state = k(str[i]);
        } else if (state == KU) {
            state = ku(str[i]);
        } else if (state == KUN) {
            state = kun(str[i]);
        } else if (state == KUND) {
            state = kund(str[i]);
        } else if (state == KUNDI) {
            return 1;
        }
    }
    return 0;
}