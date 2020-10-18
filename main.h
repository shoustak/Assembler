
#ifndef UNTITLED_MAIN_H
#define UNTITLED_MAIN_H


#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

typedef struct {
    char word[100];
    int ic;
}External;

   typedef struct {
    External external;
    struct ExternalNode * next;
}ExternalNode;

ExternalNode * exhead ;
ExternalNode * curEXNode;

void printMilim(char*fileName);
void printEntry(char * fileName);
void printExtern(char * fileName);
int getEntryValue(char * str);
void getFileName(char * argv, char * fileName);
void printToFIles(char*fileName);
void runProg(char * fileName);
int firstParse(char * fileName);
void seconedPass();

#endif

