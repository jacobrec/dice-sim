#include "freq.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

Frequency *createFrequency(int initalMax) {
    Frequency *f = malloc(sizeof(Frequency));

    f->totalThings = initalMax;
    f->amounts     = calloc(initalMax, sizeof(int));
    return(f);
}

Frequency *copyFrequency(Frequency *f) {
    Frequency *ans = malloc(sizeof(Frequency));

    ans->totalThings = f->totalThings;
    ans->amounts     = calloc(ans->totalThings, sizeof(int));

    for (int i = 0; i < ans->totalThings; i++) {
        addValue(ans, getAmount(f, i), i);
    }
    return(ans);
}

Frequency *createScalar(int num) {
    Frequency *f = createFrequency(num + 1);

    addValue(f, 1, num);
    return(f);
}

Frequency *createStandardDice(int size) {
    Frequency *f = createFrequency(size + 1);

    for (int i = 0; i < size; i++) {
        addValue(f, 1, i + 1);
    }
    return(f);
}

void expandTo(Frequency *f, int newMax) {
    if (newMax > f->totalThings) {
        f->amounts = realloc(f->amounts, sizeof(int) * newMax);
        for (int i = f->totalThings; i < newMax; i++) {
            f->amounts[i] = 0;
        }
        f->totalThings = newMax;
    }
}

void addValue(Frequency *f, int amount, int value) {
    if (value >= f->totalThings) {
        expandTo(f, value);
    }
    f->amounts[value] += amount;
}

int getAmount(Frequency *f, int value) {
    if (value < f->totalThings) {
        return(f->amounts[value]);
    }
    else{
        printf("Error: accessing out of bound item\n");
    }
}

int getTotal(Frequency *f) {
    int total = 0;

    for (int i = 0; i < f->totalThings; i++) {
        total += f->amounts[i];
    }
    return(total);
}

float getPercent(Frequency *f, int value) {
    return((getAmount(f, value) / (float)getTotal(f)) * 100);
}

void destroyFrequency(Frequency *f) {
    free(f);

    free(f->amounts);
}

int isScalar(Frequency *f) {
    return(getTotal(f) == 1);
}

int getScalarValue(Frequency *scalar) {
    for (int i = 0; i < scalar->totalThings; i++) {
        if (getAmount(scalar, i) > 0) {
            return(i);
        }
    }
}

Frequency *multiplyFreq(Frequency *f1, Frequency *f2) {
    Frequency *f = createFrequency(f1->totalThings);

    for (int i = 0; i < f1->totalThings; i++) {
        for (int j = 0; j < f2->totalThings; j++) {
            addValue(f, getAmount(f1, i) * getAmount(f2, j), i + j);
        }
    }
    return(f);
}

Frequency *increaseDieNumber(Frequency *scalar, Frequency *f) {
    Frequency *ans = copyFrequency(f);

    for (int c = 1; c < getScalarValue(scalar); c++) {
        ans = addFreq(ans, f);
    }
    return(ans);
}

Frequency *addFreq(Frequency *f1, Frequency *f2) {
    Frequency *f = createFrequency(f1->totalThings * f2->totalThings);

    for (int i = 0; i < f1->totalThings; i++) {
        for (int j = 0; j < f2->totalThings; j++) {
            if (getAmount(f1, i) > 0 && getAmount(f2, j) > 0) {
                addValue(f, getAmount(f1, i) + getAmount(f2, j), i + j);
            }
        }
    }
    return(f);
}

Frequency *subtractFreq(Frequency *f1, Frequency *f2) {
    Frequency *f = createFrequency(f1->totalThings);

    for (int i = 0; i < f1->totalThings; i++) {
        for (int j = 0; j < f2->totalThings; j++) {
            addValue(f, getAmount(f1, i) - getAmount(f2, j), i + j);
        }
    }
    return(f);
}

Frequency *divideFreq(Frequency *f1, Frequency *f2) {
    if (!isScalar(f1)) {
        fprintf(stderr, "Error: denominator must be a scalar\n");
    }
    Frequency *f = createFrequency(f1->totalThings);

    for (int i = 0; i < f1->totalThings; i++) {
        for (int j = 0; j < f2->totalThings; j++) {
            addValue(f, getAmount(f1, i) / getAmount(f2, j), i + j);
        }
    }
    return(f);
}

int rollFreq(Frequency *f) {
}

void printFreq(Frequency *f) {
    float cummulitive = 0;
    for (int i = 0; i < f->totalThings; i++) {
        if (getAmount(f, i) > 0) {
            printf("Number: %d,\tPercent: %f%%\tCummulitive: %f%%\n", i, getPercent(f, i), 100-cummulitive);
            cummulitive += getPercent(f, i);
        }
    }
}

void testFreq() {
    printf("##### Starting Freq test #####\n");

    Frequency *f = createFrequency(10);

    for (int i = 0; i < 10; i++) {
        addValue(f, i, i);
    }
    expandTo(f, 15);
    for (int i = 10; i < 15; i++) {
        addValue(f, i, i);
    }

    printf("Frequency: 0-%d with %d total items\n", f->totalThings, getTotal(f));
    for (int i = 0; i < 15; i++) {
        printf("i: %d, A: %d, P: %f\n", i, getAmount(f, i), getPercent(f, i));
    }

    Frequency *f1 = createStandardDice(6);
    Frequency *f2 = createStandardDice(6);
    printf("Created dice size d6\n");
    Frequency *ans = addFreq(f1, f2);

    printf("Frequency: 2d6\n");
    for (int i = 0; i < ans->totalThings; i++) {
        if (getAmount(ans, i) > 0) {
            printf("i: %d, A: %d, P: %f\n", i, getAmount(ans, i), getPercent(ans, i));
        }
    }

    destroyFrequency(f);
}
