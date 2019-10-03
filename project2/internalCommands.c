#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <sys/types.h>
#include "shell.h"







  	void printDir(){
  	char cwd[1024];
  	getcwd(cwd, sizeof(cwd));
  	printf("\nDirectory: %s", cwd);
  	}


  	int quit(){
	printf("\nThank you for using this shell. Good bye\n");
	exit(0);
	}

	int cd(struct simple_command com){
	if (com.arguments[1] == NULL) {
    	printDir();
    	}else if(chdir(com.arguments[1])<0){
	printf("unable to open directory\n");
	return 0;
	}else{
      	chdir(com.arguments[1]);
		printDir();
    	}
    	return 1;
  	}

	int help(struct simple_command com){
  	puts("\n***WELCOME TO MY SHELL HELP***"
  	"\nCommands supported by this shell:"
	"\n>quit"
  	"\n>cd"
	"\n>help"
	"\n>pause"
  	"\n>dir"
  	"\n>echo"
	"\n>enviro"
	"\n>clr"
  	"\n>all other general commands available through the UNIX shell"
  	"\n>this shell also performs pipe handling, background execution, redirection, and batch execution"
  	"\n>Use the man command for information on other commands"
	"\n>Have fun using this shell!");
  	return 1;
	}

	int pause(){
	getchar();
	return 1;
	}

	int dir(struct simple_command com){
	char cwd[1024];
	getcwd(cwd,sizeof(cwd));
	DIR *p;
	struct dirent *d;
	p=opendir(cwd);
	if(p==NULL){
  	perror("Cannot find directory");
  	return 0;
  	}
	while(d=readdir(p)){
  	printf("%s\n",d->d_name);
	}
	return 1;
	}

	int echo(struct simple_command com){
	int i=1;
	while(com.arguments[i]!= NULL){
  	printf("%s ", com.arguments[i]);
	i++;
	}
  	return 1;
	}

	int enviro(struct simple_command com){
	char* username=getenv("USER");
	char* homeDir=getenv("HOME");
	char* editor=getenv("EDITOR");
	char* userID=getenv("UID");
	char* terminalEmulator=getenv("TERM");
	char* shell=getenv("SHELL");
  	printf("\n\nUser is: @%s\n", username);
	printf("Home Directory is: @%s\n", homeDir);
	printf("Editor is: @%s\n", editor);
	printf("Your unique user ID is: @%s\n", userID);
	printf("The terminal emulator is: @%s\n", terminalEmulator);
	printf("The shell you are using is: @%s\n", shell);
  	return 1;
	}

	int clr(){
	printf("\033[H\033[J");
  	return 1;
	}

  	int internalCommands(struct simple_command com){
    	int commandNum=0;
  	for (int i = 0; i < numInternalCommands; i++) {
        	if (strcmp(com.word, intCommands[i]) == 0) {
            	commandNum = i+1;
            	break;
        	}
    	}
    	switch (commandNum) {
    	case 1:
	        quit();
		return 1;
     	case 2:
        	cd(com);
		return 1;
      	case 3:
        	help(com);
		return 1;
    	case 4:
		pause();
		return 1;
    	case 5:
		dir(com);
		return 1;
    	case 6:
	        echo(com);
		return 1;
    	case 7:
		enviro(com);
		return 1;
    	case 8:
	      	clr();
		return 1;
    	default:
        	break;
    	}

    	return 1;
	}




