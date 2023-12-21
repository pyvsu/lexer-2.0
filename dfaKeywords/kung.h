#include <stdio.h>

enum STATE { START, K, KU, KUN, KUNG};
enum STATE state = START;
enum STATE Start(int c);
enum STATE k(int c);
enum STATE ku(int c);
enum STATE kun(int c);
enum STATE kung(int c);
int kungDFA(const char* str);

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
    if ((char)c == 'k')
        state = K;
    else
        state = START;
    return state;
}