//create the structure and define all the functions

typedef struct Node {
    char value[256];
    struct Node *next;
} Node;

typedef struct List {
    struct Node *head;
} List;

void print_list(List *list);
void pushToEnd(List *list, char *value);
void pushToFront(List *list, char *value);
void removeFirst(List *list);
void removeLast(List *list);
void removeNode(List *list, int n);
void addElement(List *list, char *value);
List * create_list();