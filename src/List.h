//create the structure and define all the functions

typedef struct Node {
	char value[26];
	struct Node *next;
} List;

void print_list(List *head);
void pushToEnd(List *head, char *value);
void pushToFront(List **head, char *value);
void removeFirst(List **head);
void removeLast(List *head);
void removeNode(List **head, int n);