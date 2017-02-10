# Bash-Project
This C program will produce auto-complete suggestions, similar to what Bash does when beginning to type a command and pressing &lt;tab>. The program will read all of the file names in a user-provided directory and store them in a data structure made up of a 26-element array of linked lists. There is a linked list for each letter of the alphabet, whereas within each one it will store the filenames which begin with that letter in some sensible order. After reading the filenames, the user will be asked to provide the beginning of a filename they are interested in. The output will be all filenames which match that prefix. The program will continue to ask for beginnings of filenames until an empty string is entered.