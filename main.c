#include <stdio.h>
#include <string.h>

#include "freq.h"
#include "list.h"
#include "tokenizer.h"
#include "parser.h"
#include "drawAsciiTree.h"

#define BUFFER_SIZE    500

int showTree        = 0;
int showTokenStream = 0;
int hideOutput      = 0;

int roll(char *roll) {
    List_t *toks = tokenize(roll);

    if (showTokenStream) {
        printTokens(toks);
    }
    Expression_t *e = parse(toks);

    if (showTree) {
        printTree(e);
    }

    if (!hideOutput) {
        printf("Rolling: %s\n", roll);
        printFreq(evaluate(e));
    }
}

int clear(char inp[BUFFER_SIZE]) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        inp[i] = '\0';
    }
}

int hasArg(char *str, int argc, char const *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[1], str) == 0) {
            return(1);
        }
    }

    return(0);
}

int main(int argc, char const *argv[]) {
    if (hasArg("-p", argc, argv)) {
        showTree = 1;
    }
    if (hasArg("-l", argc, argv)) {
        showTokenStream = 1;
    }
    if (hasArg("-n", argc, argv)) {
        hideOutput = 1;
    }
    printf("%s\n", "Dice-o-tronic 5000: Roll the dice, see the chances, enter in a format like this '1d6+2d8'");



    char inp[BUFFER_SIZE];
    for (;; ) {
        clear(inp);
        printf("\n\n%s\n", "Roll:");
        fgets(inp, BUFFER_SIZE, stdin);
        roll(inp);
    }



    if (hasArg("-t", argc, argv)) {
        testFreq();
        testList();
    }

    return(0);
}
