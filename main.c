/*authors:
Hai Kedarya
Roei shoustak
*/
#include "main.h"
/* 
 * @description this is the main method 
 */
    int main(int argc, char* argv[]){
	int i;
	char * fileName;
        
        if(argc<2){
            fprintf(stderr, "No file found");
            exit(1);
        }
        
	fileName =  (char*) malloc(30 * sizeof(char));
        for (i = 1; i < argc; i++)
        {	
	    getFileName(argv[i], fileName);
            runProg(fileName);
        }
        exit(1);
    }
/* 
 * @description this method extrcat the parameters file name without the .as
 * @param argv is string with the file name
 * @param fileName is pointer to string at another function that will have the file name 
 */
void getFileName(char * argv, char * fileName){
int i = 0;
bool hasDot = 0;
while(1){
	if(*(argv+i) == '.'){
		hasDot = 1;
		break;
	}
	if(*(argv+i) == '\0'){
		break;
	}
	i++;
}
if(hasDot){
	memcpy(fileName, argv, i);
}else{
	strcpy(fileName, argv);
}
}


