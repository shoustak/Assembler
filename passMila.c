#include "firstPass.h"
/* 
 * @description this method parse the interger
 *param bstr is a pointer to the string
*/ 
int dec(char bstr[])
{

int i=0;
int len  = strlen(bstr);
int sum = 0;
int j = 0;

for(i=(len-1);i>=0;i--)
{
    sum = sum + (pow(2,i) * (bstr[j] - '0'));
    j++;
}
return sum;
}


/* 
 * @description this method prints the milim list into the file.ob
 *param fileName is a pointer to the file name
*/ 
void printMilim(char*fileName){
 char file2[30]; 
 int numConv[80];    
 int a[25],b[25],c[25],d[25],e[25],f[25],g[25];   
     
 FILE * fp2;
 wordsTableNode *temp;
    int conv;
   if (whead == NULL) {
      printf("List is empty.\n");
      return;
   }

       strcpy(file2, fileName);
       strcat(file2, ".ob");
          
fp2 = fopen(file2, "w");/*open the file here*/
   
   if (fp2 == NULL){
            printf("cant open file name: %s\n", file2);
   }
    

temp = whead;

while (temp != NULL) {
   
if(temp->word.line == 0)break;
   
fprintf(fp2,"line %d: ", temp->word.line);

if(strcmp(temp->word.number, "")){
strcpy(numConv,temp->word.number);
fprintf(fp2,"%07x\n",dec(numConv));

}

if(!strcmp(temp->word.number, "")){

strcpy(a,temp->word.newMila.opCode);

strcpy(b,temp->word.newMila.sourceMiun);
strcat(a, b);
   
     
strcpy(c,temp->word.newMila.sourceRegister);
strcat(a, c);

strcpy(d,temp->word.newMila.destinationMiun);
strcat(a, d);

strcpy(e,temp->word.newMila.destinationRegister);
strcat(a, e);

strcpy(f,temp->word.newMila.funct);
strcat(a, f);

strcpy(g,temp->word.newMila.a_r_e);
  
strcat(a, g);   
   
   
fprintf(fp2,"%07x\n",dec(a));
}

      
temp = temp->next;
}

      fclose(fp2);
}
/* 
 * @description this method checkes for any erors in the given parameters and fucntions
 *param myMila is a pointer to the given mila 
 *param pre_mila is a pointer to where we take from the parameters
 *param numOfParam idicates us how many parameters we got
 *return will return 1 if no eror have found and -1 if there is eror
*/ 
int checkForErorrs(preMila *pre_mila, mila *myMila, int numOfParam){

if(pre_mila->param1_miun < 0){
	strcpy(myMila->sourceMiun,"00");
}
if(!pre_mila->first_register){
	strcpy(myMila->sourceRegister,"000");
}
if(!pre_mila->param2_miun < 0){
	strcpy(myMila->destinationMiun,"00");
}

if(!pre_mila->second_register){
	strcpy(myMila->destinationRegister,"000");
}

if(numOfParam == -2 || numOfParam ==-3 ||numOfParam == 0){
	return 1;
}
if(pre_mila->operation >= RTS){
		if(pre_mila->first_register > 0 || pre_mila->second_register > 0){
			printf("found error at line: %d no need for parameters\n",LINE );
			return 1;
		}
		if(pre_mila->param1_miun > 0 && pre_mila->param1_miun > 0){
			printf("found error at line: %d no need for parameters\n",LINE );
			return 1;
			}
		if((strcmp("",pre_mila->param1)) || (strcmp("",pre_mila->param2))){
			printf("found error at line: %d no need for parameters\n",LINE );
			return 1;
		}
}
if(pre_mila->operation <= LEA){/*if we need 2 parameters*/
		if((!strcmp("",pre_mila->param1)) || (!strcmp("",pre_mila->param2))){/*if we got 1 parameter*/
			if(pre_mila->param1_miun < 0 && pre_mila->param1_miun < 0){
			printf("found error at line: %d need 2 parameters found less\n",LINE );
				return 1;
			}
		}
}
if(pre_mila->operation >= CLR && pre_mila->operation <= PRN){
	if(!pre_mila->first_register || !pre_mila->second_register){
		if(!strcmp("",pre_mila->param2) && !strcmp("",pre_mila->param1)){
			if(pre_mila->param1_miun < 0 && pre_mila->param1_miun < 0){
				printf("found error at line: %d no parameters need 1\n",LINE );
				return 1;
			}
		}
	}
}
return 0;
}

/* 
 * @description this method called from checkIfParamIsLabel if we have label name in the parameters
and assigning the proper A_R_E code  
 *param myMila is a pointer to the given mila that we want to assign 
 *param pre_mila is a pointer to where we take from the parameters
 *param numOfParam idicates us witch param is the label to check
 *return return 1 if its entry
*/ 
int checkEntryOrExtern(preMila *pre_mila, mila *myMila, int numOfParam){
bool dataType = 0;
bool isXtr = 0;
SignNode *tmp;
if (shead == NULL) {
	printf("entry List is empty checkEntryOrExtern().\n");
	return;
}
tmp = shead ;
while (tmp != NULL) {
if(numOfParam == 1){
	if(!strcmp(tmp->sign.label, pre_mila->param1)){
		if(!strcmp(tmp->sign.car,"external")){
			isXtr =1;
			break;
		}else if((!strcmp(tmp->sign.car,"string"))||(!strcmp(tmp->sign.car,"data"))){
			dataType =1;
			break;
		}
		
	}
}else if (numOfParam == 2){
	if(!strcmp(tmp->sign.label, pre_mila->param2)){
		if(!strcmp(tmp->sign.car,"external")){
			isXtr =1;
			break;
		}else if((!strcmp(tmp->sign.car,"string"))||(!strcmp(tmp->sign.car,"data"))){
			dataType =1;
			break;
		}
		
	}
}else if(numOfParam == 3){
	if(!strcmp(tmp->sign.label, pre_mila->param1)){
		if(!strcmp(tmp->sign.car,"external")){
			isXtr =1;
			break;
		}else if((!strcmp(tmp->sign.car,"string"))||(!strcmp(tmp->sign.car,"data"))){
			dataType =1;
			break;
		}
	}
	if(!strcmp(tmp->sign.label, pre_mila->param2)){
		if(!strcmp(tmp->sign.car,"external")){
			isXtr =1;
			break;
		}else if((!strcmp(tmp->sign.car,"string"))||(!strcmp(tmp->sign.car,"data"))){
			dataType =1;
			break;
		}
	}
}
        tmp = tmp->next;
   }

if(isXtr){
	strcpy(myMila->a_r_e,"001");
}else if(dataType){
	strcpy(myMila->a_r_e,"010");
}else{
	strcpy(myMila->a_r_e,"100");
}

}
/* 
 * @description this method check if there is any label in the parameters 
 *param myMila is a pointer to the given mila that we want to assign 
 *param pre_mila is a pointer to where we take from the parameters
 *return will return 0 if there is no label in the parameter,return 1 if label appeared in first param or second param
*/ 

int checkIfParamIsLabel(preMila *pre_mila, mila *myMila){
int s = 0;
s = checkInWitchParamLabel(pre_mila,myMila);


if(s > 0){
	strcpy(myMila->a_r_e,"100");
	if(s == 3){

		if(pre_mila->param1_miun<0){/*if we dont have miun for this param*/
			pre_mila->param1_miun = MIUN1;
			strcpy(myMila->sourceMiun,"01");
			checkEntryOrExtern(pre_mila, myMila ,1);
		}/*if we dont have miun for this param*/		
		if(pre_mila->param2_miun< 0){/*if we dont have miun for this param*/
			pre_mila->param2_miun = MIUN1;
			strcpy(myMila->destinationMiun,"01");
			checkEntryOrExtern(pre_mila, myMila ,2);
		}
	}	
	if(s == 1){
		if(pre_mila->param1_miun){
			if(!(pre_mila->param1_miun == MIUN2)){
				pre_mila->param1_miun = MIUN1;
				strcpy(myMila->sourceMiun,"01");
				strcpy(myMila->a_r_e,"100");
			}else{
				pre_mila->param1_miun = MIUN2;
				strcpy(myMila->sourceMiun,"01");
				checkEntryOrExtern(pre_mila, myMila ,s);
			}
		}else{
			pre_mila->param1_miun = MIUN2;
			strcpy(myMila->sourceMiun,"01");
			checkEntryOrExtern(pre_mila, myMila ,s);
		}
	}
	if(s == 2){	
		if(!pre_mila->param2_miun){
			if(!(pre_mila->param2_miun == MIUN2)){
				pre_mila->param2_miun = MIUN1;
				strcpy(myMila->destinationMiun,"01");
				strcpy(myMila->a_r_e,"100");
			}else{
				pre_mila->param2_miun = MIUN2;
				strcpy(myMila->destinationMiun,"01");
				checkEntryOrExtern(pre_mila, myMila ,s);
			}
		}else{
			pre_mila->param2_miun = MIUN2;
			strcpy(myMila->destinationMiun,"01");
			checkEntryOrExtern(pre_mila, myMila ,s);
		}
	}
}else{
	strcpy(myMila->a_r_e,"100");
	return 0;
}
	return 1;
}

/* 
 * @description this method indicates in witch parameter we have label

 *param myMila is a pointer to the given mila 
 *param pre_mila is a pointer to the given pre_mila 
 *return returns 1 if there is label in first param
or 2 if there is label in second param, return 3 if both parameters have label
*/ 
int checkInWitchParamLabel(preMila *pre_mila, mila *myMila){

char check[100]; 
int i = 0;
bool firstIslabel = 0;
int count = 1;
if(pre_mila->first_register || pre_mila->operation > LEA){
	if(pre_mila->second_register){
		return 0;
	}
	count = 2; 
	strcpy(check, pre_mila->param2);
}else{
	strcpy(check, pre_mila->param1);
}
int i3 = 0;
while(1){
if(check[i] == '\0'){
	if(count == 1){
		firstIslabel =1;
		count = 2;
		strcpy(check, pre_mila->param2);
		i = 0;
		if(pre_mila->param2_miun == MIUN3){/*if its register*/
			return 1;
		}
		continue;
	}else{
		if(firstIslabel){
			return 3;
		}
		return count;
	}	
}
i3++;

if(i3 == 30){
	break;
}
if(i >= 100){/*break move to second param*/

	if(count == 1){
		firstIslabel =1;
		strcpy(check, pre_mila->param2);
		i = 0;
		if(pre_mila->param2_miun == MIUN3){/*if its register*/
			return 1;
		}
		i++;
		continue;
	}else{
		if(firstIslabel){
			return 3;
		}
		return count;
	}	
}else if (check[i] == '\0'){/*break move to second param*/

	if(count == 1){
		firstIslabel =1;
		strcpy(check, pre_mila->param2);
		i = 0;
		if(pre_mila->param2_miun == MIUN3){/*if its register*/
			return 1;
		}
		i++;
		continue;
	}else{
		if(firstIslabel){
			return 3;
		}
		return count;
	}
}
if(check[i] == '&'){/*its miun 2*/

	if(check[i] == '&'){
		strcpy(myMila->a_r_e,"100");
		if(count == 1){
			pre_mila->param1_miun = MIUN2;
			strcpy(myMila->sourceMiun,"10");
		}else{
			pre_mila->param2_miun = MIUN2;
			strcpy(myMila->destinationMiun,"10");
		}
	}
	i++;
	if(!isalpha(check[i])){
		if(count == 1){
			if(pre_mila->param2_miun == MIUN3){/*if its register*/
			return 0;
			}
			strcpy(check, pre_mila->param2);
			i = 0;
			if(check[i] == '&'){
				i++;
				if(!isalpha(check[i])){
					return 0;
				}
			}
		}else{
			return 0;
		}	
	}
}
if(isalpha(check[i]) || isdigit(check[i])){

		i++;	
		continue;
}else{

	if(count == 2){
		if(check[i] == '\0'){
			if(firstIslabel){
			return 3;
			}
			return 2;	
		}
	}
	i = 0;
	strcpy(check, pre_mila->param2);
	count = 2;
	i++;
	continue;
}
	i++;
}
return count;
}

/* 
 * @description this method reset the values 
 *param myMila is a pointer to the given mila that we want to reset
 *param pre_mila is a pointer to the given pre_mila that we want to reset
*/ 
void resetValues(preMila *pre_mila,mila *myMila){
pre_mila->first_register=0;
pre_mila->second_register=0;
pre_mila->has_label=0;
pre_mila->operation = -1;
int hasGuide = 0;
memset(pre_mila->param1, 0, 100);
memset(pre_mila->param2, 0, 100);
pre_mila->param1_miun=-1;
pre_mila->param2_miun=-1;

memset(myMila->opCode, 0, 6);
memset(myMila->sourceMiun, 0, 2);
memset(myMila->sourceRegister, 0, 3);
memset(myMila->destinationMiun, 0, 2);
memset(myMila->destinationRegister, 0, 3);
memset(myMila->funct, 0, 5);
memset(myMila->a_r_e, 0, 3);
myMila->number = 0;
}
/* 
 * @description this method assigning values to the registers if there is any "r0-7" in line.param1-2
 *param myMila is a pointer to the given mila that we want to change
 *param (struct) line we take from him the  
*/ 
void assignRegistersValues(preMila *pre_mila,mila *myMila){
char regs [8][3] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"}; 
   int count = 0;
   int found=0;
   char check[100];
   strcpy(check, pre_mila->param1);/*assign check array the value of param1 */
   int i; 
   int i2;
   int j=0;   
	for(i = 0; i < 9;i++){/*this loop will run until it will find r0-r7 or not*/
		if(strcmp("",pre_mila->param1) == 0){

			found2=0;
			break;
		}	
		
		if(strcmp(regs[i],pre_mila->param1) == 0){
			found2=0;
			break;
		}
		
		if(!strcmp(regs[i],pre_mila->param1) == 0){
			found2=1;
		}
			
	}
	if(found2){
			IC+=1;
			strcpy (curDNode->data.word,pre_mila->param1);
			missingLine=LINE+1;	
			curDNode->data.ic=missingLine;
			DataNode *newDNode = (DataNode *) malloc(sizeof(DataNode));
   			curDNode->next = newDNode;
   			curDNode = newDNode;		
	}
	for(i = 0; i < 9;i++){/*this loop will run until it will find r0-r7 or not*/
		
		if(strcmp("",pre_mila->param2) == 0){

			found4=0;
			break;
		}
		
		if(!strcmp(regs[i],pre_mila->param2) == 0){
			found4=1;
		}
		
		if(strcmp(regs[i],pre_mila->param2) == 0){
			found4=0;
			break;
		}	
	}	
	if(found4){ /*in line line "add r3,K" keep the K to check if exist in seconed pass*/

			IC+=1;
			strcpy (curDNode->data.word,pre_mila->param2);
			
			if(found2){
			LINE+=1;
			missingLine=LINE+1;
			}
			else{
			missingLine=LINE+1;
			}	
			curDNode->data.ic=missingLine;
			DataNode *newDNode = (DataNode *) malloc(sizeof(DataNode));
   			curDNode->next = newDNode;
   			curDNode = newDNode;
		}
	
while(count <= 1){	
	for(i2 = 0; i2 < 9;i2++){/*this loop will run until it will find r0-r7 or not*/
		if(!strcmp(regs[i2],check)){
			strcpy(myMila->a_r_e,"100");
			break;
		}	
	}
   switch(i2){
	case(0):
	if(count){
	    pre_mila->second_register = 1;
	    pre_mila->param2_miun = MIUN3;
	    strcpy(myMila->destinationRegister,"000");
	    strcpy(myMila->destinationMiun,"11");
	}else{
	    pre_mila->param1_miun = MIUN3;
	    pre_mila->first_register = 1;
	    strcpy(myMila->sourceRegister,"000");
	    strcpy(myMila->sourceMiun,"11");	    
	}
	break;
	case(1):
	if(count){
	    pre_mila->second_register = 2;
	    pre_mila->param2_miun = MIUN3;
	    strcpy(myMila->destinationRegister,"001");
	    strcpy(myMila->destinationMiun,"11");
	}else{
	    pre_mila->first_register = 2;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"001");
	    strcpy(myMila->sourceMiun,"11");
	}
	break;
	case(2):
	if(count){
	    pre_mila->second_register = 3;
	    pre_mila->param2_miun = MIUN3;
	    strcpy(myMila->destinationRegister,"010");
	    strcpy(myMila->destinationMiun,"11");
	}else{
	    pre_mila->first_register = 3;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"010");
	    strcpy(myMila->sourceMiun,"11");
	}
	break;
	case (3):
	if(count){
	    pre_mila->second_register = 4;
	    pre_mila->param2_miun = MIUN3;	
	    strcpy(myMila->destinationRegister,"011");
	    strcpy(myMila->destinationMiun,"11");
	}else{
	    pre_mila->first_register = 4;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"011");
	    strcpy(myMila->sourceMiun,"11");
	}
	break;
	case(4):
	if(count){
	    pre_mila->second_register = 5;
	    pre_mila->param2_miun = MIUN3;	
	    strcpy(myMila->destinationRegister,"100");
	    strcpy(myMila->destinationMiun,"11");
	}else{
	    pre_mila->first_register = 5;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"100");
	    strcpy(myMila->sourceMiun,"11");	
	}
	break;
	case(5):
	if(count){
	    pre_mila->second_register = 6;
	    pre_mila->param2_miun = MIUN3;	
	    strcpy(myMila->destinationRegister,"101");
	    strcpy(myMila->destinationMiun,"11");
	}else{
	    pre_mila->first_register = 6;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"101");
	    strcpy(myMila->sourceMiun,"11");	
	}
	break;
	case(6):
	if(count){
	    pre_mila->second_register = 7;
	    pre_mila->param2_miun = MIUN3;	
	    strcpy(myMila->destinationRegister,"110");
	    strcpy(myMila->destinationMiun,"11");
	}else{
	    pre_mila->first_register = 7;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"110");
	    strcpy(myMila->sourceMiun,"11");	 
	}
	break;
	case(7):
	if(count){
	    pre_mila->second_register = 8;
	    pre_mila->param2_miun = MIUN3;
   	    strcpy(myMila->destinationRegister,"111");
	    strcpy(myMila->destinationMiun,"11");
	}else{
	    pre_mila->first_register = 8;
	    pre_mila->param1_miun = MIUN3;
	    strcpy(myMila->sourceRegister,"111");
	    strcpy(myMila->sourceMiun,"11");	  
	}
	break;
	default:
	if(count){/*check later if needed to cancel the MIUN assiment*/
	    pre_mila->second_register = 0;
   	    strcpy(myMila->destinationRegister,"000");
	}else{
	    pre_mila->first_register = 0;
	    strcpy(myMila->sourceRegister,"000"); 
	}
	break;
	}
	count ++;	
        strcpy(check, pre_mila->param2);/*assign check array the value of param2 */
	
    }
    }

/* 
 * @description this method assign the mila number value
 *param line is pointer to the line after getting the function name
 *return will return -1 if there is corrupted patameter, will return number of char that readen by this function
*/ 

int getNumber(char * line,mila *myMila){
char *ptr = line;
bool check = 0;/*indicates that we got any data*/
bool negative = 0;/*indicates that we got negative data*/
int i =0;
int num = 0;

if(*ptr == '#'){
	i++;
	ptr++;		
}

while(*ptr != '\0'){
	if(isspace(*ptr)){
		if(check == 1){/*corrupted patameter (has a space between data)*/
			break;
		} 
	i++;
	ptr++;
	continue;
	}
	if(*ptr == COMMA){
		break; 
	}
	
	if(*ptr == '-'){
		if(check == 0 && negative == 0){
			negative = 1;
			check = 1;
			ptr++;
			i++;
			continue;
		}else{/*5*/
			return -1;
		}
	}
	if(isdigit(*ptr)){
		if(check == 0){			
			num = *ptr - 48;
			check = 1;
		}else{		
		check = 1;
		num = num * 10;
		num += *ptr - 48;			
		}
	}else{/*corrupted patameter (has something diffrent from whole number;)*/
		return -1;
	}
++ptr;
++i;
}/*end of loop*/
	if(negative){
		num = num * -1;
	}
	strcpy(myMila->a_r_e, "100");
	myMila->number = num;
ifNum = 1 ;
	/*makeBinary(myMila->number,20);*/
	return i;
}

/* 
 * @description this method assign values to the preMila values
 *param line is pointer to the line after getting the function name
 *param preMila is a pointer to the given preMila that we want to change
 *return will return 2 if we got 2 parameters with values. 1 if got one parameter, -2 if we got comma with no parameters, -1 if we got no parameters, 0 if there is illegal operand info, -3 if there is too much commas
*/ 

int getParameters(char * line,preMila *myPreMila, mila *myMila){
bool typeOfOperation;
if(PRN >= myPreMila->operation && myPreMila->operation >= CLR){
	typeOfOperation = 2;	
	strcpy(myMila->sourceRegister,"000");
	strcpy(myMila->sourceMiun, "00");  
}
if(myPreMila->operation <= LEA){
	typeOfOperation = 1;
}
if(myPreMila->operation >= RTS){	
	strcpy(myMila->sourceRegister,"000");
	strcpy(myMila->sourceMiun, "00");
	strcpy(myMila->destinationRegister,"000");
	strcpy(myMila->destinationMiun, "00");
	strcpy(myMila->a_r_e, "100");
	typeOfOperation = 2;
}
char *ptr = line;
char *ptr2;
char gotParameter = 0;/*act as a boolean that idicates us to assign value to the next parameter in the mila*/
/*if(typeOfOperation == 2){
	gotParameter = 1;
}*/
char *temp = (char*) calloc(100,sizeof(char));  
int i =0;
int i2;
while(*ptr != '\0'){
	if(isspace(*ptr)){
	ptr++; 
	}
	if(*ptr == COMMA){
		if(gotParameter >= 1 || typeOfOperation != 1){
			printf("found error at line: %d there is too much commas", LINE);
			return -3;/* there is too much commas */
		}	
		if(*temp == 0){/*eror got comma without parameter*/
			printf("found error at line: %d got comma without paramete", LINE);
			return -1;
		}
		for(i2 = 0;i2<=i;i2++){
			*(myPreMila->param1+i2) = *(temp +i2);
		}
	free(temp);
	temp = (char*) calloc(100,sizeof(char));  
	gotParameter++;
	ptr++;
	i=0;	
	}	
	if(!isspace(*ptr)){
		if(*ptr == '#'){/*this parameter has miun 0 value*/
			i2 = 0;
			i2 = getNumber(ptr, myMila);/*go get the number value*/
			if(i2 == -1){/*no number*/
				return -2;
			}else{
				ptr = ptr + i2;/*skip the chars that we read in getNumber fucntion*/
				if(gotParameter){
					strcpy(myMila->destinationMiun, "00");
					myPreMila->param2_miun = MIUN0;/*MIUN1*/
				}else{
					strcpy(myMila->sourceMiun, "00");
					myPreMila->param1_miun = MIUN0;
				}
				while(*ptr != COMMA && *ptr != '\0'){
					ptr++;
				}		
			}
		}
		if(*ptr == '&'){/*this parameter has miun 2 value*/
			strcpy(myMila->a_r_e, "100");
			if(!gotParameter){
			strcpy(myMila->sourceMiun, "10");
			myPreMila->param1_miun = MIUN2;
			}else{
			strcpy(myMila->destinationMiun, "10");
			myPreMila->param2_miun = MIUN2;
			}
		}
	*(temp+i) = *ptr;
	i++;
	}
	if(*ptr == '\0'){
		break;
	}
	ptr++;
}
for(i2 = 0;i2<=i;i2++){
*(myPreMila->param2+i2) = *(temp +i2);
}
return 2;
}


/* 
 * @description this method assign the opcode amd funct values of the given pointed mila
 *param line is the line struct that we extract from that opcode
 *param myMila is a pointer to the given mila that we want to change
*/ 
int makepOpCodeAndFunct(int funct,mila *myMila){  
    switch(funct){
	case(MOV):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "000000");
	break;
	case(CMP):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "000001");
	break;

	case(ADD):
	strcpy(myMila->funct, "00001");
	strcpy(myMila->opCode, "000010");
	break;

	case(SUB):
	strcpy(myMila->funct, "00010");
	strcpy(myMila->opCode, "000010");
	break;

	case(LEA):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "000100");
	break;

	case(CLR):
	strcpy(myMila->funct, "00001");
	strcpy(myMila->opCode, "000101");
	break;

	case(NOT):
	strcpy(myMila->funct, "00010");
	strcpy(myMila->opCode, "000101");
	break;

	case(INC):
	strcpy(myMila->funct, "00011");
	strcpy(myMila->opCode, "000101");
	break;

	case(DEC):
	strcpy(myMila->funct, "00100");
	strcpy(myMila->opCode, "000101");
	break;

	case(JMP):
	strcpy(myMila->funct, "00001");
	strcpy(myMila->opCode, "001001");
	break;

	case(BNE):	
	strcpy(myMila->funct, "00010");
	strcpy(myMila->opCode, "001001");
	break;

	case(JSR):
	strcpy(myMila->funct, "00011");
	strcpy(myMila->opCode, "001001");
	break;

	case(RED):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "001100");
	break;

	case(PRN):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "001101");
	break;	

        case(RTS):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "001110");
	break;       
 
	case(STOP):
	strcpy(myMila->funct, "00000");
	strcpy(myMila->opCode, "001111");
	break;
        default:
	return 1;/*eror code 1 = no operation code!!*/
	break;
	return 0;/*everything is ok*/
    }
}    


