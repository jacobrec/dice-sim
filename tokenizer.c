#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "list.h"

List_t *tokenize(char *input) {
    int  index = 0;
    char c;

    List_t *toks = createList(sizeof(Token_t));

    Token_t *token = malloc(sizeof(Token_t));

    token->type = START_OF_FILE;
    token->data = 0b0000;
    push(toks, token);

    do {
        c = input[index++];
        switch (c) {
            case '+':
                token->type = OP_ADD;
                token->data = 0b1000;
                push(toks, token);
                break;

            case '-':
                token->type = OP_SUBTRACT;
                token->data = 0b1000;
                push(toks, token);
                break;

            case '*':
                token->type = OP_MULIPLY_SCALAR;
                token->data = 0b1001;
                push(toks, token);
                break;

            case '/':
                token->type = OP_DIVIDE;
                token->data = 0b1001;
                push(toks, token);
                break;

            case '(':
            case '{':
            case '[':
                token->type = BRACK_LEFT;
                token->data = 0b1111;
                push(toks, token);
                break;

            case ')':
            case '}':
            case ']':
                token->type = BRACK_RIGHT;
                token->data = 0b1111;
                push(toks, token);
                break;

            case '\0':
                break;

            case 'd': {
                if ((*((Token_t *)peek(toks))).type != NUMBER || (*((Token_t *)peek(toks))).type != BRACK_RIGHT) {
                    token->type = NUMBER;
                    token->data = 0b0001;
                    push(toks, token);
                }
                token->type = DIE;
                token->data = 0;//getNextNumber(&index, input);
                push(toks, token);
                break;
            }



            default:
                if ('0' <= c && c <= '9') {
                    token->type = NUMBER;
                    --index;

                    token->data = getNextNumber(&index, input);
                    push(toks, token);
                }
                if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
                    --index;
                    char *word = getNextWord(&index, input);
                    if (isSame(word, "ROLL")) {
                        token->type = OP_ROLL;
                        token->data = 0b0001;
                        push(toks, token);
                    }
                    free(word);
                }
        }
        /* code */
    } while (c != '\0');

    token->type = END_OF_FILE;
    token->data = 0b0000;
    push(toks, token);
    return(toks);
}

int isSame(const char *other, const char *word) {
    int index = 0;

    while (word[index] != '\0') {
        if (word[index] != other[index]) {
            return(0);
        }
        index++;
    }
    return(1);
}

int getNextNumber(int *startIndex, char *input) {
    char c   = input[*startIndex];
    int  ans = 0;

    while ('0' <= c && c <= '9') {
        ans *= 10;
        ans += (c - '0');
        c    = input[++(*startIndex)];
    }
    return(ans);
}

char *getNextWord(int *startIndex, char *input) {
    char c = input[*startIndex];

    char *ans   = malloc(50);
    int   index = 0;

    while (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
        if ('a' <= c && c <= 'z') {
            c += 'A' - 'a';
        }
        ans[index++] = c;
        c            = input[++(*startIndex)];
    }
    ans[index++] = '\0';
    return(ans);
}

void printTokennnl(Token_t tok) {
    switch (tok.type) {
        case START_OF_FILE:
            printf("%s", "STARTING");
            break;

        case END_OF_FILE:
            printf("%s", "ENDING");
            break;

        case OP_ADD:
            printf("%s", "OP_ADD");
            break;

        case OP_MULIPLY_SCALAR:
            printf("%s", "OP_SCALAR");
            break;

        case OP_MULIPLY_VECTOR:
            printf("%s", "OP_VECTOR");
            break;

        case OP_DIVIDE:
            printf("%s", "OP_DIVIDE");
            break;

        case OP_SUBTRACT:
            printf("%s", "OP_SUBTRACT");
            break;

        case BRACK_LEFT:
            printf("%s", "BRACK_LEFT");
            break;

        case BRACK_RIGHT:
            printf("%s", "BRACK_RIGHT");
            break;

        case OP_ROLL:
            printf("%s", "OP_ROLL");
            break;

        case DIE:
            printf("%s", "DIE");
            break;

        case NUMBER:
            printf("%s: %ld", "NUMBER", tok.data);
            break;
    }
}

void printToken(Token_t tok) {
    printTokennnl(tok);
    printf("\n");
}

void printTokens(List_t *toks) {
    Node_t *node = toks->head;

    printf("Starting print:\n");

    do {
        printToken(*((Token_t *)node->data));
        node = node->next;
    } while (node != NULL && node->data != NULL);
}

Token_t getOperatorToken(TType_t type) {
    Token_t tok;

    tok.type = type;
    tok.data = 0;
    return(tok);
}
