#include "main.h"
#include "firstPass.h"

/* 
 * @description this method check if this label has value
 * @param str is the label name
 * @return will return the label value or -1 if no list exist,  0 if not found in the list
 */
int getEntryValue(char str[50]){
   SignNode *temp;
   if (shead == NULL) {
      return -1;
   }
   temp = shead;
   while (temp != NULL) {
      if(!strcmp(temp->sign.label,str)){
	return temp->sign.value;
      }
      
      temp = temp->next;
   }
  return 0;
}

/* 
 * @description this method opens an entry file and print all the entry list, if not items in entry list then wont open the file
 * @param fileName is pointer to string at another function that have the file name 
 */
 
void printExtern(char * fileName){
   FILE * fp;
   char file[30];
   ExternalNode * temp;
   
   if (exhead == NULL) {
      printf("List is empty.\n");
      return;
   }
   if(exhead->external.ic == 0){
      return;
   }
   strcpy(file, fileName);
   strcat(file, ".ext");
   fp = fopen(file, "w");/*open the file here*/
   if (fp == NULL){
            printf("cant open file name: %s\n", file);
   }
   temp = exhead;
   
   while (temp != NULL) { 
	if(temp->external.ic == 0){
	break;
	}
	fprintf(fp, "label name: %s  address: %d\n", temp->external.word,temp->external.ic);
	fprintf(fp,"========================= \n");
      temp = temp->next;
   }
   fclose(fp);
}

/* 
 * @description this method opens an entry file and print all the entry list, if not items in entry list then wont open the file
 * param fileName is pointer to string at another function that have the file name 
 */
void printEntry(char * fileName){
   FILE * fp;
   EntryNode * temp;
   char file[30];
   int check=0;
   
   if (ehead == NULL) {
      printf("List is empty.\n");
      return;
   }
   if(getEntryValue(ehead->entry.label) == 0){
	return;
   } 
   strcpy(file, fileName);
   strcat(file, ".ent");
   fp = fopen(file, "w");/*open the file here*/
   
   if (fp == NULL){
            printf("cant open file name: %s\n", file);
   }
   
   fprintf(fp,"========================= \n");
   fprintf(fp,"elements of ENTRIES list are : \n");
   fprintf(fp,"======================== \n");
   temp = ehead;
   check =getEntryValue(temp->entry.label);
   while (temp != NULL) {
      if(getEntryValue(temp->entry.label) == 0){
	break;
	}
      fprintf(fp, "%s  address: %d\n", temp->entry.label,getEntryValue(temp->entry.label));
      fprintf(fp,"========================= \n");
      temp = temp->next;
   }
   printf("\n");
   fclose(fp);
}
/* 
 * @description this method manage the whole process of reading the file
 * param fileName is pointer to string at another function that have the file name 
 */
void runProg(char * fileName){
    
	bool check =  0;
        
	check = firstParse(fileName);
	if(check == 1){/*if there is any problem with the firstpass*/
		printf("found an error at file: %s\n",fileName);
		return;
 	}
	seconedPass();
	printToFIles(fileName);
    }

/* 
 * @description this method prints to the information into the files
 * param fileName is pointer to string at another function that have the file name 
 */
void printToFIles(char *fileName){

printEntry(fileName);
printExtern(fileName);
printMilim(fileName);
}



