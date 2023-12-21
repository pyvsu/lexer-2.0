#include <stdio.h>

enum STATE { START, B, BA, BAL, BALI, BALIK };
enum STATE state = START;
enum STATE Start(int c);
enum STATE b(int c);
enum STATE ba(int c);
enum STATE bal(int c);
enum STATE bali(int c);
enum STATE balik(int c);
int balikDFA(const char* str);

enum STATE Start(int c) {
    enum STATE state;
    if ((char)c == 'b')
        state = B;
    else
        state = START;
    return state;
}

enum STATE b(int c) {
    enum STATE state = B;
    if ((char)c == 'a')
        state = BA;
    else
        state = START;
    return state;
}

enum STATE ba(int c) {
    enum STATE state = BA;
    if ((char)c == 'l')
        state = BAL;
    else
        state = START;
    return state;
}

enum STATE bal(int c) {
    enum STATE state = BAL;
    if ((char)c == 'i')
        state = BALI;
    else
        state = START;
    return state;
}

enum STATE bali(int c) {
    enum STATE state = BALI;
    if ((char)c == 'k')
        state = BALIK;
    else
        state = START;
    return state;
}

enum STATE balik(int c) {
    enum STATE state = BALIK;
    return state;
}

int balikDFA(const char* str) {
    enum STATE state = START;

    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        if (state == START) {
            state = Start(str[i]);
        }

        else if (state == B) {
            state = b(str[i]);
        } else if (state == BA) {
            state = ba(str[i]);
        } else if (state == BAL) {
            state = bal(str[i]);
        } else if (state == BALI) {
            state = bali(str[i]);
        } else if (state == BALIK) {
            return 1;
        }
    }
    return 0;
}
