#include "parser.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>

void printIndents(int indentLevel) {
    printf("\n");
    for (int i = 0; i < indentLevel; i++) {
        printf("\t");
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

int grid_width      = 80;
int max_grid_height = 80;
int getBottomRungSize(Expression_t *e) {
    if (e->left == NULL || e->right == NULL) {
        return(3);
    }
    else{
        return(getBottomRungSize(e->left) + getBottomRungSize(e->right));
    }
}

char *printTreePretty(Expression_t *e, char *grid, int depth, int x) {
    char c;

    switch (e->op.type) {
        case START_OF_FILE:
            c = '=';
            break;

        case END_OF_FILE:
            c = '=';
            break;

        case OP_ADD:
            c = '+';
            break;

        case OP_MULIPLY_SCALAR:
            c = '*';
            break;

        case OP_MULIPLY_VECTOR:
            c = 'x';
            break;

        case OP_DIVIDE:
            c = '/';
            break;

        case OP_SUBTRACT:
            c = '-';
            break;

        case BRACK_LEFT:
            c = '(';
            break;

        case BRACK_RIGHT:
            c = ')';
            break;

        case OP_ROLL:
            c = '@';
            break;

        case DIE:
            c = 'd';
            break;

        case NUMBER:
            c = 'n';
            break;
    }

    int lw = 0;
    int rw = 0;
    int mw;

    grid[x + depth * grid_width] = c;

    if (e->right != NULL) {
        rw = getBottomRungSize(e->right);
    }
    if (e->left != NULL) {
        lw = getBottomRungSize(e->left);
    }

    mw = lw < rw ? rw : lw;



    if (e->left != NULL) {
        printTreePretty(e->left, grid, depth + mw, x - mw);
        for (int i = 1; i < mw; i++) {
            grid[(x - i) + (depth + i) * grid_width] = '/';
        }
    }



    if (e->right != NULL) {
        printTreePretty(e->right, grid, depth + mw, x+mw);
        for (int i = 1; i < mw; i++) {
            grid[(x + i) + (depth + i) * grid_width] = '\\';
        }
    }


}

void printTree(Expression_t *e) {
    char *grid = malloc(grid_width * max_grid_height);

    for (int i = 0; i < grid_width * max_grid_height; i++) {
        grid[i] = ' ';
        if ((i + 1) % grid_width == 0) {
            grid[i] = '\n';
        }
    }

    printTreePretty(e, grid, 0, 40);


    printf("%s", grid);
}
