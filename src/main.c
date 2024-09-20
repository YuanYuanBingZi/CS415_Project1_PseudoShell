#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <fcntl.h>


#include "string_parser.h" 
#include "run.h"
#include "main.h"

#define _GNU_SOURCE

int main(int argc, char** argv){
    if (argc == 1) {
        // No command line arguments, run in interactive mode
        run_interactive_mode();
    } else if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        // Run in file mode
        char *input_file = argv[2];
        run_file_mode(input_file);
    } else {
        write(2, "Usage:\n", 7);
        write(2, "Interactive mode: ./pseudo_shell\n", 33);
        write(2, "File mode: ./pseudo_shell -f <filename>\n", 40);
    }

    return 0;
}

    
void run_interactive_mode(){
    while(1){
        write(1, ">>> ", 4);

	    char* input = NULL;
        size_t input_size = 0;
        command_line line_commands;
        command_line command;
        int exit = 0;
    
        ssize_t input_length = getline(&input, &input_size, stdin);
        line_commands = str_filler(input, ";");
        for(int i = 0; i < line_commands.num_token; i++){
            command = str_filler(line_commands.command_list[i], " ");
            if(validate(command)){
                exit = 1;
                free_command_line(&command);
                break;
            }
            free_command_line(&command);
        }
        
        free(input);

        if (exit) {
            free_command_line(&line_commands);
            break;
        }

        free_command_line(&line_commands);
        
    }
}



void run_file_mode(char* filename){
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        write(2, "Error! Can't open input file! \n", 31);
        return;
    }

    int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0) {
        write(2, "Error! Can't open output file!\n", 31);
        fclose(input);
        return;
    }
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    command_line big_commands;
    command_line small_commands;

    dup2(output_fd, 2);
    dup2(output_fd, 1);
    while ((read = getline(&line, &len, input)) != -1) {
        big_commands = str_filler(line, ";");
        for(int i = 0; i < big_commands.num_token; i++){
            small_commands = str_filler(big_commands.command_list[i], " ");
            validate(small_commands);
            free_command_line(&small_commands);
            memset(&small_commands, 0, 0);
        }

        free_command_line(&big_commands);
        memset(&big_commands, 0, 0);
       
    }
    free(line);
    fclose(input);
    close(output_fd);

    write(2, "End of file\n", 12);
    write(2, "Have a nice day!\n", 17);
}




 


