#include "list.h"
#include "freq.h"
#include "parser.h"
#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Recursive Descent Parser
 *
 *
 * Grammer is in prority as follows, from low to high
 *
 * OP_ADD
 * OP_SUBTRACT
 *
 * OP_DIVIDE
 * OP_MULIPLY_SCALAR
 *
 * OP_ROLL
 *
 * OP_MULIPLY_VECTOR
 *
 * DIE
 *
 * NUMBER
 * BRACKETS
 *
 *
 */
List_t *     symbolList;
Token_t      currentSymbol;
Expression_t root;

Expression_t *parse(List_t *toks) {
    symbolList = toks;

    //pop(toks);  // remove END_OF_FILE
    dequeue(toks); // remove START_OF_FILE

    lvl_add();
    return(&root);
}

Expression_t binaryExpressonL(Token_t tok) {
    Expression_t ex;

    ex.op    = currentSymbol;
    ex.left  = malloc(sizeof(Expression_t));
    ex.right = malloc(sizeof(Expression_t));
    memcpy(ex.left, &root, sizeof(Expression_t));
    return(ex);
}

void binaryExpressonR(Expression_t ex) {
    memcpy(ex.right, &root, sizeof(Expression_t));
    memcpy(&root, &ex, sizeof(Expression_t));
}

void lvl_add() {
    lvl_div();

    while (currentSymbol.type == OP_ADD || currentSymbol.type == OP_SUBTRACT) {
        Expression_t ex = binaryExpressonL(currentSymbol);
        lvl_div();
        binaryExpressonR(ex);
    }
}

void lvl_div() {
    lvl_roll();

    while (currentSymbol.type == OP_MULIPLY_SCALAR || currentSymbol.type == OP_DIVIDE) {
        Expression_t ex = binaryExpressonL(currentSymbol);
        lvl_roll();
        binaryExpressonR(ex);
    }
}

void lvl_roll() {
    lvl_mulVec();

    while (currentSymbol.type == OP_ROLL) { // For now, hope theres no rolls
    }
}

void lvl_mulVec() {
    lvl_die();

    while (currentSymbol.type == OP_MULIPLY_VECTOR) {
        Expression_t ex = binaryExpressonL(currentSymbol);
        lvl_die();
        binaryExpressonR(ex);
    }
}

void lvl_die() {
    lvl_num();

    while (currentSymbol.type == DIE) {
        Expression_t ex = binaryExpressonL(currentSymbol);
        lvl_num();
        binaryExpressonR(ex);
    }
}

void lvl_num() {
    nextSymbol();

    switch (currentSymbol.type) {
        case NUMBER:
            root.left  = NULL;
            root.right = NULL;
            root.op    = currentSymbol;
            nextSymbol();
            break;

        case BRACK_LEFT:
            lvl_add();
            nextSymbol();
            break;

        default:
            nextSymbol();
            break;
    }
}

Frequency *evaluate(Expression_t *expr) {
    switch (expr->op.type) {
        case OP_ROLL: {
            Frequency *l = evaluate(expr->left);

            Frequency *ans = createScalar(rollFreq(l));

            free(l);

            return(ans);
        }

        case OP_ADD: {
            Frequency *l = evaluate(expr->left);
            Frequency *r = evaluate(expr->right);

            Frequency *ans = addFreq(l, r);

            free(l);
            free(r);

            return(ans);
        }

        case OP_SUBTRACT: {
            Frequency *l = evaluate(expr->left);
            Frequency *r = evaluate(expr->right);

            Frequency *ans = subtractFreq(l, r);

            free(l);
            free(r);

            return(ans);
        }

        case OP_DIVIDE: {
            Frequency *l = evaluate(expr->left);
            Frequency *r = evaluate(expr->right);

            Frequency *ans = divideFreq(l, r);

            free(l);
            free(r);

            return(ans);
        }

        case OP_MULIPLY_VECTOR: {
            Frequency *l = evaluate(expr->left);
            Frequency *r = evaluate(expr->right);

            Frequency *ans = increaseDieNumber(l, r);

            free(l);
            free(r);

            return(ans);
        }

        case OP_MULIPLY_SCALAR: {
            Frequency *l = evaluate(expr->left);
            Frequency *r = evaluate(expr->right);

            Frequency *ans = multiplyFreq(l, r);

            free(l);
            free(r);

            return(ans);
        }

        case DIE: {
            Frequency *l = evaluate(expr->left);
            Frequency *r = evaluate(expr->right);

            free(l);
            free(r);

            return(createMultiDice(getScalarValue(l), getScalarValue(r)));
        }

        case NUMBER: {
            return(createScalar(expr->op.data));
        }
    }
}

void nextSymbol() {
    Token_t *tokPtr = dequeue(symbolList);

    currentSymbol = *tokPtr;

    free(tokPtr);
}
