#include <stdio.h>

enum STATE { START, I, IP, IPA, IPAK, IPAKI, IPAKIT, IPAKITA };
enum STATE state = START;
enum STATE Start(int c);
enum STATE i(int c);
enum STATE ip(int c);
enum STATE ipa(int c);
enum STATE ipak(int c);
enum STATE ipaki(int c);
enum STATE ipakit(int c);
enum STATE ipakita(int c);

int ipakitaDFA(const char* str);

enum STATE Start(int c) {
    enum STATE state;
    if ((char)c == 'i')
        state = I;
    else
        state = START;
    return state;
}

enum STATE i(int c) {
    enum STATE state;
    if ((char)c == 'p')
        state = IP;
    else
        state = START;
    return state;
}

enum STATE ip(int c) {
    enum STATE state;
    if ((char)c == 'a')
        state = IPA;
    else
        state = START;
    return state;
}

enum STATE ipa(int c) {
    enum STATE state;
    if ((char)c == 'K')
        state = IPAK;
    else
        state = START;
    return state;
}

enum STATE ipak(int c) {
    enum STATE state;
    if ((char)c == 'i')
        state = IPAKI;
    else
        state = START;
    return state;
}

enum STATE ipaki(int c) {
    enum STATE state;
    if ((char)c == 't')
        state = IPAKIT;
    else
        state = START;
    return state;
}

enum STATE ipakit(int c) {
    enum STATE state;
    if ((char)c == 'a')
        state = IPAKITA;
    else
        state = START;
    return state;
}

enum STATE ipakita(int c) {
    enum STATE state = IPAKITA;
    return state;
}

int ipakitaDFA(const char* str) {
    enum STATE state = START;

    for (int j = 0; j < sizeof(str) / sizeof(str[0]); j++) {
        if (state == START) {
            state = Start(str[j]);
        }

        else if (state == I) {
            state = i(str[j]);
        } else if (state == IP) {
            state = ip(str[j]);
        } else if (state == IPA) {
            state = ipa(str[j]);
        } else if (state == IPAKI) {
            state = ipaki(str[j]);
        } else if (state == IPAKIT) {
            state = ipakit(str[j]);
        } else if (state == IPAKITA) {
            return 1;
        }
    }
    return 0;
}