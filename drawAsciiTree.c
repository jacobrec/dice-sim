#include "parser.h"
#include "tokenizer.h"
#include <stdio.h>

void printIndents(int indentLevel){
    printf("\n");
    for(int i = 0; i < indentLevel; i++){
        printf("\t", indentLevel);
    }
}

void printTreeIndented(Expression_t *e, int indentLevel) {
    printIndents(indentLevel);
    printTokennnl(e->op);
    if (e->left != NULL && e->right != NULL) {
        printf(":(");
        printIndents(indentLevel);
        if (e->left != NULL) {
            printTreeIndented(e->left, indentLevel + 1);
            printf(",");
        }
        printIndents(indentLevel);
        if (e->right != NULL) {
            printTreeIndented(e->right, indentLevel + 1);
        }
        printIndents(indentLevel);
        printf(")");
    }

}

void printTree(Expression_t *e) {
    printTreeIndented(e, 0);
    printf("\n");
}
