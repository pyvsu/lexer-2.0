#include <stdio.h>

enum STATE { START, S, SI, SIM, SIMU, SIMUL, SIMULA };
enum STATE state = START;

enum STATE Start(int c);
enum STATE s(int c);
enum STATE si(int c);
enum STATE sim(int c);
enum STATE simu(int c);
enum STATE simul(int c);
enum STATE simula(int c);

int checkSimula(const char* str);

enum STATE Start(int c) {
    enum STATE state;
    if ((char)c == 's')
        state = S;
    else
        state = START;
    return state;
}

enum STATE s(int c) {
    enum STATE state = S;
    if ((char)c == 'i')
        state = SI;
    else
        state = START;
    return state;
}

enum STATE si(int c) {
    enum STATE state = SI;
    if ((char)c == 'm')
        state = SIM;
    else
        state = START;
    return state;
}

enum STATE sim(int c) {
    enum STATE state = SIM;
    if ((char)c == 'u')
        state = SIMU;
    else
        state = START;
    return state;
}
enum STATE simu(int c) {
    enum STATE state = SIMU;
    if ((char)c == 'l')
        state = SIMUL;
    else
        state = START;
    return state;
}

enum STATE simul(int c) {
    enum STATE state = SIMUL;
    if ((char)c == 'a')
        state = SIMULA;
    else
        state = START;
    return state;
}

enum STATE simula(int c) {
    enum STATE state = SIMUL;
    return state;
}

int checkSimula(const char* str) {
    enum STATE state = START;

    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        if (state == START) {
            state = Start(str[i]);
        }

        else if (state == S) {
            state = s(str[i]);
        } else if (state == SI) {
            state = si(str[i]);
        } else if (state == SIM) {
            state = sim(str[i]);
        } else if (state == SIMU) {
            state = simu(str[i]);
        } else if (state == SIMUL) {
            state = simul(str[i]);
        } else if (state == SIMULA) {
            return 1;
        }
    }
    return 0;
}