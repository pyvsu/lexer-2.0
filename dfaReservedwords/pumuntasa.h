#include <stdio.h>

enum STATE {
    START,
    P,
    PU,
    PUM,
    PUMU,
    PUMUN,
    PUMUNT,
    PUMUNTA,
    PUMUNTAS,
    PUMUNTASA
};
enum STATE state = START;

enum STATE Start(int c);
enum STATE p(int c);
enum STATE pu(int c);
enum STATE pum(int c);
enum STATE pumu(int c);
enum STATE pumun(int c);
enum STATE pumunt(int c);
enum STATE pumunta(int c);
enum STATE pumuntas(int c);
enum STATE pumuntasa(int c);

int checkPumuntasa(const char* str);

enum STATE Start(int c) {
    enum STATE state;
    if ((char)c == 'p')
        state = P;
    else
        state = START;
    return state;
}

enum STATE p(int c) {
    enum STATE state = P;
    if ((char)c == 'u')
        state = PU;
    else
        state = START;
    return state;
}

enum STATE pu(int c) {
    enum STATE state = PU;
    if ((char)c == 'm')
        state = PUM;
    else
        state = START;
    return state;
}

enum STATE pum(int c) {
    enum STATE state = PUM;
    if ((char)c == 'u')
        state = PUMU;
    else
        state = START;
    return state;
}

enum STATE pumu(int c) {
    enum STATE state = PUMU;
    if ((char)c == 'n')
        state = PUMUN;
    else
        state = START;
    return state;
}

enum STATE pumun(int c) {
    enum STATE state = PUMUN;
    if ((char)c == 't')
        state = PUMUNT;
    else
        state = START;
    return state;
}

enum STATE pumunt(int c) {
    enum STATE state = PUMUNT;
    if ((char)c == 'a')
        state = PUMUNTA;
    else
        state = START;
    return state;
}

enum STATE pumunta(int c) {
    enum STATE state = PUMUNTA;
    if ((char)c == 's')
        state = PUMUNTA;
    else
        state = START;
    return state;
}
enum STATE pumuntas(int c) {
    enum STATE state = PUMUNTAS;
    if ((char)c == 'a')
        state = PUMUNTASA;
    else
        state = START;
    return state;
}

enum STATE pumuntasa(int c) {
    enum STATE state = PUMUNTAS;
    return state;
}

int checkPumuntasay(const char* str) {
    enum STATE state = START;

    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        if (state == START) {
            state = Start(str[i]);
        }

        else if (state == P) {
            state = p(str[i]);
        } else if (state == PU) {
            state = pu(str[i]);
        } else if (state == PUM) {
            state = pum(str[i]);
        } else if (state == PUMU) {
            state = pumu(str[i]);
        } else if (state == PUMUN) {
            state = pumun(str[i]);
        } else if (state == PUMUNT) {
            state = pumunt(str[i]);
        } else if (state == PUMUNTA) {
            state = pumunta(str[i]);
        } else if (state == PUMUNTAS) {
            state = pumuntas(str[i]);
        } else if (state == PUMUNTASA) {
            return 1;
        }
    }
    return 0;
}
