#include "files.h"

FILE *ReadFile(const char *str) {
  FILE *pfile = fopen(str, "r");

  if (pfile == NULL) {
    printf("Error: Could not open the file (%s). Please check the path "
           "provided.\n",
           str);
    return NULL;
  }

  return pfile;
}

long int GetCharPositionFromFile(FILE *pfile) { return (ftell(pfile)); }
char ReadCharFromFile(FILE *pfile) { return fgetc(pfile); }
void UnReadLastCharFromFile(char ch, FILE *pfile) { ungetc(ch, pfile); }
void UnReadLastManyCharFromFile(long int size, FILE *pfile) {
  fseek(pfile, size, SEEK_CUR);
}

void CloseFile(FILE *pfile) { fclose(pfile); }
