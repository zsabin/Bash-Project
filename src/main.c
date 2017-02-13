#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

char * get_next_file_name(DIR *dir_p);
int get_file_names(char *dir_name, char **buffer);
char * read_user_input(char *buffer, int buffer_size);
char * copy_string(char *src);
int is_file_name_to_ignore(char *file_name);

const int MAX_PATH_LENGTH = 4096; 
 
/* Reads the path to a directory from the user and prints out the list of files
 * in that directory until the user inputs an empty string.
 * 
 * TODO: After inserting a directory name the user should be prompted for part
 * of a file name and should be given a list of all the files in that directory
 * that begin with that prefix.
 */
int main() {   
    char input[MAX_PATH_LENGTH];
    const int results_size = 100;
    char *results[results_size];
    int i;

    printf("\nEnter a folder name: ");
    while (read_user_input(input, MAX_PATH_LENGTH)) {
        for (i = 0; i < results_size; i++) {
            results[i] = NULL;
        }

        if (get_file_names(input, results)){
            printf("Invalid Directory\n");
        }
        else {
            printf("Files in %s:\n", input);
            for (i = 0; i < results_size && results[i]; i++) {
                printf("%s\n", results[i]);
            }
        }
        printf("\nEnter a folder name: ");
    }
    return EXIT_SUCCESS;
}

/* Reads user input, strips the trailing new line character and stores the
 * result in the given buffer. Returns the resulting buffer as a convenience.
 */
char * read_user_input(char *buffer, int buffer_size) {
    fgets(buffer, buffer_size, stdin);
    return buffer = strtok(buffer, "\n");
}

/* Attempts to get the names of all of the files in the specified directory
 * and store them in the given buffer. Returns 0 if this function successfully 
 * accessed the directory or a positive integer representing the error.
 * 
 * TODO: convert buffer to an array of linked lists or a trie as specified in 
 * the assignment description.
 */
int get_file_names(char *dir_name, char **buffer) {
    DIR *dir_p;
    char *file_name;
    int i;

    errno = 0;
    dir_p = opendir(dir_name);
    if (errno) {
        return errno;
    }

    for(i = 0; file_name = get_next_file_name(dir_p);) {
        if (!is_file_name_to_ignore(file_name)) {
            buffer[i] = file_name;
            i++;
        }
    }
    closedir(dir_p);
    return 0;
}

int is_file_name_to_ignore(char *file_name) {
    return !strcmp(file_name, ".") || !strcmp(file_name, "..");
}

/* Returns a pointer to the string representing the name of the file pointed to 
 * by the specified directory stream and then moves the stream to point to the 
 * next file in the directory. Returns NULL if there are no more files in the 
 * directory.
 */
char * get_next_file_name(DIR *dir_p) {
    struct dirent *entity;
    if (entity = readdir(dir_p)) {
        return copy_string(entity->d_name);
    }
    return NULL;
}

/* Allocates sufficient memory to hold the specified string and copies the
 * string to this new memory location. Returns the pointer to this new memory
 * location.
 */
char * copy_string(char *src) {
    int str_size = strlen(src) + 1;
    char *dest = malloc(str_size);
    strcpy(dest, src);
    return dest;
}
