#ifndef guess_h
#define guess_h
#include"GuessNumber.c"
#include"MakeNumber.c"
#include"IsRight.c"
#include"IsValidNum.c"
int MakeNumber(void);
void GuessNumber(int number);
int IsValidNum(int number);
int IsRight(int number, int guess);
#endif