#include "firstPass.h"
/* 
 * @description this method check if temp2 is extern
 *temp the sign that we want to check
 *temp2 check where is the line number of the extern has defined
*/ 
void checkIfExtern(DataNode*temp,SignNode *temp2){
  static int done2=1;


   while (done2!=0) {

      if(!temp->data.ic){done2=0;}
     
      if(temp2 == NULL){
      
	temp2= shead;
	checkIfExtern(temp->next,temp2);
      
      }
      
      if(!strcmp(temp->data.word,temp2->sign.label)&&temp2->sign.value==0){

 		if(temp2->sign.value==0){/*if the match was extern type*/
		
		strcpy(curEXNode->external.word,temp->data.word);
		curEXNode->external.ic=temp->data.ic;
		ExternalNode *newEXNode = (ExternalNode *) malloc(sizeof(ExternalNode));
		curEXNode->next = newEXNode;
		curEXNode = newEXNode;

      		}

      		temp2= shead;
      		checkIfExtern(temp->next,temp2);
      }

     		 temp2 = temp2->next;
   }
  
  }
/* 
 * @description this method sortes the final the list of the milim
 *temp the missing value 
*/ 
void SortLinkedList(wordsTableNode *temp)
    {

   wordsTableNode * temp2=temp->next;
   mila tempMila;
   char tempNUM[100];
   int tempvar;/*temp variable to store node data*/

    while(temp != NULL)
    {
        temp2=temp;
         
        while (temp2->next !=NULL)/*travel till the second last element */
        {
           if(temp2->word.line < temp->word.line)/*compare the data of the nodes */
            {
              
              tempMila = temp2->word.newMila;
              tempvar = temp2->word.line;
              strcpy(tempNUM,temp2->word.number);
              
              temp2->word.line = temp->word.line;/*swap the data*/
	      temp2->word.newMila = temp->word.newMila;/*swap the data*/
	     	strcpy(temp2->word.number,temp->word.number);
		
              temp->word.line = tempvar;
              temp->word.newMila = tempMila;
	      strcpy(temp->word.number,tempNUM);
            }
            
            
         temp2 = temp2->next;    /* move to the next element */
        }
        temp = temp->next;    /* move to the next node */
    }
}
/* 
 * @description this method compares between the missing values and the location in the sign label list 
 *temp the missing value 
 *temp2 the location of the label
*/ 
void compareLists(DataNode*temp,SignNode *temp2){
static int done=1;
  char *ptr;
  int dist;
int ispar=0;
   while (done!=0) {

      if(!temp->data.ic){done=0;}
     
      if(temp2 == NULL){
      
	temp2= shead;
	compareLists(temp->next,temp2);
      
      }
      		ptr = temp->data.word;
		if(*ptr == 38){/*if the match was & type*/
		ptr++;   
		strcpy(temp->data.word,ptr);
		ispar=1;
      		}
      
      if(!strcmp(temp->data.word,temp2->sign.label)){
      		
      	      	if(ispar){
      	      

      	      	binaryNum((curWNode->word.line)-(temp->data.ic),20);
		strcpy(curWNode->word.number,arr3);
		curWNode->word.line=temp->data.ic;
		wordsTableNode *newWNode = (wordsTableNode *) malloc(sizeof(wordsTableNode));
		curWNode->next = newWNode;
		curWNode = newWNode;
      	      	
      	      	}
      		
      		if(!ispar){
      		if(temp2->sign.value==0){/*if the match was extern type*/
		binaryNum(1,23);
		strcpy(curWNode->word.number,arr3);
		curWNode->word.line=temp->data.ic;
		wordsTableNode *newWNode = (wordsTableNode *) malloc(sizeof(wordsTableNode));
		curWNode->next = newWNode;
		curWNode = newWNode;
      		}
      		
      		if(temp2->sign.value!=0){/*if the match was not extern type*/
		binaryNum(temp2->sign.value,23);
		strcpy(curWNode->word.number,arr3);
		curWNode->word.line=temp->data.ic;
		wordsTableNode *newWNode = (wordsTableNode *) malloc(sizeof(wordsTableNode));
		curWNode->next = newWNode;
		curWNode = newWNode;
      		}      		
      		}

      		temp2= shead;
      		compareLists(temp->next,temp2);
      }

     		 temp2 = temp2->next;
     		 
   }
 }
	
/* 
 * @description this method parse the integer into bits in string
 *toPrint is the number
 *sibit is the number of bits
*/ 
void binaryNum(int toPrint,int sibit){

unsigned i; 

int j=0;

    for (i = 1 << sibit; i > 0; i = i / 2,j++) 
        if(toPrint & i){
        arr3[j]='1';
        }else{
        arr3[j]='0';
        }
          arr3[j]='\0';

if(sibit==20){
strcat(arr3, "100");
}
}

  
