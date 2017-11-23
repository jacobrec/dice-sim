#ifndef FREQ_H_
#define FREQ_H_

typedef struct {
    int  totalThings;
    int *amounts;
}Frequency;

Frequency *createFrequency(int initalMax);
Frequency *copyFrequency(Frequency *f);
void expandTo(Frequency *f, int newMax);
void addValue(Frequency *f, int amount, int value);
int getAmount(Frequency *f, int value);
float getPercent(Frequency *f, int value);
int getTotal(Frequency *f);
void destroyFrequency(Frequency *f);

Frequency *createScalar(int num);
Frequency *createStandardDice(int size);


int isScalar(Frequency *f);
int getScalarValue(Frequency *scalar);

Frequency *increaseDieNumber(Frequency *scalar, Frequency *f);

Frequency *multiplyFreq(Frequency *f1, Frequency *f2);
Frequency *addFreq(Frequency *f1, Frequency *f2);
Frequency *subtractFreq(Frequency *f1, Frequency *f2);
Frequency *divideFreq(Frequency *f1, Frequency *f2);
int rollFreq(Frequency *f1);

void printFreq(Frequency* f);

void testFreq();


#endif
