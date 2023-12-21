#include <stdio.h>

enum STATE { START, K, KA, KAR };
enum STATE state = START;

enum STATE Start(int c);
enum STATE k(int c);
enum STATE ka(int c);
enum STATE kar(int c);
;
int checkKar(const char* str);

enum STATE Start(int c) {
    enum STATE state;
    if ((char)c == 'k')
        state = K;
    else
        state = START;
    return state;
}

enum STATE k(int c) {
    enum STATE state = K;
    if ((char)c == 'a')
        state = KA;
    else
        state = START;
    return state;
}

enum STATE ka(int c) {
    enum STATE state = KA;
    if ((char)c == 'r')
        state = KAR;
    else
        state = START;
    return state;
}

enum STATE kar(int c) {
    enum STATE state = KA;
    return state;
}

int checkInt(const char* str) {
    enum STATE state = START;

    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        if (state == START) {
            state = Start(str[i]);
        }

        else if (state == K) {
            state = k(str[i]);
        } else if (state == KA) {
            state = ka(str[i]);
        } else if (state == KAR) {
            return 1;
        }
    }
    return 0;
}