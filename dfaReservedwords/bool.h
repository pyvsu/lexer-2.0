#include <stdio.h>

enum STATE { START, B, BO, BOO, BOOL };
enum STATE state = START;

enum STATE Start(int c);
enum STATE b(int c);
enum STATE bo(int c);
enum STATE boo(int c);
enum STATE booll(int c);

int checkBalik(const char* str);

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
    if ((char)c == 'o')
        state = BO;
    else
        state = START;
    return state;
}

enum STATE bo(int c) {
    enum STATE state = BO;
    if ((char)c == 'o')
        state = BOO;
    else
        state = START;
    return state;
}

enum STATE boo(int c) {
    enum STATE state = BOO;
    if ((char)c == 'l')
        state = BOOL;
    else
        state = START;
    return state;
}

enum STATE booll(int c) {
    enum STATE state = BOO;
    return state;
}

int checkBool(const char* str) {
    enum STATE state = START;

    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        if (state == START) {
            state = Start(str[i]);
        }

        else if (state == B) {
            state = b(str[i]);
        } else if (state == BO) {
            state = bo(str[i]);
        } else if (state == BOO) {
            state = boo(str[i]);
        } else if (state == BOOL) {
            return 1;
        }
    }
    return 0;
}