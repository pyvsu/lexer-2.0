#include <stdio.h>
#include <string.h>

enum RW_State {
    RW_STATE_0,
    RW_STATE_1,
    RW_STATE_2,
    RW_STATE_3,
    RW_STATE_4,
    RW_STATE_5,
    RW_STATE_6,
    RW_STATE_7,
    RW_STATE_8,
    RW_STATE_9,
    RW_STATE_10,
    RW_STATE_11,
    RW_STATE_12,
    RW_STATE_13,
    RW_STATE_14,
    RW_STATE_15,
    RW_STATE_16,
    RW_STATE_17,
    RW_STATE_18,
    RW_STATE_19,
    RW_STATE_20,
    RW_STATE_21,
    RW_STATE_22,
    RW_STATE_23,
    RW_STATE_24,
    RW_STATE_25,
    RW_STATE_26,
    RW_STATE_27,
    RW_STATE_28,
    RW_STATE_29,
    RW_STATE_30,
    RW_STATE_31,
    RW_STATE_32,
    RW_STATE_33,
    RW_STATE_34,
    RW_STATE_35,
    RW_STATE_ACCEPTED
};

int classifyReservedWord(const char *keyword) {
    enum RW_State currentState = RW_STATE_0;
    int idx;

    for (idx = 0; idx < strlen(keyword); idx++) {
        char c = keyword[idx];

        switch (currentState) {
            case RW_STATE_0:
                switch (c) {
                    case 'b':
                        currentState = RW_STATE_1;
                        break;
                    case 'd':
                        currentState = RW_STATE_4;
                        break;
                    case 'i':
                        currentState = RW_STATE_6;
                        break;
                    case 'k':
                        currentState = RW_STATE_8;
                        break;
                    case 'm':
                        currentState = RW_STATE_10;
                        break;
                    case 'p':
                        currentState = RW_STATE_20;
                        break;
                    case 's':
                        currentState = RW_STATE_28;
                        break;
                    case 't':
                        currentState = RW_STATE_33;
                        break;
                    default:
                        return 0;
                }
                break;

            // bool branch
            case RW_STATE_1:
                if (c == 'o') {
                    currentState = RW_STATE_2;
                } else
                    return 0;
                break;

            case RW_STATE_2:
                if (c == 'o') {
                    currentState = RW_STATE_3;
                } else
                    return 0;
                break;

            case RW_STATE_3:
                if (c == 'l') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;

            // des branch
            case RW_STATE_4:
                if (c == 'e') {
                    currentState = RW_STATE_5;
                } else
                    return 0;
                break;

            case RW_STATE_5:
                if (c == 's') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;

            // int branch
            case RW_STATE_6:
                if (c == 'n') {
                    currentState = RW_STATE_7;
                } else
                    return 0;
                break;

            case RW_STATE_7:
                if (c == 't') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;

            // kar branch
            case RW_STATE_8:
                if (c == 'a') {
                    currentState = RW_STATE_9;
                } else
                    return 0;
                break;

            case RW_STATE_9:
                if (c == 'r') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;

            // mali branch
            case RW_STATE_10:
                if (c == 'a') {
                    currentState = RW_STATE_11;
                } else
                    return 0;
                break;

            case RW_STATE_11:
                if (c == 'l') {
                    currentState = RW_STATE_12;
                } else if (c == 'g') {
                    currentState = RW_STATE_13;
                } else
                    return 0;
                break;

            case RW_STATE_12:
                if (c == 'i') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;

            // magpatuloy branch
            case RW_STATE_13:
                if (c == 'p') {
                    currentState = RW_STATE_14;
                } else
                    return 0;
                break;

            case RW_STATE_14:
                if (c == 'a') {
                    currentState = RW_STATE_15;
                } else
                    return 0;
                break;

            case RW_STATE_15:
                if (c == 't') {
                    currentState = RW_STATE_16;
                } else
                    return 0;
                break;

            case RW_STATE_16:
                if (c == 'u') {
                    currentState = RW_STATE_17;
                } else
                    return 0;
                break;

            case RW_STATE_17:
                if (c == 'l') {
                    currentState = RW_STATE_18;
                } else
                    return 0;
                break;

            case RW_STATE_18:
                if (c == 'o') {
                    currentState = RW_STATE_19;
                } else
                    return 0;
                break;

            case RW_STATE_19:
                if (c == 'y') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;

            // pumuntasa branch
            case RW_STATE_20:
                if (c == 'u') {
                    currentState = RW_STATE_21;
                } else
                    return 0;
                break;

            case RW_STATE_21:
                if (c == 'm') {
                    currentState = RW_STATE_22;
                } else
                    return 0;
                break;

            case RW_STATE_22:
                if (c == 'u') {
                    currentState = RW_STATE_23;
                } else
                    return 0;
                break;

            case RW_STATE_23:
                if (c == 'n') {
                    currentState = RW_STATE_24;
                } else
                    return 0;
                break;

            case RW_STATE_24:
                if (c == 't') {
                    currentState = RW_STATE_25;
                } else
                    return 0;
                break;

            case RW_STATE_25:
                if (c == 'a') {
                    currentState = RW_STATE_26;
                } else
                    return 0;
                break;

            case RW_STATE_26:
                if (c == 's') {
                    currentState = RW_STATE_27;
                } else
                    return 0;
                break;

            case RW_STATE_27:
                if (c == 'a') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;

            // simula branch
            case RW_STATE_28:
                if (c == 'i') {
                    currentState = RW_STATE_29;
                } else
                    return 0;
                break;

            case RW_STATE_29:
                if (c == 'm') {
                    currentState = RW_STATE_30;
                } else
                    return 0;
                break;

            case RW_STATE_30:
                if (c == 'u') {
                    currentState = RW_STATE_31;
                } else
                    return 0;
                break;

            case RW_STATE_31:
                if (c == 'l') {
                    currentState = RW_STATE_32;
                } else
                    return 0;
                break;

            case RW_STATE_32:
                if (c == 'a') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;

            // tama branch
            case RW_STATE_33:
                if (c == 'a') {
                    currentState = RW_STATE_34;
                } else
                    return 0;
                break;

            case RW_STATE_34:
                if (c == 'm') {
                    currentState = RW_STATE_35;
                } else
                    return 0;
                break;

            case RW_STATE_35:
                if (c == 'a') {
                    currentState = RW_STATE_ACCEPTED;
                } else
                    return 0;
                break;

            case RW_STATE_ACCEPTED:
                return keyword[idx] == '\0' ? 1 : 0;

            default:
                return 0;
        }
    }
}

// int main() {
//     printf("bool: %d\n", classifyReservedWord("bool"));
//     printf("des: %d\n", classifyReservedWord("des"));
//     printf("int: %d\n", classifyReservedWord("int"));
//     printf("kar: %d\n", classifyReservedWord("kar"));
//     printf("mali: %d\n", classifyReservedWord("mali"));
//     printf("magpatuloy: %d\n", classifyReservedWord("magpatuloy"));
//     printf("pumuntasa: %d\n", classifyReservedWord("pumuntasa"));
//     printf("simula: %d\n", c*lassifyReservedWord("simula"));
//     printf("tama: %d\n", classifyReservedWord("tama"));
//     return 0;
// }
