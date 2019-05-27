#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){


	// if(argc != 2){
	// 	printf("usage ./a Path_To_Directory\n");
	// 	printf("For Example:\n\n");
	// 	printf("If \"BCompSci\" Folder Contains all the files that you want to process\n");
	// 	printf("Then command for running is   -->    ./a BCompSci\n");
	// 	return 0;
	// }

	char fileNameArgv[100];
	printf("Enter the name of directory that have files: ");
	scanf("%s", fileNameArgv);
	printf("\nTransferring all files from %s To output folder in this directory..\n",fileNameArgv);
	char *s = "ls";
	char tmp[] = "ls ";
	
	char tmp_loc[] = "|sort >> temp.txt";


	
	s = malloc(strlen(fileNameArgv) + 20);
	
	strcat(s, tmp);
	strcat(s,fileNameArgv);
	strcat(s,tmp_loc);
	//printf("%s\n",s );
	system(s);
	
	char inputFile[200];
	FILE *fp = fopen("temp.txt", "r");

	system("mkdir output");	
	printf("-------------------------\n"
			"|	Copying files...|\n"
			"-------------------------\n");

	while(fgets(inputFile, 200, fp) != NULL){
		
		char dir_name[200] = "";//resetting the string
		int breakLoop = 0;
		for(int i = 0; (i < strlen(inputFile)) && (breakLoop == 0); i++){
			//NOT INCLUDING . and /
			//--CHECKING FOR ALL SPECIAL CHAR--if the current char is special
			if((inputFile[i] >= 33 && inputFile[i] <= 45) || (inputFile[i] >= 58 &&
			 	inputFile[i] <= 64) ||	(inputFile[i] >= 91 && inputFile[i] <= 96) || 
				(inputFile[i] >= 123 && inputFile[i] <= 127 )){
				//printf("SPECIAL CHARACHTER OBSERVED--- %c -number-%i\n", inputFile[i], inputFile[i]);


				dir_name[i] = '\0'; 
				char cmnd[100] ="ls ./output/";
				strcat(cmnd, dir_name);
				strcat(cmnd, " 2>> outputCurrDir.txt"); // THis file will not get the error if there is a directory that have 
				//same (and will be empty). and it will have some error if there is no directory of that name
				
				system(cmnd);

				FILE *outputFile = fopen("outputCurrDir.txt", "r");
				char fileName[200];

				//IN THIS IF--THERE IS A Directory in the output folder that will have a directory of current name
				if(fgets(fileName, 200, outputFile) == NULL){
					//Making the copy command that will copy the current file from argv[1] directory and
					//put it in the ./output/Current_dir  
					strcpy(cmnd, "cp ");
					strcat(cmnd, fileNameArgv);
					strcat(cmnd, "/");
					char *pos;
					if ((pos=strchr(inputFile, '\n')) != NULL)
   						*pos = '\0';
					strcat(cmnd, inputFile);
					strcat(cmnd, " ");
					strcat(cmnd, "./output/");
					strcat(cmnd, dir_name);
					system(cmnd);//Executing the command
					breakLoop = 1;
					//SO- HERE take the file and cp it to the sub directory
					//Break out of the for loop
				}
				//IF IT IS NOT NUll THEN there is an error which indicates that there is no directory
				//of that name inside the output folder
				else{
					//make a new directory of that name--dir_name array
					strcpy(cmnd, "mkdir ");
					strcat(cmnd, "./output/");
					strcat(cmnd, dir_name);
					system(cmnd);

					char cmnd_for_subdirs[200];
					strcpy(cmnd_for_subdirs, cmnd);
					strcat(cmnd_for_subdirs,"/Picks");
					system(cmnd_for_subdirs);
					strcpy(cmnd_for_subdirs,cmnd);
					strcat(cmnd_for_subdirs,"/Culls");
					system(cmnd_for_subdirs);
					//Move the file to that
					strcpy(cmnd, "cp ");
					strcat(cmnd, fileNameArgv);
					strcat(cmnd, "/");
					char *pos;
					if ((pos=strchr(inputFile, '\n')) != NULL)
   						*pos = '\0';
					strcat(cmnd, inputFile);
					strcat(cmnd, " ");
					strcat(cmnd, "./output/");
					strcat(cmnd, dir_name);
					system(cmnd);



					breakLoop = 1;
					//Break out of the for loop
				}
				system("rm outputCurrDir.txt");
			}
			//if there is no special char it will keep adding to the dir name
			else{
				dir_name[i] = inputFile[i];
			}
			
		}
	}
	system("rm temp.txt");
	printf("\nSuccessfully copied files to sub directories in output folder!\n");
}






