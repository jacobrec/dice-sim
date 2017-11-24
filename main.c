#include <stdio.h>
#include "freq.h"
#include "list.h"
#include "tokenizer.h"
#include "parser.h"
#include "drawAsciiTree.h"

#define BUFFER_SIZE    500

int roll(char *roll) {
    List_t *toks = tokenize(roll);

    //printTokens(toks);
    Expression_t *e = parse(toks);

    //printTree(e);

    printf("Rolling: %s\n", roll);
    printFreq(evaluate(e));
}

int clear(char inp[BUFFER_SIZE]) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        inp[i] = '\0';
    }
}

int main(int argc, char const *argv[]) {
    printf("%s\n", "Dice-o-tronic 5000: Roll the dice, see the chances, enter in a format like this '1d6+2d8'");

    char inp[BUFFER_SIZE];
    for (;; ) {
        clear(inp);
        printf("\n\n%s\n", "Roll:");
        fgets(inp, BUFFER_SIZE, stdin);
        roll(inp);
    }



    //testFreq();
    //testList();
    return(0);
}
