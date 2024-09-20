#include <unistd.h>
#include <string.h>
#include "command.h"
#include "run.h"

int validate(command_line command){
    char* cm = NULL;
    
    if(command.num_token == 0){
        write(2, "Error! Unrecognized Command!\n", 29);
        return 0;
    }else{
        cm = command.command_list[0];
        if(strcmp(cm, "exit") == 0){
            return 1;
        }else if(strcmp(cm, "ls") == 0 || strcmp(cm, "pwd") == 0){
            interactive_mode(command);
        }else if(strcmp(cm, "mkdir") == 0 || strcmp(cm, "cd") == 0 || strcmp(cm, "cp") == 0 ||strcmp(cm, "mv") == 0 ||strcmp(cm, "rm") == 0 ||strcmp(cm, "cat") == 0){
            file_mode(command);
        }else{
            write(2, "Error! Unrecognized command: ", 29);
            write(2, cm, strlen(cm));
            write(2, "\n", 1);
        }
                 
    }

    return 0;
}

     
void interactive_mode(command_line tokens){
    char* cm = tokens.command_list[0];

    if (tokens.num_token > 1){
            error_parameters(cm);
        }
    
    if(strcmp(cm, "ls") == 0){
        listDir();
    }else{
        showCurrentDir();
    }
}


void file_mode(command_line tokens){
    char* cm = tokens.command_list[0];

    if(strcmp(cm, "mkdir") == 0){
        if(tokens.num_token == 2){
            makeDir(tokens.command_list[1]);
        }else{
            error_parameters(cm);}
    }else if(strcmp(cm, "cd") == 0){
        if(tokens.num_token == 2){
            changeDir(tokens.command_list[1]);
        }else{
            error_parameters(cm);}
    }else if(strcmp(cm, "cp") == 0){
        if(tokens.num_token == 3){
            copyFile(tokens.command_list[1], tokens.command_list[2]);
        }else{
            error_parameters(cm);}
    }else if(strcmp(cm, "mv") == 0){
        if(tokens.num_token == 3){
            moveFile(tokens.command_list[1], tokens.command_list[2]);
        }else{
            error_parameters(cm);}
    }else if(strcmp(cm, "rm") == 0){
        if(tokens.num_token == 2){
            deleteFile(tokens.command_list[1]);
        }else{
            error_parameters(cm);}
    }else{
        if(tokens.num_token == 2){
            displayFile(tokens.command_list[1]);
        }else{
            error_parameters(cm);}
    }
}


void error_parameters(char* cm){
    write(2, "Error! Unsupported parameters for command: ", 43);
    write(2, cm, strlen(cm));
    write(2, "\n", 1);

}
