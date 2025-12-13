#ifndef FILES_H
#define FILES_H

#include "./../core/common/common.h"

FILE *ReadFile(const char *str);
long int GetCharPositionFromFile(FILE *pfile);
char ReadCharFromFile(FILE *pfile);
void UnReadLastCharFromFile(char ch, FILE *pfile);
void CloseFile(FILE *pfile);
void UnReadLastManyCharFromFile(long int size, FILE *pfile);

#endif // !FILES_H
