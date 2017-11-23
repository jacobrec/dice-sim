#ifndef PARSER_H_
#define PARSER_H_
#include "list.h"
#include "freq.h"
#include "tokenizer.h"

typedef struct exp {
    struct exp *left;
    struct exp *right;
    Token_t     op;
}Expression_t;

Frequency* evaluate(Expression_t* expr);

Expression_t *parse();

void binaryExpresson(Token_t tok);


void lvl_add();
void lvl_div();
void lvl_roll();
void lvl_mulVec();
void lvl_die();


void nextSymbol();

#endif
