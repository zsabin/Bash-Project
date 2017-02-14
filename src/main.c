#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

char * get_next_file_name(DIR *dir_p);
int get_file_names(char *dir_name, char **buffer);
char * read_user_input(char *buffer, int buffer_size);
void print_strings_with_prefix(char **strings, int strings_size, char *prefix);
int starts_with(char *str, char *prefix);
char * copy_string(char *src);
int is_file_name_to_ignore(char *file_name);

const int MAX_PATH_LENGTH = 4096; 
const int MAX_FILE_NAME_LENGTH = 256;
 
/* Reads the names of each of the files in a user-specified directory. Then 
 * reads file prefixes from the user and prints the list of names of the
 * files in the directory that begin with the given prefix. The program exits 
 * when the user enters an empty string. 
 */
int main() {   
    char dir_name[MAX_PATH_LENGTH];
    char file_prefix[MAX_FILE_NAME_LENGTH];
    
    /* TODO: Replace file_names with an array of linked lists or trie */
    const int file_names_size = 100;
    char *file_names[file_names_size];
    
    int i;

    printf("\nEnter a folder name: ");
    read_user_input(dir_name, MAX_PATH_LENGTH);
    for (i = 0; i < file_names_size; i++) {
        file_names[i] = NULL;
    }
        
    if (get_file_names(dir_name, file_names)){
        printf("Invalid Directory\n");
        return EXIT_SUCCESS;
    }
    
    printf("Enter the beginning of a filename:\n");
    while (read_user_input(file_prefix, MAX_FILE_NAME_LENGTH)) {
        printf("\nFiles starting with %s in %s\n", file_prefix, dir_name);
        print_strings_with_prefix(file_names, file_names_size, file_prefix);
        printf("Enter the beginning of a filename:\n");
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

/* TODO: Update function to ignore all file names that do not start with an
 * alphabetic character.
 */
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

/* Prints all of the strings in the specified array that begin with the given 
 * prefix.
 */
void print_strings_with_prefix(char **strings, int strings_size, char *prefix) {
    int i;
    for (i = 0; i < strings_size && strings[i]; i++) {
        if (starts_with(strings[i], prefix)) {
            printf("%s\n", strings[i]);
        }
    }
}
       
/* Returns a 1 if the specified string begins with the given prefix and a 0 
 * otherwise.
 */
int starts_with(char *str, char *prefix) {
    int i;
    for (i = 0; i < strlen(prefix); i++) {
        if (str[i] != prefix[i]) {
            return 0;
        }
    }
    return 1;
}
