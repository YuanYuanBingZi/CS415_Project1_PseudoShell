#include "command.h"
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

void listDir(){ /*for the ls command*/
    DIR *dir;
    struct dirent *dirent;
    
    dir = opendir(".");
    if(dir == NULL){
        write(2, "Error! Directory does not exist!\n", 33);
        return;}

    // Loop through directory entries and print their names
    while((dirent = readdir(dir)) != NULL){
         // Use the write to print the entry's name to the standard output
        write(1, dirent->d_name, strlen(dirent->d_name));
        write(1, " ", 1);
    }
    write(1, "\n", 1);
    closedir(dir);
}


void showCurrentDir(){ /*for the pwd command*/
    char path[1024];
    
    // Use the getcwd to retrieve the current directory path
    if(getcwd(path, sizeof(path)) != NULL){
        size_t len = strlen(path);
        write(1, path, len);
        write(1, "\n", 1);
     }else{
        // If getcwd fails, print an error message to the standard error
        write(2, "Error! Current Directory is Empty!\n", 35);
        return;
     }
}


void makeDir(char *dirName){/*for the mkdir command*/
    // Handle the case where dirName is NULL
    if(dirName == NULL){
        write(2, "Error! Unsupported parameters for command\n", 42);
        return;
    // Check if the directory already exists using the access
    }else if(access(dirName, F_OK) != -1){
        write(2, "Directory already exists!", 25);
        write(2, "\n", 1);
    // If the directory doesn't exist, create it using the mkdir
    }else{
        mkdir(dirName, 0777);// The permissions 0777 allow read, write, and execute permissions
    }
}

void changeDir(char *dirName){ /*for the cd command*/
    DIR *dir;
    struct dirent *dirent;
    
    // Handle cases where dirName is NULL or an empty string
    if(dirName == NULL || strlen(dirName) == 0){
        write(2, "Error! No Directory Name!\n", 26);
        return;
    }
    
    dir = opendir(".");
    int find = 0;

    while((dirent = readdir(dir)) != NULL){
        // Check if the provided dirName is '.', '..', or matches a directory entry
        if(strcmp(dirName, ".") == 0|| strcmp(dirName, "..") == 0 || strcmp(dirent->d_name, dirName) == 0){
            chdir(dirName);
            find = 1; // Indicate that the directory was found and changed to
            break;
        }
    }

    if(find == 0){
        write(2, "Error! No such Directory!\n", 26);}
    closedir(dir);

}


void copyFile(char *sourcePath, char *destinationPath){/*for the cp command*/
    int source_fd, dest_fd;
    char buffer[4096];
    ssize_t bytes_read, bytes_written;

    source_fd = open(sourcePath, O_RDONLY);
    if(source_fd == -1){
        write(2, "Error! Can't open the source file\n", 34);
        return;
    } 
    
    struct stat st;
    if (lstat(destinationPath, &st) == 0 && S_ISDIR(st.st_mode)) {
    // if the dest is dir, construct the filepath
    char dest_path[1024];
    strcpy(dest_path, destinationPath);
    if (dest_path[strlen(dest_path) - 1] != '/') {
        strcat(dest_path, "/");}
    strcat(dest_path, sourcePath);
    dest_fd = open(dest_path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    } else {
        //if the dest is file, open it
        dest_fd = open(destinationPath, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    }
    
    if (dest_fd == -1) {
        write(2, "Error! Can't open the dest file!\n", 33);
        close(source_fd);
        return;
    }

    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            write(2, "Error! Fail in Writing Process!\n", 32);
            close(source_fd);
            close(dest_fd);
            return;
        }
    }

    close(source_fd);
    close(dest_fd);

} 



void moveFile(char *sourcePath, char *destinationPath){/*for the mv command*/
   copyFile(sourcePath, destinationPath);
   deleteFile(sourcePath);
}



void deleteFile(char *filename) {/*for the rm command*/
    // Check if the file with the given filename exists
    if(access(filename, F_OK) == 0){
        // If the file exists, use the unlink to delete it
        unlink(filename);
    }else{
        // If the file doesn't exist, print an error message
        write(2, "Error! File does not exist!\n", 28);
    }
}



void displayFile(char *filename){/*for the cat command*/
    int fd;
    char buffer;
    ssize_t bytes_read;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        write(2, "Error! Can't open the file!\n", 28);
        return;
    }

    while ((bytes_read = read(fd, &buffer, 1)) > 0) {
        write(1, &buffer, 1);
    }
    write(1, "\n", 1);

    if (bytes_read == -1) {
        write(2, "Error! Can't read the file!\n", 28);
    }

    close(fd);
}





















