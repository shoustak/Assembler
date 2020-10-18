#include "words.h"
#include "firstPass.h"

/* 
 * @description this method pass on file for first time
*/ 

int firstParse(char * fileName)
{
FILE *fp;
char file[30];
strcpy(file,fileName);
strcat(file, ".as");
printf("real file name:  %s\n", file);
fp = fopen(file, "r");
if(fp == NULL){
 	printf("cant open file:  %s", file);
	return 0;
}
int flagForError = 0;
int parametersCheck;
char * line = NULL;
size_t len = 0;
ssize_t read;
int insertCode=0;
int place=0;
char * ptr;
int labelFlag;
int length;
int commandLine;
char functLabel;
preMila pre_Mila;
mila lineMila;

exhead = (ExternalNode *) malloc(sizeof(ExternalNode));/*extren table declartion*/
curEXNode = exhead;

whead = (wordsTableNode *) malloc(sizeof(wordsTableNode));/*words table declartion*/
curWNode = whead;

ehead = (EntryNode *) malloc(sizeof(EntryNode));/*entries table declartion*/
curENode = ehead;

shead = (SignNode *) malloc(sizeof(SignNode));/*symbols table declartion*/
curSNode = shead;

dhead = (DataNode *) malloc(sizeof(DataNode));/*data table declartion*/
curDNode = dhead;

IC=100;
DC=0;
LINE = 100;  


while ((read = getline(&line, &len, fp)) != -1) {/*get lines*/
	commandLine=0;
	ifNum = 0;
	found2 = 0;
	foundInum = 0;
	found4 = 0;
	resetValues(&pre_Mila, &lineMila);/*resets the the mila values*/
	ptr = line;
	labelFlag = 0;
	functLabel = -1;

while(*ptr == ' ')/*clear spaces before line*/
{
	ptr++;
	place++;
}

if(*ptr == ';')/*if the line is command line*/
{
	commandLine=1;

}

if(!commandLine){

while(1){ /*THE SCAN LOOP*/

if(*ptr == '\0'){    /*if the input end*/        	
	break; 
}

if(*ptr == ':')
{ 
	labelFlag = checkForLabel(line);/*equal 1 if tere is label, 0 if not*/	
	
	if(labelFlag)
	{
	pre_Mila.has_label = 1;
	}else{    
     		flagForError =1; /*if we got : and we get false from funtion their is a problem and break*/
	}
}

if(*ptr == '.')
{ 
switch(checkForGuide(line,place)){

	case 1: {/*case if it is .data*/
		pre_Mila.hasGuide = 1;
		len = addData(line,place);
		if(labelFlag){
	        addSign(label, "data", LINE-len);
	        }
		}
	break;
	
	case 2: {/*case if it is .string*/
		pre_Mila.hasGuide = 2;
		length = addString(line,place);
		if(length == 0){
			flagForError =1;
		}
		if(labelFlag){
		addSign(label, "string", LINE-length);
		}
		}
	break;
	
	case 3: {/*case if it is .entry*/

		handleEntry(line,place);
		pre_Mila.hasGuide = 3;
		}
	break;
	
	case 4: {/*case if it is .extern*/
		pre_Mila.hasGuide = 4;
		handleExtern(line,place);
		}
	break;

}
}
if(functLabel == -1){
	if(isalpha(*ptr)){
	functLabel = checkFunct(ptr,&pre_Mila);/*will return the funct number 1-16 if found any*/	
		if(functLabel >= 0){
			if(functLabel == STOP){
				ptr+=4;
			}else{	
				ptr+=3;
			}
		makepOpCodeAndFunct(functLabel, &lineMila);
		}
	}
}
if(functLabel >= 0){/*start look for parameters*/

	if(!isspace(*ptr)){/*if its not blank space */	
		parametersCheck = getParameters(ptr, &pre_Mila, &lineMila);
	
			if(parametersCheck > 0){
				assignRegistersValues(&pre_Mila, &lineMila);
				checkIfParamIsLabel(&pre_Mila, &lineMila);
				if(!flagForError){				
					flagForError = checkForErorrs(&pre_Mila, &lineMila,parametersCheck);	
				}else{
					checkForErorrs(&pre_Mila, &lineMila,parametersCheck);	
				}
			}
			break;		
	
	}else{
		if(functLabel >= RTS){
			getParameters(ptr, &pre_Mila, &lineMila);
		}
	}
}

if(functLabel >= 0 && labelFlag)
{

insertCode=1;
addSign(label, "code", LINE);

}
/*moving ptr to next char in line*/
place++;
ptr++;

}	
/*moving line number dynamically dependent on the line parameters*/
if(functLabel >= 0){
if(found2&&found4&&!foundInum){
curWNode->word.newMila=lineMila;	
		curWNode->word.line=LINE-1;	
		wordsTableNode *newWNode = (wordsTableNode *) malloc(sizeof(wordsTableNode));
   		curWNode->next = newWNode;
   		curWNode = newWNode;
}else{
		curWNode->word.newMila=lineMila;	
		curWNode->word.line=LINE;	
		wordsTableNode *newWNode = (wordsTableNode *) malloc(sizeof(wordsTableNode));
   		curWNode->next = newWNode;
   		curWNode = newWNode;
   	}	
   	
   		LINE++;
		
		if((found2&&foundInum)||(found4&&!foundInum)){
		LINE++;
		}else if(!found2&&!found4&&foundInum){
		LINE++;
		}else if(found2&&!found4){
		LINE++;
		}else if(found4&&!found2){
		LINE++;
		}else if(found2&&!found4&&!foundInum){
		LINE=LINE;
		}
		
}
if(ifNum){
	makeBinary(lineMila.number,20);
}
place = 0;
IC++;
/*moving to next line IC grow by 1*/
  }
}
fclose(fp);
return flagForError;
}


/* 
 * @description this method pass on file for seconed time
 *compareLists complte the missing data 
 *SortLinkedList sorting the final words table
 *checkIfExtern checking if there need to open an .ext file
*/ 

void seconedPass()
{
DataNode *temp;
SignNode *temp2;
wordsTableNode * temp3;

   if (dhead == NULL||shead==NULL||whead==NULL) {
      printf("List is empty.\n");
      return;
   }
   
   temp2 = shead;
   temp = dhead;
   temp3 = whead;
   compareLists(temp,temp2);
   SortLinkedList(temp3);
   checkIfExtern(temp,temp2);
}
/* 
 * @description this method handle the entry and adds it to the list
 *compareLists line is pointer to the line
 *place is the place in the line
 *return will return 1 if there is error
*/ 
int handleEntry(char * line,int place){
char *ptr;
char *ptr2;
int i=0;
int i2 = 0;
char *str;
ptr = strtok(line," ");
ptr2 = strtok(NULL,"");

while(isalpha(*ptr2))
{
ptr2++;
i++;
}

while(*ptr2 != '\0')
{
if(isalpha(*ptr2)||isdigit(*ptr2)||(!isspace(*ptr2)))
{
printf("ERROR-cant be more than 1 parmeter in ENTRY statement!");
return 1; /*return 1 for error*/
}
ptr2++;
i++;
}

ptr2=ptr2-i;

i = 0;

str = (char*)calloc(31, sizeof(char));
while(*(ptr2+i) != '\0'){
if(isdigit(*(ptr2+i)) || isalpha(*(ptr2+i))){
*(str+i2) = *(ptr2+i);
i2++;

}
i++;
}
*(str+i2+1) = '\0';

strcpy(curENode->entry.label, str); /*put the entry label in list*/    
    EntryNode *newENode = (EntryNode *) malloc(sizeof(EntryNode));
    curENode->next = newENode;
    curENode = newENode;
free(str);
}

/* 
 * @description this method pass on file for seconed time
 *line is  pointer to the readen line
 *return will return 1 if found label
*/ 

bool checkForLabel(char * line){
char regs [8][3] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"}; 

char * ptr1 = line;
int i=0, i2 ;
int error=0;

while(*ptr1 == ' ')
{
	ptr1++;
	
}

if(!isalpha(*ptr1) && !isdigit(*ptr1))
{
        fprintf(stderr,"LABEL MUST BE START WITH LETTER\n");

}

while(*ptr1 != ':'){
	label[i] = *ptr1;
	ptr1++;
	i++;
}

if(*ptr1 == ':' && (*(ptr1-1))==' ')
{
	error=1;
	fprintf(stderr,"CANT BE SPACE BEFORE SEMICOLON IN LABEL");
	return 0;
}

for(i2=0; i2 < 8; i2++){
    if (!strcmp(label, regs[i2]))
    {
    	fprintf(stderr,"LABEL CANT BE REGISTER NAME");
    	return 0;
    }
}

if(*ptr1 == ':')
{
	label[i] = '\0';
}

return 1;
}
/* 
 * @description function check if it .string/.data/.external/.entry,and if it is illigel input, return 0
 *line is  pointer to the readen line
 *place is the place in the line
 *return the type of guide in int
*/ 
int checkForGuide(char * line,int place){

char *ptr1 = line;
char guide[80];
int i = 0;

while(*ptr1 != '.')
{
	ptr1++;
}
ptr1++;

while(*ptr1 != ' ')
{
	guide[i] = *ptr1;
	ptr1++;
	i++;
}
guide[i] = '\0';

    if (!strcmp(guide, "data")){

        return 1;
    }else if (!strcmp(guide, "string")){

        return 2;
    }else if (!strcmp(guide, "entry")){

        return 3;
    }else if (!strcmp(guide, "extern")){
        return 4;}
    return 0;
}
/* 
 * @description this method adds items to the ExternalNode list
 *param extName is the External name
 *param numOfline is number of line
 *return will return 
*/ 
void handleExtern(char * line,int place){

char * ptr2 = line;
ptr2 = ptr2 + place + 1 ;
int i = 0;

while(*ptr2 != ' ')
{
	ptr2++;
	
}

while(*ptr2 == ' ')
{
	ptr2++;
	
}

while(*ptr2 != NULL ){
externy[i] = *ptr2;
	ptr2++;
	i++;
}

externy[i-1] = '\0';

addSign(externy, "external", 0);
}

/* 
 * @description adds a string guida
 *line is  pointer to the readen line
 *place is the place in the line
 *return the number of line to jump
*/ 
int addString(char * line,int place){
 int i=0;
int i2 = 0;
char *p;
int len = 0;
char *ptr3 = line+1;
int numOfP = 0;
char  arr[100];
char * temp;
isString=1;

/*check if there is two "X" if not, error and return */
for(p = line;*p != '\0';p++){

	if(*p == 34){/*34 is ascii value of ( " ) */
	if(numOfP == 1){
	i2++;
	}
	numOfP++;
	}
}

if(numOfP != 2){
printf("line:%d must be 2 quotation marks. you insert: %d quotation marks.\n",LINE,numOfP); 
return 0;
}

while(*ptr3 != '.' && *ptr3 != '\0')
{
	ptr3++;	
}
while(*ptr3 != 34 && *ptr3 != '\0')
{
	ptr3++;
}	
ptr3++;
while(*ptr3 !='"' && *ptr3 != '\0'){
/*first is type of int24. can found in words.h file */
first = *ptr3;
arr24[i] = first;
makeBinary(arr24[i], 23);

LINE++;			
ptr3++;
i++;
len++;
}
i++;
arr24[i] = '\0';
i++;
makeBinary(0, 23);
++LINE;
DC += len + 1;

return len+1;
}


/* 
 * @description this method extrcat the parameters from "data" Guide type lines
 * @param line is pointer to the location in the line that the program read right now
 * @return the funct number 1-16 or 0 if not found
 */
int addData(char * line,int place){
int i=0;
int i2=0;
char *p;
int len = 0;
int send = 0;
char arrNumer[100];
p = line;
int itsNeg=0;


while(*p<48 || *p>57 )
{
if(*p=='-'){itsNeg=1;break;}
p++;
}

while(*p != '\0'){
/*first is type of int24. can found in words.h file */

arrNumer[i] = *p;
p++;
i++;
if(*p==',')
{

arrNumer[i] = '\0';
if(itsNeg)
	arrNumer[i-len] = '-';
	
sscanf(arrNumer, "%d", &send);
makeBinary(send, 23);
LINE++;		
len++;
p++;
i=0;
}

}

arrNumer[i] = '\0';
if(itsNeg)
	arrNumer[i-len] = '-';
	
sscanf(arrNumer, "%d", &send);
makeBinary(send, 23);
LINE++;	
len++;

DC += len;


return len;

}

/* 
 * @description this method check if there is any funct name
 * @param line is pointer to the location in the line that the program read right now
 * @return the funct number 1-16 or -1 if not fount, in case we searched to whole line and did not found any funct name will return -1;
 */
int checkFunct(char * line, preMila *pre_mila){
char ops [16][5]={"mov","cmp","add", "sub", "lea","clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"}; 
char *s;
int i;
if(*(line +1)== '\0'){
return -1;}
if(*(line +2) == '\0'){  
return -1;}
s = (char*)calloc(5, sizeof(char));
*s = *line;
*(s+1) = *(line +1);
*(s+2) = *(line +2);
for(i = 0;i<16;i++){
	if(!strcmp(s, ops[i])){
	pre_mila->operation = i;
	free(s);
	return i;
	}
}
if(*(line +3) != '\0'){  
*(s+3) = *(line +3);
if(!strcmp(s, ops[STOP])){
	pre_mila->operation = STOP;
	free(s);
	return STOP;
}
}
free(s);
return -1;
}

 

/* 
 * @description this method insert LABEL to the symbol table
 *label is label name
 *character is the type of label
 *value is location in the lines
 *return the number of line to jump
*/ 
void addSign(char label[50], char character[50], int value) {
	
    strcpy(curSNode->sign.label, label);
    curSNode->sign.value = (value);
    strcpy(curSNode->sign.car, character);

    SignNode *newSNode = (SignNode *) malloc(sizeof(SignNode));
    curSNode->next = newSNode;
    curSNode = newSNode;

}
/* 
 * @description this method takes a number and parse it to string of bits then insert it to the list
 *toPrint is the number
 *sibit is the number of bits
*/ 
void makeBinary(int toPrint,int sibit){

unsigned i; 

int j=0;

    for (i = 1 << sibit; i > 0; i = i / 2,j++) 
        if(toPrint & i){
        arr2[j]='1';
        }else{
        arr2[j]='0';
        }
          arr2[j]='\0';

strcpy(curWNode->word.number,arr2);
if(sibit==20)
strcat(curWNode->word.number, "100");
if(isString){
curWNode->word.line=LINE;	
}else if(foundInum&&found2||foundInum&&found4){
curWNode->word.line=++LINE;
}else{
curWNode->word.line=LINE++;	
}
wordsTableNode *newWNode = (wordsTableNode *) malloc(sizeof(wordsTableNode));
curWNode->next = newWNode;
curWNode = newWNode;



  
}


