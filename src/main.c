#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

char * get_next_file_name(DIR *dir_p);
int get_file_names(char *dir_name, char **buffer);
char * copy_string(char *src);
int is_file_name_to_ignore(char *file_name);
 
/* Takes in the path of a directory as a command line argument and prints out 
 * the names of all of the files in that directory.
 * 
 * TODO: Update this so it reads directory paths from the user until the user
 * enters an empty string 
 */
int main(int argc, char **argv) {    
    const int buffer_size = 100;
    char* buffer[buffer_size];
    int i;

    for (i = 0; i < buffer_size; i++) {
        buffer[i] = NULL;
    }

    if (get_file_names(argv[1], buffer)){
        printf("Invalid Directory\n");
    }

    for (i = 0; i < buffer_size && buffer[i]; i++) {
        printf("%s\n", buffer[i]);
    }
    return EXIT_SUCCESS;
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
