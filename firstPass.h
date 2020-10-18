#include "main.h"
#define COMMA 44
#define MAX_LENGTH 200
char label[80];
char externy[80];
char string[80];
#define MIUN0 1
#define MIUN1 2
#define MIUN2 3
#define MIUN3 4

#define MOV 0
#define CMP 1
#define ADD 2
#define SUB 3
#define LEA 4
#define CLR 5
#define NOT 6
#define INC 7
#define DEC 8
#define JMP 9
#define BNE 10
#define JSR 11
#define RED 12
#define PRN 13
#define RTS 14
#define STOP 15
int found2;
int foundInum;
int found4;
 int IC;
 int DC;
 int LINE;
 int missingLine;
bool ifNum ;
int isString;
typedef struct {
int first_register;
int second_register;
int has_label;
int operation;
int hasGuide;
char param1[100];
char param2[100];
int param1_miun;
int param2_miun;
}preMila;

typedef struct { 
	char opCode[7];
	char sourceMiun[3];
	char sourceRegister[4];
	char destinationMiun[3];
	char destinationRegister[4];
	char funct[6];
	char a_r_e[4];
	int addressOflabel;
	int number;
    }mila;
    
/*=========================*/
       typedef struct {
    char label[50];
}Entry;

   typedef struct {
    Entry entry;
    struct EntryNode * next;
}EntryNode;

EntryNode * ehead ;
EntryNode * curENode;
/*==========================*/
      
typedef struct {
    char label[50];
    int value;
    bool hasValue;
    int location;
    char car[50];
}Sign;

typedef struct {
    Sign sign;
    struct SignNode * next;
}SignNode;

SignNode * shead ;
SignNode * curSNode;
/*==========================*/

typedef struct {
    char word[100];
    int ic;
}Data;

typedef struct DNode {
    Data data;
    struct DNode* next;
}DataNode;

DataNode* dhead;
DataNode* curDNode;

/*==========================*/
typedef struct{
	mila newMila;
	char number[100];
	int line;
}wordsTable;
typedef struct {
    wordsTable word;
    struct wordsTableNode * next;
}wordsTableNode;

void SortLinkedList(wordsTableNode * temp);
wordsTableNode * whead;
wordsTableNode * curWNode;
char arr2[100];
char arr3[100];
int dec(char bstr[]);
int checkForErorrs(preMila *pre_mila, mila *myMila, int numOfParam);
void makeBinary(int toPrint,int sibit);
int getNumber(char * line,mila *myMila);
int checkInWitchParamLabel(preMila *pre_mila, mila *myMila);
int checkIfLabelIsParam(preMila *pre_mila, mila *myMila);
void resetValues(preMila *pre_mila,mila *myMila);
int addData(char * line,int place);
void printMila(preMila *pre_mila, mila *myMila);
int checkFunct(char *line, preMila *pre_mila);
void assignRegistersValues(preMila *pre_mila,mila *myMila);
int getParameters(char * line,preMila *myPreMila, mila *myMila);
int makepOpCodeAndFunct(int funct,mila *myMila);
bool checkForLabel(char * line);
int checkForGuide(char * line,int place);
void handleExtern(char * line,int place);
void addSign(char label[50], char character[50], int value);
int handleEntry(char * line,int place);
void binaryNum(int toPrint,int sibit);
void checkIfExtern(DataNode*temp,SignNode *temp2);
void compareLists(DataNode*temp,SignNode *temp2);

