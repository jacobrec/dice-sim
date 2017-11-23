#ifndef TOKINIZE_H_
#define TOKINIZE_H_

#include <stdint.h>
#include "list.h"
typedef enum {START_OF_FILE, DIE, NUMBER, OP_ROLL, OP_MULIPLY_VECTOR, OP_ADD, OP_MULIPLY_SCALAR, OP_DIVIDE, OP_SUBTRACT, BRACK_LEFT, BRACK_RIGHT, END_OF_FILE } TType_t;

typedef struct {
    TType_t type;
    int64_t data;

} Token_t;

List_t* tokenize(char* input);

int getNextNumber(int* startIndex, char *input);
char *getNextWord(int* startIndex, char *input);

void printToken(Token_t tok);
void printTokennnl(Token_t tok);
void printTokens(List_t* toks);

Token_t getOperatorToken(TType_t type);

int isSame(const char *other, const char *word);
#endif
