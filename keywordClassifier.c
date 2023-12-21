#include <stdio.h>
#include <string.h>

enum KW_State {
    KW_STATE_0,
    KW_STATE_1,
    KW_STATE_2,
    KW_STATE_3,
    KW_STATE_4,
    // STATE_5,
    KW_STATE_6,
    KW_STATE_7,
    KW_STATE_8,
    KW_STATE_9,
    KW_STATE_10,
    KW_STATE_11,
    // STATE_12,
    KW_STATE_13,
    KW_STATE_14,
    KW_STATE_15,
    KW_STATE_16,
    KW_STATE_17,
    KW_STATE_18,
    KW_STATE_19,
    KW_STATE_20,
    KW_STATE_21,
    KW_STATE_22,
    KW_STATE_23,
    KW_STATE_24,
    KW_STATE_25,
    // STATE_26,
    KW_STATE_27,
    KW_STATE_28,
    KW_STATE_29,
    KW_STATE_30,
    KW_STATE_31,
    KW_STATE_32,
    KW_STATE_33,
    KW_STATE_34,
    KW_STATE_35,
    // STATE_36,
    KW_STATE_37,
    // STATE_38,
    KW_STATE_39,
    KW_STATE_40,
    KW_STATE_41,
    KW_STATE_42,
    // STATE_43,
    KW_STATE_ACCEPTED
};

int classifyKeyword(const char *keyword) {
    enum KW_State currentState = KW_STATE_0;
    int idx;

    for (idx = 0; idx < strlen(keyword); idx++) {
        char c = keyword[idx];

        switch (currentState) {
            case KW_STATE_0:
                switch (c) {
                    case 'b':
                        currentState = KW_STATE_1;
                        break;
                    case 'i':
                        currentState = KW_STATE_6;
                        break;
                    case 'p':
                        currentState = KW_STATE_13;
                        break;
                    case 't':
                        currentState = KW_STATE_39;
                        break;
                    case 'w':
                        currentState = KW_STATE_27;
                        break;
                    case 'k':
                        currentState = KW_STATE_33;
                        break;
                    default:
                        return 0;
                }
                break;

            // balik branch
            case KW_STATE_1:
                if (c == 'a') {
                    currentState = KW_STATE_2;
                } else
                    return 0;
                break;

            case KW_STATE_2:
                if (c == 'l') {
                    currentState = KW_STATE_3;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_3:
                if (c == 'i') {
                    currentState = KW_STATE_4;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_4:
                if (c == 'k') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;

            // ipakita branch
            case KW_STATE_6:
                if (c == 'p') {
                    currentState = KW_STATE_7;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_7:
                if (c == 'a') {
                    currentState = KW_STATE_8;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_8:
                if (c == 'k') {
                    currentState = KW_STATE_9;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_9:
                if (c == 'i') {
                    currentState = KW_STATE_10;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_10:
                if (c == 't') {
                    currentState = KW_STATE_11;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_11:
                if (c == 'a') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;

            // para branch
            case KW_STATE_13:
                if (c == 'a') {
                    currentState = KW_STATE_14;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_14:
                if (c == 'r') {
                    currentState = KW_STATE_15;
                } else if (c == 's') {
                    currentState = KW_STATE_16;
                } else if (c == 'n') {
                    currentState = KW_STATE_18;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_15:
                if (c == 'a') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;

            // pasok branch
            case KW_STATE_16:
                if (c == 'o') {
                    currentState = KW_STATE_17;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_17:
                if (c == 'k') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;

            // pangungusap branch
            case KW_STATE_18:
                if (c == 'g') {
                    currentState = KW_STATE_19;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_19:
                if (c == 'u') {
                    currentState = KW_STATE_20;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_20:
                if (c == 'n') {
                    currentState = KW_STATE_21;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_21:
                if (c == 'g') {
                    currentState = KW_STATE_22;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_22:
                if (c == 'u') {
                    currentState = KW_STATE_23;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_23:
                if (c == 's') {
                    currentState = KW_STATE_24;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_24:
                if (c == 'a') {
                    currentState = KW_STATE_25;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_25:
                if (c == 'p') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;

                // walangbalik branch
            case KW_STATE_27:
                if (c == 'a') {
                    currentState = KW_STATE_28;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_28:
                if (c == 'l') {
                    currentState = KW_STATE_29;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_29:
                if (c == 'a') {
                    currentState = KW_STATE_30;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_30:
                if (c == 'n') {
                    currentState = KW_STATE_31;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_31:
                if (c == 'g') {
                    currentState = KW_STATE_32;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_32:
                if (c == 'b') {
                    currentState = KW_STATE_1;
                } else {
                    return 0;
                }
                break;

            // kung branch
            case KW_STATE_33:
                if (c == 'u') {
                    currentState = KW_STATE_34;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_34:
                if (c == 'n') {
                    currentState = KW_STATE_35;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_35:
                if (c == 'g') {
                    currentState = KW_STATE_ACCEPTED;
                } else if (c == 'd') {
                    currentState = KW_STATE_37;
                } else {
                    return 0;
                }
                break;

            // kundi branch
            case KW_STATE_37:
                if (c == 'i') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;

            // tigil branch
            case KW_STATE_39:
                if (c == 'i') {
                    currentState = KW_STATE_40;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_40:
                if (c == 'g') {
                    currentState = KW_STATE_41;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_41:
                if (c == 'i') {
                    currentState = KW_STATE_42;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_42:
                if (c == 'l') {
                    currentState = KW_STATE_ACCEPTED;
                } else {
                    return 0;
                }
                break;

            case KW_STATE_ACCEPTED:
                return keyword[idx] == '\0' ? 1 : 0;

            default:
                return 0;
        }
    }
}

// int main() {
//     printf("balik: %d\n", classifyKeyword("balik"));
//     printf("ipakita: %d\n", classifyKeyword("ipakita"));
//     printf("para: %d\n", classifyKeyword("para"));
//     printf("pasok: %d\n", classifyKeyword("pasok"));
//     printf("pangungusap: %d\n", classifyKeyword("pangungusap"));
//     printf("tigil: %d\n", classifyKeyword("tigil"));
//     printf("walangbalik: %d\n", classifyKeyword("walangbalik"));
//     printf("kung: %d\n", classifyKeyword("kung"));
//     printf("kundi: %d\n", classifyKeyword("kundi"));

//     printf("kundi - should be 0: %d\n", classifyKeyword("kundii"));
//     printf("should be 0: %d\n", classifyKeyword("ee"));
//     printf("should be 0: %d\n", classifyKeyword("red"));
//     printf("should be 0: %d\n", classifyKeyword("exampletest"));

//     return 0;
// }
