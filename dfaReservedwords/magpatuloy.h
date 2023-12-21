#include <stdio.h>

enum STATE {
    START,
    M,
    MA,
    MAG,
    MAGP,
    MAGPA,
    MAGPAT,
    MAGPATU,
    MAGPATUL,
    MAGPATULO,
    MAGPATULOY
};
enum STATE state = START;

enum STATE Start(int c);
enum STATE m(int c);
enum STATE ma(int c);
enum STATE mag(int c);
enum STATE magp(int c);
enum STATE magpa(int c);
enum STATE magpat(int c);
enum STATE magpatu(int c);
enum STATE magpatul(int c);
enum STATE magpatulo(int c);
enum STATE magpatuloy(int c);

int checkMagpatuloy(const char* str);

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
    if ((char)c == 'g')
        state = MAG;
    else
        state = START;
    return state;
}

enum STATE mag(int c) {
    enum STATE state = MAG;
    if ((char)c == 'p')
        state = MAGP;
    else
        state = START;
    return state;
}

enum STATE magp(int c) {
    enum STATE state = MAGP;
    if ((char)c == 'a')
        state = MAGPA;
    else
        state = START;
    return state;
}

enum STATE magpa(int c) {
    enum STATE state = MAGPA;
    if ((char)c == 't')
        state = MAGPAT;
    else
        state = START;
    return state;
}

enum STATE magpat(int c) {
    enum STATE state = MAGPAT;
    if ((char)c == 'u')
        state = MAGPATU;
    else
        state = START;
    return state;
}

enum STATE magpatu(int c) {
    enum STATE state = MAGPATU;
    if ((char)c == 'l')
        state = MAGPATUL;
    else
        state = START;
    return state;
}
enum STATE magpatul(int c) {
    enum STATE state = MAGPATUL;
    if ((char)c == 'o')
        state = MAGPATULO;
    else
        state = START;
    return state;
}

enum STATE magpatulo(int c) {
    enum STATE state = MAGPATULO;
    if ((char)c == 'y')
        state = MAGPATULOY;
    else
        state = START;
    return state;
}

enum STATE magpatuloy(int c) {
    enum STATE state = MAGPATULO;
    return state;
}

int checkMagpatuloy(const char* str) {
    enum STATE state = START;

    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        if (state == START) {
            state = Start(str[i]);
        }

        else if (state == M) {
            state = m(str[i]);
        } else if (state == MA) {
            state = ma(str[i]);
        } else if (state == MAG) {
            state = mag(str[i]);
        } else if (state == MAGP) {
            state = magp(str[i]);
        } else if (state == MAGPA) {
            state = magpa(str[i]);
        } else if (state == MAGPAT) {
            state = magpat(str[i]);
        } else if (state == MAGPATU) {
            state = magpatu(str[i]);
        } else if (state == MAGPATUL) {
            state = magpatul(str[i]);
        } else if (state == MAGPATULO) {
            state = magpatuloy(str[i]);
        } else if (state == MAGPATULOY) {
            return 1;
        }
    }
    return 0;
}